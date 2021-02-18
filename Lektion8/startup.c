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
}

