/*
 * libMD407
 * keypad_driver.c
 * Keypad connected to PD8-PD15
 * Driver for KEYPAD
 */
#include "libMD407.h"

static int keypad_init( int initval );

static void keypad_deinit( int deinitval);

static int keypad_read(char *ptr, int len);

DEV_DRIVER_DESC KeyPad =
{
	{"Keypad"},
	keypad_init,
	keypad_deinit,
	0,
	0,
	0,
	0,
	0,
	0,
	keypad_read
};

/* KEYPAD types and constants definitions */
#define GPIO_ODR_HIGH 	((volatile unsigned char *) 0x40020C15)            // höga pinnarna def 
#define GPIO_IDR_HIGH 	((volatile unsigned char *) 0x40020C11)
#define GPIO_MODER 		((volatile unsigned long *) 0x40020C00)
#define GPIO_OTYPER 	((volatile unsigned short *) 0x40020C04)
#define GPIO_PUPDR 		((volatile unsigned long *) 0x40020C0C)
#define GPIO_ODR_LOW 	((volatile unsigned char *) 0x40020C14)    

/* Define functions here */
static int keypad_init( int initval ){
	* ( (unsigned char *) 0x40020C15) = 0x0;
    * ( (unsigned char *) 0x40020C11) = 0x0;
    * ( (unsigned char *) 0x40020C14) = 0x0;
    
    * ( (unsigned long *) 0x40020C00) &= 0x0000FFFF;  // GPIO_MODER nollställs
    * ( (unsigned long *) 0x40020C00) |= 0x55005555;  // GPIO_MODER initieras
    * ( (unsigned short *) 0x40020C04) &= 0x00FF;       // GPIO_OTYPER nollställs & initieras
    
    * ( (unsigned long *) 0x40020C0C) &= 0x0000FFFF;       // GPIO_PUPDR nollställs
    * ( (unsigned long *) 0x40020C0C) |= 0x00AA0000;       // GPIO_PUPDR initieras
	
	return 1;
}

static void keypad_deinit( int deinitval){ }

/* Funktioner till keypad_read */

void ActivateRow(unsigned int row){
    switch (row) {
        case 1: * GPIO_ODR_HIGH = 0x10; break;
        case 2: * GPIO_ODR_HIGH = 0x20; break;
        case 3: * GPIO_ODR_HIGH = 0x40; break;
        case 4: * GPIO_ODR_HIGH = 0x80; break;
        default: *GPIO_ODR_HIGH = 0;
    }
}  

int ReadColumn(void){
    unsigned char c;
    c = * GPIO_IDR_HIGH;
    if ( c & 0x8 ) 
        return 0x4;
    if ( c & 0x4 ) 
        return 0x3;
    if ( c & 0x2 ) 
        return 0x2;
    if ( c & 0x1 ) 
        return 0x1;
    return 0;
}      

unsigned char keyb(void){
    unsigned char key[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0xC,0xE,0,0xF,0xD};
    unsigned int row, col;
    for (int row = 1; row <= 4; row++){
        ActivateRow(row);
        col = ReadColumn();
        if  (col != 0 ){
            ActivateRow(0);
            return key [ 4 * (row-1) + (col-1) ];
        }
    }
    ActivateRow(0);
    return 0xFF;
}

static int keypad_read(char *ptr, int len){
	char c = keyb();
	if( c == 0xFF )
		return 0;
	*ptr = c;
	return 1;
} 
