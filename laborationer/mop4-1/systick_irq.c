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

#define GPIO_ODR_LOW ((volatile unsigned char *) 0x40020C14) 
#define GPIO_MODER ((volatile unsigned long *) 0x40020C00)
#define SCB_VTOR ((volatile unsigned int *) 0xE000DE08) //adress till registret där vektortabellens basadress bestäms
  
#define STK_CTRL ((volatile unsigned int *)(0xE000E010))
#define STK_LOAD ((volatile unsigned int *)(0xE000E014))
#define STK_VAL ((volatile unsigned int *)(0xE000E018))

#define SIMULATOR

static volatile int systick_flag;
static volatile int delay_count;

#ifdef  SIMULATOR
#define DELAY_COUNT 100
#else
#define DELAY_COUNT 1000000
#endif



void delay_1mikro( void )
{
    *STK_CTRL = 0;
    *STK_LOAD = ( 168 - 1 );
    *STK_VAL = 0;
    *STK_CTRL = 7;
}


void systick_irq_handler( void )
{
    *STK_CTRL = 0;
    delay_count -- ;
    if( delay_count > 0 ) delay_1mikro();
    else systick_flag = 1;
}

void delay( unsigned int count )
{
    if( count == 0 ) return;
    delay_count = count;
    systick_flag = 0;
    delay_1mikro();
}

void init_app( void )
{
        * ( (unsigned char *) 0x40020C14) = 0x0;
        
        * ( (unsigned long *) 0x40020C00) = 0x00005555;  // GPIO_MODER initieras
        
        *SCB_VTOR = 0x2001C000;
        
        * ((void (**) (void) ) 0x2001C03C) = systick_irq_handler;
        
        systick_flag = 0;

}


void main(void)
{
    
    init_app();
    *GPIO_ODR_LOW = 0;
    delay(DELAY_COUNT);
    *GPIO_ODR_LOW = 0xFF;
    
    while(1){
        if( systick_flag ){
            break;
        }
    }
    *GPIO_ODR_LOW = 0;
}

