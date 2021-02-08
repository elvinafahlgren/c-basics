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

void init_app(void)
{


void delay_250ns( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    *STK_LOAD = ( (168/4) -1 );
    *STK_VAL = 0;
    *STK_CTRL = 5;
    while( (*STK_CTRL & 0x10000 )== 0 );
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
        delay_250ns(4);
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

void main(void)
{
    init_app();
    while(1)
    {
        Bargraph = 0;
        delay_milli(500);
        Bargraph = 0xFF;
        delay_milli(500);
    }
}

