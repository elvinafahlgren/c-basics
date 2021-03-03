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
/* timer 6 */
#define     TIM6_CR1    ((volatile unsigned short * ) 0x40001000)
#define     TIM6_DIER    ((volatile unsigned short * ) 0x4000100C)
#define     TIM6_CNT    ((volatile unsigned short * ) 0x40001024)
#define     TIM6_ARR    ((volatile unsigned short * ) 0x4000102C)
#define     UDIS    (1<<1)
#define     CEN    (1<<0)

#define GPIO_D_ODRLOW ((volatile unsigned char *) 0x40020C14) 
#define GPIO_MODER ((volatile unsigned long *) 0x40020C00)

void gpio_init( void )
{
	* ( (unsigned char *) 0x40020C14) = 0x0;
        
	* ( (unsigned long *) 0x40020C00) = 0x00005555;  // GPIO_MODER initieras
}

void timer6_init()
{
	*TIM6_CR1 &= ~CEN; /* Stoppa räknarmodul */
	*TIM6_DIER |= UDIS; /* Vi behöver inget "update"-event.. */
	*TIM6_ARR = 0xFFFF; /* Sätt räknarregistret */
	*TIM6_CR1 |= CEN; /* Starta räknarmodul */
}

void main( void )
{
	short random = 0;
	gpio_init();
	timer6_init();
	while( 1 )
	{
		random = ( char ) *TIM6_CNT;
		*GPIO_D_ODRLOW = random;
	}
}

