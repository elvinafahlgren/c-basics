/*
 * 	startup.c
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

#define GPIO_ODR_HIGH ((volatile unsigned char *) 0x40020C15)            // höga pinnarna def 
#define GPIO_ODR_LOW ((volatile unsigned char *) 0x40020C14) 
#define GPIO_IDR_HIGH ((volatile unsigned char *) 0x40020C11)
#define GPIO_MODER ((volatile unsigned long *) 0x40020C00)
#define GPIO_OTYPER ((volatile unsigned short *) 0x40020C04)
#define GPIO_PUPDR ((volatile unsigned long *)0x40020C0C


void app_init(void){
    
    * ( (unsigned char *) 0x40020C15) = 0x0;
	* ( (unsigned char *) 0x40020C14) = 0x0;
    * ( (unsigned char *) 0x40020C11) = 0x0;
    
    * ( (unsigned long *) 0x40020C00) &= 0x0000FFFF;  // GPIO_MODER nollställs
    * ( (unsigned long *) 0x40020C00) |= 0x55005555;  // GPIO_MODER initieras
    * ( (unsigned short *) 0x40020C04) &= 0x00FF;       // GPIO_OTYPER nollställs & initieras
    
    * ( (unsigned long *) 0x40020C0C) &= 0x0000FFFF;       // GPIO_PUPDR nollställs
    * ( (unsigned long *) 0x40020C0C) |= 0x00AA0000;       // GPIO_PUPDR initieras

    
}


void ActivateRow(unsigned int row){
    switch (row) {
        case 1: * GPIO_ODR_HIGH = 0x10; break;
        case 2: * GPIO_ODR_HIGH = 0x20; break;
        case 3: * GPIO_ODR_HIGH = 0x40; break;
        case 4: * GPIO_ODR_HIGH = 0x80; break;
        default: *GPIO_ODR_HIGH = 0;
    }
}  

int ReadColumn(void){
    unsigned char c;
    c = * GPIO_IDR_HIGH;
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
        * GPIO_ODR_LOW = 0;
        return;
    }
    * GPIO_ODR_LOW = segCode[c];
}
    
void main(void)
{
    app_init();
    //unsigned char * key[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0xC,0xE,0,0xF,0xD};
    while (1) {
        out7seg( keyb() );
    }
}


