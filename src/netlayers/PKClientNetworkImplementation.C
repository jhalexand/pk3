/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKClientNetworkImplementation.C
 *    DATE: Sat Apr 26 19:12:04 US/Eastern 1997
 *************************************************************************/
#include "PKClientNetworkImplementation.h"

#include "debug.h"

#include "CLIENTMainServer.h"
#include "CLIENTGameServer.h"
#include <Network/NETReadWriteSocket.h>
#include <Network/NETRequestID.h>
#include <Network/NetworkException.h>
#include <PKClientInterface.h>

/*************************************************************************
 * Function Name: PKClientNetworkImplementation::PKClientNetworkImplementation
 * Parameters: PKClientInterface* client, XtAppContext app, char *hostname, int port, char *name, char *acct, char *local
 * Effects: 
 *************************************************************************/

PKClientNetworkImplementation::PKClientNetworkImplementation(PKClientInterface*
        client, XtAppContext app, const char *hostname, int port, 
        const char *name, const char *acct, const char *local)
{
  client_ = client ;
  app_ = app ;

  main_ = new CLIENTMainServer(client_, app_, hostname, port, name,
			       acct, local, this);
  game_ = null ;
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::PKClientNetworkInterface
 * Parameters: PKClientInterface *client, XtAppContext app, char *hostname, int port, // of game server int playerNum
 * Effects: 
 *************************************************************************/

PKClientNetworkImplementation::PKClientNetworkImplementation(PKClientInterface
        *client, XtAppContext app, const char *hostname, int port, 
        int playerNum)
{
  client_ = client ;
  app_ = app;
  main_ = null;
  game_ = new CLIENTGameServer(client_, app_, hostname, port, playerNum, this);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::hangup
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::hangup()
{
  if(main_) {
    hangupOnMainServer() ;
  }
  if(game_) {
    hangupOnGameServer() ;
  }
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::hangupOnGameServer
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::hangupOnGameServer()
{
  if(game_) {
    dprintf(("hanging up on the game server\n"));
    game_->hangup();
    delete game_;
    game_ = null;
    client_->endGame();
  }
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::hangupOnMainServer
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::hangupOnMainServer()
{
  if(main_) {
    dprintf(("hanging up on the main server\n"));
    main_->hangup();
    delete main_;
    main_ = null;
  }
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::createGame
 * Parameters: 
 * Returns: void
 * Effects: will be answered by CREATE_GAME_ACK, which will set playerNum
 *          and gameID
 *************************************************************************/
void
PKClientNetworkImplementation::createGame()
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->createGame();
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::joinGame
 * Parameters: int gameID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::joinGame(int gameID)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->joinGame(gameID);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::addAIPlayer
 * Parameters: int gameID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::addAIPlayer(int playerNum, PKAILevel aiLevel)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->addAIPlayer(playerNum, aiLevel);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::setTeam
 * Parameters: int teamID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::setTeam(int teamID)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->setTeam(playerNum_, teamID);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::setPaddle
 * Parameters: PKTypeID paddle
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::setPaddle(PKTypeID paddle)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->setPaddle(playerNum_, paddle);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::sendKombatKode
 * Parameters: char *kode
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::sendKombatKode(const char *kode)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->sendKombatKode(playerNum_, kode);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::sendChatText
 * Parameters: char *text
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::sendChatText(const char *text)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->sendChatText(playerNum_, text);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::rejectPlayer
 * Parameters: int playerNum
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::rejectPlayer(int playerToReject)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->rejectPlayer(playerNum_, playerToReject);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::cancelGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::cancelGame()
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->cancelGame();
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::startGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::startGame()
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->startGame();
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::ready
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::ready()
{
  if(game_) game_->ready();
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::sendAction
 * Parameters: PKID id, PKActionID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::sendAction(PKActionID id)
{
  if(game_) game_->sendAction(id);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::attachToGameServer
 * Parameters: const char *host, int port
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::attachToGameServer(const char *host, int port)
{
  if(game_) delete game_;
  game_ = new CLIENTGameServer(client_, app_, host, port,
			       playerNum_, this);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::setTeam
 * Parameters: int playerNum, int teamID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::setTeam(int playerNum, int teamID)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->setTeam(playerNum, teamID);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::setPaddle
 * Parameters: int playerNum, PKTypeID paddle
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::setPaddle(int playerNum, PKTypeID paddle)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->setPaddle(playerNum, paddle);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::sendKombatKode
 * Parameters: int playerNum, char *kode
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::sendKombatKode(int playerNum, const char *kode)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->sendKombatKode(playerNum, kode);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::sendChatText
 * Parameters: int playerNum, char *text
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::sendChatText(int playerNum, const char *text)
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
    return;
  }
  main_->sendChatText(playerNum, text);
}


/*************************************************************************
 * Function Name: PKClientNetworkImplementation::endGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkImplementation::endGame()
{
  if(!main_) {
    client_->error("Connection to mainserver lost");
  }
  else {
    main_->endGame();
  }

  client_->endGame() ;
}
