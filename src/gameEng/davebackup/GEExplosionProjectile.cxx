/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GEExplosionProjectile.cxx
 *    DATE: Sun May  4  6:18:23 US/Eastern 1997
 *************************************************************************/
#include "GEExplosionProjectile.h"
#include "GEContainer.h"
#include "GERemoveObjectEvent.h"
#include "PKGameEngine.h"

/*************************************************************************
 * Function Name: GEExplosionProjectile::GEExplosionProjectile
 * Parameters: PKID id, PKTypeID type, int injury, GEContainer* cont, int width, int height, PKPoint& pos, PKVector& vect, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GEExplosionProjectile::GEExplosionProjectile(PKID id,
					     PKTypeID type,
					     int injury,
					     GEContainer* cont,
					     int width,
					     int height,
					     PKPoint& pos,
					     PKVector& vect,
					     PKGameEngine* engine,
					     hrtime_t time)
    : GEProjectile(id, type, injury, cont, width, height, pos, vect, engine)
{
  _timer = gethrtime();
  _time_to_explode = time;
 
}


/*************************************************************************
 * Function Name: GEExplosionProjectile::~GEExplosionProjectile
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEExplosionProjectile::~GEExplosionProjectile()
{
}


/*************************************************************************
 * Function Name: GEExplosionProjectile::update
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEExplosionProjectile::update()
{
  if ((gethrtime() - _timer) > _time_to_explode)
    {
      GERemoveObjectEvent* roevent = new GERemoveObjectEvent(_engine, this);
    _engine->addEvent(roevent);
    }
}


