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
// till _iniuart
#define BIT_UE		(1<<13)
#define BIT_TE		(1<<3)
#define	BIT_RE		(1<<2)

// till _tstchar
#define BIT_RXNE	(1<<5)
#define	BIT_TXE		(1<<7)

// Usart registers
typedef struct
{
	volatile unsigned short sr;
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

char _iniuart( void )
{
	// Baudraten bestäms som vi tidigare sett i BRR
	USART1->brr = 0x2D9;
	// Antalet stoppbitar bestäms i CR2
	USART1->cr2 = 0;
	/*
	* Kretsen aktiveras genom CR1, 
	* här bestäms också ramens längd och antal bitar
	*/
	USART1->cr1 = BIT_UE | BIT_TE | BIT_RE;
}


char _tstchar( void )
{
	if( (USART1->sr & BIT_RXNE ) == BIT_RXNE)
		return (char) USART1->dr;
	return 0;
}

void _outchar( char c )
{
	while (( USART1->sr & BIT_TXE ) == 0 );
	USART1->dr = (unsigned short) c;
}	



void main(void)
{	/* enkel "eko"-funktion */
	char c;
	_iniuart();
	while(1)
	{
		c = _tstchar();
		if ( c )
			_outchar(c);
		
	}
}

