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


#define port8ptrA ( ( volatile char *) 0x100000 ) 
#define port8ptrB ( ( volatile char *) 0x100001 ) 

void saveRelation( int ); 
int comparePorts( void ); 

/* Read and compare 100 values from ports A and B 
 * Determine the percentage of values A less than or equal to B 
 * Place the result in the global variable 'percentage' 
 */
 
char result[100]; 
int percentage; 
void main(void) { 
	percentage = 0; 
	for( int i=0; i<100;i++)
		saveRelation( comparePorts() ); 
		
	int i = 0;
	while( i < 100 ){ 
		if( result[i] ) 
			percentage++;
		i++;
	} 
} 

void saveRelation( int relation ) 
{ 
	static int items = 0; 
	result[items++] = relation; 
} 

int comparePorts( void ) { 
	if (*port8ptrA <= *port8ptrB) 
		return 1; 
	return 0; 
}
