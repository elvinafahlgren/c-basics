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

char *list[]={"Hello","World","Again"};


void CircularShiftRight(char** p1, char** p2, char** p3)
{
	/* Spara adressen till p3 i p*/
	char *p = *p3;
	/* Shifta */
	*p3 = *p2;
	*p2 = *p1;
	*p1 = p;
}

void main(void)
{
	/* "Hello World Again" */
	printf( "%s %s %s\n", list[0],list[1],list[2] );
	CircularShiftRight( &list[0], &list[1], &list[2]);
	/* "Again Hello World" */
	printf( "%s %s %s\n", list[0],list[1],list[2] );
}

