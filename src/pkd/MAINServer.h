/*************************************************************************/
/*    NAME: Jeff Alexander                                               */
/*    FILE: MAINServer.h                                                 */
/*    ASGN: Final Proj                                                   */
/*    DATE:                                                              */
/*************************************************************************/

#ifndef MAIN_SERVER_HEADER
#define MAIN_SERVER_HEADER

//#include "MAINNetwork.h"
//#include "MAINUserList.h"
//#include "MAINGameList.h"

#include <Network/NETReadWriteSocket.h>


class MAINUser;
class MAINGame;
class MAINNetwork;
class MAINUserList;
class MAINGameList;

class MAINServer {
public:
	MAINServer(int argc, char **argv);
	virtual ~MAINServer();

	void startItUp();

	void addUser(MAINUser *user);
	void removeUserFromList(int userID);

	void addGame(MAINGame* game);
	int addUserToGame(MAINUser *user, int gameID);
	void deleteGame(int gameID);

	void attachServerToGame(NETReadWriteSocket *socket, int gameID, char *host, int port);

	void informUserOfGames(MAINUser *theUser);

	void announceChatText(int playerNum, char *text);
	
	// If a client dies, this will be called
	void checkAndRemoveUserFromGames(MAINUser *theUser);
	void makeClientRemoveAll(MAINUser* theUser);

	MAINGame* getGameBySocketAddress(int sockAddr);
  int getGamePort();
  int getClientPort();
protected:
	MAINNetwork*      _network;
	MAINUserList*     _lurkers;
	MAINGameList*     _games;

};

#endif
