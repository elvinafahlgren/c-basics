/*
 * libMD407
 * asciidisplay_driver.c
 * Display connected to PE
 * Driver for ASCIIDISPLAY
 */
#include "libMD407.h"
static int asciidisplay_init( int initval );
static void asciidisplay_deinit( int deinitval);
static int asciidisplay_write(char *ptr, int len);

DEV_DRIVER_DESC AsciiDisplay =
{
	{"AsciiDisplay"},
	asciidisplay_init,
	asciidisplay_deinit,
	0,
	0,
	0,
	0,
	0,
	asciidisplay_write,
	0
};

/* ASCIIDISPLAY types and constants definitions */
#define STK_CTRL 	((volatile unsigned int *)(0xE000E010))
#define STK_LOAD 	((volatile unsigned int *)(0xE000E014))
#define STK_VAL 	((volatile unsigned int *)(0xE000E018))
#define SIMULATOR 

#define PORT_BASE 	0x40021000
/* Definiera word-adresser för initieringar */
#define portModer 	((volatile unsigned int *) (PORT_BASE))
#define portOtyper 	((volatile unsigned short *) (PORT_BASE + 0x4))
#define portOspeedr ((volatile unsigned int *) (PORT_BASE + 0x8))
#define portPupdr 	((volatile unsigned int *) (PORT_BASE + 0xC))
/* Definiera byte-adresser för data och stryrregister */
#define portIdrLow 	((volatile unsigned char *) (PORT_BASE + 0x10))
#define portIdrHigh ((volatile unsigned char *) (PORT_BASE + 0x11))
#define portOdrLow 	((volatile unsigned char *) (PORT_BASE + 0x14))
#define portOdrHigh ((volatile unsigned char *) (PORT_BASE + 0x15))
/* Definiera styrregister, detta är konstanter, bitmasker, inte adresser! */
#define B_E 		0x40	/* Enable-signal */
#define B_SELECT	4		/* Select ASCII-display */
#define B_RW 		2 		/* 0=Write, 1=Read */
#define B_RS 		1 		/* 0=Control, 1=Data */


/* Define functions here */
/* Adressera ASCII-dispay och ettställ de bitar som är 1 i x */
void ascii_ctrl_bit_set( unsigned char x ) 
{
	char c;
	c = *portOdrLow;	// c tilldelas det värde som portOdrLow pekar på
	*portOdrLow = B_SELECT | x | c;	// 0100 | 0001 | 0010 = 0111 ??? vad händer???
}

/* Adressera ASCII-display och nollställ de bitar som är 1 i x */
void ascii_ctrl_bit_clear( unsigned char x )
{
	char c;
	c = *portOdrLow;
	c = c & ~x;
	*portOdrLow = B_SELECT | c;
}

void ascii_write_controller( unsigned char c )
{
	ascii_ctrl_bit_set( B_E ); 		// E=1
	*portOdrHigh = c;
	ascii_ctrl_bit_clear( B_E );	// E=0
	delay_250ns();
}

char ascii_read_controller( void )
{
	char c;
	ascii_ctrl_bit_set( B_E );		// E=1
	delay_250ns();
	delay_250ns();
	c = *portIdrHigh;				// läs från inport
	ascii_ctrl_bit_clear( B_E );	// E=0
	return c;
}

char ascii_read_status( void )
{
	char c;
	*portModer = 0x00005555;
	ascii_ctrl_bit_set( B_RW );		// RW = 1
	ascii_ctrl_bit_clear( B_RS );	// RS = 0
	c = ascii_read_controller();
	*portModer = 0x55555555;
	return c;
}

char ascii_read_data( void )
{
	char c;
	*portModer = 0x00005555;
	ascii_ctrl_bit_set( B_RW );		// RW = 1
	ascii_ctrl_bit_set( B_RS );		// RS = 1
	c = ascii_read_controller();
	*portModer = 0x55555555;
	return c;
}

void ascii_write_cmd( unsigned char command )
{
	ascii_ctrl_bit_clear( B_RS );
	ascii_ctrl_bit_clear( B_RW );
	ascii_write_controller( command );
}

void ascii_write_data( unsigned char data )
{
	ascii_ctrl_bit_set( B_RS );
	ascii_ctrl_bit_clear( B_RW );
	ascii_write_controller( data );
}

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

void ascii_gotoxy( int x, int y)
{
	char adress = x - 1;
	if( y == 2)
		adress += 0x40;
	ascii_write_cmd( 0x80 | adress );		 
}

void ascii_write_char( unsigned char c )
{
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_data( c );
	delay_micro( 43 );
}



static int asciidisplay_init( int initval ){
	* ( (unsigned long *) (PORT_BASE)) = 0x55555555;  	// GPIO_MODER initieras
    * ( (unsigned short *) (PORT_BASE + 0x14)) = 0x0;	// initierar utgången 
	
	/* ascii_init */
	// Function set RS RW 0 0 1 1 N F X X		(N=0 -> 1rad, N=1 -> 2 rader) (F=0 -> 5x8 punkter, F=1 -> 5x11 punkter)
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_cmd( 0x38 );
	delay_micro( 39 );
	
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_cmd( 0xE ); /*00001110*/
	delay_micro( 39 );
	
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_cmd( 1 );
	delay_milli( 2 );
	
	while( ( ascii_read_status() & 0x80 ) == 0x80 );
	delay_micro( 8 );
	ascii_write_cmd( 0x6 );
	delay_micro( 39 );
	
	return 1;
}
static void asciidisplay_deinit( int deinitval){}

static int asciidisplay_write(char *ptr, int len){
	
	
	ascii_gotoxy(1,1);		// skriver endast till en rad
	
	while( len-- )
		ascii_write_char( *ptr++ );
	
	
	//ascii_gotoxy(1,2); vill vi läggt till att den byter rad när raden är full?
	return 1;	// för nu, kan behöva ändras
} 