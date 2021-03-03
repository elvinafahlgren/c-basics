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

// Usart registers
typedef struct
{
	union {
		volatile unsigned short sr;
		struct {
			volatile unsigned short 
			pe:1, fe:1, nf:1, ore:1, idle:1,
			rxne:1, tc:1, txe:1, ldb:1, cts:1,
			unused:6;
		}
	};
	
	volatile unsigned short Unused0;
	volatile unsigned short dr;
	volatile unsigned short Unused1;
	volatile unsigned short brr;
	volatile unsigned short Unused2;
	volatile unsigned short cr1;
	volatile unsigned short Unused3;
	volatile unsigned short cr2;
	volatile unsigned short Unused4;
	volatile unsigned short cr3;
	volatile unsigned short Unused5;
	volatile unsigned short gtpr;
} USART;

#define USART1 ((USART*)0x40011000)

char inbuf;
char outbuf;

void usart_irq_routine()
{
	// if((USART1->cr1 & (1<<7)) && (USART1->sr & (1<<7)))
	if((USART1->cr1 & (1<<7)) && USART1->txe)
	{
		USART1->dr = (unsigned short)outbuf;
		USART1->cr1 &= ~(1 << 7);
	}
	if(USART1->rxne) {
		inbuf = USART1->dr;
		
	}
}

#define NVIC_USART1_ISER 0xE000E104

void main(void)
{
	// Initialize USART
	USART1->cr2 = 0;
	USART1->cr3 = 0;
	USART1->cr1 = 0x202C; // 0010000000101100
	USART1->brr = 0x2D9;
	
	// Set up interrupt handler
	*((void(**)(void))0x2001C0D4) = usart_irq_routine; 
	// = på denna adrass skall pekaren till usart irq ligga
	// Enable interrupt in NVIC
	*((unsigned int *) 0xE000E104) |= (1<<5);
	
	while (1)
	{
		char c = inbuf;
		inbuf = 0;
		
		if(c != 0){
			// Skicka tillbaks c till terminalen
			outbuf = c;
			USART1->cr1 |= (1<<7); // TXEIE
		}
	}
}

