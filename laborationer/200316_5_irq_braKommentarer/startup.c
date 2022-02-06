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

/* Port E */
#define 	PORT_E_BASE			0x40020C00
#define 	GPIO_E_MODER 		((volatile unsigned int *) 	(PORT_E_BASE))
#define 	GPIO_E_OTYPER 		((volatile unsigned short *)(PORT_E_BASE + 0x4))
#define 	GPIO_E_OSPEEDR 		((volatile unsigned int *)	(PORT_E_BASE + 0x8))
#define 	GPIO_E_PUPDR 		((volatile unsigned int *) 	(PORT_E_BASE + 0xC))
#define 	GPIO_E_IDR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x10))
#define 	GPIO_E_IDR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x11))
#define 	GPIO_E_ODR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x14)) 
#define 	GPIO_E_ODR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x15))

/* Pekare till SYSCFG_EXTICR1, EXTI och NVIC_ISER0*/
#define  	SYSCFG_EXTICR1     	((volatile unsigned int *)0x40013808)
#define  	EXTI_IMR           	((volatile unsigned int *)0x40013C00)
#define  	EXTI_FTSR          	((volatile unsigned int *)0x40013C0C)
#define  	EXTI_RTSR          	((volatile unsigned int *)0x40013C08)
#define  	EXTI_PR            	((volatile unsigned int *)0x40013C14)
#define  	NVIC_ISER0       	((volatile unsigned int *) 0xE000E100)

/* irq nr */
#define 	NVIC_EXTI2_IRQ_BPOS     (1<<8)
#define 	NVIC_EXTI1_IRQ_BPOS     (1<<7)
#define 	NVIC_EXTI0_IRQ_BPOS     (1<<6)

/* nedan används när Generera avbrott hos EXTI0,1,2 */
#define 	EXTI2_IRQ_BPOS          (1<<2)
#define 	EXTI1_IRQ_BPOS          (1<<1)
#define 	EXTI0_IRQ_BPOS          (1<<0)

/* Avbrottsvektorer med adresser */
#define 	EXTI2_IRQVEC     	((void (**) (void) ) 0x2001C060 ) 
#define 	EXTI1_IRQVEC     	((void (**) (void) ) 0x2001C05C )
#define 	EXTI0_IRQVEC     	((void (**) (void) ) 0x2001C058 )

/* Statisk variabel som används för att lagra senaste tangenten */
static char lastkey;
/* Statisk variabel som används för tangentbordets tillstånd */
static char locked;

void init_gpio(void)
{
	/* PORT E
	 * b15-b8 used for hexadecimal display 
	 * b7-b5 used for output to rows
	 * b4-b0 used for input from columns, NOR gate and switchcases */
    * GPIO_E_MODER |= 0x55555400;  		// GPIO_D_MODER initieras
	/* utgångar är push-pull */
	* GPIO_E_OTYPER = 0x00000000;
    /* ingångar b4,b3,b2 är pull-down */
    * GPIO_E_PUPDR |= 0x000002A4;
}

void KeybIRQ( void );
void s1IRQ( void );
void s2IRQ( void );

/* initieringar */
void init_exti(void)
{	
    /* koppla PE2,PE1,PE0 till EXTI2,1,0*/
    *SYSCFG_EXTICR1 |= 0x0444;

    /* Konfigurera EXTI2,1,0 för att generera avbrott */
    * EXTI_IMR |= (EXTI2_IRQ_BPOS | EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);
	/* Konfigurera trigger selection bit för avbrottslinor */
    * EXTI_RTSR |= (EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);	/* enable trigger on falling edge */
	* EXTI_FTSR &= ~(EXTI1_IRQ_BPOS | EXTI0_IRQ_BPOS);	/* disable trigger on rising edge */
	* EXTI_FTSR |= EXTI2_IRQ_BPOS;		/* enable trigger on rising edge */
	* EXTI_RTSR &= ~EXTI2_IRQ_BPOS;		/* disable trigger on falling edge */
	
	/* Sätt upp avbrottsvektor */
    * EXTI0_IRQVEC = KeybIRQ;
	* EXTI1_IRQVEC = s1IRQ;
	* EXTI1_IRQVEC = s2IRQ;

    /* enable den bit i NVIC som kontrollerarar den avbrottslina som EXTI kopplats till */
    * NVIC_ISER0 |= (NVIC_EXTI1_IRQ_BPOS | NVIC_EXTI1_IRQ_BPOS | NVIC_EXTI1_IRQ_BPOS);

}

unsigned char get( void )
{
	unsigned short c;
	/* Kolla om tangenten är 0, dvs, b7 och b4 är aktiva */
	*GPIO_E_ODR_LOW = 0x80 ; 
	c = *GPIO_E_IDR_LOW & 0x18;
	if ( c & 0x10 )
	{ 
		lastkey = 0; 
		return;
	}
	/* Kolla om tangenten är 1, dvs, b7 och b3 är aktiva */
	if ( c & 8 )
	{ 
		lastkey = 1; 
		return;
	}
	/* Kolla om tangenten är 2, dvs, b6 och b4 är aktiva */
	*GPIO_E_ODR_LOW = 0x40 ; 
	c = *GPIO_E_IDR_LOW & 0x18;
	if ( c & 0x10 )
	{ 
		lastkey = 2; 
		return;
	}
	/* Kolla om tangenten är 3, dvs, b6 och b3 är aktiva */
	if ( c & 8 )
	{ 
		lastkey = 3; 
		return;
	}
	/* Kolla om tangenten är 4, dvs, b5 och b4 är aktiva */
	*GPIO_E_ODR_LOW = 0x20 ; 
	c = *GPIO_E_IDR_LOW & 0x18;
	if ( c & 0x10 )
	{ 
		lastkey = 4; 
		return;
	}
	/* Kolla om tangenten är 5, dvs, b5 och b3 är aktiva */
	if ( c & 8 )
	{ 
		lastkey = 5; 
		return;
	}
}

void KeybIRQ( void )
{
	lastkey = get();
	*GPIO_E_ODR_LOW = 0xE0; 	/* Aktivera keypad */
	*EXTI_PR = EXTI0_IRQ_BPOS;	/* Clear this interupt */
}
void s1IRQ( void )
{
	*EXTI_PR = EXTI1_IRQ_BPOS;	/* Clear this interupt */
	locked = 0;
}
void s2IRQ( void )
{
	*EXTI_PR = EXTI2_IRQ_BPOS;	/* Clear this interupt */
	locked = 1;
}
    
void main(void)
{
    init_gpio();
	init_exti();
    locked = 1;
	*GPIO_E_ODR_LOW = 0xE0;		/* Aktivera keypad */
    while (1) {
        if( locked ) 
			*GPIO_E_ODR_HIGH = 0xF;
		else
			*GPIO_E_ODR_HIGH = lastkey;
    }
}



