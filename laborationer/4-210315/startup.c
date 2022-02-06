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

/* Adress till System Control Block registret */
#define 	SCB_VTOR			0xE000ED00
/* Port till avbrottsvektorer */
#define 	ML_ATMO_IRQVEC  	((void (**) (void) ) (SCB_VTOR + 0x134) )
#define 	ML_PANIC_IRQVEC     ((void (**) (void) ) (SCB_VTOR + 0x138) )

/* irq nr */
#define 	NVIC_ML_ATMO_IRQ_BPOS 		(1<<29)		/* 61/32 = 1, 61-32 = 29 */
#define 	NVIC_ML_PANIC_IRQ_BPOS     	(1<<28)		/* 61/32 = 1, 62-32 = 28 */


/* a) struct som representerar marslandarmodulens register */
typedef struct MarsLanderModule{
	/* control registret består av endast 3 bitar, 
	 * vi har endast char, short och int, därför 
	 * låter jag kontrollregistret ha char (4 bitar) */
	volatile unsigned char ML_CTRL;		/* control register */
	volatile char reserved1;
	volatile short reserved2;
	volatile unsigned int ML_STATE;		/* state register */
	volatile unsigned short ML_LS;		/* life support register*/
	volatile unsigned short ML_ORI;		/* orientation register */
	volatile unsigned char ML_IRQ;		/* interrupt request register*/
} MARS_LANDER_MODULE, *PMARS_LANDER_MODULE;
/* Definiera marslandaren på den givna adressen */
#define MarsLander	(PMARS_LANDER_MODULE 0xE000E0F0);

/* ML_CTRL */
#define		STAB	0 	/* När en etta skrivs aktiveras stabiliserings raketer kort, vilket rättställer landarens vinkel */
#define 	BRAKE	2	/* När en etta skrivs aktiveras bromsraketerna kort, och landarens hastighet minskar. */
#define		PANIC	4	/* När en etta skrivs aktiveras nödprotokollet och landaren försöker ta sig tillbaks till moderskeppet.*/

/* ML_IRQ */
#define 	ATMO	0	/* Sätts till 1 när landaren är tillräckligt nära marken för att påbörja ”landing” state */
#define		PANIC	2	/* Sätts till 1 när landaren fått för hög vinkel mot marken eller för hög hastighet.*/

void irq_handler ( void )
{
	/* EJ KLAR */
}

void init_app(void)
{
	/* EJ KLAR */
    /* Osäker här
    *SYSCFG_EXTICR1 |= 0x0044;
	 */

    /* Konfigurera AMO och PANIC för att generera avbrott */
    * EXTI_IMR |= ( (1 << AMO) | (1 << PANIC) );
    * EXTI_RTSR |= ( (1 << AMO) | (1 << PANIC) );
	* EXTI_FTSR &= ~( (1 << AMO) | (1 << PANIC) );

    * ML_ATMO_IRQVEC = atmo_irq_handler;
	* ML_PANIC_IRQVEC = panic_irq_handler;

    /* konfig den bit i NVIC som kontrollerarar den avbrottslina som PANIC och ATMO kopplats till */
    * NVIC_ISER0 |= (NVIC_ML_PANIC_IRQ_BPOS | NVIC_ML_ATMO_IRQ_BPOS );

}

void main(void)
{
	/* EJ KLAR */
    init_app();	
}



