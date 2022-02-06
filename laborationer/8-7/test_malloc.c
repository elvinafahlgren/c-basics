/*
 * 	startup.c
 *
 */
__attribute__((naked)) __attribute__((section (".start_section")) )
/*
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		// set stack 
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					// call main 
__asm__ volatile(".L1: B .L1\n");				// never return 
}
*/
#include 	<errno.h>
void startup ( void )
{
__asm__ volatile(
 " LDR R0,=stack_top\n"		/* initiera tack frpn länkning */
 " MOV SP,R0\n"
 " BL _crt_init\n"			/* initiera run-time funktionerna */
 " BL main\n"
 ".L1: B .L1\n"
 ) ;
}

extern char heap_low;	/* Definierad av länkaren */
extern char heap_top;	/* Definierad av länkaren */
char *heap_end;

char * _srbk(int incr)
{
	char *prev_heap_end;
	if (heap_end == 0) {
		heap_end = &heap_low;
	}
	prev_heap_end = heap_end;
	
	if (heap_end + incr > &heap_top) {
		/* Kollision mellan och och stack... */
		errno = ENOMEM;
		return (char *)-1;
	}
	heap_end += incr;
	return (char *) prev_heap_end;
}

static void _crt_init() {
extern char __bss_start__;	/* Definierad av länkaren */
extern char __bss_end__;	/* Definierad av länkaren */
	char *s;
	heap_end = 0;
	s = &__bss_start__;
	while( s < &__bss_end__)
		*s++ = 0;
	s = &heap_low;
	while( s < &heap_top )
		*s++ = 0;
}


void main(void)
{
	char *dbuf1,*dbuf2,*dbuf3;
	dbuf1 = malloc( 100 );
	dbuf2 = malloc( 150 );
	dbuf3 = malloc( 15 );
	free( dbuf2 );
	dbuf2 = malloc( 50 );
	free( dbuf1 );
	free( dbuf2 );
	free( dbuf3 );
}

