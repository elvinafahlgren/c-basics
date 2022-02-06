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

/* Adress för Status och styrregister */
#define 	STK_CTRL 		((volatile unsigned int *)(0xE000E010))
/* Adress för räknarintervall */
#define 	STK_LOAD 		((volatile unsigned int *)(0xE000E014))
/* Adress för räknarvärde */
#define 	STK_VAL 		((volatile unsigned int *)(0xE000E018))


/* Blockerande förfröjning på 10 millisekunder */
void blocked_delay_10ms( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
//    *STK_LOAD = ( (1680000 - 1 );	/* 10 ms */
	*STK_LOAD = ( (168 - 1 ));	/* Simulator value */
    *STK_VAL = 0;
    *STK_CTRL = 5;  /* Sätter enable och clksource*/
    /* börjar räkna */
    while( (*STK_CTRL & 0x10000 )== 0 );    /* Vänta till countflag = 1 */
    *STK_CTRL = 0;
}


/* Blockerande förfröjning på 250 mikrosekunder */
void delay_250mys( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    *STK_LOAD = ( (168000/4) -1 );	/* 250 us */
    *STK_VAL = 0;
    *STK_CTRL = 5;  /* Sätter enable och clksource*/
    /* börjar räkna */
    while( (*STK_CTRL & 0x10000 )== 0 );	/* Vänta till countflag = 1 */
    *STK_CTRL = 0;
}


/* Blockerande fördröjning på 100 mikrosekunder*/
void delay_100_micro( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    *STK_LOAD = ( 16800 - 1 ); /* 100 us */
    *STK_VAL = 0;
    *STK_CTRL = 5;  /* Sätter enable och clksource*/
    /* börjar räkna */
    while( (*STK_CTRL & 0x10000 ) == 0 );    /* Vänta till countflag = 1 */
    *STK_CTRL = 0;
}

/* Blockerande fördröjning på 10 millosekunder
 * Anvädner delay_100_micro */
void delay_ms(unsigned int ms)
{
	/* Number of 100 usecs delays
	 * are obtained from:
	 * (ms * 10), assuming ms  > 0
	*/
	unsigned int delay = ms*10;
    while(delay)
    {
        delay_100_micro();
        delay--;
    }
}

/* Anvädner delay_100_micro */
void delay_shortpulse(unsigned int w)
{
	/* Number of 100 usecs delays
	 * are obtained from:
	 * (w * 10), assuming w  > 0
	*/
	unsigned int delay = (w*10)-2;
    while( delay > 0 )
    {
		delay_100_micro();
        delay--;
    }
}

#define SIMULATOR 

/* Blockerande förfröjning på 250 nanosekunder */
void delay_250ns( void )
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    *STK_LOAD = ( (168/4) -1 ); /* 250 ns */
    *STK_VAL = 0;
    *STK_CTRL = 5;  //sätter enable och clksource
    // börjar räkna
    while( (*STK_CTRL & 0x10000 )== 0 );    //vänta till countflag=1
    *STK_CTRL = 0;
}
/* Blockerande förfröjning på 1 mikrosekund
 * Anropar delay_250ns */
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
/* Blockerande förfröjning på 1 millisekund
 * Anropar delay_micro */
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


/* Blockerande förfröjning på 10 sekunder */
void delay10sec( void )
{
	/* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
	*STK_LOAD = ( (16800000 - 1 ));
    *STK_VAL = 0;
    *STK_CTRL = 5;  /* Sätter enable och clksource*/
    /* börjar räkna */
    while( (*STK_CTRL & 0x10000 )== 0 );    /* Vänta till countflag = 1 */
    *STK_CTRL = 0;	
}

void main(void)
{
}

