/*
 * libMD407
 * usart_driver.c
 * USART driver
 * Drivers for STDIN, STDOUT and STDERR
 */
 
#include "libMD407.h"

/* Define functions here */

static int usart_init( int initval );
static void usart_deinit( int deinitval);
static int usart_write(char *ptr, int len);
static int usart_read(char *ptr, int len);

DEV_DRIVER_DESC StdIn =
{
	{"stdin"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	0,
	usart_read
};

DEV_DRIVER_DESC StdOut =
{
	{"stdout"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	usart_write,
	0
};

DEV_DRIVER_DESC StdErr =
{
	{"stderr"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	usart_write,
	0
};

/* USART types and constants definitions */
.....

/* USART implementation */
static int usart_init( int initval ) { ... }
static void usart_deinit( int deinitval){ ... }
static int usart_write(char *ptr, int len){ ... }
static int usart_read(char *ptr, int len){ ... } 