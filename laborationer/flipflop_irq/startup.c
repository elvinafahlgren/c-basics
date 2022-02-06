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
#define  	SYSCFG_EXTICR2     	((volatile unsigned int *) (0x4001380C))
#define  	SYSCFG_EXTICR3     	((volatile unsigned int *) (0x40013810))

/* Port EXTI */
#define  	EXTI_IMR           	((volatile unsigned int *) (0x40013C00))
#define  	EXTI_RTSR          	((volatile unsigned int *) (0x40013C08))
#define  	EXTI_FTSR          	((volatile unsigned int *) (0x40013C0C))
#define  	EXTI_PR            	((volatile unsigned int *) (0x40013C14))

/* Port NVIC */
#define 	NVIC_ISER0       	((volatile unsigned int *) 0xE000E100)
#define 	NVIC_ISER1       	((volatile unsigned int *) 0xE000E104)

/* Port till avbrottsvektorer */
#define 	EXTI9_5_IRQVEC  	((void (**) (void) ) 0x2001C09C )		/* EXTI[9:5] */
#define 	EXTI3_IRQVEC     	((void (**) (void) ) 0x2001C064 )
#define 	EXTI2_IRQVEC     	((void (**) (void) ) 0x2001C060 ) 
#define 	EXTI1_IRQVEC     	((void (**) (void) ) 0x2001C05C )
#define 	EXTI0_IRQVEC     	((void (**) (void) ) 0x2001C058 )

/* irq nr */
#define 	NVIC_EXTI5_9_IRQ_BPOS   (1<<23)		/* EXTI[9:5] */
#define 	NVIC_EXTI3_IRQ_BPOS     (1<<9)
#define 	NVIC_EXTI2_IRQ_BPOS     (1<<8)
#define 	NVIC_EXTI1_IRQ_BPOS     (1<<7)
#define 	NVIC_EXTI0_IRQ_BPOS     (1<<6)

/* nedan används när Generera avbrott hos respektive EXTI */
#define 	EXTI8_IRQ_BPOS          (1<<8)
#define 	EXTI7_IRQ_BPOS          (1<<7)
#define 	EXTI6_IRQ_BPOS          (1<<6)
#define 	EXTI5_IRQ_BPOS          (1<<5)
#define 	EXTI4_IRQ_BPOS          (1<<4)
#define 	EXTI3_IRQ_BPOS          (1<<3)
#define 	EXTI2_IRQ_BPOS          (1<<2)
#define 	EXTI1_IRQ_BPOS          (1<<1)
#define 	EXTI0_IRQ_BPOS          (1<<0)




static volatile int count;

void irq_handler ( void );


/* initieringar av exti */
void init_exti(void)
{	
    /* koppla PE0 till EXTI0, PE1 till EXTI1 och PE2 till EXTI2*/
    *SYSCFG_EXTICR1 |= 0x0444;

    /* Konfigurera EXTI2,1,0 för att generera avbrott */
    * EXTI_IMR |= (EXTI2_IRQ_BPOS | EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);
	/* Konfigurera trigger selection bit för avbrottslinor */
    * EXTI_RTSR |= (EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);	/* enable trigger on falling edge */
	* EXTI_FTSR &= ~(EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);	/* disable trigger on rising edge */
	* EXTI_FTSR |= EXTI2_IRQ_BPOS;		/* enable trigger on rising edge */
	* EXTI_RTSR &= ~EXTI2_IRQ_BPOS;		/* disable trigger on falling edge */
	
	/* Sätt upp avbrottsvektorer */
    * EXTI0_IRQVEC = irq_handler;
	* EXTI1_IRQVEC = irq_handler;
	* EXTI2_IRQVEC = irq_handler;

    /* enable den bit i NVIC som kontrollerarar den avbrottslina som respektive EXTI kopplats till */
    * NVIC_ISER0 |= (NVIC_EXTI0_IRQ_BPOS | NVIC_EXTI1_IRQ_BPOS | NVIC_EXTI2_IRQ_BPOS);

}

void irq_handler ( void )
{
    /* Om avbrott från EXTI0: */
    if( *EXTI_PR & EXTI0_IRQ_BPOS )
    {
        /* kvittera avbrott från EXTI0 */
        * EXTI_PR |= EXTI0_IRQ_BPOS;
	}
}

void main(void)
{
}

