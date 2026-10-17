/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKGameServerInterface.C
 *    DATE: Sat Apr 26 16:21:51 US/Eastern 1997
 *************************************************************************/
#include "PKGameServerInterface.h"

#include "PKGameServerImplementation.h"


/*************************************************************************
 * Function Name: PKGameServerInterface::PKGameServerInterface
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKGameServerInterface::PKGameServerInterface(const char *host, int port, int gameID) 
{
  imp_ = new PKGameServerImplementation(host, port, gameID);
}


/*************************************************************************
 * Function Name: PKGameServerInterface::~PKGameServerInterface
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKGameServerInterface::~PKGameServerInterface()
{
  delete imp_;
}


/*************************************************************************
 * Function Name: PKGameServerInterface::receive
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::init(PKGameEngineInterface *engine) 
{
  imp_->init(engine);
}


/*************************************************************************
 * Function Name: PKGameServerInterface::receive
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::receive() 
{
  imp_->receive();
}


/*************************************************************************
 * Function Name: PKGameServerInterface::broadcastUpdate
 * Parameters: PKObject&
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::broadcastUpdate(PKObject& object)
{
  imp_->broadcastUpdate(object);
}


/*************************************************************************
 * Function Name: PKGameServerInterface::broadcastGameStatus
 * Parameters: PKGameStatus&
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::broadcastGameStatus(PKGameStatus& status)
{
  imp_->broadcastGameStatus(status);
}


/*************************************************************************
 * Function Name: PKGameServerInterface::broadcastAddObject
 * Parameters: PKObject&
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::broadcastAddObject(PKObject& toAdd)
{
  imp_->broadcastAddObject(toAdd);
}


/*************************************************************************
 * Function Name: PKGameServerInterface::broadcastRemoveObject
 * Parameters: PKID ID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::broadcastRemoveObject(PKID toRemove)
{
  imp_->broadcastRemoveObject(toRemove);
}
/*************************************************************************
 * Function Name: PKGameServerInterface::broadcastAnimateObject
 * Parameters: PKObject&, PKAnimID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::broadcastAnimateObject(PKID toAnimate,
					      PKAnimID anim)
{
  imp_->broadcastAnimateObject(toAnimate, anim);
}


/*************************************************************************
 * Function Name: PKGameServerInterface::broadcastPlaySound
 * Parameters: PKSoundID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::broadcastPlaySound(PKSoundID id)
{
  imp_->broadcastPlaySound(id);
}


/*************************************************************************
 * Function Name: PKGameServerInterface::broadcastPauseGame
 * Parameters:
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::broadcastPauseGame(boolean p)
{
  imp_->broadcastPauseGame(p);
}


/*************************************************************************
 * Function Name: PKGameServerInterface::broadcastEndGame
 * Parameters:
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerInterface::broadcastEndGame()
{
  imp_->broadcastEndGame();
}


/*************************************************************************
 * Function Name: PKGameServerInterface::numPlayers
 * Parameters: 
 * Returns: int
 * Effects: 
 *************************************************************************/
int
PKGameServerInterface::numPlayers() 
{
  return imp_->numPlayers();
}


/*************************************************************************
 * Function Name: PKGameServerInterface::paddles
 * Parameters: 
 * Returns: PKTypeID *
 * Effects: 
 *************************************************************************/
PKTypeID *
PKGameServerInterface::paddles()
{
  return imp_->paddles();
}


/*************************************************************************
 * Function Name: PKGameServerInterface::kode
 * Parameters: 
 * Returns: PKKombatKodeID
 * Effects: 
 *************************************************************************/
PKKombatKodeID
PKGameServerInterface::kode()
{
  return imp_->kode();
}


