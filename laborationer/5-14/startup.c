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

#define STK_CTRL 	((volatile unsigned int *)(0xE000E010))
#define STK_LOAD 	((volatile unsigned int *)(0xE000E014))
#define STK_VAL 	((volatile unsigned int *)(0xE000E018))
#define SIMULATOR 

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
__attribute__((naked))
void graphic_initalize(void)
{
	__asm volatile (" .HWORD 0xDFF0\n");
	__asm volatile (" BX LR\n");
}

__attribute__((naked))
void graphic_clear_screen(void)
{
	__asm volatile (" .HWORD 0xDFF1\n");
	__asm volatile (" BX LR\n");
}


__attribute__((naked))
void graphic_pixel_set( int x, int y)
{
	__asm volatile (" .HWORD 0xDFF2\n");
	__asm volatile (" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_clear( int x, int y)
{
	__asm volatile (" .HWORD 0xDFF3\n");
	__asm volatile (" BX LR\n");
}

typedef struct
{
	char x,y;
} POINT, *PPOINT;

typedef struct
{
	POINT p0;
	POINT p1;
	
} LINE, *PLINE;

typedef struct polygonpoint
{
	char x,y;
	struct polygonpoint *next;
} POLYPOINT, *PPOLYPOINT;

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

int draw_line( PLINE l )
{
	
	POINT start = l->p0;
	POINT end = l->p1;
	
	int x0 = start.x;
	int x1 = end.x;
	int y0 = start.y;
	int y1 = end.y;
	
	int steep;
	
	if(abs(y1 - y0) > abs(x1 - x0))
		steep = 1;
	else
		steep = 0;
	
	if(steep)
	{
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	
	if(x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	
	int error = 0;
	int ystep;
	int y = y0;
	int deltax = x1 - x0;
	int deltay = abs(y1 - y0);
	
	if(y0 < y1)
		ystep = 1;
	else
		ystep = -1;
	
	for(int x = x0; x < x1; x++)
	{
		if(steep)
			graphic_pixel_set(y,x);
		else
			graphic_pixel_set(x,y);
			
		error = error + deltay;
		
		if(2 * error >= deltax)
		{
			y = y + ystep;
			error = error - deltax;
		}
	}
	
}

int draw_polygon( PPOLYPOINT p )
{
	POINT p0 = {p->x, p->y};
	PPOLYPOINT ptr = p->next;
	
	POINT p1;
	LINE line;
	
	while( ptr != 0 )
	{
		p1.x = ptr->x;
		p1.y = ptr->y;
		line.p0 = p0;
		line.p1 = p1;
		draw_line(&line);
		p0.x = p1.x;
		p0.y = p1.y;
		ptr = ptr->next;
	}
}

POLYPOINT pg8 = { 20,20, 0};
POLYPOINT pg7 = { 20,55, &pg8};
POLYPOINT pg6 = { 70,60, &pg7};
POLYPOINT pg5 = { 80,35, &pg6};
POLYPOINT pg4 = { 100,25, &pg5};
POLYPOINT pg3 = { 90,10, &pg4};
POLYPOINT pg2 = { 40,10, &pg3};
POLYPOINT pg1 = { 20,20, &pg2}; 


void main(void)
{
	graphic_initalize();
	graphic_clear_screen();

	while( 1 )
	{
		draw_polygon( &pg1 );
		delay_milli( 500 );
		graphic_clear_screen();
	}
} 


