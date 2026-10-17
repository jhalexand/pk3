/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKClientNetworkInterface.C
 *    DATE: Sat Apr 26 15:33:14 US/Eastern 1997
 *************************************************************************/
#include "PKClientNetworkInterface.h"

#include "PKClientNetworkImplementation.h"

/*************************************************************************
 * Function Name: PKClientNetworkInterface::PKClientNetworkInterface
 * Parameters: PKClientInterface* client, XtAppContext app, char *hostname, int port, char *name, char *acct, char *local
 * Effects: 
 *************************************************************************/

PKClientNetworkInterface::PKClientNetworkInterface(PKClientInterface* client,
        XtAppContext app, const char *hostname, int port, 
        const char *name, const char *acct, const char *local)
{
  imp_ = new PKClientNetworkImplementation(client, app,
					   hostname, port,
					   name, acct, local);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::PKClientNetworkInterface
 * Parameters: PKClientInterface *client, XtAppContext app, char *hostname, int port, // of game server int playerNum
 * Effects: 
 *************************************************************************/

PKClientNetworkInterface::PKClientNetworkInterface(PKClientInterface *client,
        XtAppContext app, const char *hostname, int port, 
        int playerNum)
{
  imp_ = new PKClientNetworkImplementation(client, app,
					   hostname, port,
					   playerNum);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::hangup
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::hangup()
{
  imp_->hangup();
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::createGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::createGame()
{
  imp_->createGame();
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::joinGame
 * Parameters: int gameID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::joinGame(int gameID)
{
  imp_->joinGame(gameID);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::addAIPlayer
 * Parameters: int teamID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::addAIPlayer(int playerNum, PKAILevel aiLevel)
{
  imp_->addAIPlayer(playerNum, aiLevel);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::setTeam
 * Parameters: int teamID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::setTeam(int teamID)
{
  imp_->setTeam(teamID);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::setPaddle
 * Parameters: PKTypeID paddle
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::setPaddle(PKTypeID paddle)
{
  imp_->setPaddle(paddle);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::sendKombatKode
 * Parameters: char *kode
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::sendKombatKode(const char *kode)
{
  imp_->sendKombatKode(kode);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::sendChatText
 * Parameters: char *text
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::sendChatText(const char *text)
{
  imp_->sendChatText(text);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::rejectPlayer
 * Parameters: int playerNum
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::rejectPlayer(int playerNum)
{
  imp_->rejectPlayer(playerNum);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::cancelGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::cancelGame()
{
  imp_->cancelGame();
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::startGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::startGame()
{
  imp_->startGame();
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::ready
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::ready()
{
  imp_->ready();
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::sendAction
 * Parameters: PKID id, PKActionID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::sendAction(PKActionID action)
{
  imp_->sendAction(action);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::setTeam
 * Parameters: int playerNum, int teamID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::setTeam(int playerNum, int teamID)
{
  imp_->setTeam(playerNum, teamID);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::setPaddle
 * Parameters: int playerNum, PKTypeID paddle
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::setPaddle(int playerNum, PKTypeID paddle)
{
  imp_->setPaddle(playerNum, paddle);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::sendKombatKode
 * Parameters: int playerNum, char *kode
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::sendKombatKode(int playerNum, const char *kode)
{
  imp_->sendKombatKode(playerNum, kode);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::sendChatText
 * Parameters: int playerNum, char *text
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::sendChatText(int playerNum, const char *text)
{
  imp_->sendChatText(playerNum, text);
}


/*************************************************************************
 * Function Name: PKClientNetworkInterface::endGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClientNetworkInterface::endGame()
{
  imp_->endGame();
}


