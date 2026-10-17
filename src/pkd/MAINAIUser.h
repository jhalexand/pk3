/*************************************************************************/
/*    NAME: Jeff Alexander                                               */
/*    FILE: MAINUser.h                                                   */
/*    ASGN: Final Project                                                */
/*    DATE: Sat Apr 26 21:22:19 1997                                     */
/*************************************************************************/


#ifndef MAINAIUSER_HEADER
#define MAINAIUSER_HEADER

#include "MAINServer.h"
#include "MAINGame.h"
#include "MAINUser.h"
#include <Network/NETReadWriteSocket.h>
#include <PKids.h>
#include <PKGameClasses.h>

class MAINAIUser : public MAINUser {
public:
	MAINAIUser(int playerNum, MAINServer *server);
	virtual ~MAINAIUser() { }

        // we don't care about these anymore
        virtual void respondToRequest() { }
	virtual void userRejected(int whichUser) { }
	virtual void gameCanceled() { }
	virtual void gameStarted(const PKGameParameters&) { }
	virtual void attachToGameServer(const char*,int) { }
	virtual void userLeft(int) { }
	virtual void userJoined(int, const PKPlayerInfo&) { }
	virtual void addGameToList(int, const PKGameProgress&) { }
	virtual void deleteGameFromList(int) { }
	virtual void addUserToList(int, const char*, const char*, const char*) { }
	virtual void deleteUserFromList(int userID) { }

        // we still care about these, but we have no network to talk
        // to.
	virtual void userSetTeam(int whichUser, int whichTeam);
	virtual void userSetPaddle(int whichUser, PKTypeID whichPaddle);

        // hopefully, no one will call these
	virtual int fileDescriptor() {assert(false) ; return -1; }
	virtual NETReadWriteSocket* getSocket() {assert(false); return null;}

	virtual int getID() const { return playerNumber(); }
};
#endif
