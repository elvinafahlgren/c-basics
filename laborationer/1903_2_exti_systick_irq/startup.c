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
#define 	PORT_D_BASE			0x40020C00
#define 	GPIO_D_MODER 		((volatile unsigned int *) 	(PORT_D_BASE))
#define 	GPIO_D_OTYPER 		((volatile unsigned short *)(PORT_D_BASE + 0x4))
#define 	GPIO_D_ODR_LOW 		((volatile unsigned char *) (PORT_D_BASE + 0x14))

/* Port E */
#define 	PORT_E_BASE			0x40020C00
#define 	GPIO_E_MODER 		((volatile unsigned int *) 	(PORT_E_BASE))
#define 	GPIO_E_PUPDR 		((volatile unsigned int *) 	(PORT_E_BASE + 0xC))
#define 	GPIO_E_IDR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x10))
/*______________________________________________________________________________*/

/* Port SYSCFG */
#define  	SYSCFG_BASE        	((volatile unsigned int *) (0x40013800))
#define  	SYSCFG_EXTICR1     	((volatile unsigned int *) (0x40013808))
/* Port EXTI */
#define  	EXTI_IMR           	((volatile unsigned int *) (0x40013C00))
#define  	EXTI_RTSR          	((volatile unsigned int *) (0x40013C08))
#define  	EXTI_FTSR          	((volatile unsigned int *) (0x40013C0C))
#define  	EXTI_PR            	((volatile unsigned int *) (0x40013C14))
/* Port NVIC */
#define 	NVIC_ISER0       	((volatile unsigned int *) 0xE000E100)
/* Port till avbrottsvektorer */
#define 	EXTI1_IRQVEC     	((void (**) (void) ) 0x2001C05C )
#define 	EXTI0_IRQVEC     	((void (**) (void) ) 0x2001C058 )
/* irq nr */
#define 	NVIC_EXTI1_IRQ_BPOS     (1<<7)
#define 	NVIC_EXTI0_IRQ_BPOS     (1<<6)
/* nedan används när Generera avbrott hos respektive EXTI */
#define 	EXTI1_IRQ_BPOS          (1<<1)
#define 	EXTI0_IRQ_BPOS          (1<<0)
/*______________________________________________________________________________*/

/* Adress för Status och styrregister */
#define 	STK_CTRL 		((volatile unsigned int *)(0xE000E010))
/* Adress för räknarintervall */
#define 	STK_LOAD 		((volatile unsigned int *)(0xE000E014))
/* Adress för räknarvärde */
#define 	STK_VAL 		((volatile unsigned int *)(0xE000E018))
/* Port till avbrottsvektor */
#define		SYSTICK_IRQVEC	((volatile unsigned int *)(0x2001C03C))

static volatile unsigned char Pulse0measure, Pulse1measure;
static volatile unsigned int Pulse0time, Pulse1time;


void portInit( void )
{
	*GPIO_D_MODER = 0;
	*GPIO_D_OTYPER = 0x00005555;
	*GPIO_E_MODER = 0;
	*GPIO_E_PUPDR = 0x00000000;
}

void systick_irq_handler( void )
{
	if( Pulse0measure )
		Pulse0time++;
	if( Pulse1measure )
		Pulse1time++;
}

void systickInit( void )
{
	/* SystemCoreClock = 16000000 */
	*SYSTICK_IRQVEC = systick_irq_handler;
	
	*STK_CTRL = 0;
	*STK_LOAD = ( 1680000 - 1 );	/* 10 ms*/
	*STK_VAL = 0;
	*STK_CTRL = 7;
}

/* Avbrott både positiv och negativ flank */
void exti0_irq_handler ( void )
{
    /* Om avbrott från EXTI0: */
    if( *EXTI_PR & EXTI0_IRQ_BPOS )
    {
        /* kvittera avbrott från EXTI0 */
        * EXTI_PR |= EXTI0_IRQ_BPOS;
		if( *GPIO_E_IDR_LOW & 1)
		{	/* Positive edge */
			Pulse0measure = 1;
			Pulse0time = 0;
		}else{	/* Negative edge */
			Pulse0measure = 0;
		}
	}
}

/* Avbrott både positiv och negativ flank */
void exti1_irq_handler ( void )
{
    /* Om avbrott från EXTI1: */
    if( *EXTI_PR & EXTI1_IRQ_BPOS )
    {
        /* kvittera avbrott från EXTI1 */
        * EXTI_PR |= EXTI1_IRQ_BPOS;
		if( *GPIO_E_IDR_LOW & 2 )
		{	/* Positive edge */
			Pulse1measure = 1;
			Pulse1time = 0;
		}else{	/* Negative edge */
			Pulse1measure = 0;
		}
	}
}

/* initieringar av exti */
void extiInit(void)
{	
    /* koppla PE0 till EXTI0, PE1 till EXTI1 */
    *SYSCFG_EXTICR1 |= 0x0044;

    /* Konfigurera EXTI2,1,0 för att generera avbrott */
    * EXTI_IMR |= (EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);
	/* Konfigurera trigger selection bit för avbrottslinor */
    * EXTI_RTSR |= (EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);	/* enable trigger on falling edge */
	* EXTI_FTSR |= (EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);	/* enable trigger on rising edge */
	
	/* Sätt upp avbrottsvektorer */
    * EXTI0_IRQVEC = exti0_irq_handler;
	* EXTI1_IRQVEC = exti1_irq_handler;

    /* enable den bit i NVIC som kontrollerarar den avbrottslina som respektive EXTI kopplats till */
    * NVIC_ISER0 |= (NVIC_EXTI1_IRQ_BPOS | NVIC_EXTI0_IRQ_BPOS);

}

/* skriver ut siffra i sju-segmentskod */
void out7seg( unsigned char c ){
    static unsigned char segCode[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    if ( c > 15 ) {
        * GPIO_D_ODR_LOW = 0;
        return;
    }
    * GPIO_D_ODR_LOW = segCode[c];
}

void main(void)
{
	char c;
	Pulse0measure = 0;
	Pulse1measure = 0;
	Pulse0time = 0;
	Pulse1time = 0;
	portInit();
	extiInit();
	systickInit();
	while( 1 )
	{
		if( *GPIO_E_IDR_LOW & 0x80 )
		{	/* Show signal source 2*/
			if( Pulse1measure )
				c = 16;		/* Turn off... */
			else
			{
				if( Pulse1time > 9 )
					c = 0xE;
				else
					c = Pulse1time;
			}
		}else{	/* Show signal source 1 */
			if( Pulse0measure )
				c = 16;		/* Turn off... */
			else
			{
				if( Pulse0time > 9 )
					c = 0xE;
				else
					c = Pulse0time;
			}
		}
		out7seg( c );
	}
}


