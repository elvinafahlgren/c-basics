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

#define GPIO_D_ODR_LOW ((volatile unsigned char *) 0x40020C14) // port D
#define GPIO_D_MODER ((volatile unsigned long *) 0x40020C00)   // port D

#define GPIO_E_MODER ((volatile unsigned short *) 0x40021000)  // E
#define GPIO_E_IDR_LOW ((volatile unsigned char *) 0x40021010)  // E
#define GPIO_E_ODR_LOW ((volatile unsigned char *) 0x40021014)  // E

#define  SYSCFG_BASE        ((volatile unsigned int *)0x40013800)
#define  SYSCFG_EXTICR1     ((volatile unsigned int *)0x40013808)
#define  EXTI_IMR           ((volatile unsigned int *)0x40013C00)
#define  EXTI_FTSR          ((volatile unsigned int *)0x40013C0C)
#define  EXTI_RTSR          ((volatile unsigned int *)0x40013C08)
#define  EXTI_PR            ((volatile unsigned int *)0x40013C14)
#define  EXTI3_IRQVEC       ((void (**) (void)) 0x2001C064)


#define EXTI3_IRQVEC     ((void (**) (void) ) 0x2001C064 )
#define EXTI2_IRQVEC     ((void (**) (void) ) 0x2001C060 ) 
#define EXTI1_IRQVEC     ((void (**) (void) ) 0x2001C05C )
#define EXTI0_IRQVEC     ((void (**) (void) ) 0x2001C058 )
#define NVIC_ISER0       ((volatile unsigned int *) 0xE000E100)

#define NVIC_EXTI3_IRQ_BPOS     (1<<9)
#define NVIC_EXTI2_IRQ_BPOS     (1<<8)
#define NVIC_EXTI1_IRQ_BPOS     (1<<7)
#define NVIC_EXTI0_IRQ_BPOS     (1<<6)
#define EXTI3_IRQ_BPOS          (1<<3)
#define EXTI2_IRQ_BPOS          (1<<2)
#define EXTI1_IRQ_BPOS          (1<<1)
#define EXTI0_IRQ_BPOS          (1<<0)

static volatile int count;

void irq_handler0 ( void )
{
    /* Om avbrott från EXTI0:
     * kvittera avbrott från EXTI0 */
    if( *EXTI_PR & EXTI0_IRQ_BPOS )
    {
        //count++;
        * EXTI_PR |= EXTI0_IRQ_BPOS;
        
        if ( *GPIO_E_IDR_LOW & 0x1 ){  //0001
            *GPIO_E_ODR_LOW |= 16;  //              ettställ PE4
            *GPIO_E_ODR_LOW &= ~16; // 10000 01111  nollställ PE4
            count++;
        }
    }
}

void irq_handler1 ( void )
{
    /* Om avbrott från EXTI1:
     * kvittera avbrott från EXTI1 */
    if( *EXTI_PR & EXTI1_IRQ_BPOS )
    {
        //count++;
        * EXTI_PR |= EXTI1_IRQ_BPOS;

        if ( *GPIO_E_IDR_LOW & 0x2){   //0010
            *GPIO_E_ODR_LOW |= 32;  // 100000        ettställ PE5
            *GPIO_E_ODR_LOW &= ~32; // 100000 011111 nollställ PE5
            count = 0;
        }
    }
}
void irq_handler2 ( void )
{
    /* Om avbrott från EXTI2:
     * kvittera avbrott från EXTI2 */
    if( *EXTI_PR & EXTI2_IRQ_BPOS )
    {
        //count++;
        * EXTI_PR |= EXTI2_IRQ_BPOS;

        if ( *GPIO_E_IDR_LOW & 0x4){   //0100
            *GPIO_E_ODR_LOW |= 64;  // 1000000         ettställ PE6
            *GPIO_E_ODR_LOW &= ~64; // 1000000 0111111 nollställ PE5
            
            if ( *GPIO_D_ODR_LOW == 0xFF ){
                *GPIO_D_ODR_LOW = 0;
            } 
            else {
                *GPIO_D_ODR_LOW = 0xFF;
            }
        }
    }
}

void init_app(void){
    
    * ( (unsigned short *) 0x40021000) = 0x5500;        // GPIO_MODER E 
    * ( (unsigned char *) 0x40021010) = 0x0;        // GPIO_E_IDR_LOW
    * ( (unsigned char *) 0x40021014) = 0x0;        // GPIO_E_ODR_LOW


    * ( (unsigned char *) 0x40020C14) = 0x0;
    * ( (unsigned long *) 0x40020C00) = 0x00005555;  // GPIO_MODER D initieras

    /* koppla PE0, PE1, PE2 till EXTI*/
    *SYSCFG_EXTICR1 |= 0x0444;

    /* Konfigurera EXTI2, EXTI1, EXTI0 för att generera avbrott */
    * EXTI_IMR |= EXTI2_IRQ_BPOS;   
    * EXTI_IMR |= EXTI1_IRQ_BPOS;  
    * EXTI_IMR |= EXTI0_IRQ_BPOS;   
 

    * EXTI_RTSR |= EXTI2_IRQ_BPOS;
    * EXTI_RTSR |= EXTI1_IRQ_BPOS;
    * EXTI_RTSR |= EXTI0_IRQ_BPOS;

    * EXTI0_IRQVEC = irq_handler0;             //sätt upp avbrottsvektor 0
    * EXTI1_IRQVEC = irq_handler1;             //sätt upp avbrottsvektor 1
    * EXTI2_IRQVEC = irq_handler2;             //sätt upp avbrottsvektor 2

    /* konfig den bit i NVIC som kontrollerarar den avbrottslina som EXTI2 EXTI1 EXTI0 kopplats till */
    * NVIC_ISER0 |= NVIC_EXTI2_IRQ_BPOS;
    * NVIC_ISER0 |= NVIC_EXTI1_IRQ_BPOS;
    * NVIC_ISER0 |= NVIC_EXTI0_IRQ_BPOS;

}
void main(void)
{
    init_app();
    while(1){
        * GPIO_D_ODR_LOW = count;
    }
}


