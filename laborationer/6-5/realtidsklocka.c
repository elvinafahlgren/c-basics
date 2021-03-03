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

volatile int ticks;
volatile int seconds;

void timer6_init()
{
	ticks = 0;
	seconds = 0;
	*TIM6_CR1 &= ~CEN;
	*TIM_IRQVEC = timer6_interrupt;
	*NVIC_TIM6_ISER |= NVIC_TIM6_IRQ_BPOS
	*TIM6_DIER |= UDIS;
	*TIM6_ARR = 0xFFFF;
	*TIM6_CR1 |= CEN;
}

void main(void)
{
}

