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
 

/* Aktivera rad */
void ActivateRow(unsigned int row){
    switch (row) {
		/* b7 motsvarar b15, b6 b14 osv i GPIO_ODR_HIGH*/
		/* Rad=1 -> b7 = 1 */
        case 1: * GPIO_ODR_HIGH = 0x80; break;
		/* Rad=2 -> b6 = 1 */
        case 2: * GPIO_ODR_HIGH = 0x40; break;
		/* Rad=3 -> b5 = 1 */
        case 3: * GPIO_ODR_HIGH = 0x20; break;
		/* Rad=4 -> b4 = 1 */
        case 4: * GPIO_ODR_HIGH = 0x10; break;
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
unsigned char keyb_ald_ctrl(void)
{
	/* statusord med 16*/
    unsigned char keystatus = "123A456B789CE0FD";
    unsigned int row, col;
	unsigned short bit = 0;	/* 16 bitars ord */
    for (int row = 1; row <= 4; row++){
		/* Aktivera rad */
        ActivateRow(row);
		/* Läs kolumn */
        col = ReadColumn();
		/* Om en kolumn är aktiv ...*/
        if  (col != 0 ){
			/* deaktivera GPIO_ODR_HIGH */
            ActivateRow(0);
			/* sätt den " 4 * (row-1) + (col-1) " biten i en temporära bithållaren */
			bit |= (0x01 << (4 * (row-1) + (col-1));
            return ( unsigned char) keystatus & (4 * (row-1) + (col-1));
        }
    }
	/* deaktivera GPIO_ODR_HIGH */
	ActivateRow(0);
	/* om en eller flera tangenter är nedtryckt */
	if( bit != 0 )
	{
		/* returnera alla bitar som är nedtryckta*/
		return char bit & keystatus;
	}
	/* om ingen tangent är nedtryckt */
    return 0xFF;
}

/* skriver ut emoji i sju-segmentskod */
void outEmoji( unsigned char c ){
    static unsigned char segCode[]={0x40,0x62,0x54,0x49,0x5D,0x6B,0x64};
	
	/* övriga parametervärden, större än 5 */
    if ( c > 5 ) {
        * GPIO_ODR_LOW = segCode[6];
        return;
    }
	/* returnera vald parameter */
    * GPIO_ODR_LOW = segCode[c];
}


unsigned char is_numeric( unsigned short s )
{
	/* EJ KLAR */
	unsigned char c;
	c = keyb_ald_ctrl();	/* Hämta värde från keypad */
	/* om */
	if
	
	return;
}
    
void main(void)
{
	
}



