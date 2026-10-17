/*************************************************************************/
/*    NAME:                                                              */
/*    FILE: MAINGameList.h                                               */
/*    ASGN:                                                              */
/*    DATE: Thu May  1 15:23:17 1997                                     */
/*************************************************************************/


#ifndef MAINGAMELIST_HEADER
#define MAINGAMELIST_HEADER

#include "MAINGame.h"
#include "MAINUser.h"

class MAINGameList {
public:
	MAINGameList();
	virtual ~MAINGameList();

	void insert(MAINGame *theGame);
	MAINGame* search(int gameID);
	void remove(int gameID);

	void informUserOfGames(MAINUser *theUser);
	void checkAndRemoveUser(MAINUser *theUser);

	void removeAllGamesFromClient(MAINUser *theUser);
	MAINGame* getGameBySocketAddress(int sockAddr);

	void printGames();
	
protected:
	MAINGame *_head;
};

#endif
