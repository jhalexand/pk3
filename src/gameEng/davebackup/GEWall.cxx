/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEWall.C
 *    DATE: Mon Apr 28 18:30:45 US/Eastern 1997
 *************************************************************************/
#include "GEWall.h"
#include <PKInjuries.h>

/*************************************************************************
 * Function Name: GEWall::GEWall
 * Parameters: PKID id, PKTypeID type, GEContainer* cont
 * Effects: 
 *************************************************************************/

GEWall::GEWall(PKID id,
			PKTypeID type,
			int team,
			GEContainer* cont,
			int width,
			int height,
			PKPoint pos,
			PKVector vect,
			PKGameEngine* engine)
    : GEGameObject(id, type, PK_INJURY_NONE, cont, width, height,
			    pos, vect, engine),
	 _team(team)
{
}


/*************************************************************************
 * Function Name: GEWall::~GEWall
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEWall::~GEWall()
{
}


/*************************************************************************
 * Function Name: GEWall::intersect
 * Parameters: GEGameObject* obj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEWall::intersect(GEGameObject* obj)
{
    obj->intersectWithWall(this);
}

