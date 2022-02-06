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

/* struct för robot */
typedef struct rbt
{
	union{
		char ctrl;
		char RS:1,:2, EN:1, :2, IA:1, IE:1;
	};
	union{
		char status;	
		char :2, ER:1, :1, IP:1;
	};
	unsigned short reserved;
	unsigned short dataY;
	unsigned short dataX;
	unsigned short posY;
	unsigned short posX;
}ROBOT,*PROBOT;

ROBOT robot = {};

/* struct som innehåller två variabler x och y*/
typedef struct point
{
	unsigned short x;
	unsigned short y;
	struct point * next;
} POINT, *PPOINT;

/* Alternativ till bitfält */
#define ENBIT	(1<<3)
#define RSBIT	(1<<0)

/* robotarmens förflyttningsmetod */
void move_robot( ROBOT *p, unsigned short x, unsigned short y )
{
	/* Dataregistren initieras med målkoordinaterna */
	p->dataX = x;
	p->dataY = y;
	/* Roborarmen aktiveras */
	p->EN = 1;
	/* ? */
	p->ctrl |= ENBIT; /*Alternativ*/
	/* Vänta tills robotarmen nått målkoordinaterna */
	while( p->posX != x || p->posY != y );
	/* Deaktivera robotarmen */
	p->EN = 0;
	/* ? */
	p->ctrl &= ~ENBIT; /*Alternativ*/
}

void init_robot( ROBOT *p )
{
	p->RS = 1;
	/* ? */
	p->ctrl |= RSBIT; 	/* Alternativ */
	p->ctrl = 0;
	/* Placera robot i position (0,0)*/
	move_robot(p,0,0);
}
/* Koordinaterna som roboten skall förlyttas till */
POINT p4 = {36,39,0};
POINT p3 = {25,27,&p4};
POINT p2 = {12,14,&p3};
POINT p1 = {1,2,&p2};

extern void delayMS( unsigned short ms );

void main(void)
{
	/* Definiera robotarm */
	ROBOT *p = (ROBOT *) 0x1000000;
	/* definiera och initiera point */
	POINT *pt = &p1;
	unsigned short x,y;
	/* Initiera robot */
	init_robot( p );
	x = y = 0;
	while(pt != 0)
	{
		/* Förflytta robotarm till position x och y i pointern */
		move_robot( p , pt->x, pt->y );
		/* Efter avslutad förflyttning måste robotarmen vila i så 
		 * många millisekunder som är skillnaden i x-led under
		 * föregående förflyttningens */
		/* Beroende på om förflyttningen i x-led är större eller mindre
		 * järmfört med föregående*/
		if( pt->x > x )
			delayMS( pt->x - x);
		else if( pt->x < x) 
			delayMS( x - pt->x);
		x = pt->x;
		y = pt->y;
		pt = pt->next; /* måste inte detta göras också? */
	}
}

