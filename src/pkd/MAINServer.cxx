/*************************************************************************
 *    NAME: Jeffrey Alexander
 *    USER: jla
 *    FILE: MAINServer.cxx
 *    DATE: Sun Apr 27 21:00:16 US/Eastern 1997
 *************************************************************************/
#include "MAINServer.h"
#include "MAINNetwork.h"
#include "MAINUserList.h"
#include "MAINGameList.h"
#include "MAINUser.h"
#include "MAINGame.h"

/*************************************************************************/
/* Function Name: MAINServer::MAINServer                                 */
/* Parameters: char *argv, int argc                                      */
/* Effects:                                                              */
/*************************************************************************/

MAINServer::MAINServer(int argc, char **argv)
{
	_network = new MAINNetwork(this);
	_lurkers = new MAINUserList(this);
	_games = new MAINGameList();
}


/*************************************************************************/
/* Function Name: MAINServer::~MAINServer                                */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

MAINServer::~MAINServer()
{
	delete _network;
	delete _lurkers;
	delete _games;
}

/*************************************************************************/
/* Function Name: MAINServer::startItUp                                  */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::startItUp()
{
	while (1) {
		_network->listen();
	}
}


/*************************************************************************/
/* Function Name: MAINServer::addUserToGame                              */
/* Parameters: MAINUser *user, int gameID                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
int
MAINServer::addUserToGame(MAINUser *user, int gameID)
{
	// don't need to acknowledge this... it is just called by the user
	MAINGame *theGame = _games->search(gameID);
	int playerNum;
	if (theGame) {
		playerNum = theGame->addUser(user);
		if (playerNum >= 0) {
			// if the game isn't full, and it isn't in progress
			user->setGame(theGame);
		}
	} else {
		playerNum = -3;  // -3 = Game does not exist
	}

	return playerNum;
}


/*************************************************************************/
/* Function Name: MAINServer::addUser                                    */
/* Parameters: MAINUser *user                                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::addUser(MAINUser *user)
{
	_lurkers->insert(user);
	// adding a user to the list should tell it about all current users
	// and all current games... userlist will have to know about server
	_lurkers->announceNewUser(user);
	dprintf(("I've just added a user to the lurkers list.  The new list is:\n"));
	_lurkers->printUsers();
}


/*************************************************************************/
/* Function Name: MAINServer::addGame                                    */
/* Parameters: MAINGame* game                                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::addGame(MAINGame* game)
{
	_games->insert(game);
	_lurkers->announceNewGame(game);
}


/*************************************************************************/
/* Function Name: MAINServer::removeUserFromList                         */
/* Parameters: int userID                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::removeUserFromList(int userID)
{
	_lurkers->remove(userID);
	_lurkers->announceDeleteUser(userID);
	dprintf(("I've just removed a user from the lurker list.  It is now:\n"));
	_lurkers->printUsers();
}


/*************************************************************************/
/* Function Name: MAINServer::deleteGame                                 */
/* Parameters: int gameID                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::deleteGame(int gameID)
{
	_games->remove(gameID);
	_lurkers->announceDeleteGame(gameID);
}

/*************************************************************************/
/* Function Name: MAINServer::announceChatText                           */
/* Parameters: char* text                                                 */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::announceChatText(int playerNum, char *text)
{
	_lurkers->announceChatText(playerNum, text);
}


/*************************************************************************/
/* Function Name: MAINServer::attachServerToGame                         */
/* Parameters: NETReadWriteSocket *socket, gameID, char *host, int port  */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::attachServerToGame(NETReadWriteSocket *socket, int gameID, char *host, int port)
{
	MAINGame* theGame = _games->search(gameID);
	if (gameID) {
		theGame->setGameSocket(socket);
		theGame->attachUsersToGameServer(host, port);
	}
}

/*************************************************************************/
/* Function Name: MAINServer::informUserOfGames                          */
/* Parameters: MAINUser* theUser                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::informUserOfGames(MAINUser *theUser)
{
	_games->informUserOfGames(theUser);
}

/*************************************************************************/
/* Function Name: MAINServer::checkAndRemoveUserFromGames                */
/* Parameters: MAINUser* theUser                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::checkAndRemoveUserFromGames(MAINUser *theUser)
{
	_games->checkAndRemoveUser(theUser);
}

/*************************************************************************/
/* Function Name: MAINServer::makeClientRemoveAll                        */
/* Parameters: MAINUser* theUser                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINServer::makeClientRemoveAll(MAINUser *theUser)
{
	_lurkers->removeAllUsersFromClient(theUser);
	_games->removeAllGamesFromClient(theUser);
}

/*************************************************************************/
/* Function Name: MAINServer::getGameBySocketAddress                     */
/* Parameters: int sockAddr                                              */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
MAINGame*
MAINServer::getGameBySocketAddress(int sockAddr)
{
	return _games->getGameBySocketAddress(sockAddr);
}
/*************************************************************************
 * Function Name: MAINServer::getGamePort
 * Parameters: 
 * Returns: int
 * Effects: 
 *************************************************************************/
int
MAINServer::getGamePort()
{
  return _network->getGamePort();
}


/*************************************************************************
 * Function Name: MAINServer::getClientPort
 * Parameters: 
 * Returns: int
 * Effects: 
 *************************************************************************/
int
MAINServer::getClientPort()
{
  return _network->getClientPort();
}


