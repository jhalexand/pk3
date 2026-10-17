/*************************************************************************/
/*    NAME: Jeff Alexander                                               */
/*    FILE: MAINUser.h                                                   */
/*    ASGN: Final Project                                                */
/*    DATE: Sat Apr 26 21:22:19 1997                                     */
/*************************************************************************/


#ifndef MAINUSER_HEADER
#define MAINUSER_HEADER

#include "MAINServer.h"
#include "MAINGame.h"
#include <Network/NETReadWriteSocket.h>
#include <PKids.h>
#include <PKGameClasses.h>

class MAINUser : public PKPlayerInfo {
protected:
  MAINUser() {} // for subclasses
public:
	MAINUser(NETReadWriteSocket *socket, int userID, MAINServer *server);
	virtual ~MAINUser();

	virtual void setGame(MAINGame *game);

	// Talk to the socket and see wassup
	virtual void respondToRequest();

	// send info out to the network... these should be called by the game
	// note that these all send ACK messages
	virtual void userSetTeam(int whichUser, int whichTeam);
	virtual void userSetPaddle(int whichUser, PKTypeID whichPaddle);
	virtual void userSetKombatKode(int whichUser, const char *whichKode);
	virtual void userSetText(int whichUser, const char *text);
	virtual void userRejected(int playerNum);
	virtual void userLeft(int whichUser);
	virtual void userJoined(int whichUser, const PKPlayerInfo& player);

	virtual void gameCanceled();
	virtual void gameStarted(const PKGameParameters& params);
	virtual void attachToGameServer(const char *host, int port);

	// these methods are called by the server when user is not in a
	// game
	virtual void addGameToList(int gameID, const PKGameProgress& progress);
	virtual void deleteGameFromList(int gameID);
	virtual void addUserToList(int userID, 
                const char *name, const char *account, const char *host);
	virtual void deleteUserFromList(int userID);

	virtual void addChatText(int playerNum, const char *text);
	
	virtual int fileDescriptor() {return _socket->fileDescriptor();}
	virtual NETReadWriteSocket* getSocket() {return _socket;}

	virtual int getID() const {return _userID;}

        virtual void setPaddle(PKTypeID) ;
        virtual void setTeam(int) ;


	virtual MAINUser* getNext() {return _next;}
	virtual void setNext(MAINUser *user) {_next = user;}

	virtual int isAI() const { return aiLevel() != PK_AI_HUMAN; }
	
protected:
	int                   _userID;
        NETReadWriteSocket   *_socket;
	MAINGame             *_game;
	MAINServer           *_server;
	MAINUser             *_next;
};
#endif
