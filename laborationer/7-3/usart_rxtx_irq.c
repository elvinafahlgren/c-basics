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

// Definiera register (Interrupt Set Enable) och bitmask 
#define NVIC_USART1_ISER        ( (volatile unsigned int *) 0xE000E104 )
#define NVIC_USART1_IRQ_BPOS    (1<<5)
#define USART1_IRQVEC           ( (void (**) (void) ) 0x2001C0D4 )          // avbrottsvektor
// för _iniuart
#define BIT_EN      (1<<13)     // USART enable
#define BIT_RXNEIE  (1<<5)      // receive interrupt enable
#define BIT_TE      (1<<3)      // transmitter enable
#define BIT_RE      (1<<2)      // receiver enable
// för tstchar
#define BIT_RXNE    (1<<5) //kollar om ett tecken finns tillängligt "Receive data register full"
#define BIT_TXE     (1<<7)

#define TXEIE		(1<<7)	/* TXE Interrupt Enable */
#define TCIE		(1<<6)	/* TC Interrupt Enable */
/* Statusbitarna i SR definieras: */
#define TC			(1<<6)	/* Transmission complete */


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

#define USART1 ((USART*) 0x40011000)
char inbuf;
char outbuf;


char usart_tstchar(void){
    char c = inbuf;
    inbuf = 0;
    return c;
}

void usart_irq_routine(void){
    if( USART1->sr & BIT_RXNE ){
        inbuf = (char) USART1->dr;
    }
	if( ( ( USART1->cr1 & TXEIE) !=0 ) && ( ( USART1->sr & BIT_TXE) !=0 ) ){
		USART1->dr = (unsigned short) outbuf;
		USART1->cr1 &= ~TXEIE;	/* Deaktivera avbrott för TXE */
	}
}

char usart_init(void){
    inbuf = 0;
    *USART1_IRQVEC = usart_irq_routine;
    *NVIC_USART1_ISER |= NVIC_USART1_IRQ_BPOS;
    USART1->brr = 0x2D9;
    USART1->cr3 = 0;
    USART1->cr2 = 0;
    USART1->cr1 = BIT_EN | BIT_RXNEIE | BIT_TE | BIT_RE;

}

void usart_outchar( char c ){
	outbuf = c;
	USART1->cr1 |= TXEIE;       /* aktivera avbrott för TXE */
}

void main(void)
{
    /*enkel "eko"-funktion*/
    char c;
    usart_init();
    while (1){
        c = usart_tstchar();
        if ( c ){
            usart_outchar(c);
        }
    }
}

