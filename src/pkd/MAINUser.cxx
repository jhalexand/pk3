/*************************************************************************
 *    NAME: Jeffrey Alexander
 *    USER: jla
 *    FILE: MAINUser.cxx
 *    DATE: Sun Apr 27 21:00:23 US/Eastern 1997
 *************************************************************************/
#include "MAINUser.h"
#include "MAINGame.h"
#include "MAINServer.h"
#include "MAINdefs.h"
#include <debug.h>
#include <Network/NETReadWriteSocket.h>
#include <Network/NETids.h>
#include <Network/NETStream.h>
#include <PKids.h>
#include <PKGameClasses.h>
#include <PKConstants.h>
#include <sys/types.h>
#include <sys/utsname.h>

#if (defined(USEDPRINTF)) || (!defined(NDEBUG) && !defined(NODPRINTF))
#define dprintUser(str) { printf("[MAINUser %x] ", getID()); dprintf(str); }
#else
#define dprintUser(str)
#endif


/*************************************************************************/
/* Function Name: MAINUser::MAINUser                                     */
/* Parameters: NETReadWriteSocket *socket, int userID                    */
/* Effects:                                                              */
/*************************************************************************/

MAINUser::MAINUser(NETReadWriteSocket *socket, int userID, MAINServer *server)
{
	_socket = socket;
	_userID = userID;
	_server = server;
        setTeam(1);
	setPaddle(PK_TYPE_CYRAX_1);
}


/*************************************************************************/
/* Function Name: MAINUser::~MAINUser                                    */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

MAINUser::~MAINUser()
{
	delete _socket;
}


/*************************************************************************/
/* Function Name: MAINUser::setGame                                      */
/* Parameters: MAINGame *game                                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::setGame(MAINGame *game)
{
	_game = game;
}


/*************************************************************************/
/* Function Name: MAINUser::respondToRequest                             */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::respondToRequest()
{
	int request = _socket->getInt();

	dprintUser(("Got a request from a user: %d\n", request));
	if (request == NETRequest::CONNECT_AS_CLIENT) {
		// store info internally
		dprintUser(("...it was a CONNECT_AS_CLIENT request.\n"));
		setUsername(_socket->getString());
		setAccount(_socket->getString());
		setHostname(_socket->getString());
		// now i'm complete and server can tell everybody about me
		_server->addUser(this);

		_socket->startRequest(NETRequest::CONNECT_AS_CLIENT_ACK);
		_socket->sendInt(_userID);
		_socket->endRequest();
	} else if (request == NETRequest::CREATE_GAME) {
		// tell server to create a game with this as creator
		int userID = _socket->getInt();
		MAINGame* game = new MAINGame(_server);
		game->setID((int)game);
		int playerNum = game->addUser(this);
		_server->addGame(game);
// game will make client remove all when it adds the client... so make sure we
// don't tell the client to add anything after the server told it to remove
// everything.
//		_server->makeClientRemoveAll(this);
		_server->removeUserFromList(_userID);
//		_server->makeClientRemoveAll(this);

		// tell client we're all set
		PKGameParameters params = game->getParams();
                params.debugPrint();

		dprintUser(("Got CREATE_GAME...\n"));
		_socket->startRequest(NETRequest::CREATE_GAME_ACK);
		NETStream tmpStream(_socket);
		tmpStream << (int)game << playerNum << params;
		_socket->endRequest();
		dprintUser(("...CREATE_GAME_ACK has been sent out for player %d.\n", playerNum));
	} else if (request == NETRequest::JOIN_GAME) {
		// tell server to add user to game with this and game id
		dprintUser(("Got JOIN_GAME...\n"));
		int userID = _socket->getInt();
		int gameID = _socket->getInt();
//		_server->makeClientRemoveAll(this);
		int playerNum = _server->addUserToGame(this, gameID); // this sets _game
		dprintUser(("Assigning player number %d\n", playerNum));

		// fixed by bh Mon May  5 02:32:32 EDT 1997 to >=0 from !=-1
		PKGameParameters params;
		if (playerNum >= 0) { // otherwise error
			_server->removeUserFromList(userID);
			params = _game->getParams();
			_socket->startRequest(NETRequest::JOIN_GAME_ACK);
			NETStream tmpStream(_socket);
			tmpStream << playerNum << params;
			_socket->endRequest();
			dprintUser(("...JOIN_GAME_ACK has been sent out.\n"));
		} else { // there was a problem, send back the error
			_socket->startRequest(NETRequest::JOIN_GAME_REJECT_ACK);
			NETStream tmpStream(_socket);
			tmpStream << playerNum;
			_socket->endRequest();
			dprintUser(("...JOIN_GAME_REJECT_ACK has been sent out.\n"));
		}

	} else if (request == NETRequest::ADD_AI_PLAYER) {
	  // tell game to add an AI player
	  dprintUser(("Server got ADD_AI_PLAYER!\n"));
	  int playerNum = _socket->getInt();
	  PKAILevel aiLevel = (PKAILevel)_socket->getInt();
	  dprintUser(("ai player to be added as player %d, level %d\n",
		   playerNum, aiLevel));
 	  if(_game) {
 	    _game->announceAddAIPlayer(playerNum, aiLevel);
 	  }
	} else if (request == NETRequest::SET_TEAM) {
		// tell game to tell players to set team of this player
		// assign my own team
		int gameID = _socket->getInt();
		int playerNum = _socket->getInt();
		int teamID = _socket->getInt();

		if (_game) {
			//_team = teamID;
			// This now gets set in "userSetTeam" which is called by the
			// game object this user belongs too.  It is set based on which
			// user's team is being set, instead of which user actually made
			// the change (this is so that one user can set another user's
			// team -- for AI users)
			
			_game->announceSetTeam(playerNum, teamID);
		}
	} else if (request == NETRequest::SET_PADDLE) {
		// tell game to tell players to set paddle of this player
		// assign my own paddle
		int gameID = _socket->getInt();
		int playerNum = _socket->getInt();
		int paddleType = _socket->getInt(); // this is a PKTypeID actually

		if (_game) {
			setPaddle((PKTypeID)paddleType);
			_game->announceSetPaddle(playerNum, paddle());
		}
	} else if (request == NETRequest::SEND_KOMBAT_KODE) {
		// tell game to tell players to set kombat kode
		int gameID = _socket->getInt();
		int playerNum = _socket->getInt();
		char *kode = _socket->getString();
		if (_game) {
			_game->announceSetKombatKode(playerNum, kode);
		}
	} else if (request == NETRequest::SEND_CHAT_TEXT) {
		// tell game to send chat text
		int gameID = _socket->getInt();
		int playerNum = _socket->getInt();
		char *text = _socket->getString();
		if (_game) {
			_game->announceSetText(playerNum, text);
		} else {
			_server->announceChatText(playerNum, text);
		}
	} else if (request == NETRequest::REJECT_PLAYER) {
		// tell game to get rid of player and inform clients
		int gameID = _socket->getInt();
		int playerNum = _socket->getInt();
		int rejectedPlayer = _socket->getInt();

		if (_game) {
			_game->rejectUser(rejectedPlayer);
		}
	} else if (request == NETRequest::START_GAME) {
		// this does _not_ talk to the game...  tell the client to start up
		// the game server.  it'll then be linked to the game object and
		// that will tell all the users to connect to the game server
		int gameID = _socket->getInt();

		if (_game) {
			struct utsname unstruct;
			uname(&unstruct);
			char *hostname = unstruct.nodename;
			_socket->startRequest(NETRequest::START_GAME_ACK);
			NETStream tmpStream(_socket);
			tmpStream << _game->getParams() << hostname << _server->getGamePort();
			_socket->endRequest();
		}
	} else if (request == NETRequest::CANCEL_GAME) {
		// tell game to tell players to cancel game gathering
		// and somehow get rid of game object...
		int gameID = _socket->getInt();
		dprintUser(("CANCEL GAME WAS CALLED!!!!\n"));
		if (_game) {
			_game->announceGameCanceled(); // ACK is sent out here
			_game->dumpAllUsers();
			_server->deleteGame(gameID);
			_game = 0;
		}
	} else if (request == NETRequest::END_GAME) {
		// server should do the same thing server-side as in CANCEL_GAME
		// but it should not send a CANCEL_GAME to the clients..
		int gameID = _socket->getInt();
		dprintUser(("Ending the game...\n"));
		if (_game) {
			_game = 0;
		}
	}
		
	dprintUser(("---Done responding to user request---\n"));
}

/*************************************************************************/
/* Function Name: MAINUser::userSetTeam                                  */
/* Parameters: int whichUser, int whichTeam                              */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::userSetTeam(int whichUser, int whichTeam)
{
	if (whichUser != playerNumber()) { // this is not me, inform the client
		_socket->startRequest(NETRequest::SET_TEAM_ACK);
		_socket->sendInt(whichUser);
		_socket->sendInt(whichTeam);
		_socket->endRequest();
	} else { // this is me, the client knows
		setTeam(whichTeam);
	}
}

/*************************************************************************/
/* Function Name: MAINUser::userSetPaddle                                */
/* Parameters: int whichUser, PKTypeID whichPaddle                       */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::userSetPaddle(int whichUser, PKTypeID whichPaddle)
{
	if (whichUser != playerNumber()) {
		_socket->startRequest(NETRequest::SET_PADDLE_ACK);
		_socket->sendInt(whichUser);
		_socket->sendInt(whichPaddle);
		_socket->endRequest();
	} else { // this is me, the client knows
            setPaddle(whichPaddle);
        }
}


/*************************************************************************/
/* Function Name: MAINUser::userSetKombatKode                            */
/* Parameters: int whichUser, char *whichKode                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::userSetKombatKode(int whichUser, const char *whichKode)
{
	if (whichUser != _userID) {
		_socket->startRequest(NETRequest::SEND_KOMBAT_KODE_ACK);
		_socket->sendInt(whichUser);
		_socket->sendString(whichKode);
		_socket->endRequest();
	}
}


/*************************************************************************/
/* Function Name: MAINUser::userSetText                                  */
/* Parameters: int whichUser, char *text                                 */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::userSetText(int whichUser, const char *text)
{
	if (whichUser != _userID) {
		_socket->startRequest(NETRequest::SEND_CHAT_TEXT_ACK);
		_socket->sendInt(whichUser);
		_socket->sendString(text);
		_socket->endRequest();
	}
}


/*************************************************************************/
/* Function Name: MAINUser::userRejected                                 */
/* Parameters: int whichUser                                             */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::userRejected(int playerNum)
{
    dprintUser(("Sending REJECT_PLAYER_ACK\n"));
    _socket->startRequest(NETRequest::REJECT_PLAYER_ACK);
    _socket->sendInt(playerNum);
    _socket->endRequest();

}


/*************************************************************************/
/* Function Name: MAINUser::gameCanceled                                 */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::gameCanceled()
{
	dprintUser(("Sending the acknowledgement to cancel (from MAINUser::gameCanceled)\n"));
	_socket->startRequest(NETRequest::CANCEL_GAME_ACK);
	_socket->endRequest();
}


/*************************************************************************/
/* Function Name: MAINUser::gameStarted                                  */
/* Parameters: PKGameParameters params, int numObjs, PKObject[] objs     */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::gameStarted(const PKGameParameters& params)
{
	_socket->startRequest(NETRequest::START_GAME_ACK);
	NETStream theStream(_socket);
	theStream << params;
	_socket->endRequest();
}

/*************************************************************************/
/* Function Name: MAINUser::attachToGameServer                           */
/* Parameters: char *host, int port                                      */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::attachToGameServer(const char *host, int port)
{
	_socket->startRequest(NETRequest::ATTACH_TO_GAME_SERVER);
	_socket->sendString(host);
	_socket->sendInt(port);
	NETStream theStream(_socket);
	theStream << _game->getParams();
	_socket->endRequest();
}


/*************************************************************************/
/* Function Name: MAINUser::userLeft                                     */
/* Parameters: int whichUser                                             */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::userLeft(int whichUser)
{
	dprintUser(("Sending a REMOVE_PLAYER request.\n"));
	_socket->startRequest(NETRequest::REMOVE_PLAYER);
	_socket->sendInt(whichUser);
	_socket->endRequest();
	dprintUser(("Sent a REMOVE_PLAYER request.\n"));
}


/*************************************************************************/
/* Function Name: MAINUser::userJoined                                   */
/* Parameters: int whichUser, PKPlayerInfo player                        */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::userJoined(int whichUser, const PKPlayerInfo& player)
{
	dprintUser(("Sending an ADD_PLAYER request.\n"));
	_socket->startRequest(NETRequest::ADD_PLAYER);
	NETStream theStream(_socket);
	theStream << whichUser << player;
	_socket->endRequest();
	dprintUser(("Sent an ADD_PLAYER request.\n"));
}


/*************************************************************************/
/* Function Name: MAINUser::addGameToList                                */
/* Parameters: gameID                                                    */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::addGameToList(int gameID, const PKGameProgress& progress)
{
	_socket->startRequest(NETRequest::ADD_GAME);
	NETStream theStream(_socket);
	theStream << gameID << progress;
	_socket->endRequest();
}


/*************************************************************************/
/* Function Name: MAINUser::deleteGameFromList                           */
/* Parameters: gameID                                                    */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::deleteGameFromList(int gameID)
{
	_socket->startRequest(NETRequest::REMOVE_GAME);
	_socket->sendInt(gameID);
	_socket->endRequest();
}


/*************************************************************************/
/* Function Name: MAINUser::addUserToList                                */
/* Parameters: userID, char *name, char *account, char *host             */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::addUserToList(int userID, 
        const char *name, const char *account, const char *host)
{
	_socket->startRequest(NETRequest::ADD_USER);
	_socket->sendInt(userID);
	_socket->sendString(name);
	_socket->sendString(account);
	_socket->sendString(host);
	_socket->endRequest();
}


/*************************************************************************/
/* Function Name: MAINUser::deleteUserFromList                           */
/* Parameters: userID                                                    */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUser::deleteUserFromList(int userID)
{
	_socket->startRequest(NETRequest::REMOVE_USER);
	_socket->sendInt(userID);
	_socket->endRequest();
	dprintUser(("Telling a user to delete someone from user list\n"));
}

/*************************************************************************/
/* Function Name: MAINUser::addChatText                                  */
/* Parameters: char *text                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void MAINUser::addChatText(int playerNum, const char *text)
{
	_socket->startRequest(NETRequest::SEND_CHAT_TEXT_ACK);
	_socket->sendInt(playerNum);
	_socket->sendString(text);
	_socket->endRequest();
}


void
MAINUser::setPaddle(PKTypeID paddle)
{
    PKTypeID leftPaddle = (PKTypeID)((paddle%2) ? paddle : (paddle-1));
    if(team() % 2) {
        PKPlayerInfo::setPaddle(leftPaddle);
    } else {
        PKPlayerInfo::setPaddle( (PKTypeID)(leftPaddle+1) );
    }
}

void
MAINUser::setTeam(int team)
{
    PKPlayerInfo::setTeam(team);
    setPaddle(paddle()); // fix the paddle
}
