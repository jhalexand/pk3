/*************************************************************************
 *    NAME: Jeffrey Alexander
 *    USER: jla
 *    FILE: MAINGameList.cxx
 *    DATE: Thu May  1 15:34:09 US/Eastern 1997
 *************************************************************************/
#include "MAINGameList.h"
#include "MAINGame.h"
#include "MAINUser.h"

/*************************************************************************/
/* Function Name: MAINGameList::MAINGameList                             */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

MAINGameList::MAINGameList()
{
	_head = 0;
}


/*************************************************************************/
/* Function Name: MAINGameList::~MAINGameList                            */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

MAINGameList::~MAINGameList()
{
	delete _head;
}


/*************************************************************************/
/* Function Name: MAINGameList::insert                                   */
/* Parameters: MAINGame *theGame                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINGameList::insert(MAINGame *theGame)
{
	theGame->setNext(_head);
	_head = theGame;
}


/*************************************************************************/
/* Function Name: MAINGameList::search                                   */
/* Parameters: int gameID                                                */
/* Returns: MAINGame*                                                    */
/* Effects:                                                              */
/*************************************************************************/
MAINGame*
MAINGameList::search(int gameID)
{
	MAINGame *curr = _head;
	while (curr != 0) {
		if (curr->getID() == gameID) {
			return curr;
		}
		curr = curr->getNext();
	}
	return 0;
}


/*************************************************************************/
/* Function Name: MAINGameList::delete                                   */
/* Parameters: int gameID                                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINGameList::remove(int gameID)
{
	MAINGame *curr, *prev;
	curr = _head;
	if (curr) {
		if (curr->getID() == gameID) {
			_head = curr->getNext();
			delete curr;
		} else {
			while (curr) {
				if (curr->getID() == gameID) {
					prev->setNext(curr->getNext());
					delete curr;
					break;
				}
				prev = curr;
				curr = curr->getNext();
			}
		}
	}
}


/*************************************************************************/
/* Function Name: MAINGameList::informUserOfGames                        */
/* Parameters: MAINUser *theUser                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINGameList::informUserOfGames(MAINUser *theUser)
{
	MAINGame *curr = _head;
	// call theUser->addGameToList(int gameID, PKGameProgress progress)

	while (curr) {
		theUser->addGameToList(curr->getID(), curr->getProgress());
		curr = curr->getNext();
	}
}

/*************************************************************************/
/* Function Name: MAINGameList::checkAndRemoveUser                       */
/* Parameters: MAINUser *theUser                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINGameList::checkAndRemoveUser(MAINUser *theUser)
{
	MAINGame *curr = _head;
	while (curr) {
		MAINGame *next = curr->getNext();
		// WARNING: this might cause curr to be deleted!!
		curr->dealWithUserDied(theUser);
		curr = next;
	}
}

/*************************************************************************/
/* Function Name: MAINGameList::removeAllGamesFromClient                 */
/* Parameters: MAINUser *theUser                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINGameList::removeAllGamesFromClient(MAINUser *theUser)
{
	MAINGame *curr= _head;

	while (curr) {
		theUser->deleteGameFromList(curr->getID());
		curr = curr->getNext();
	}
}

/*************************************************************************/
/* Function Name: MAINGameList::getGameBySocketAddress                   */
/* Parameters: int sockAddr                                              */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
MAINGame*
MAINGameList::getGameBySocketAddress(int sockAddr)
{
	MAINGame *curr = _head;
	MAINGame *theOne = 0;

	while (curr) {
		if ((int)curr->getGameSocket() == sockAddr) {
			theOne = curr;
		}
		curr = curr->getNext();
	}
	return theOne;
}

/*************************************************************************/
/* Function Name: MAINGameList::printGames                               */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINGameList::printGames()
{
	MAINGame *curr = _head;

	while (curr) {
		printf("Here's a game: %d", curr->getID());
		
		curr = curr->getNext();
	}
}
