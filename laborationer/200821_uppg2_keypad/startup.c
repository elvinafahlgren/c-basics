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

//Port D
#define PORT_D_BASE			0x40020C00
#define GPIO_D_MODER 		((volatile unsigned int *) 	(PORT_D_BASE))
#define GPIO_D_OTYPER 		((volatile unsigned short *)(PORT_D_BASE + 0x4))
#define GPIO_D_OSPEEDR 		((volatile unsigned int *)	(PORT_D_BASE + 0x8))
#define GPIO_D_PUPDR 		((volatile unsigned int *) 	(PORT_D_BASE + 0xC))
#define GPIO_D_IDR_LOW 		((volatile unsigned char *) (PORT_D_BASE + 0x10))
#define GPIO_D_IDR_HIGH 	((volatile unsigned char *) (PORT_D_BASE + 0x11))
#define GPIO_D_ODR_LOW 		((volatile unsigned char *) (PORT_D_BASE + 0x14)) 
#define GPIO_D_ODR_HIGH 	((volatile unsigned char *) (PORT_D_BASE + 0x15))


void app_init(void)
{
	/* b15-b12, b7-b0 utport, 
	 * b11-b8 inport */
    * GPIO_D_MODER = 0x55005555;
	/* inport pull-down */
    * GPIO_D_PUPDR |= 0x00AA0000;
    * GPIO_D_OTYPER = 0; 

    /* Nollställ output */
	* GPIO_D_ODR_HIGH = 0x0;
	* GPIO_D_ODR_LOW = 0x0;
}

void ActivateRow(unsigned int row){
    switch (row) {
        case 1: * GPIO_D_ODR_HIGH = 0x10; break;
        case 2: * GPIO_D_ODR_HIGH = 0x20; break;
        case 3: * GPIO_D_ODR_HIGH = 0x40; break;
        case 4: * GPIO_D_ODR_HIGH = 0x80; break;
        default: *GPIO_D_ODR_HIGH = 0;
    }
}  

int ReadColumn(void){
    unsigned char c;
    c = * GPIO_D_IDR_HIGH;
    if ( c & 0x8 ) 
        return 0x4;
    if ( c & 0x4 ) 
        return 0x3;
    if ( c & 0x2 ) 
        return 0x2;
    if ( c & 0x1 ) 
        return 0x1;
    return 0;
}      


unsigned char keyb(void){
    unsigned char key[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0xC,0xE,0,0xF,0xD};
    unsigned int row, col;
    for (int row = 1; row <= 4; row++){
        ActivateRow(row);
        col = ReadColumn();
        if  (col != 0 ){
            ActivateRow(0);
            return key [ 4 * (row-1) + (col-1) ];
        }
    }
    ActivateRow(0);
    return 0xFF;
}

void out7seg( unsigned char c ){
    static unsigned char segCode[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    if ( c > 15 ) {
        * GPIO_D_ODR_LOW = 0;
        return;
    }
    * GPIO_D_ODR_LOW = segCode[c];
}

    

char keycode( void )
{
	char c;
	/* Vänta tills tangenten tryckts ner */
	while( (c = keyb()) == 0xFF );
	char code = c;
	/* Vänta tills tangenten släpps upp */
	while( (c = keyb()) != 0xFF );
	/* returnera tangentkod */
	return code;
}

char get_valid_value( void )
{
	char code1, code2;
	do{
		code1 = keycode();	/* Hämta värde från keypad */
	}while( code1 >= 10 );	/* tills siffran är <= 9 */
		
	do{
		code2 = keycode();
	}while( code1 >= 10 );
	
	/* Första siffran tolkas som de mest signifikanta fyra bitarna */
	return ((code1 << 4) | code1);
}

char get_valid_method( void )
{
	char code;
	do{
		code = keycode();	/* Hämta värde från keypad */
	}while( code <= 10 || code == 14 || code == 15);	/* tills siffran är >= 10 */
		
	return code;
}

char valconvert( char method, char value )
{
	if( method == 0xA )
		return value;
	
	if( method == 0xB )
		return ~value;
	
	if( method == 0xC )
		return ( value << 1 );
		
	if( method == 0xD ){
		return ( value >> 1 );
	}
	return 0;
}
 
    
void main(void)
{
    app_init();
	
    while (1) {
		/* Läs value från keypad */
        char value = get_valid_value();
		/* Läs method från keypad */
		char method = get_valid_method();
		/* Skriv ut konverterat värde till hexadecimal display */
		*GPIO_D_ODR_LOW = valconvert(method, value);
    }
}


