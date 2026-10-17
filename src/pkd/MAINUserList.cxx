/*************************************************************************
 *    NAME: Jeffrey Alexander
 *    USER: jla
 *    FILE: MAINUserList.cxx
 *    DATE: Thu May  1  1:59:15 US/Eastern 1997
 *************************************************************************/
#include "MAINUserList.h"
#include "MAINUser.h"
#include "MAINGame.h"
#include <PKGameClasses.h>

/*************************************************************************/
/* Function Name: MAINUserList::MAINUserList                             */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

MAINUserList::MAINUserList(MAINServer *theServer)
{
	_head = 0;
	_server = theServer;
}


/*************************************************************************/
/* Function Name: MAINUserList::~MAINUserList                            */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

MAINUserList::~MAINUserList()
{
	if (_head) {
		delete _head;
	}
}


/*************************************************************************/
/* Function Name: MAINUserList::insert                                   */
/* Parameters: MAINUser *user                                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUserList::insert(MAINUser *user)
{
	MAINUser *curr = _head;
	while (curr) {
		int newID = curr->getID();
		const char *name = curr->username();
		const char *account = curr->account();
		const char *host = curr->hostname();
		user->addUserToList(newID, name, account, host);
		curr = curr->getNext();
	}
	_server->informUserOfGames(user);
	user->setNext(_head);
	_head = user;
}


/*************************************************************************/
/* Function Name: MAINUserList::remove                                   */
/* Parameters: int userID                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUserList::remove(int userID)
{
	MAINUser *prev, *curr;
	curr = _head;
	if (curr) {
		if (curr->getID() == userID) {
			_head = _head->getNext();
		} else {
			prev = curr;
			curr = curr->getNext();
			while (curr != 0) {
				if (curr->getID() == userID) {
					prev->setNext(curr->getNext());
					break;
				}
				prev = curr;
				curr = curr->getNext();
			}
		}
	}
}


/*************************************************************************/
/* Function Name: MAINUserList::announceNewUser                          */
/* Parameters: MAINUser *user                                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUserList::announceNewUser(MAINUser *user)
{
	int newID = user->getID();
	const char *name = user->username();
	const char *account = user->account();
	const char *host = user->hostname();
	MAINUser* curr=_head;
	while (curr != 0) {
		curr->addUserToList(newID, name, account, host);
		curr = curr->getNext();
	}
}


/*************************************************************************/
/* Function Name: MAINUserList::announceDeleteUser                       */
/* Parameters: int userID                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUserList::announceDeleteUser(int userID)
{
	MAINUser* curr=_head;
	while (curr != 0) {
		curr->deleteUserFromList(userID);
		curr = curr->getNext();
	}
}


/*************************************************************************/
/* Function Name: MAINUserList::announceNewGame                          */
/* Parameters: MAINGame* game                                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUserList::announceNewGame(MAINGame* game)
{
	int newID = game->getID();
	PKGameProgress prog = game->getProgress();
	MAINUser *curr=_head;
	while (curr != 0) {
		curr->addGameToList(newID, prog);
		curr = curr->getNext();
	}
}


/*************************************************************************/
/* Function Name: MAINUserList::announceDeleteGame                       */
/* Parameters: int gameID                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUserList::announceDeleteGame(int gameID)
{
	MAINUser *curr=_head;
	while (curr != 0) {
		curr->deleteGameFromList(gameID);
		curr = curr->getNext();
	}
}

/*************************************************************************/
/* Function Name: MAINUserList::announceChatText                         */
/* Parameters: char *text                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUserList::announceChatText(int playerNum, char *text)
{
	MAINUser *curr = _head;
	while (curr != 0) {
		curr->addChatText(playerNum, text);
		curr = curr->getNext();
	}
}


/*************************************************************************/
/* Function Name: MAINUserList::removeAllUsersFromClient                 */
/* Parameters: MAINUser *theUser                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINUserList::removeAllUsersFromClient(MAINUser *theUser)
{
	MAINUser *curr=_head;

	while (curr != 0) {
		theUser->deleteUserFromList(curr->getID());
		curr = curr->getNext();
	}
}


/*************************************************************************/
/* Function Name: MAINUserList::printUsers                               */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects: print all the users in the list... use only for debugging    */
/*************************************************************************/
void
MAINUserList::printUsers()
{
	MAINUser *curr=_head;

	while (curr != 0) {
		printf("Here's a user: %s\n", curr->username());
		curr = curr->getNext();
	}
}
