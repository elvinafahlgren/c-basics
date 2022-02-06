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

#define GPIO_E_BASE 	0x40021000
#define GPIO_E_MODER 	((volatile unsigned int *) (GPIO_E_BASE))
#define GPIO_E_OTYPER 	((volatile unsigned short *) (GPIO_E_BASE + 0x4))
#define GPIO_E_OSPEEDR 	((volatile unsigned int *) (GPIO_E_BASE + 0x8))
#define GPIO_E_PUPDR 	((volatile unsigned int *) (GPIO_E_BASE + 0xC))
#define GPIO_E_IDR_LOW 	((volatile unsigned char *) (GPIO_E_BASE + 0x10))
#define GPIO_E_ODR_LOW 	((volatile unsigned char *) (GPIO_E_BASE + 0x14))

#define GPIO_D_IDR_LOW 	((volatile unsigned char *) 0x40020C10) // port D
#define GPIO_D_MODER 	((volatile unsigned long *) 0x40020C00)	// port D

#define STK_CTRL 		((volatile unsigned int *)(0xE000E010))
#define STK_LOAD 		((volatile unsigned int *)(0xE000E014))
#define STK_VAL 		((volatile unsigned int *)(0xE000E018))

#define setbit(x)		(*GPIO_E_ODR_LOW |= (1<<x))
#define clearbit(x)		(*GPIO_E_ODR_LOW &= ~(1<<x))

void delay_100_micro( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    *STK_LOAD = ( 16800 - 1 ); /* 100 us */
    *STK_VAL = 0;
    *STK_CTRL = 5;  //sätter enable och clksource
    // börjar räkna
    while( (*STK_CTRL & 0x10000 ) == 0 );    //vänta till countflag=1
    *STK_CTRL = 0;
}


void delay_ms(unsigned int ms)
{
	/* Number of 100 usecs delays
	 * are obtained from:
	 * (ms * 10), assuming ms  > 0
	*/
	unsigned int delay = ms*10;
    while(delay)
    {
        delay_100_micro();
        delay--;
    }
}

void delay_shortpulse(unsigned int w)
{
	/* Number of 100 usecs delays
	 * are obtained from:
	 * (w * 10), assuming w  > 0
	*/
	unsigned int delay = (w*10)-2;
    while( delay > 0 )
    {
		delay_100_micro();
        delay--;
    }
}


void init_app(void)
{
	* GPIO_E_MODER &= 0xFFFFFF00;
	* GPIO_E_MODER |= 0x00000050;
    * GPIO_E_PUPDR &= 0xFFFFFF00;
	* GPIO_E_PUPDR |= 0x00000055;	//pull-up eller pull-dowm
	* GPIO_E_OTYPER &= 0xFFFFFFF3;	//push/pull
	
	* GPIO_D_MODER &= 0xFFFFFF00;
	* GPIO_D_MODER |= 0x00000050;
	
	setbit(3);
	clearbit(2);
}

void main(void)
{
	unsigned int w,p;
    init_app();
    while(1){
		
		switch( *GPIO_D_IDR_LOW & 3 ){
			case 0: w = 2; p = 10; break;
			case 1: w = 4; p = 10; break;
			case 2: w = 20; p = 100; break;
			default: w = 40; p = 200; break;
		}
		
		setbit(2);		//b2=high
		delay_100_micro();
		clearbit(3);	//b3=low
		delay_shortpulse( w );
		setbit(3);
		delay_100_micro();
		clearbit(2);
		delay_ms( p - w );
    }
}



