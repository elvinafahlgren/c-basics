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

#define GPIO_ODR_HIGH ((volatile unsigned char *) 0x40020C15)   
#define GPIO_IDR_HIGH ((volatile unsigned char *) 0x40020C11)
#define GPIO_MODER ((volatile unsigned long *) 0x40020C00)
#define GPIO_OTYPER ((volatile unsigned short *) 0x40020C04)
#define GPIO_PUPDR ((volatile unsigned long *) 0x40020C0C)

#define MAX_POINTS 25 

void init_app( void )
{
    * ( (unsigned char *) 0x40020C15) = 0x0;
    * ( (unsigned char *) 0x40020C11) = 0x0;
    
    * ( (unsigned long *) 0x40020C00) = 0x55005555;  // GPIO_MODER initieras
    * ( (unsigned short *) 0x40020C04) &= 0x00FF;       // GPIO_OTYPER nollställs & initieras
    
    * ( (unsigned long *) 0x40020C0C) &= 0x0000FFFF;       // GPIO_PUPDR nollställs
    * ( (unsigned long *) 0x40020C0C) |= 0x00AA0000;       // GPIO_PUPDR initieras

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



typedef struct
{
	char x,y;
} POINT, *PPOINT;

typedef struct
{
	int numpoints;
	int sizex;
	int sizey;
	POINT px[ MAX_POINTS ];
} GEOMETRY, *PGEOMETRY; 

typedef struct tObj
{
	PGEOMETRY geo;
	int dirx,diry;
	int posx,posy;
	void (* draw ) (struct tObj *);
	void (* clear ) (struct tObj *);
	void (* move ) (struct tObj *);
	void (* set_speed ) (struct tObj *, int, int);
} OBJECT, *POBJECT; 

void draw_object( POBJECT o)
{	
	int currentposx = o->posx;
	int currentposy = o->posy;
	
	for(int i = 0; i < (o->geo)->numpoints; i++)
	{
		POINT currentp = (o->geo)->px[i];
		graphic_pixel_set(currentposx + currentp.x, currentposy + currentp.y);		
	} 
}

void clear_object( POBJECT o)
{	
	int currentposx = o->posx;
	int currentposy = o->posy;
	
	for(int i = 0; i < (o->geo)->numpoints; i++)
	{
		POINT currentp = (o->geo)->px[i];
		graphic_pixel_clear(currentposx + currentp.x, currentposy + currentp.y);		
	} 
}

void move_ballobject(POBJECT o )
{
	clear_object( o );
	
	o->posx = (o->posx + o->dirx);
	o->posy = (o->posy + o->diry);
	
	if( o->posx < 1)
	{
		o->dirx = -1 * o->dirx;
		o->posx = 1;
	}
	
	if( ((o->posx + (o->geo)->sizex) ) > 128 )
	{
		o->dirx = -1 * o->dirx;
		o->posx = 128 - (o->geo)->sizex;
	}
	
	if( o->posy < 1)
	{
		o->diry = -1 * o->diry;
		o->posy = 1;
	}
	
	if( ((o->posy + (o->geo)->sizey) ) > 64 )
	{
		o->diry = -1 * o->diry;
		o->posy = 64 - (o->geo)->sizey;
	}
	
	draw_object( o );
}

void move_spiderobject(POBJECT o )
{
	clear_object( o );
	
	o->posx = (o->posx + o->dirx);
	o->posy = (o->posy + o->diry);
	
	draw_object( o );
}

/* om object o1 överlappar object o2 returnera 1, annars 0 */
int objects_overlap( POBJECT o1, POBJECT o2 )
{
	
	for(int i = 0; i < (o1->geo)->numpoints; i++)
	{
		POINT currentPo1 = (o1->geo)->px[i];
		int o1x = o1->posx + currentPo1.x;
		int o1y = o1->posy + currentPo1.y;
		
		for(int j = 0; j < (o2->geo)->numpoints; j++)
		{
			POINT currentPo2 = (o2->geo)->px[j];
			int o2x = o2->posx + currentPo2.x;
			int o2y = o2->posy + currentPo2.y;
			
			if((o1x == o2x) & (o1y == o2y))
				return 1;
		}	
	} 
	return 0;
}

int object_out( POBJECT o )
{
	if( o->posx < 1)
		return 1;
	
	if( ((o->posx + (o->geo)->sizex) ) > 128 )
		return 1;
		
	if( o->posy < 1)
		return 1;
	
	if( ((o->posy + (o->geo)->sizey) ) > 64 )
		return 1;
		
	return 0;	
}

void set_object_speed(POBJECT o, int speedx, int speedy)
{
	o->dirx = speedx;
	o->diry = speedy;
}

GEOMETRY ball_geometry =
{
 12, 	/* numpoints */
 4,4, 	/* sizex,sizey */
 {
		/* px[0,1,2 ...] */
	{0,1},{0,2},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,1}, {3,2}
 }
}; 

static OBJECT ball =
{
	&ball_geometry, /* geometri för en boll */
	0,0, /* initiala riktningskoordinater */
	1,1, /* initial startposition */
	draw_object,
	clear_object,
	move_ballobject,
	set_object_speed
}; 

GEOMETRY spider_geometry =
{
 22, 	/* numpoints */
 6,8, 	/* sizex,sizey */
 {
		/* px[0,1,2 ...] */
	{2,0},{3,0},{1,1},{4,1},{0,2},
	{1,2},{2,2},{3,2},{4,2},{5,2},
	{0,3},{2,3},{3,3},{5,3},{1,4},
	{4,4},{2,5},{3,5},{1,6},{4,6},{0,7},{5,7}
 }
}; 

static OBJECT spider =
{
	&spider_geometry, /* geometri för en spindel */
	0,0, /* initiala riktningskoordinater */
	64,32, /* initial startposition */
	draw_object,
	clear_object,
	move_spiderobject,
	set_object_speed
}; 

int main(void)
{
	char c;
	POBJECT victim = &ball;
	POBJECT creature = &spider;
	init_app();
	graphic_initalize();
	graphic_clear_screen();
	victim->set_speed( victim, 4, 1);

	while( 1 )
	{
		victim->move( victim );
		creature->move( creature );
		c = keyb();
		switch( c )
		{
			case 6: creature->set_speed( creature, 2, 0); break;
			case 4: creature->set_speed( creature, -2, 0); break;
			case 5: creature->set_speed( creature, 0, 0); break;
			case 2: creature->set_speed( creature, 0, -2); break;
			case 8: creature->set_speed( creature, 0, 2); break;
			default:
			creature->set_speed( creature, 0, 0); break;
		}
		if( objects_overlap( victim, creature ) || object_out( creature ) )
		{
		// Game over
			break;
		}
		delay_milli(20);
	}
}


