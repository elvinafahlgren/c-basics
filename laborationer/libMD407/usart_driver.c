/*
 * libMD407
 * usart_driver.c
 * USART driver
 * Drivers for STDIN, STDOUT and STDERR
 */
 
#include "libMD407.h"

/* Define functions here */

static int usart_init( int initval );
static void usart_deinit( int deinitval);
static int usart_write(char *ptr, int len);
static int usart_read(char *ptr, int len);

DEV_DRIVER_DESC StdIn =
{
	{"stdin"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	0,
	usart_read
};

DEV_DRIVER_DESC StdOut =
{
	{"stdout"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	usart_write,
	0
};

DEV_DRIVER_DESC StdErr =
{
	{"stderr"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	usart_write,
	0
};

/* USART types and constants definitions */
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

/* USART implementation */
static int usart_init( int initval ) { 
    // Baudraten bestäms som vi tidigare sett i BRR
	USART1->brr = 0x2D9;
	// Antalet stoppbitar bestäms i CR2
	USART1->cr2 = 0;
	/*
	* Kretsen aktiveras genom CR1, 
	* här bestäms också ramens längd och antal bitar
	*/
	USART1->cr1 = BIT_UE | BIT_TE | BIT_RE;
    
    return 1;
}

static void usart_deinit( int deinitval){/* funktion för när vi är färdiga med usart */
    /* stäng av interrupt */
    USART1->cr1 = 0;
}

/* funktioner från usart_polling */
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
    if( c == '\n') _outchar('\r'); 
}	


static int usart_write(char *ptr, int len){ 
    
    int len0 = len;
    
    while(len--)
        _outchar(*ptr++);
    
    return len0;
    	
	
}

static int usart_read(char *ptr, int len){
    int len0 = len;
    
    while(len--)
        *ptr++ = _tstchar();
    
    return len0;

} 