/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GESZProjectile.cxx
 *    DATE: Sat May  3 19:39:30 US/Eastern 1997
 *************************************************************************/
#include "GESZProjectile.h"
#include "PKGameEngine.h"
#include "GERemoveObjectEvent.h"
#include "GEPlayer.h"

/*************************************************************************
 * Function Name: GESZProjectile::GESZProjectile
 * Parameters: PKID id, PKTypeID type, int injury, GEContainer* cont, int width, int height, PKPoint& pos, PKVector& vect, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GESZProjectile::GESZProjectile(PKID id,
						 PKTypeID type,
						 int injury,
						 GEContainer* cont,
						 int width,
 						 int height,
						 PKPoint& pos,
						 PKVector& vect,
						 PKGameEngine* engine,
			       int seeking,
			       int teamToAttack)
    : GEProjectile (id, type, injury, cont, width, height, pos, vect, engine)
{
  _team_to_attack = teamToAttack;
  _seeking = seeking;
  _timer = gethrtime();
  engine->broadcastPlaySound (PK_SOUND_SUB_PROJ_THROW);

}


/*************************************************************************
 * Function Name: GESZProjectile::~GESZProjectile
 * Parameters: 
 * Effects: 
 *************************************************************************/

GESZProjectile::~GESZProjectile()
{
}


/*************************************************************************
 * Function Name: GESZProjectile::intersectWithPlayer
 * Parameters: GEGameObject* player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GESZProjectile::intersectWithPlayer(GEGameObject* player)
{
  ((GEPlayer *) player)->freeze();
  //GEProjectile::intersectWithPlayer(player);
  GERemoveObjectEvent* roevent = new GERemoveObjectEvent(_engine, this); 
  _engine->addEvent(roevent);
  _engine->broadcastPlaySound (PK_SOUND_SUB_PROJ_HIT);
}

void
GESZProjectile::intersectWithWall (GEGameObject *wall)
{
    GERemoveObjectEvent* roevent = new GERemoveObjectEvent(_engine, this); 
    _engine->addEvent(roevent);
}

void
GESZProjectile::update()
{

  if (!_seeking) return;
  if ((gethrtime() - _timer) > 250000000)
    {
      GEPlayer *player = _engine->choosePlayer (_team_to_attack);
      // Choose a player on the other team
      if (player == NULL) return;
      double len = length (_vector);
 
      PKPoint otherpos = player->getPosition();
      PKVector resultvector = otherpos - _pos;
      PKVector result = resultvector / length (resultvector);
      result = result * len;

      _vector = result;
      _engine->broadcastUpdate (this);
      _timer = gethrtime();
    }

}
 
