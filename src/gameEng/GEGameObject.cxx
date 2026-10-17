/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEGameObject.cxx
 *    DATE: Fri Apr 25 11:34:23 US/Eastern 1997
 *************************************************************************/
#include "GEGameObject.h"
#include "GEContainer.h"
#include "PKGameEngine.h"
#include <iostream.h>
#include <sys/time.h>

/*************************************************************************
 * Function Name: GEGameObject::GEGameObject
 * Parameters: PKID id, PKTypeID type, GEContainer* cont, PKPoint& pos, PKVector& vect
 * Effects: 
 *************************************************************************/

GEGameObject::GEGameObject(PKID id,
					  PKTypeID type,
					  int injury,
					  GEContainer* cont,
					  int width,
					  int height,
					  PKPoint& pos,
					  PKVector& vect,
					  PKGameEngine* engine)
    : PKObject(id, type, pos, vect), _cont(cont), _height(height),
	 _width(width), _heightAdjust(0), _widthAdjust(0), _engine(engine),
	 _injury(injury)
{
    _timestamp = gethrtime();
}

/*************************************************************************
 * Function Name: GEGameObject::GEGameObject
 * Parameters: int uniqueID, PKTypeID graphic, PKPoint* pos
 * Effects: 
 *************************************************************************/

GEGameObject::GEGameObject(PKID id,
					  PKTypeID type,
					  int injury,
					  GEContainer* cont,
					  int width,
					  int height,
					  PKGameEngine* engine)
    : PKObject(id, type), _cont(cont), _height(height), _width(width),
	 _heightAdjust(0), _widthAdjust(0), _engine(engine), _injury(injury)
{
    _timestamp = gethrtime();
}


/*************************************************************************
 * Function Name: GEGameObject::~GEGameObject
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEGameObject::~GEGameObject()
{
  // Broadcast a remove object on this id..
  setVector (PKVector (0, 0));
  _engine->broadcastUpdate (this);
   if ((getTypeID() != PK_TYPE_WALL_HORIZONTAL) &&
           (getTypeID() != PK_TYPE_WALL_VERTICAL))
  _engine->broadcastRemoveObject (_ID);
}


/*************************************************************************
 * Function Name: GEGameObject::adjustVelocity
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEGameObject::adjustVelocity()
{
    //default is to do nothing.
}

/*************************************************************************
 * Function Name: GEGameObject::operator==
 * Parameters: const GEGameObject &obj
 * Returns: int
 * Effects: returns whether or not two references to GEGameObjects
 * point to the same location.  This is needed for the RW lists.
 *************************************************************************/
int
GEGameObject::operator==(const GEGameObject &obj) const
{
    return (this == &obj);
}
