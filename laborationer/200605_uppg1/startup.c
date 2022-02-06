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

#define MAX 4 
unsigned short student_year[MAX]; 
unsigned char student_grade[MAX]; 
int c; 

void init_data(){
	student_year[0] = 2000; 
	student_grade[0] = 4; 
	student_year[1] = 2000; 
	student_grade[1] = 3; 
	student_year[2] = 1998; 
	student_grade[2] = 5; 
	student_year[3] = 2002; 
	student_grade[3] = 4; 
}

int sum_grade( int year ) { 
	int x = 0; 
	for( int i=0; i < MAX; i++) { 
		if( student_year[i] == year ) 
			x += student_grade[i]; 
	} 
	return x; 
} 

int main( void ) {
	int a, b; 
	init_data(); 
	a = sum_grade(2020); 
	b = sum_grade(2000); 
	c = a+b; 
}


// Det följer kod (inte visat hart) som senare använder 'c' 
// vi kan alltsa inte "optimera bort" tilldelningen. 


