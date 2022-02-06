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

#define GPIO_D_ODR_LOW 	((volatile unsigned char *) 0x40020C14)
#define GPIO_D_MODER 	((volatile unsigned long *) 0x40020C00)

#define GPIO_E_BASE 	0x40021000
#define GPIO_E_MODER 	((volatile unsigned short *) 0x40021000)
#define GPIO_E_IDR_LOW 	((volatile unsigned char *) 0x40021010)
#define GPIO_E_ODR_LOW 	((volatile unsigned char *) 0x40021014) 

#define  SYSCFG_BASE        ((volatile unsigned int *)0x40013800)
#define  SYSCFG_EXTICR2     ((volatile unsigned int *)0x4001380C)
#define  SYSCFG_EXTICR3     ((volatile unsigned int *)0x4001380C)
#define  EXTI_IMR           ((volatile unsigned int *)0x40013C00)
#define  EXTI_RTSR          ((volatile unsigned int *)0x40013C08)
#define  EXTI_FTSR          ((volatile unsigned int *)0x40013C0C)
#define  EXTI_PR            ((volatile unsigned int *)0x40013C14)

#define EXTI9_5_IRQVEC  		((void (**) (void) ) 0x2001C09C )		//EXTI9_5_EXTI (se vektortabell)
#define NVIC_ISER0       		((volatile unsigned int *) 0xE000E100) 	//Interrupt set-enable bit (s-14 quick-guide)
#define NVIC_EXTI5_9_IRQ_BPOS   (1<<23)

#define EXTI5_IRQ_BPOS          (1<<5)
#define EXTI6_IRQ_BPOS          (1<<6)
#define EXTI7_IRQ_BPOS          (1<<7)
#define EXTI8_IRQ_BPOS          (1<<8)

static volatile int count;


typedef struct sCruiseControl{
	volatile unsigned char ctrl;	// control register
	volatile unsigned short sm;		// state machine register
	volatile unsigned short vel;		// velocity control register
	volatile unsigned char ir;		// interrupt request register
} CRUISE_CONTROL, *PCRUISE_CONTROL;
#define CruiseC	(PCRUISE_CONTROL 0xA00)

#define		AUTO	1 	//0001
#define 	LOCK	2	//0010
#define		DEC		4	//0100
#define		INC		8	//1000

#define		CROFF	1
#define		CRON	2
#define 	DREQ	4
#define		IREQ	8

void irq_handler ( void )
{
    /* Om avbrott från EXTI5: */
    if( CruiseC->ir & AUTO ){		
		if( CruiseC-ir & CROFF ){
			CruiseC->ctrl = 0;
			CruiseC->ir |= CROFF;
			/* kvittera avbrott från EXTI5 */
			* EXTI_PR |= EXTI5_IRQ_BPOS;
		}else if( CruiseC-ir & DREQ ){
			if( CruiseC->vel != 0 )
				CruiseC->ctrl = DEC|AUTO;
			CruiseC->ir |= DREQ;
			/* kvittera avbrott från EXTI7 */
			* EXTI_PR |= EXTI7_IRQ_BPOS;
		}else if( CruiseC-ir & IREQ ){
			if( CruiseC->vel != 0xFF )
				CruiseC->ctrl = INC|AUTO;
			CruiseC->ir |= IREQ;
			/* kvittera avbrott från EXTI8 */
			* EXTI_PR |= EXTI8_IRQ_BPOS;
		}
		if( CruiseC-ir & IREQ ){
			CruiseC->ctrl = 0;
			CruiseC->ir |= IREQ;
			/* kvittera avbrott från EXTI8 */
			* EXTI_PR |= EXTI8_IRQ_BPOS;
		}
    }
	else if( CruiseC-ir & CRON ){
		/* Aktivera farthållare */
		CruiseC->ctrl = 0;			//0->AUTO
		CruiseC->sm = 0x55; 		//0x55->SM
		CruiseC->sm = 0xAA; 		//0xAA->SM
		CruiseC->sm = 0x55; 		//0x55->SM
		CruiseC->ctrl |= AUTO;		//1->AUTO
		CruiseC->ctrl = LOCK|AUTO;
		CruiseC->ctrl |= CRON;
		/* kvittera avbrott från EXTI6 */
		* EXTI_PR |= EXTI6_IRQ_BPOS;
	}
}

void init_app(void){
    
    CruiseC->ctrl = 0;
    /* koppla PE0, PE1, PE2, PE3 till EXTI*/
    *SYSCFG_EXTICR2 |= 0x4440;
	*SYSCFG_EXTICR3 |= 0x0004;

    /* Konfigurera EXTI2, EXTI1, EXTI0 för att generera avbrott */
    * EXTI_IMR |= ( EXTI5_IRQ_BPOS | EXTI6_IRQ_BPOS | EXTI7_IRQ_BPOS | EXTI8_IRQ_BPOS );
    * EXTI_RTSR |= ( EXTI5_IRQ_BPOS | EXTI6_IRQ_BPOS | EXTI7_IRQ_BPOS | EXTI8_IRQ_BPOS);
	* EXTI_FTSR &= ~( EXTI5_IRQ_BPOS | EXTI6_IRQ_BPOS | EXTI7_IRQ_BPOS | EXTI8_IRQ_BPOS);

    * EXTI9_5_IRQVEC = irq_handler;

    /* konfig den bit i NVIC som kontrollerarar den avbrottslina som EXTI5_9 kopplats till */
    * NVIC_ISER0 |= NVIC_EXTI5_9_IRQ_BPOS;

}

void main(void)
{
    init_app();
	
}


