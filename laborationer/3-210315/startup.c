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
#define 	GPIO_D_ODR_LOW 		((volatile unsigned char *) (PORT_D_BASE + 0x14)) 
#define 	GPIO_D_ODR_HIGH 	((volatile unsigned char *) (PORT_D_BASE + 0x15))

/* Port E */
#define 	PORT_E_BASE			0x40021000
#define 	GPIO_E_MODER 		((volatile unsigned int *) 	(PORT_E_BASE))
#define 	GPIO_E_IDR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x10))
#define 	GPIO_E_ODR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x14)) 

/*IRQ FLIP FLOP*/
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

/* SYSTICK IRQ */
/* Adress för Status och styrregister */
#define 	STK_CTRL 		((volatile unsigned int *)(0xE000E010))
/* Adress för räknarintervall */
#define 	STK_LOAD 		((volatile unsigned int *)(0xE000E014))
/* Adress för räknarvärde */
#define 	STK_VAL 		((volatile unsigned int *)(0xE000E018))
/* Port till avbrottsvektor */
#define		SYSTICK_IRQVEC	((volatile unsigned int *)(0x2001C03C))


/* om tiden skall fortsätta */
static volatile unsigned char time_active;
/* Variabel som håller den aktuella tiden som räknas i 10 millisekunder */
static volatile unsigned int time_in_10ms;
void systick_irq_handler( void );

/* 10 millisekunder motsvarar en hundradels sekund,
 * därför har vi en delay på 10 millisekunder */
void start_time_10ms_period( void )
{
	/* SystemCoreClock = 100000000 */
	*SYSTICK_IRQVEC = systick_irq_handler;
	*STK_CTRL = 0;
//    *STK_LOAD = ( (1000000 - 1 );	/* 10 ms */
	*STK_LOAD = ( (100 - 1 ));	/* Simulator value */
	*STK_VAL = 0;
	*STK_CTRL = 7;
}

void systick_irq_handler( void )
{
	/* Räkna så länge tidtagaruret är aktivt */
    if( time_active ){
		time_in_10ms++;
		start_time_period();
	}
}

/* Icke-blockerande fördröjningsrutin */
void start_time(void)
{
	time = 0;
	time_active = 1;
	start_time_10ms_period();
}


/* Avbrott både positiv och negativ flank 
 * Hanterar avbrott från EXTI0 */
void exti0_irq_handler ( void )
{
    /* Om avbrott från EXTI0: */
    if( *EXTI_PR & EXTI0_IRQ_BPOS )
    {
        /* kvittera avbrott från EXTI0 */
        * EXTI_PR |= EXTI0_IRQ_BPOS;
		if( *GPIO_E_IDR_LOW & 1 )	/* Positiv flank */
		{	
			time_in_10ms = 0;		/* Nollställ tid */
			start_time(void);		/* Starta tiden */
		}else						/* Negativ flank */
		{
			time_active = 0;		/* Sluta ta tid */
			time_in_10ms = 0;		/* Nollställ tid */
		}
	}
}

void exti1_irq_handler ( void )
{
    /* Om avbrott från EXTI1: */
    if( *EXTI_PR & EXTI1_IRQ_BPOS )
    {
        time_active = 0;			/* Sluta ta tid */
		time_in_10ms = 0;			/* Nollställ tid */
	}
}


/* initieringar */
void init_app(void)
{
	* GPIO_D_MODER = 0x55555555; 	/* b15-b0 är utgångar */
	* GPIO_E_MODER &= 0xFFFE0000;	/* nollställ de bitar som skall användas */
	* GPIO_E_MODER |= 0x000150000;	/* b7,b6,b5 är utgångar, b4-b0 är ingångar */
	
    /* koppla PE till EXTI1 och EXTI0*/
    *SYSCFG_EXTICR1 |= 0x0044;

    /* Konfigurera EXTI1 och EXTI0 för att generera avbrott */
    * EXTI_IMR |= ( EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS );
    * EXTI_RTSR |= EXTI0_IRQ_BPOS;		/* enable trigger på positiv flank (när klockan strtar) */
	* EXTI_FTSR |= EXTI0_IRQ_BPOS;		/* enable trigger på negativ flank (när klockan stannar)*/
	* EXTI_RTSR |= EXTI1_IRQ_BPOS;		/* enable trigger på positiv flank (när klockan nollställs) */
	* EXTI_FTSR &= ~EXTI1_IRQ_BPOS;		/* disable trigger på negativ flank (när klockan stannar)*/
	/* Sätt upp avbrottsvektor */
    * EXTI1_IRQVEC = exti0_irq_handler;
	* EXTI1_IRQVEC = exti1_irq_handler;
    /* konfig den bit i NVIC som kontrollerarar den avbrottslina som EXTI0 och EXTI1 kopplats till */
    * NVIC_ISER0 |= (NVIC_EXTI1_IRQ_BPOS | NVIC_EXTI0_IRQ_BPOS);

}

void main(void)
{
	init_app();
	while(1)
	{
		/* EJ KLAR */
	}
}

