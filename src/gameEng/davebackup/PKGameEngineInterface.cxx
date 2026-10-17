/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: PKGameEngineInterface.cxx
 *    DATE: Thu Apr 24 21:36:44 US/Eastern 1997
 *************************************************************************/
#include <PKGameEngineInterface.h>
#include "PKGameEngine.h"

#include <iostream.h>

/*************************************************************************
 * Function Name: PKGameEngineInterface::PKGameEngineInterface
 * Parameters: PKGameServerInterface* server, int numplayers, PKTypeID
players[], PKKombatKodeID kode
 * Effects: 
 *************************************************************************/

PKGameEngineInterface::PKGameEngineInterface(PKGameServerInterface* server,
									int numplayers,
									PKTypeID players[],

PKKombatKodeID kode)
{
    _gameEngine = new PKGameEngine(server, numplayers, players, kode);
}


/*************************************************************************
 * Function Name: PKGameEngineInterface::~PKGameEngineInterface
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKGameEngineInterface::~PKGameEngineInterface()
{
    delete _gameEngine;
}


/*************************************************************************
 * Function Name: PKGameEngineInterface::mainloop
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameEngineInterface::mainloop()
{
    _gameEngine->mainloop();
}


/*************************************************************************
 * Function Name: PKGameEngineInterface::handleAction
 * Parameters: int id, PKActionID action
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameEngineInterface::handleAction(int id, PKActionID action)
{
    _gameEngine->handleAction(id, action);
}


/*************************************************************************
 * Function Name: PKGameEngineInterface::handleHangup
 * Parameters: int playerNum
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameEngineInterface::handleHangup(int playerNum)
{
    _gameEngine->handleHangup(playerNum);
}

