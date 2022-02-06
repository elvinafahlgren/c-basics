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
#define 	GPIO_D_ODR	 		((volatile unsigned short *) (PORT_D_BASE + 0x14))

/* Port E */
#define 	PORT_E_BASE			0x40020C00
#define 	GPIO_E_MODER 		((volatile unsigned int *) 	(PORT_E_BASE))
#define 	GPIO_E_PUPDR 		((volatile unsigned int *) 	(PORT_E_BASE + 0xC))
#define 	GPIO_E_IDR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x10))
/*______________________________________________________________________________*/

/* Port SYSCFG */
#define  	SYSCFG_BASE        	((volatile unsigned int *) (0x40013800))
#define  	SYSCFG_EXTICR1     	((volatile unsigned int *) (0x40013808))
#define  	SYSCFG_EXTICR2     	((volatile unsigned int *) (0x4001380C))
#define  	SYSCFG_EXTICR3     	((volatile unsigned int *) (0x40013810))
/* Port EXTI */
#define  	EXTI_IMR           	((volatile unsigned int *) (0x40013C00))
#define  	EXTI_RTSR          	((volatile unsigned int *) (0x40013C08))
#define  	EXTI_FTSR          	((volatile unsigned int *) (0x40013C0C))
#define  	EXTI_PR            	((volatile unsigned int *) (0x40013C14))
/* Port NVIC */
#define 	NVIC_ISER0       	((volatile unsigned int *) 0xE000E100)
/* Port till avbrottsvektorer */
#define 	EXTI2_IRQVEC     	((void (**) (void) ) 0x2001C060 ) 
#define 	EXTI1_IRQVEC     	((void (**) (void) ) 0x2001C05C )
#define 	EXTI0_IRQVEC     	((void (**) (void) ) 0x2001C058 )
/* irq nr */
#define 	NVIC_EXTI2_IRQ_BPOS     (1<<8)
#define 	NVIC_EXTI1_IRQ_BPOS     (1<<7)
#define 	NVIC_EXTI0_IRQ_BPOS     (1<<6)
/* nedan används när Generera avbrott hos respektive EXTI */
#define 	EXTI2_IRQ_BPOS          (1<<2)
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

static volatile char Clock1running, Clock2running, Clock3running;
static volatile short Clock1, Clock2, Clock3;


void portInit( void )
{
	*GPIO_D_MODER = 0x55555555;
	*GPIO_E_MODER = 0;
}

void systick_irq_handler( void )
{
	if( Clock1running )
		Clock1++;
	if( Clock2running )
		Clock2++;
	if( Clock3running )
		Clock3++;
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
			Clock1running = 1;
		}else{	/* Negative edge */
			Clock1running = 0;
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
		if( *GPIO_E_IDR_LOW & 2)
		{	/* Positive edge */
			Clock2running = 1;
		}else{	/* Negative edge */
			Clock2running = 0;
		}
	}
}

/* Avbrott både positiv och negativ flank */
void exti2_irq_handler ( void )
{
    /* Om avbrott från EXTI2: */
    if( *EXTI_PR & EXTI2_IRQ_BPOS )
    {
        /* kvittera avbrott från EXTI2 */
        * EXTI_PR |= EXTI2_IRQ_BPOS;
		if( *GPIO_E_IDR_LOW & 4)
		{	/* Positive edge */
			Clock3running = 1;
		}else{	/* Negative edge */
			Clock3running = 0;
		}
	}
}

/* initieringar av exti */
void extiInit(void)
{	
    /* koppla PE0 till EXTI0, PE1 till EXTI1, PE2 till EXTI2 */
    *SYSCFG_EXTICR1 |= 0x0444;

    /* Konfigurera EXTI0,1,2 för att generera avbrott */
    * EXTI_IMR |= (EXTI0_IRQ_BPOS | EXTI1_IRQ_BPOS | EXTI2_IRQ_BPOS);
	/* Konfigurera trigger selection bit för avbrottslinor */
    * EXTI_RTSR |= (EXTI2_IRQ_BPOS | EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);	/* enable trigger on falling edge */
	* EXTI_FTSR |= (EXTI2_IRQ_BPOS | EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);	/* enable trigger on rising edge */
	
	/* Sätt upp avbrottsvektorer */
    * EXTI0_IRQVEC = exti0_irq_handler;
	* EXTI1_IRQVEC = exti1_irq_handler;
	* EXTI2_IRQVEC = exti2_irq_handler;

    /* enable den bit i NVIC som kontrollerarar den avbrottslina som respektive EXTI kopplats till */
    * NVIC_ISER0 |= (NVIC_EXTI2_IRQ_BPOS | NVIC_EXTI1_IRQ_BPOS | NVIC_EXTI0_IRQ_BPOS);

}

void main(void)
{
	portInit();
	extiInit();
	systickInit();
	while( 1 )
	{
		switch( *GPIO_E_IDR_LOW >> 6 )
		{
			case 0: *GPIO_D_ODR = 0; break;
			case 1:
					if( *GPIO_E_IDR_LOW & (1<<3) )	/* RESET */
					{
						Clock1running = 0;
						Clock1 = 0;
					}
					*GPIO_D_ODR = Clock1; break;
			case 2:
					if( *GPIO_E_IDR_LOW & (1<<4) )	/* RESET */
					{
						Clock2running = 0;
						Clock2 = 0;
					}
					*GPIO_D_ODR = Clock2; break;
			case 3:
					if( *GPIO_E_IDR_LOW & (1<<5) )	/* RESET */
					{
						Clock3running = 0;
						Clock3 = 0;
					}
					*GPIO_D_ODR = Clock3; break;
		}
	}
}

