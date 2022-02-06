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
#define 	GPIO_E_OSPEEDR 		((volatile unsigned int *)	(PORT_E_BASE + 0x8))
#define 	GPIO_E_PUPDR 		((volatile unsigned int *) 	(PORT_E_BASE + 0xC))
#define 	GPIO_E_IDR	 		((volatile unsigned short *) (PORT_E_BASE + 0x10))
#define 	GPIO_E_ODR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x14)) 
#define 	GPIO_E_ODR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x15))
/*________________________________________________________________________________*/

/* Port SYSCFG */
#define  	SYSCFG_BASE        	((volatile unsigned int *) (0x40013800))
#define  	SYSCFG_EXTICR2     	((volatile unsigned int *) (0x4001380C))
/* Port EXTI */
#define  	EXTI_IMR           	((volatile unsigned int *) (0x40013C00))
#define  	EXTI_RTSR          	((volatile unsigned int *) (0x40013C08))
#define  	EXTI_FTSR          	((volatile unsigned int *) (0x40013C0C))
#define  	EXTI_PR            	((volatile unsigned int *) (0x40013C14))
/* Port NVIC */
#define 	NVIC_ISER0       	((volatile unsigned int *) 0xE000E100)
/* Port till avbrottsvektorer */
#define 	EXTI9_5_IRQVEC  	((void (**) (void) ) 0x2001C09C )		/* EXTI[9:5] */
/* irq nr */
#define 	NVIC_EXTI5_9_IRQ_BPOS   (1<<23)		/* EXTI[9:5] */
/* nedan används när Generera avbrott hos EXTI7 */
#define 	EXTI7_IRQ_BPOS          (1<<7)
/*________________________________________________________________________________*/

/* Adress för Status och styrregister */
#define 	STK_CTRL 		((volatile unsigned int *)(0xE000E010))
/* Adress för räknarintervall */
#define 	STK_LOAD 		((volatile unsigned int *)(0xE000E014))
/* Adress för räknarvärde */
#define 	STK_VAL 		((volatile unsigned int *)(0xE000E018))


static unsigned int visitors;

void delay10sec( void )
{
	/* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
	*STK_LOAD = ( (16800000 - 1 ));	/* Simulator value */
    *STK_VAL = 0;
    *STK_CTRL = 5;  /* Sätter enable och clksource*/
    /* börjar räkna */
    while( (*STK_CTRL & 0x10000 )== 0 );    /* Vänta till countflag = 1 */
    *STK_CTRL = 0;	
}

void sensor_irq( void )
{
    if( *GPIO_E_IDR & 1 )
    {	/* inpassering */
        visitors++;
		*GPIO_E_ODR_LOW |= (1<<2);
	}
	if( *GPIO_E_IDR & 2 )
    {	/* utpassering */
        visitors--;
		*GPIO_E_ODR_LOW |= (1<<3);
	}
	*GPIO_E_ODR_LOW |= (1<<6);
	/* kvittera avbrott från EXTI7 */
	* EXTI_PR |= EXTI7_IRQ_BPOS;
}


void init_app( void )
{
	*GPIO_E_MODER = 0x55551150;
	*GPIO_E_OTYPER = 0; 		/* andvänd push/pull */
	*GPIO_E_PUPDR = 0x0000800A;	/* Flytande, aktivt höga -> "pull-down" */
}


void init_irq( void )
{
	/* koppla PE7 till EXTI7 */
    *SYSCFG_EXTICR1 |= 0x4000;

    /* Konfigurera EXTI2,1,0 för att generera avbrott */
    * EXTI_IMR |= EXTI7_IRQ_BPOS;
	/* Konfigurera trigger selection bit för avbrottslinor */
    * EXTI_RTSR |= EXTI7_IRQ_BPOS;		/* enable trigger on falling edge */
	* EXTI_FTSR &= ~EXTI7_IRQ_BPOS;		/* disable trigger on rising edge */
	
	/* Sätt upp avbrottsvektorer */
    * EXTI9_5_IRQVEC = sensor_irq;

    /* enable den bit i NVIC som kontrollerarar den avbrottslina som respektive EXTI kopplats till */
    * NVIC_ISER0 |= NVIC_EXTI5_9_IRQ_BPOS;
}


void main(void)
{
	visitors = 0;
	init_app();
	init_irq();
	while( 1 )
	{
		*GPIO_E_ODR_HIGH = (unsigned char) visitors;
		delay10sec();
	}
}

