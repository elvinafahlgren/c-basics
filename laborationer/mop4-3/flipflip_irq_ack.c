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

#define GPIO_D_ODR_LOW 	((volatile unsigned char *) 0x40020C14) // port D
#define GPIO_D_MODER 	((volatile unsigned long *) 0x40020C00)	// port D

#define GPIO_E_MODER 	((volatile unsigned short *) 0x40021000)  	// E
#define GPIO_E_IDR_LOW 	((volatile unsigned char *) 0x40021010) 	// E
#define GPIO_E_ODR_LOW 	((volatile unsigned char *) 0x40021014)  	// E



#define SYSCFG_EXTICR1          0x40013808
#define EXTI_IMR                0x40013C00
#define EXTI_RTSR               0x40013C08
#define EXTI_PR                 0x40013C14
#define NVIC_ISER0              0xE000E100
#define EXTI3_IRQ_BPOS          (1<<3)
#define EXTI3_IRQVEC            0x2001C064
#define NVIC_EXTI3_IRQ_BPOS     (1<<9)

static volatile int count;

void irq_handler ( void )
{
    /* Om avbrott från EXTI3:
     * kvittera avbrott från EXTI3 */
    if( *((unsigned int *) EXTI_PR) & EXTI3_IRQ_BPOS )
    {
        //count++;
        *((unsigned int *) EXTI_PR) |= EXTI3_IRQ_BPOS;
        
        if ( *GPIO_E_IDR_LOW & 0x1 ){  //0001
            *GPIO_E_ODR_LOW |= 16;  //              ettställ PE4
            *GPIO_E_ODR_LOW &= ~16; // 10000 01111  nollställ PE4
            count++;
        }
        if ( *GPIO_E_IDR_LOW & 0x2){   //0010
            *GPIO_E_ODR_LOW |= 32;  // 100000        ettställ PE5
            *GPIO_E_ODR_LOW &= ~32; // 100000 011111 nollställ PE5
            count = 0;
        }
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
    
    *((unsigned int *) SYSCFG_EXTICR1) |= 0x4000;
    *((unsigned int *) EXTI_IMR) |= EXTI3_IRQ_BPOS;   /* Konfigurera EXTI3 för att generera avbrott */
    *((unsigned int *) EXTI_RTSR) |= EXTI3_IRQ_BPOS;
    *((void (**) (void)) EXTI3_IRQVEC) = irq_handler;             //sätt upp avbrottsvektor
    *((unsigned int *) NVIC_ISER0) |= NVIC_EXTI3_IRQ_BPOS;
}
void main(void)
{
    init_app();
    while(1){
        * GPIO_D_ODR_LOW = count;
    }
}


