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

/* Port D */
#define 	GPIO_D_MODER 		((volatile unsigned int *) 	(0x40020C00))
#define 	GPIO_D_OTYPER 		((volatile unsigned short *)(0x40020C04))
#define 	GPIO_D_ODR_LOW 		((volatile unsigned char *) (0x40020C14)) 

/* Adress för Status och styrregister */
#define 	STK_CTRL 		((volatile unsigned int *)(0xE000E010))
/* Adress för räknarintervall */
#define 	STK_LOAD 		((volatile unsigned int *)(0xE000E014))
/* Adress för räknarvärde */
#define 	STK_VAL 		((volatile unsigned int *)(0xE000E018))

/* Blockerande förfröjning på 250 mikrosekunder */
void delay_250mys( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    *STK_LOAD = ( (168000/4) -1 );
    *STK_VAL = 0;
    *STK_CTRL = 5;  /* Sätter enable och clksource*/
    /* börjar räkna */
    while( (*STK_CTRL & 0x10000 )== 0 );    //vänta till countflag=1
    *STK_CTRL = 0;
}

void init_app( void )
{
	/* PORT D */
	*GPIO_D_MODER &= ~3;	/* Återställ bit 0 mode */
	*GPIO_D_MODER |= 0;		/* bit 0 sätts som utgång */
	*GPIO_D_OTYPER &= ~1;	/* återställ bit 0 typ, är nu push/pull*/
	
}

void main(void)
{
	int i;
	init_app();
	while(1)
	{
		*GPIO_D_ODR_LOW = 0;
		for(i = 0; i < 2000; i++)
			delay_250mys();
		*GPIO_D_ODR_LOW = 0xFF;
		for(i = 0; i < 2000; i++)
			delay_250mys();			
	}
}

