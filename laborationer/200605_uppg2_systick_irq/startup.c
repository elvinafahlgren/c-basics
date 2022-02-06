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

#define STK_CTRL 			((volatile unsigned int *)(0xE000E010))
#define STK_LOAD 			((volatile unsigned int *)(0xE000E014))
#define STK_VAL 			((volatile unsigned int *)(0xE000E018))
#define SYSTICK_IRQVEC		((volatile unsigned int *)(0x2001C03C))

void app_init(void)
{
	* GPIO_D_MODER = 0x55005555;
    * GPIO_D_PUPDR = 0x00AA0000;	//pull-dowm
	* GPIO_D_OTYPER = 0x00000000;	//push/pull
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
    for (row = 1; row <= 4; row++){
        ActivateRow(row);
        if  ( col = ReadColumn() ){
            ActivateRow(0);
            return key [ 4 * (row-1) + (col-1) ];
        }
    }
    ActivateRow(0);
    return 0xFF;
}

void out7seg( unsigned char c ){
    static unsigned char segCode[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71, 0x40}; // 0x40 tillagt
    if ( c > 16 ) {
        * GPIO_D_ODR_LOW = 0;
        return;
    }
    * GPIO_D_ODR_LOW = segCode[c];
}

void blocked_delay_10ms( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
//    *STK_LOAD = ( (1680000 - 1 );	/* 10 ms */
	*STK_LOAD = ( (168 - 1 ));	/* Simulator value */
    *STK_VAL = 0;
    *STK_CTRL = 5;  //sätter enable och clksource
    // börjar räkna
    while( (*STK_CTRL & 0x10000 )== 0 );    //vänta till countflag=1
    *STK_CTRL = 0;
}

void delay_delay(unsigned int ms)
{
	while( ms/10 ){
		blocked_delay_10ms();
		ms -= 10;
	}
}

static int timeout;
void systick_irq_handler( void );

void start_timeout_period( void )
{
	/* SystemCoreClock = 168000000 */
	*SYSTICK_IRQVEC = systick_irq_handler;
	*STK_CTRL = 0;
//	*STK_LOAD = ( 1680000-1 );
	*STK_LOAD = ( 1680-1 )	/* Simulatior value */
	*STK_VAL = 0;
	*STK_CTRL = 7;
}

void systick_irq_handler( void )
{
    if( timeout ){
		timeout--;
		start_timeout_period();
	}
}

void start_timeout( void )
{
	timeout = 500; /* 100 * 10 ms = 1 sec */
	start_timeout_period();
}

void display3sec( char c )
{
	for( int i = 0; i < 3; i++)
	{
		out7seg(0xFF);
		blocked_delay( 500 );
		out7seg(c);
		blocked_delay( 500 );
	}
}
    
void main(void)
{
	char tmp;
	
    app_init();
	while(1) 
	{
		/* Slumptal mellan 1-8*/
		unsigned int t = random() >> 4;
		t++;
		
		blocked_delay(t * 1000);
		
		/* Generera slumptal 0-15 */
		t = random() >> 3;
		out7seg( (char) t );
		start_timeout();
		do{
			tmp = keyb();
			if( t == tmp )
				break;
		}while(timeout);
		
		if( timeout )
		{
			display3sec( tmp );
		}else{
			display3sec( 16 );
			break;
		}
	}
}



