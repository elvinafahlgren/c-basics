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
	switch( method& 3 )
	{
		case0: rv = value; break;
		case1:rv = ( value ^ 0xFFFFFFFF ); break;	// or rv = ~value; 
		case2:rv = ( value >> 16 ); break;
		case3:rv = ( (value >> 8) & 0xFFFF);
			if(rv & 0x8000 )
				rv = (rv | 0xFFFF0000 );
				break;
	} 
	return rv;
}

void main(void)
{
}

