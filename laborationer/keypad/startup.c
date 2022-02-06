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

/* Aktivera rad */
void ActivateRow(unsigned int row){
    switch (row) {
		/* Rad=1 -> b4 = 1 */
        case 1: * GPIO_ODR_HIGH = 0x10; break;
		/* Rad=2 -> b5 = 1 */
        case 2: * GPIO_ODR_HIGH = 0x20; break;
		/* Rad=3 -> b6 = 1 */
        case 3: * GPIO_ODR_HIGH = 0x40; break;
		/* Rad=4 -> b7 = 1 */
        case 4: * GPIO_ODR_HIGH = 0x80; break;
		/* default */
        default: *GPIO_ODR_HIGH = 0;
    }
}  

/* Läs kolumn */
int ReadColumn(void){
    unsigned char c;
    c = * GPIO_IDR_HIGH;
	/* Om b3=1, returnera kolumn = 4 */
    if ( c & 0x8 ) 
        return 0x4;
	/* Om b2=1, returnera kolumn = 3 */
    if ( c & 0x4 ) 
        return 0x3;
	/* Om b1=1, returnera kolumn = 2 */
    if ( c & 0x2 ) 
        return 0x2;
	/* Om b0=1, returnera kolumn = 1 */
    if ( c & 0x1 ) 
        return 0x1;
    return 0;
}      

/* returnerar det nedtryckta värdet från keypad */
unsigned char keyb(void){
    unsigned char key[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0xC,0xE,0,0xF,0xD};
    unsigned int row, col;
    for (int row = 1; row <= 4; row++){
		/* Aktivera rad */
        ActivateRow(row);
		/* Läs kolumn */
        col = ReadColumn();
		/* Om en kolumn är aktiv ...*/
        if  (col != 0 ){
			/* deaktivera GPIO_ODR_HIGH */
            ActivateRow(0);
			/* Returnera index 4 * (row-1) + (col-1) i key-arrayen */
            return key [ 4 * (row-1) + (col-1) ];
        }
    }
    ActivateRow(0);
    return 0xFF;
}

/* skriver ut siffra i sju-segmentskod */
void out7seg( unsigned char c ){
    static unsigned char segCode[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    if ( c > 15 ) {
        * GPIO_ODR_LOW = 0;
        return;
    }
    * GPIO_ODR_LOW = segCode[c];
}

void app_init(void)
{  
	/* nollställ GPIO_MODER*/
    * ( (unsigned long *) 0x40020C00) &= 0x0000FFFF; 	//GPIO_MODER
	/* b4-b7 är utgångar
	 * b0-b3 är insignaler*/
    * ( (unsigned long *) 0x40020C00) |= 0x55000000;	//GPIO_MODER
	/* utgångar push-pull */
    * ( (unsigned short *) 0x40020C04) &= 0x00FF;       // GPIO_OTYPER 
    /* inpinnar pull-down*/
    * ( (unsigned long *) 0x40020C0C) &= 0x0000FFFF; 	// GPIO_PUPDR nollställs
    * ( (unsigned long *) 0x40020C0C) |= 0x00AA0000;   	// GPIO_PUPDR initieras
} 

void main(void)
{
	
}

