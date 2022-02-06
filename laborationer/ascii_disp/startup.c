/*
 * 	startup.c
 *
 */
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}
/* Adress för Status och styrregister */
#define 	STK_CTRL 		((volatile unsigned int *)(0xE000E010))
/* Adress för räknarintervall */
#define 	STK_LOAD 		((volatile unsigned int *)(0xE000E014))
/* Adress för räknarvärde */
#define 	STK_VAL 		((volatile unsigned int *)(0xE000E018))

#define SIMULATOR 

/* Port E */
#define 	PORT_E_BASE			0x40021000
#define 	GPIO_E_MODER 		((volatile unsigned int *) 	(PORT_E_BASE))
#define 	GPIO_E_OTYPER 		((volatile unsigned short *)(PORT_E_BASE + 0x4))
#define 	GPIO_E_OSPEEDR 		((volatile unsigned int *)	(PORT_E_BASE + 0x8))
#define 	GPIO_E_PUPDR 		((volatile unsigned int *) 	(PORT_E_BASE + 0xC))
#define 	GPIO_E_IDR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x10))
#define 	GPIO_E_IDR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x11))
#define 	GPIO_E_ODR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x14)) 
#define 	GPIO_E_ODR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x15))

/* Definiera styrregister, detta är konstanter, bitmasker, inte adresser! */
#define B_E 		0x40	/* Enable-signal */
#define B_SELECT	4		/* Select ASCII-display */
#define B_RW 		2 		/* 0=Write, 1=Read */
#define B_RS 		1 		/* 0=Control, 1=Data */


/* Adressera ASCII-dispay och ettställ de bitar som är 1 i x */
void ascii_ctrl_bit_set( unsigned char x ) 
{
	char c;
	c = *GPIO_E_ODR_LOW;	// c tilldelas det värde som GPIO_E_ODR_LOW pekar på
	*GPIO_E_ODR_LOW = B_SELECT | x | c;	// 0100 | 0001 | 0010 = 0111 ??? vad händer???
}

/* Adressera ASCII-display och nollställ de bitar som är 1 i x */
void ascii_ctrl_bit_clear( unsigned char x )
{
	char c;
	c = *GPIO_E_ODR_LOW;
	c = c & ~x;
	*GPIO_E_ODR_LOW = B_SELECT | c;
}

void ascii_write_controller( unsigned char c )
{
	ascii_ctrl_bit_set( B_E ); 		// E=1
	*GPIO_E_ODR_HIGH = c;
	ascii_ctrl_bit_clear( B_E );	// E=0
	delay_250ns();
}

char ascii_read_controller( void )
{
	char c;
	ascii_ctrl_bit_set( B_E );			// E=1
	delay_250ns();
	delay_250ns();
	c = *GPIO_E_IDR_HIGH;				// läs från inport
	ascii_ctrl_bit_clear( B_E );		// E=0
	return c;
}

char ascii_read_status( void )
{
	char c;
	*GPIO_E_MODER = 0x00005555;
	ascii_ctrl_bit_set( B_RW );		// RW = 1
	ascii_ctrl_bit_clear( B_RS );	// RS = 0
	c = ascii_read_controller();
	*GPIO_E_MODER = 0x55555555;
	return c;
}

char ascii_read_data( void )
{
	char c;
	*GPIO_E_MODER = 0x00005555;
	ascii_ctrl_bit_set( B_RW );		// RW = 1
	ascii_ctrl_bit_set( B_RS );		// RS = 1
	c = ascii_read_controller();
	*GPIO_E_MODER = 0x55555555;
	return c;
}

void ascii_write_cmd( unsigned char command )
{
	ascii_ctrl_bit_clear( B_RS );
	ascii_ctrl_bit_clear( B_RW );
	ascii_write_controller( command );
}

void ascii_write_data( unsigned char data )
{
	ascii_ctrl_bit_set( B_RS );
	ascii_ctrl_bit_clear( B_RW );
	ascii_write_controller( data );
}

void delay_250ns( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    *STK_LOAD = ( (168/4) -1 );
    *STK_VAL = 0;
    *STK_CTRL = 5;  //sätter enable och clksource
    // börjar räkna
    while( (*STK_CTRL & 0x10000 )== 0 );    //vänta till countflag=1
    *STK_CTRL = 0;
}

void delay_micro(unsigned int us)
{
/* Simulator value */
#ifdef SIMULATOR
    us = us / 1000;
    us++;
#endif
    while( us > 0 )
    {
        delay_250ns();
        delay_250ns();
        delay_250ns();
        delay_250ns();
        us--;
    }
}

void delay_milli(unsigned int ms)
{
#ifdef  SIMULATOR
    ms = ms / 1000;
    ms++;
#endif
    while(ms > 0)
    {
        delay_micro(1000);
        ms--;
    }
}

void ascii_gotoxy( int x, int y)
{
	char adress = x - 1;
	if( y == 2)
		adress += 0x40;
	ascii_write_cmd( 0x80 | adress );		 
}

void ascii_write_char( unsigned char c )
{
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_data( c );
	delay_micro( 43 );
}

void init_app(void)
{
    *GPIO_E_MODER = 0x55555555;  // GPIO_MODER initieras
    *GPIO_E_ODR_LOW = 0x0;	// initierar utgången 
}

void ascii_init( void )
{
	// Function set RS RW 0 0 1 1 N F X X		(N=0 -> 1rad, N=1 -> 2 rader) (F=0 -> 5x8 punkter, F=1 -> 5x11 punkter)
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_cmd( 0x38 );
	delay_micro( 39 );
	
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_cmd( 0xE ); /*00001110*/
	delay_micro( 39 );
	
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_cmd( 1 );
	delay_milli( 2 );
	
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_cmd( 0x6 );
	delay_micro( 39 );
}

int main( int argc, char **argv)
{
	char *s ;
	char test1[] = "Alfanumerisk ";
	char test2[] = "Display - test";
	
	init_app();
	ascii_init();
	ascii_gotoxy(1,1);
	s = test1;
	while( *s )
		ascii_write_char( *s++ );
	ascii_gotoxy(1,2);
	s = test2;
	while( *s )
		ascii_write_char( *s++ );
	return 0;	
	
}

