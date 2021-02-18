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
#include "image.h"
////////////////////////////////////////////////////////////////////////////////
// Builtin graphics functions
////////////////////////////////////////////////////////////////////////////////

__attribute__((naked))
void graphics_initialize ( void )
{
	__asm volatile ("  .HWORD  0xDFF0\n");
	__asm volatile ("  BX LR\n");
}

__attribute__((naked))
void graphics_clear_screen ( void )
{
	__asm volatile ("  .HWORD  0xDFF1\n");
	__asm volatile ("  BX LR\n");
}

__attribute__((naked))
void graphics_pixel_set ( int x, int y )
{
	__asm volatile ("  .HWORD  0xDFF2\n");
	__asm volatile ("  BX LR\n");
}

__attribute__((naked))
void graphics_pixel_clear ( int x, int y )
{
	__asm volatile ("  .HWORD  0xDFF3\n");
	__asm volatile ("  BX LR\n");
}

////////////////////////////////////////////////////////////////////////////////
// Your code goes here
////////////////////////////////////////////////////////////////////////////////

void main(void)
{
	graphics_initialize;
	graphics_clear_screen;
	
	gimp_image.width;
	
	for(int y = 0; y < gimp_image.height; y++)
	{
		for(int x = 0; x < gimp_image.width; x++)
		{
			if(gimp_image.pixel_data[(y * gimp_image.width + x) * 3] == 0) graphics_pixel_set(x, y);
		}
	}
}

