/*
 * 
 * 
 * Structar för spelobjekt.
 * 
 * 
 */

#define MAX_POINTS 100 
/* Struct för en punkt */
typedef struct
{
	char x,y;
} POINT, *PPOINT;

/* Struct för en linje */
typedef struct
{
	POINT p0;
	POINT p1;
}LINE, *PLINE;

/* Struct för en labyrint */
typedef struct mz
{
	int numlines;
	LINE lines[MAX_POINTS];
	void (* draw ) (struct mz *);
}MAZE, *PMAZE;

/* Struct för en geometrisk form */
typedef struct
{
	int numpoints;
	int sizex;
	int sizey;	
	POINT px[ MAX_POINTS ];
} GEOMETRY, *PGEOMETRY; 

/* Struct för ett objekt */
typedef struct tObj
{
	PGEOMETRY geo;
	int posx,posy;
	void (* draw ) (struct tObj *);
	void (* clear ) (struct tObj *);
} OBJECT, *POBJECT; 

/* Struct för ett rörelseobjekt */
typedef struct mtObj
{
	POBJECT obj;
	int dirx,diry;
	void (* move ) (struct mtObj *);
	void (* set_speed ) (struct mtObj *, int, int);
} MOVABLEOBJECT, *PMOVABLEOBJECT; 
