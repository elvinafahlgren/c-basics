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

typedef struct
{
	int a;
	int b;
	int c;
}POST,*PPOST;

int compare_post( PPOST pp, POST p)
{
	while( pp )
	{
		if((pp->a == p.a) && (pp->b == p.b) && (pp->c == p.c))	// eller *pp == p
			return 1;
		pp++;
	}
	return 0;
}
void main(void)
{
}

