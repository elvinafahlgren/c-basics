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
/* Port D */
#define 	PORT_D_BASE			0x40020C00
#define 	GPIO_D_MODER 		((volatile unsigned int *) 	(PORT_D_BASE))
#define 	GPIO_D_OTYPER 		((volatile unsigned short *)(PORT_D_BASE + 0x4))
#define 	GPIO_D_OSPEEDR 		((volatile unsigned int *)	(PORT_D_BASE + 0x8))
#define 	GPIO_D_PUPDR 		((volatile unsigned int *) 	(PORT_D_BASE + 0xC))
#define 	GPIO_D_IDR_LOW 		((volatile unsigned char *) (PORT_D_BASE + 0x10))
#define 	GPIO_D_IDR_HIGH 	((volatile unsigned char *) (PORT_D_BASE + 0x11))
#define 	GPIO_D_ODR_LOW 		((volatile unsigned char *) (PORT_D_BASE + 0x14)) 
#define 	GPIO_D_ODR_HIGH 	((volatile unsigned char *) (PORT_D_BASE + 0x15))

/* Port E */
#define 	PORT_E_BASE			0x40021000
#define 	GPIO_E_MODER 		((volatile unsigned int *) 	(PORT_E_BASE))
#define 	GPIO_E_OTYPER 		((volatile unsigned short *)(PORT_E_BASE + 0x4))
#define 	GPIO_E_OSPEEDR 		((volatile unsigned int *)	(PORT_E_BASE + 0x8))
#define 	GPIO_E_PUPDR 		((volatile unsigned int *) 	(PORT_E_BASE + 0xC))
#define 	GPIO_E_IDR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x10))
#define 	GPIO_E_IDR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x11))
#define 	GPIO_E_ODR_LOW 		((volatile unsigned char *) (PORT_E_BASE + 0x14)) 
#define 	GPIO_E_ODR_HIGH 	((volatile unsigned char *) (PORT_E_BASE + 0x15))


/* Port D */
#define 	GPIO_D_MODER 		((volatile unsigned int *) 	(0x40020C00))
#define 	GPIO_D_OTYPER 		((volatile unsigned short *)(0x40020C04))
#define 	GPIO_D_OSPEEDR 		((volatile unsigned int *)	(0x40020C08))
#define 	GPIO_D_PUPDR 		((volatile unsigned int *) 	(0x40020C0C))
#define 	GPIO_D_IDR_LOW 		((volatile unsigned char *) (0x40020C10))
#define 	GPIO_D_IDR_HIGH 	((volatile unsigned char *) (0x40020C11))
#define 	GPIO_D_ODR_LOW 		((volatile unsigned char *) (0x40020C14)) 
#define 	GPIO_D_ODR_HIGH 	((volatile unsigned char *) (0x40020C15))

/* Port E */
#define 	GPIO_E_MODER 		((volatile unsigned int *) 	(0x40021000))
#define 	GPIO_E_OTYPER 		((volatile unsigned short *)(0x40021004))
#define 	GPIO_E_OSPEEDR 		((volatile unsigned int *)	(0x40021008))
#define 	GPIO_E_PUPDR 		((volatile unsigned int *) 	(0x4002100C))
#define 	GPIO_E_IDR_LOW 		((volatile unsigned char *) (0x40021010))
#define 	GPIO_E_IDR_HIGH 	((volatile unsigned char *) (0x40021011))
#define 	GPIO_E_ODR_LOW 		((volatile unsigned char *) (0x40021014)) 
#define 	GPIO_E_ODR_HIGH 	((volatile unsigned char *) (0x40021015))

void init_app(void)
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


void main(void)
{
}

