/*
 * 	startup-crt.c
 *  includes: _crt_init, _crt_deinit, _sbrk for malloc-support.
 *  template functions for stdio: 
 */

#include	<errno.h>
#include 	<sys/stat.h>
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<unistd.h>

#include 	<libmd407.h>

/* Lägg till h-filer */
#include	<objects.h>
#include	<object_functions.h>
#include	<logic_functions.h>
  
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=__stack_top\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL _crt_init\n");			/* init C-runtime library */
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(" BL _crt_deinit\n");			/* deinit C-runtime library */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

/* Drivrutiner för grafik display */
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


/* Geometrin för "GOAL:)" */
static GEOMETRY goal_geometry =
{
	83, 	/* numpoints */
	64,128, 	/* sizex,sizey */
	{
		/* px[0,1,2 ...] */
	{1,0},{2,0},{3,0},{4,0},{5,0},{9,0},{10,0},{11,0},{18,0},{22,0},{30,0},{31,0}, //12
	{0,1},{1,1},{5,1},{8,1},{9,1},{11,1},{12,1},{17,1},{18,1},{28,1},{31,1},{32,1},//12
	{0,2},{8,2},{12,2},{13,2},{17,2},{18,2},{19,2},{22,2},{32,2},//9
	{0,3},{3,3},{4,3},{5,3},{8,3},{13,3},{16,3},{17,3},{12,3},{32,3},//10
	{0,4},{5,4},{8,4},{13,4},{16,4},{17,4},{18,4},{19,4},{22,4},{28,4},{32,4},//11
	{0,5},{1,5},{5,5},{8,5},{9,5},{12,5},{13,5},{19,5},{22,5},{23,5},{24,5},{25,5},{32,5},//13
	{1,6},{2,6},{3,6},{4,6},{5,6},{9,6},{10,6},{11,6},{12,6},{16,6},{19,6},{31,6},{32,6},//13
	{5,7},{30,7},{31,7}//3
	}
};

/* Mål-objekt */
static OBJECT goal =
{
	&goal_geometry, /* geometrin för spelaren */
	81,54, 			/* initial startposition */
	draw_object,
	clear_object,
}; 

/* Labyrint */
static MAZE maze =
{
	18,
	{
	{0,14, 21,14},
	{52,29, 63,29},
	{94,29, 127,29},
	{13,29, 25,29},
	{58,40, 112,40},
	{26,47, 38,47},
	{79,51, 112,51},
	
	{38,0, 38,47},
    {52,0, 52,29},
    {63,8, 63,29},
    {79,8, 79,40},
    {94,8, 94,29},
    {108,8, 108,17},
    {117,8, 117,29},
    {13,29, 13,63},
    {58,40, 58,52},
    {112,40, 112,51},
    {79,51, 79,63}
	},
	draw_maze
};

/* Geometrin för en boll */
static GEOMETRY ball_geometry =
{
	12, 	/* numpoints */
	4,4, 	/* sizex,sizey */
	{
		/* px[0,1,2 ...] */
	{0,1},{0,2},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,1},{3,2}
	}
}; 

/* Player-objekt */
static OBJECT player_object = 
{
	&ball_geometry, /* geometrin för spelaren */
	2,4, /* initial startposition */
	draw_object,
	clear_object
};

/* Player-objekt som kan röra sig */
static MOVABLEOBJECT player =
{
	&player_object, /* geometrin för spelaren */
	0,0, 			/* initiala riktningskoordinater */
	move_object,
	set_object_speed
}; 

/* Huvudprogram */
int main(void)
{
	
	setvbuf(stdout, 0, _IONBF, 0);
    printf("\nWelcome to the Mazegame!\nTry find your way out.");	/* Välkomstmeddelande */
    char buffer[1];				/* Buffer för inmatning från keypad */
	char c; 					/* Sparar keypad-värdet */
	POBJECT finish = &goal;		/* Pekare till målet */
	PMAZE bounds = &maze;		/* Pekare till labyrint */
	PMOVABLEOBJECT adventurer = &player;	/* Pekare till spelare */
	graphic_initalize();		/* Initiera skärm*/
	graphic_clear_screen();		/* Renasar skärm */
	
	finish->draw( finish );		/* Rita ut mål */
	bounds->draw( bounds );		/* Rita ut labyrint */

	while( 1 )
	{
		adventurer->move( adventurer );
		if(read(KEYPAD, buffer, 1)){	/* Läs av keypad */
			c = buffer[0];
		}
		switch( c )
		{
			case 6: adventurer->set_speed( adventurer, 1, 0); break;
			case 4: adventurer->set_speed( adventurer, -1, 0); break;
			case 5: adventurer->set_speed( adventurer, 0, 0); break;
			case 2: adventurer->set_speed( adventurer, 0, -1); break;
			case 8: adventurer->set_speed( adventurer, 0, 1); break;
			default:
			adventurer->set_speed( adventurer, 0, 0); break;
		}
		
		/* Skapar points för att kunna undersöka om rektanglar överlappar */
		POINT p0 = {finish->posx, finish->posy};
		POINT p1 = {finish->posx + (finish->geo)->sizex, finish->posy + (finish->geo)->sizey};
		
		POINT r0 = {(adventurer->obj)->posx, (adventurer->obj)->posy};
		POINT r1 = {(adventurer->obj)->posx + ((adventurer->obj)->geo)->sizex, (adventurer->obj)->posy + ((adventurer->obj)->geo)->sizey};
		
		/* Om rektangel av spelar-objeket överlappar labyrinten eller åker utanför spelområdet */
		if(rect_overlap_maze(r0, r1, bounds)  || object_out( (adventurer->obj) )){
			printf("\nOuch!");
			adventurer->set_speed( adventurer, 0, 0);
			(adventurer->obj)->clear(adventurer->obj);
			set_object_position( adventurer->obj, 2, 4 );
		}		
		
		/* Om rektangel av spelar-objeket överlappar reklangel av mål-objektet, då vinner man */
		if( rect_overlap(p0, p1, r0, r1) ) 
		{
			printf("\nYou won! Contratulation!"); 
			break;
		}
	}
}





