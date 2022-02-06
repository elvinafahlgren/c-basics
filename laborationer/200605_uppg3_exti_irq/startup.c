/*
 * 	startup.c
 *
 */
 /*
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

/* Port D pekaradresser */
#define GPIO_D_BASE			((volatile unsigned int *) 0x40020C00)
#define GPIO_D_ODR_LOW 		((volatile unsigned char *) 0x40020C14) 
#define GPIO_D_ODR_HIGH 	((volatile unsigned char *) 0x40020C15)

/* Port E pekaradresser */
#define GPIO_E_BASE 		((volatile unsigned int *) 0x40021000)
#define GPIO_E_IDR_LOW 		((volatile unsigned char *) 0x40021010)
#define GPIO_E_IDR_HIGH		((volatile unsigned char *) 0x40021011)

/* Bestämda adresser */
#define  SYSCFG_EXTICR1     ((volatile unsigned int *)0x40013808)
#define  EXTI_IMR           ((volatile unsigned int *)0x40013C00)
#define  EXTI_FTSR          ((volatile unsigned int *)0x40013C0C)
#define  EXTI_RTSR          ((volatile unsigned int *)0x40013C08)
#define  EXTI_PR            ((volatile unsigned int *)0x40013C14)

#define NVIC_ISER0       	((volatile unsigned int *) 0xE000E100)
/* irq nr */
#define NVIC_EXTI1_IRQ_BPOS	(1<<7)
/* nedan används när Generera avbrott hos EXTI1 */
#define EXTI1_IRQ_BPOS    	(1<<1)
/* avbrottsvektor */
#define EXTI1_IRQVEC     	((void (**) (void) ) 0x2001C05C )

/* EXTI1 är multiplexsignal */

void irq_handler( void );
/* initieringar */
void init_app(void)
{
	* GPIO_D_BASE = 0x55555555;	// port d ingång
	* GPIO_E_BASE = 0;			// port e utgång
	
    /* koppla PE till EXTI1*/
    *SYSCFG_EXTICR1 |= 0x0040;

    /* Konfigurera EXTI1 för att generera avbrott */
    * EXTI_IMR |= EXTI1_IRQ_BPOS;
    * EXTI_RTSR |= EXTI1_IRQ_BPOS;
	* EXTI_FTSR |= EXTI1_IRQ_BPOS;
	
	/* Sätt upp avbrottsvektor */
    * EXTI1_IRQVEC = irq_handler;

    /* konfig den bit i NVIC som kontrollerarar den avbrottslina som EXTI kopplats till */
    * NVIC_ISER0 |= NVIC_EXTI1_IRQ_BPOS;

}

void irq_handler ( void )
{
    /* Om avbrott från EXTI1:*/
    if( *EXTI_PR & EXTI1_IRQ_BPOS )
    {        
		/* om s1 är hög */
		if(*GPIO_E_IDR_LOW & 1)
		{
			/* och s2 är hög */
			if(*GPIO_E_IDR_LOW & 2){
				/* Visa D8-15*/
				*GPIO_D_ODR_HIGH = *GPIO_E_IDR_HIGH;
			}
			else{
				/* Om s2 är låg visa D0-7*/
				*GPIO_D_ODR_LOW = *GPIO_E_IDR_HIGH;
			}
		}else{
			/* om s1 är låg och s2 är hög */
			if(*GPIO_E_IDR_LOW & 2){
				/* släck d0-7 */
				*GPIO_D_ODR_HIGH = 0xFF;
			}
			else{
				/* och både s1 och s2 är låga släck d8-15 */
				*GPIO_D_ODR_LOW = 0xFF;
			}
		}
		/* kvittera avbrott från EXTI1 */
        *EXTI_PR |= EXTI1_IRQ_BPOS;
    }
}



void main(void)
{
	init_app();
	while(1);
}
