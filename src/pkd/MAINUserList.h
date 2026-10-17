/*************************************************************************/
/*    NAME: Jeff Alexander                                               */
/*    FILE: MAINUserList.h                                               */
/*    ASGN: Final Project                                                */
/*    DATE: Thu May  1 01:27:18 1997                                     */
/*************************************************************************/


#ifndef MAINUSERLIST_HEADER
#define MAINUSERLIST_HEADER

#include "MAINUser.h"
#include "MAINGame.h"

class MAINUserList {
public:
	MAINUserList(MAINServer *theServer);
	virtual ~MAINUserList();

	void insert(MAINUser *user); // this must go through list, telling
	// *user about each user in the game.
	void remove(int userID); // take user out of the list

	void announceNewUser(MAINUser *user); // tell everybody else about the
	// newbie
	void announceDeleteUser(int userID); // tell everybody else about a
	// removal from the user list

	void announceNewGame(MAINGame* game); // tell everybody about a new game
	void announceDeleteGame(int gameID); // tell everybody to remove a game

	void announceChatText(int playerNum, char *text);

	void removeAllUsersFromClient(MAINUser *theUser);

	void printUsers();
	
protected:
	MAINUser      *_head;
	MAINServer    *_server;
};

#endif
