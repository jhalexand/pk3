/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEBall.C
 *    DATE: Sun Apr 27 17:50:08 US/Eastern 1997
 *************************************************************************/
#include "GEBall.h"
#include "GEWall.h"
#include "GEContainer.h"
#include "GEInjureTeamEvent.h"
#include "PKGameEngine.h"
#include <PKDimensions.h>
#include <PKInjuries.h>

/*************************************************************************
 * Function Name: GEBall::GEBall
 * Parameters: PKID id, PKTypeID type, GEContainer* cont, PKPoint& pos, PKVector& vect
 * Effects: 
 *************************************************************************/

GEBall::GEBall(PKID id,
			PKTypeID type,
			GEContainer* cont,
			PKPoint& pos,
			PKVector& vect,
			PKGameEngine* engine)
    : GEProjectile(id, type, PK_INJURY_NONE, cont,
			    PK_DIM_BALL_WIDTH, PK_DIM_BALL_HEIGHT,
			    pos, vect, engine)
{
}



/*************************************************************************
 * Function Name: GEBall::~GEBall
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEBall::~GEBall()
{
}


/*************************************************************************
 * Function Name: GEBall::intersect
 * Parameters: GEGameObject* obj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEBall::intersect(GEGameObject* obj)
{
    obj->intersectWithBall(this);
}


/*************************************************************************
 * Function Name: GEBall::intersectWithBall
 * Parameters: GEGameObject* ball
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEBall::intersectWithBall(GEGameObject* ball)
{
}


/*************************************************************************
 * Function Name: GEBall::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEBall::intersectWithWall(GEGameObject* wall)
{
    _engine->getPhysics()->bounceWithWall (this, wall); 
    _engine->broadcastUpdate (this);

    int team = ((GEWall*) wall)->getTeam();

    if (team != 0) //a wall with team 0 is either the top or bottom wall
	   //when ball hits wall, players lose 10% of their life
	   _engine->addEvent(new GEInjureTeamEvent(_engine, team, 10));
}


/*************************************************************************
 * Function Name: GEBall::intersectWithPlayer
 * Parameters: GEGameObject* player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEBall::intersectWithPlayer(GEGameObject* player)
{
  _engine->getPhysics()->bounceWithPlayer (this, player);
  _engine->broadcastUpdate (this);
}


/*************************************************************************
 * Function Name: GEBall::intersectWithProjectile
 * Parameters: GEGameObject* obj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEBall::intersectWithProjectile(GEGameObject* obj)
{
}


