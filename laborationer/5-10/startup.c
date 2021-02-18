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

#define STK_CTRL ((volatile unsigned int *)(0xE000E010))
#define STK_LOAD ((volatile unsigned int *)(0xE000E014))
#define STK_VAL ((volatile unsigned int *)(0xE000E018))
#define SIMULATOR 

void delay_250ns( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    *STK_LOAD = ( (168/4) -1 );
    *STK_VAL = 0;
    *STK_CTRL = 5;  //sätter enable och clksource
    // börjar räkna
    while( (*STK_CTRL & 0x10000 )== 0 );    //vänta till countflag=1
    *STK_CTRL = 0;
}

void delay_micro(unsigned int us)
{
#ifdef SIMULATOR
    us = us / 1000;
    us++;
#endif
    while( us > 0 )
    {
        delay_250ns();
        delay_250ns();
        delay_250ns();
        delay_250ns();
        us--;
    }
}

void delay_milli(unsigned int ms)
{
#ifdef  SIMULATOR
    ms = ms / 1000;
    ms++;
#endif
    while(ms > 0)
    {
        delay_micro(1000);
        ms--;
    }
}
attribute((naked))
void graphics_initialize ( void )
{
    asm volatile ("  .HWORD  0xDFF0\n");
    asm volatile ("  BX LR\n");
}

attribute((naked))
void graphics_clear_screen ( void )
{
    asm volatile ("  .HWORD  0xDFF1\n");
    asm volatile ("  BX LR\n");
}

attribute((naked))
void graphics_pixel_set ( int x, int y )
{
    asm volatile ("  .HWORD  0xDFF2\n");
    asm volatile ("  BX LR\n");
}

attribute((naked))
void graphics_pixel_clear ( int x, int y )
{
    asm volatile ("  .HWORD  0xDFF3\n");
    asm volatile ("  BX LR\n");
}

void main(void)
{
	int i;
	graphic_initalize();
	graphic_clear_screen();
	for( i = 1; i <= 128; i++ ) /* rita en horisonell linje */
		graphic_pixel_set( i, 10 );
	 for( i = 1; i <= 64; i++ ) /* rita en vertikal linje */
		graphic_pixel_set( 10, i );
	 delay_milli( 500 ); /* vänta 0,5 sekunder */
	 for( i = 1; i <= 128; i++ )
		graphic_pixel_clear( i, 10 ); /* sudda horisontella linjen */
	 for( i = 1; i <= 64; i++ )
		graphic_pixel_clear( 10, i ); /* sudda vertikala linjen */ 
}

