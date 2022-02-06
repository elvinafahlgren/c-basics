/*
 * 
 * Logiska funktioner.
 * Undersöker överlappning.
 * 
 * 
 */

/* Undersök om två rektanglar överlappas */
int rect_overlap(POINT p0, POINT p1, POINT r0, POINT r1)
{
	/* Om något av objektens y-position befinner sig mellan det andra objektets y-position, undersök också... */	
	if(((p0.y <= r0.y) && (p1.y >= r0.y)) || ((r0.y <= p0.y) && (r1.y >= p0.y))){
		/* om något av objektens x-position befinner sig mellan det andra objektets x-position, returnera då 0. */	
		if( ((p0.x <= r0.x) && (p1.x >= r0.x)) || ((r0.x <= p0.x) && (r1.x >= p0.x)) )
			return 1;		
	}
		
	return 0;
}

/* Undersök om två objekt överlappar maze */
int rect_overlap_maze(POINT r0, POINT r1, PMAZE m)
{
	for(int i = 0; i < m->numlines; i++){
		if( (rect_overlap( (m->lines[i]).p0, (m->lines[i]).p1, r0, r1) )) 
			return 1;
	}
	return 0;
}

/* Undersök om objekt är utanför kanterna */
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
