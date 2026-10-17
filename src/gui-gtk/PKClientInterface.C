/*************************************************************************
 *    NAME: Michael Pellauer
 *    USER: cs032082
 *    FILE: PKClientInterface.cxx
 *    DATE: Mon Apr 28  1:39:41 US/Eastern 1997
 *************************************************************************/
#include "PKClientInterface.h"
#include "PKClient.h"
#include "PKClientObject.h"
#include <PKKey.h>
#include <PKObject.h>
#include <PKids.h>
#include <PKGameClasses.h>
#include <PKGraphicsInterface.h>
#include <PKClientNetworkInterface.h>
#include <PKGameClasses.h>

/*************************************************************************/
/* Function Name: PKClientInterface::PKClientInterface                   */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

PKClientInterface::PKClientInterface(PKClient* imp)
{
  client_ = imp;
}

/*************************************************************************/
/* Function Name: PKClientInterface::handleKeyPress                      */
/* Parameters: PKKey key                                                 */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::handleKeyPress(PKKey key)
{
  client_->handleKeyPress(key);
}


/*************************************************************************/
/* Function Name: PKClientInterface::handleKeyRelease                    */
/* Parameters: PKKey key                                                 */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::handleKeyRelease(PKKey key)
{
  client_->handleKeyRelease(key);
}

PKClientObject*
PKClientInterface::getStateOfObject(PKID id)
{
  return client_->getStateOfObject(id);
}

/*************************************************************************/
/* Function Name: PKClientInterface::addUser                             */
/* Parameters: int userID, char* user, char* account, char* host         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::addUser(int userID, const char* user, 
        const char* account, const char* host)
{
  client_->addUser(userID, user, account, host);
}


/*************************************************************************/
/* Function Name: PKClientInterface::removeUser                          */
/* Parameters: int userID                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::removeUser(int userID)
{
  client_->removeUser(userID);
}


/*************************************************************************/
/* Function Name: PKClientInterface::addGame                             */
/* Parameters: int gameID, PKGameParameters parms                        */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::addGame(int gameID, const PKGameProgress& prog)
{
  client_->addGame(gameID, prog);
}


/*************************************************************************/
/* Function Name: PKClientInterface::removeGame                          */
/* Parameters: int gameID                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::removeGame(int gameID)
{
  client_->removeGame(gameID);
}


/*************************************************************************/
/* Function Name: PKClientInterface::enterGameSetup                      */
/* Parameters: int gameID, PKGameParameters parms                        */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::enterGameSetup(int gameID, const PKGameParameters& parms, 
        int playerNum)
{
  client_->enterGameSetup(gameID, parms, playerNum);
}

void
PKClientInterface::error(const char* err) {
  client_->error(err);
}

/*************************************************************************/
/* Function Name: PKClientInterface::addPlayer                           */
/* Parameters: int playerNum, PKPlayerInfo info                          */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::addPlayer(int playerNum, const PKPlayerInfo& info)
{
  client_->addPlayer(playerNum, info);
}


/*************************************************************************/
/* Function Name: PKClientInterface::removePlayer                        */
/* Parameters: int playerNum                                             */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::removePlayer(int playerNum)
{
  client_->removePlayer(playerNum);
}

void
PKClientInterface::rejectPlayer(int playerNum)
{
  client_->rejectPlayer(playerNum);
}


/*************************************************************************/
/* Function Name: PKClientInterface::setPaddle                           */
/* Parameters: int playerNum, PKTypeID paddle                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::setPaddle(int playerNum, PKTypeID paddle)
{
  client_->setPaddle(playerNum, paddle);
}


/*************************************************************************/
/* Function Name: PKClientInterface::setTeam                             */
/* Parameters: int playerNum, int team                                   */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::setTeam(int playerNum, int team)
{
  client_->setTeam(playerNum, team);
}

void
PKClientInterface::setKombatKode(int playerNum, const char* kode)
{
  //Do Later!!!
}

void
PKClientInterface::setChatText(int playerNum, const char* text)
{
  //Do Later!!!
}

void
PKClientInterface::returnToMainScreen()
{
  client_->returnToMainScreen();
}

/*************************************************************************/
/* Function Name: PKClientInterface::enterGamePlay                       */
/* Parameters: PKGameParameters parms, int numObjects, PKObject* obj     */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::enterGamePlay(const PKGameParameters& parms)
{
  client_->enterGamePlay(parms);
}


/*************************************************************************/
/* Function Name: PKClientInterface::cancel                              */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::cancel()
{
  client_->cancel();
}


/*************************************************************************/
/* Function Name: PKClientInterface::addObject                           */
/* Parameters: PKID unique, PKTypeID type, PKPoint pos                   */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::addObject(const PKObject& obj)
{
  client_->addObject(obj);
}


/*************************************************************************/
/* Function Name: PKClientInterface::removeObject                        */
/* Parameters: PKID id                                                   */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::removeObject(PKID id)
{
  client_->removeObject(id);
}


/*************************************************************************/
/* Function Name: PKClientInterface::update                              */
/* Parameters: PKObject obj                                              */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::update(const PKObject& obj)
{
  client_->update(obj);
}


/*************************************************************************/
/* Function Name: PKClientInterface::updateAnimation                     */
/* Parameters: PKID unique, PKAnimID id                                  */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::updateAnimation(PKID unique, PKAnimID id)
{
  client_->updateAnimation(unique, id);
}


/*************************************************************************/
/* Function Name: PKClientInterface::gameStatus                          */
/* Parameters: PKGameStatus stat                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
PKClientInterface::gameStatus(const PKGameStatus& stat)
{
  client_->gameStatus(stat);
}

void
PKClientInterface::endGame()
{
  client_->endGame();
}
