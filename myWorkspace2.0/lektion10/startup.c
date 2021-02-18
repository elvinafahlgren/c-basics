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

unsigned short ctr = 0;

void EXTI1_irq_handler( void )
{
	// write ctr to GPIO D output
	*((unsigned char *) 0x40020C14) = ctr++;
}

void main(void)
{
	// Gonfig GPIO D
	*((unsigned int *) 0x40020C00) = 0x55555555;
	
	/* Connect  pin 1 in GPIO port D to EXTI interrupt 1 */
	volatile unsigned int * SYSCFG_EXTICR = (unsigned int *) 0x40013808;
	// EXTI 1 is bits 4-7 in SYSCFG_EXTICR1 (SYSCFG_EXTICR[0])
	// Port D has code 0011
	SYSCFG_EXTICR[0] &= 0xFFFFFF0F;
	SYSCFG_EXTICR[0] |= 0x40;
	
	/* Configure EXTI 1 to not be masked , and trigger on both flanks */
	volatile unsigned int * EXTI_IMR = 		(unsigned int *)0x40013C00;
	volatile unsigned int * EXTI_EMR = 		(unsigned int *)0x40013C04;
	volatile unsigned int * EXTI_RTSR = 	(unsigned int *)0x40013C08;
	volatile unsigned int * EXTI_FTSR = 	(unsigned int *)0x40013C0C;
	volatile unsigned int * EXTI_SWIER = 	(unsigned int *)0x40013C10;
	volatile unsigned int * EXTI_PR = 		(unsigned int *)0x40013C14;
	
	*EXTI_IMR |= 0x2;	// Unmask EXTI_1
	*EXTI_EMR |= 0x2;	// Unmask EXTI_1
	*EXTI_FTSR |= 0x2;	// Trigger positive flank
	*EXTI_RTSR |= 0x2;	// Trigger negative flank
	*EXTI_PR |= 0x2;	// Kvittera interrupt
	
	/* Enable interrupt EXTI1 */
	volatile unsigned int * NVIC_ISER = (unsigned int *)0xE000E100;
	// Vector table in Quick Guide tells us EXTI1 is IRQ 7
	unsigned int EXTI1_IRQ = 7;
	NVIC_ISER[EXTI1_IRQ / 32] |= (1 << (EXTI1_IRQ % 32));
	
	/* Place our handler in interrupt vector table */
	volatile unsigned int * SCB_VTOR = (unsigned int *)0xE000ED08;
	// Vector table in Quick Guide tells us EXTI1 offset is 5C
	*((void (**)(void))(*SCB_VTOR + 0x5C)) = EXTI1_irq_handler;
	
	// Software trigger interrupt
	*EXTI_SWIER |= 0x2;
	
	while(1){
	};	
}

