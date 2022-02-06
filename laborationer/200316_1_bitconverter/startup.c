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

unsigned int bitconvert(int method, unsigned int value)
{
	unsigned int rv;
	switch( method & 3 )
	{
		/*om method (b1b0) = 00, returnera bitvis and av value */
		case 0: rv = 0x20000207 & value; break;
		/*om method (b1b0) = 01, returnera bitvis komplement av value */
		case 1: rv = ~value; break;											// or rv = ( value ^ 0xFFFFFFFF )
		/*om method (b1b0) = 10, returnera de 16 mest signifikanta bitarna av value */
		case 2: rv = ( value >> 16 ); break;
		/*om method (b1b0) = 10, returnera det 32-bitars tal som bildas från det 16 bitars 
		 * teckenutvidgade extraherade tal från b24-b8 hos value */
		case 3: rv = ( (value >> 8) & 0xFFFF);
				if(rv & 0x8000 )
					rv = (rv | 0xFFFF0000 );
				break;
	}
	return rv;
}

void main(void)
{
}

