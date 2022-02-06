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

/* Krypterar (ändrar) en sträng på ett sådant sätt att
 * först biten (bit 0) i första tecknet inverteras
 * för det andra tecknet inverteras den andra biten etc.
 * Krypteringen är cirkulär så för åttonde tecknet är bit 7 vänd (?)*/
void encrypt( char *str )
{
	char *x = str;
	unsigned char mask = 0x1;
	while( *x )
	{
		if( *x & mask )
			*x = *x & (~mask);
		else
			*x = *x | mask;
		mask = mask << 1;
		if( mask == 0 )
			mask = 0x1;
		x++;
	}
}

void main(void)
{
}

