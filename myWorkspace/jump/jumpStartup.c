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
#define GPIO_D_CONFIG	0x40020C00
#define GPIO_D_OUT		0x40020C14

void main(void)
{
	// Skriv 0x55555555 till GPIO_D_CONFIG
	*((unsigned int *)GPIO_D_CONFIG) = 0x55555555;
	
	// Skriv0 0xAA till GPIO_D_OUT
	*((unsigned char*)GPIO_D_OUT) = 0xAA;
	
	// Gör så att en lampa studsar fram och tillbaka på bargraphen
	while(1)
	{
		for(int i = 0; i < 7; i++)
		{
			unsigned char c = (1 << i);
			*((unsigned int *)GPIO_D_CONFIG) = c;
			
			for(int j = 0; j < 1000; j++) {} //delay
		}
		
		for(int i = 7; i > 0; i--)
		{
			unsigned char c = (1 << i);
			*((unsigned int *)GPIO_D_CONFIG) = c;
			
			for(int j = 0; j < 1000; j++) {} //delay
		}
	}
}

