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

void mystrcat(char *out, char *in1, char *in2, unsigned int bitvec)
{
	int i=0;
	while(*in1)
		out[i++]=*in1++;
	/* variabel som håller koll på vilken bit som skall jämföras */
	int bit = 0;
	while(*in2)
	{
		if( 0x1 & (bitvec >> bit) )	/* shiftar till den bit som skall jämförsa med 1 och i så fall skriva ut */
			out[i++]=*in2++;
		else
			*in2++;
		bit++;
	}
	out[i]='\0';
}

char total[100];

int main(void)
{
	char *str1="Hello";
	char *str2=" World!!";
	int length;
	mystrcat(total, str1, str2, 0x20);
}



