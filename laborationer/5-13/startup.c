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

typedef struct
{
	POINT p;
	char x,y;
	
} RECT, *PRECT;

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

int draw_rect( PRECT r )
{
	POINT start = r->p;
	char dx = r->x;
	char dy = r->y;
	
	//linje1
	char x0 = start.x;
	char y0 = start.y;
	char x1 = start.x + dx;
	char y1 = start.y;	
	LINE line1 = {x0,y0, x1,y1};
	draw_line(&line1);
	
	//linje2
	x1 = start.x;
	y1 = start.y + dy;
	LINE line2 = {x0,y0, x1,y1};
	draw_line(&line2);
	
	//linje3
	y0 = start.y + dy;
	x1 = start.x + dx;
	LINE line3 = {x0,y0, x1,y1};
	draw_line(&line3);
	
	//linje4
	x0 = start.x + dx;
	y0 = start.y;
	LINE line4 = {x0,y0, x1,y1};
	draw_line(&line4);
	

}

RECT rectangles[]={
{10,10, 20,10},
{25,25, 10,20},
{40,30, 70,20},
{60,35, 10,10},
{70,10, 5,5},
}; 

void main(void)
{
	graphic_initalize();
	graphic_clear_screen();

	while( 1 )
	{
		for( int i = 0; i< sizeof(rectangles)/sizeof( RECT ); i++)
		{
			draw_rect( &rectangles[i] );
			delay_milli( 500 );
		}
			graphic_clear_screen(); 
	}
}

