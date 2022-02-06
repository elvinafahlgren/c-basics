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
/* Port till avbrottsvektor */
#define		SYSTICK_IRQVEC	((volatile unsigned int *)(0x2001C03C))


/*____________________________EXEMPEL FRÅN BOKEN_______________________________________*/

//adress till registret där vektortabellens basadress bestäms
#define SCB_VTOR 			((volatile unsigned int *) 0xE000DE08)

#define SIMULATOR

static volatile int systick_flag;
static volatile int delay_count;

#ifdef  SIMULATOR
#define DELAY_COUNT 100
#else
#define DELAY_COUNT 1000000
#endif


/* Tillsammans med avbrottshanterare åstakommer 1us fördröjning */
void delay_1mikro( void )
{
    *STK_CTRL = 0;
	/* Initiera räknarkretsen för 1us räknarintervall */
    *STK_LOAD = ( 168 - 1 );
    *STK_VAL = 0;
    *STK_CTRL = 7;
}


void systick_irq_handler( void )
{
	/* Deaktivera räknaren */
    *STK_CTRL = 0;
	/* Inkrementera delay_count */
    delay_count--;
	/* Om ytterligare fördröjning 1us krävs */
    if( delay_count > 0 ) 
		delay_1mikro();
    else 
		systick_flag = 1;
}

/* Icke-blockerande fördröjningsrutin 
 * Fördröjer den anropade funktionen count us*/
void delay( unsigned int count )
{
    if( count == 0 ) 
		return;
    delay_count = count;
    systick_flag = 0;
    delay_1mikro();
}

void init_handler( void )
{
        *SCB_VTOR = 0x2001C000;
        
        * SYSTICK_IRQVEC = systick_irq_handler;
        
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
		/* Här placeras kod som kan utföras undet väntetiden */
        }
    }
	/* Här finns den kod som "väntar" på time-out */
    *GPIO_ODR_LOW = 0;
}


/*____________________________ANNAT EXEMPEL FRÅN TENTA____________________________________________*/

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

/* Icke-blockerande fördröjningsrutin */
void start_timeout( void )
{
	timeout = 500; /* 100 * 10 ms = 1 sec */
	start_timeout_period();
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
			/* Här placeras kod som kan utföras under väntetiden */
		}while(timeout);
		
		if( timeout )
		{
			/* Här placeras kod som kan utföras under väntetiden */
		}else{
			display3sec( 16 );
			break;
		}
	}
}

