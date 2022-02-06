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

/* Port E */
#define 	PORT_E_BASE			0x40020C00
#define 	GPIO_E_MODER 		((volatile unsigned int *) 	(PORT_E_BASE))
#define 	GPIO_E_OTYPER 		((volatile unsigned short *)(PORT_E_BASE + 0x4))
#define 	GPIO_E_PUPDR 		((volatile unsigned int *) 	(PORT_E_BASE + 0xC))
#define 	GPIO_E_IDR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x10))
#define 	GPIO_E_IDR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x11))
#define 	GPIO_E_ODR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x15))

/* Adress för Status och styrregister */
#define 	STK_CTRL 		((volatile unsigned int *)(0xE000E010))
/* Adress för räknarintervall */
#define 	STK_LOAD 		((volatile unsigned int *)(0xE000E014))
/* Adress för räknarvärde */
#define 	STK_VAL 		((volatile unsigned int *)(0xE000E018))


/* Blockerande förfröjning på 10 millisekunder */
void delay_10ms( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
	*STK_LOAD = ( (1680000 - 1 );	/* 10 ms */
    *STK_VAL = 0;
    *STK_CTRL = 5;  /* Sätter enable och clksource*/
    /* börjar räkna */
    while( (*STK_CTRL & 0x10000 )== 0 );    /* Vänta till countflag = 1 */
    *STK_CTRL = 0;
}

/* returnerar tangenternas tillstånd */
unsigned get_kbd_stat( void )
{
	unsigned char row1, row2;
	*GPIO_E_ODR_LOW = 0x10;
	row1 = (*GPIO_E_IDR_LOW << 4);
	*GPIO_E_ODR_LOW = 0x20
	row2 = *GPIO_E_IDR_LOW;
	return ( row1 | row2 );
}

void disp_kbd( void )
{
	unsigned char c;
	int i;
	while( 1 )
	{
		c = get_kbd_stat();
		delay_10ms();
		if( c == get_kbd_stat() )
		{
			switch( c )
			{
				case 0;		*GPIO_E_ODR_HIGH = 0xFF; break;
				case 1;		*GPIO_E_ODR_HIGH = 0x07; break;
				case 2;		*GPIO_E_ODR_HIGH = 0x06; break;
				case 4;		*GPIO_E_ODR_HIGH = 0x05; break;
				case 8;		*GPIO_E_ODR_HIGH = 0x04; break;
				case 0x10;	*GPIO_E_ODR_HIGH = 0x03; break;
				case 0x20;	*GPIO_E_ODR_HIGH = 0x02; break;
				case 0x40;	*GPIO_E_ODR_HIGH = 0x01; break;
				case 0x80;	*GPIO_E_ODR_HIGH = 0x00; break;
				default:
					/* flera tangenter nedtryckta */
					i = 0;
					while( c )
					{
						if ( c & 1 )
							i++;
						c >>= 1;
					}
					*GPIO_E_ODR_HIGH = (unsigned char) (i << 4);
			}
		}
	}
}

void init_app( void )
{
	*GPIO_E_MODER = 0x55550500;	/* bit 8-15, 5,4 sätts som utgångar, övriga som ingångar */
	*GPIO_E_PUPDR = 0x000000AA;	/* bit 3,2,1,0 pull-down */
	*GPIO_E_OTYPER = 0;			/* utgångar, push-pull */
}

void main(void)
{
}

