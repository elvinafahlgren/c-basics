/*
 * 
 * 
 * Funtioner som tillhör objekten.
 * Målar ut, rensar, flyttar, sätter hastighet och position.
 * 
 */
/* Rita ett objekt */
void draw_object( POBJECT o)
{	
	int currentposx = o->posx;
	int currentposy = o->posy;
	
	/* Gå igenom objektets point-lista och ritar ut varje pixel för nuvarande positon */
	for(int i = 0; i < (o->geo)->numpoints; i++)
	{
		POINT currentp = (o->geo)->px[i];
		graphic_pixel_set(currentposx + currentp.x, currentposy + currentp.y);		
	} 
}

/* Rita en linje */
void draw_straght_line( PLINE l )
{
	
	POINT start = l->p0;
	POINT end = l->p1;
	
	int x0 = start.x;
	int x1 = end.x;
	int y0 = start.y;
	int y1 = end.y;
	
	/* Rita ut varje pixel mellan de två punkterna */
	for(int x = x0; x <= x1; x++){
		
		for(int y = y0; y <=y1; y++){
			graphic_pixel_set(x,y);
		}
	}	
}

/* Rita labyrint, använder draw_straght_line för att rita ut varje linje */
void draw_maze(PMAZE m)
{
	for(int i = 0; i < m->numlines; i++){
		draw_straght_line( &(m->lines[i]) );
	}
}

/* Rensar objektet från skärmen */
void clear_object( POBJECT o)
{	
	int currentposx = o->posx;
	int currentposy = o->posy;
	
	/* Gå igenom objektets point-lista och rensar varje pixel för nuvarande positon */
	for(int i = 0; i < (o->geo)->numpoints; i++)
	{
		POINT currentp = (o->geo)->px[i];
		graphic_pixel_clear(currentposx + currentp.x, currentposy + currentp.y);		
	} 
}

/* Flytta objekt */
void move_object(PMOVABLEOBJECT mo )
{
	/* Rensa objektet */
	clear_object( (mo->obj) );
	
	/* Sätter ny position */
	(mo->obj)->posx = ((mo->obj)->posx + mo->dirx);
	(mo->obj)->posy = ((mo->obj)->posy + mo->diry);
	
	/* Ritar ut på nytt */
	draw_object( mo->obj );
}

/* Ge objekt ny hastighet*/
void set_object_speed(PMOVABLEOBJECT mo, int speedx, int speedy)
{
	mo->dirx = speedx;
	mo->diry = speedy;
}

/* Ge objekt ny position*/
void set_object_position(POBJECT o, int x, int y)
{
	o->posx = x;
	o->posy = y;
}
