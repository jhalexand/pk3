/*************************************************************************
 *    NAME: Jeffrey Alexander
 *    USER: jla
 *    FILE: MAINGame.cxx
 *    DATE: Mon Apr 28 21:17:41 US/Eastern 1997
 *************************************************************************/
#include "MAINGame.h"
#include "MAINServer.h"
#include "MAINUser.h"
#include <stdlib.h>
#include <Network/NETReadWriteSocket.h>
#include <Network/NETids.h>
#include <Network/NETStream.h>
#include <PKids.h>
#include <PKGameClasses.h>
#include "MAINdefs.h"
#include <PKConstants.h>
#include "MAINAIUser.h"

#if (defined(USEDPRINTF)) || (!defined(NDEBUG) && !defined(NODPRINTF))
#define dprintGame(str) { printf("[MAINGame %x] ", getID()); dprintf(str); }
#else
#define dprintGame(str)
#endif


/*************************************************************************/
/* Function Name: MAINGame::MAINGame                                     */
/* Parameters: int gameID                                                */
/* Effects:                                                              */
/*************************************************************************/

MAINGame::MAINGame(MAINServer *server)
{
    _userArray = new MAINUser*[PLAYERS_PER_GAME];
    _gameParms.setNumPlayers(PLAYERS_PER_GAME);

    for (int i=0;i<PLAYERS_PER_GAME;i++) {
        _userArray[i]=null;
        _gameParms.getPlayer(i).setPlayerNumber(-1);
        _gameParms.getPlayer(i).setPaddle(PK_TYPE_INVALID);
    }

    int bg = (rand() * 100) % NUM_BACKGROUNDS;
    _bgID = (PKBackgroundID)bg;
    _gameParms.setBackground(_bgID);

    _mainServer = server;
    _serverSocket = null;

    _gameParms.setKode(PK_KOMBAT_KODE_NONE);
}


/*************************************************************************/
/* Function Name: MAINGame::~MAINGame                                    */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

MAINGame::~MAINGame()
{
    // deleting a userArray does _not_ delete the users in it.
    delete[] _userArray;
}


/*************************************************************************/
/* Function Name: MAINGame::addUser                                      */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    int
MAINGame::addUser(MAINUser *user)
{
    int i, player;

    if(gameFull()) return -1;
    if(gameStarted()) return -2;

    // find the first empty slot for the user
    for (i = 0; i < PLAYERS_PER_GAME; i++) {
        if (!_userArray[i]) {
            _userArray[i] = user;
            player = i;
            break;
        }
    }

    user->setGame(this); // just to make sure
    user->setPlayerNumber(player);
    user->setLife(MAX_LIFE);
    _gameParms.getPlayer(player) = *user;

    // ???
    if(!user->isAI()) {
        _mainServer->makeClientRemoveAll(user);
    }


    // tell everybody else about this new player.
    for (i=0;i<PLAYERS_PER_GAME;i++) {
        if (_userArray[i] && (i != player)) {
            _userArray[i]->userJoined(player, *user);
        }
    }

    return player;
}


/*************************************************************************/
/* Function Name: MAINGame::removeUser                                   */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::removeUser(int userID)
{
    // tell everybody about the dead user (except the dead user
    // himself, who we just kill).
    for (int i=0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i]) {
            if (userID == _userArray[i]->getID()) {
                clearPlayer(i);
            } else {
                _userArray[i]->userLeft(userID);
            }
        }
    }
}
/*************************************************************************/
/* Function Name: MAINGame::removeDeadUser                               */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::removeDeadUser(int userID)
{
    for (int i=0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i]) {
            if (userID == _userArray[i]->getID()) {
                clearPlayer(i);
            }
        }
    }
}


/*************************************************************************/
/* Function Name: MAINGame::setGameSocket                                */
/* Parameters: NETReadWriteSocket *socket                                */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::setGameSocket(NETReadWriteSocket *socket)
{
    _serverSocket = socket;

    // acknowledge the connection
    dprintGame(("Acknowledging server connection\n"));

    _serverSocket->startRequest(NETRequest::CONNECT_AS_GAMESERVER_ACK);
    NETStream tmpStream(_serverSocket);
    tmpStream << getParams();
    _serverSocket->endRequest();
    dprintGame(("CONNECT_AS_GAME_SERVER_ACK sent\n"));
}


/*************************************************************************/
/* Function Name: MAINGame::respondToRequest                             */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::respondToRequest()
{
    // Does this do anything?
}


/*************************************************************************
 * Function Name: MAINGame::announceAddAIPlayer
 * Parameters: int whichUser, PKAILevel whichLevel
 * Returns: void
 * Effects:
 *************************************************************************/
void
MAINGame::announceAddAIPlayer(int whichUser, PKAILevel whichLevel)
{
    dprintGame(("Adding AI level %d as player %d\n", whichLevel,
            whichUser));
    if(_userArray[whichUser]) {
        dprintGame(("Slot %d already occupied; ignoring\n", whichUser));
        return;
    }
    MAINAIUser *ai = new MAINAIUser(whichUser, _mainServer);
    addUser(ai);
}


/*************************************************************************/
/* Function Name: MAINGame::announceSetTeam                              */
/* Parameters: int whichUser, int whichTeam                              */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::announceSetTeam(int whichUser, int whichTeam)
{
    for (int i = 0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i]) {
            _userArray[i]->userSetTeam(whichUser, whichTeam);
            dprintGame(("Player %d told to set player %d to team %d\n",
                    i, whichUser, whichTeam));
        }
    }
    // UPDATE GAME PARAMETERS TOO...
    _gameParms.getPlayer(whichUser).setTeam(_userArray[whichUser]->team());
    _gameParms.getPlayer(whichUser).setPaddle(_userArray[whichUser]->paddle());
}


/*************************************************************************/
/* Function Name: MAINGame::announceSetPaddle                            */
/* Parameters: int whichUser, PKTypeID whichPaddle                       */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINGame::announceSetPaddle(int whichUser, PKTypeID whichPaddle)
{
    // tell everybody to set their paddle appropriately
    for (int i = 0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i]) {
            _userArray[i]->userSetPaddle(whichUser, whichPaddle);
            dprintGame(("Player %d told to set player %d to paddle %d\n",
                    i, whichUser, whichPaddle));
        }
    }
    // UPDATE GAME PARAMETERS TOO...
    _gameParms.getPlayer(whichUser).setPaddle(_userArray[whichUser]->paddle());
}


/*************************************************************************/
/* Function Name: MAINGame::announceSetKombatKode                        */
/* Parameters: int whichUser, char *whichKode                            */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::announceSetKombatKode(int whichUser, char *whichKode)
{
    // UPDATE GAME PARAMETERS TOO...
    assert(false); // this is quite unimplemented...
    for (int i = 0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i] && (i != whichUser)) {
            _userArray[i]->userSetKombatKode(whichUser, whichKode);
        }
    }
}


/*************************************************************************/
/* Function Name: MAINGame::announceSetText                              */
/* Parameters: int whichUser, char *text                                 */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::announceSetText(int whichUser, char *text)
{
    for (int i = 0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i] && (i != whichUser)) {
            _userArray[i]->userSetText(whichUser, text);
        }
    }

}


/*************************************************************************/
/* Function Name: MAINGame::announceRejectUser                           */
/* Parameters: int whichUser                                             */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::rejectUser(int playerNum)
{
    dprintGame(("Rejecting user %d\n", playerNum));
    for (int i=0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i]) {
            _userArray[i]->userRejected(playerNum);
            if (playerNum == _userArray[i]->getID()) {
                if(!_userArray[i]->isAI()) {
                    _mainServer->addUser(_userArray[i]);
                }
                clearPlayer(i);
            }
        }
    }
}


/*************************************************************************/
/* Function Name: MAINGame::announceGameCanceled                         */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::announceGameCanceled()
{
    for (int i = 0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i]) {
            _userArray[i]->gameCanceled();
            if(!_userArray[i]->isAI()) {
                _mainServer->addUser(_userArray[i]);
            }
            clearPlayer(i);
        }
    }
}


/*************************************************************************/
/* Function Name: MAINGame::announceGameStarted                          */
/* Parameters: PKGameParameters params, int numObjs, PKObject[] objs     */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::announceGameStarted(const PKGameParameters& params)
{
    dprintGame(("Broadcasting start of game\n"));
    params.debugPrint();

    for (int i = 0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i]) {
            _userArray[i]->gameStarted(params);
        }
    }
}


/*************************************************************************/
/* Function Name: MAINGame::dumpAllUsers                                 */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::dumpAllUsers()
{
    for (int i=0;i<PLAYERS_PER_GAME;i++) {
        if (_userArray[i]) {
            if(!_userArray[i]->isAI()) {
                _mainServer->addUser(_userArray[i]);
            }
            clearPlayer(i);
        }
    }
}


/*************************************************************************/
/* Function Name: MAINGame::attachUsersToGameServer                      */
/* Parameters: char *host, int port                                      */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::attachUsersToGameServer(char *host, int port)
{
    dprintGame(("Telling clients about game server on %s:%d\n",
            host, port));
    for (int i = 0; i < PLAYERS_PER_GAME; i++) {
        if (_userArray[i]) {
            _userArray[i]->attachToGameServer(host, port);
        }
    }
}


/*************************************************************************/
/* Function Name: MAINGame::getParams()                                  */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
const PKGameParameters&
MAINGame::getParams() const 
{
    _gameParms.debugPrint();
    return _gameParms;
}


/*************************************************************************/
/* Function Name: MAINGame::getProgress()                                */
/* Parameters:                                                           */
/* Returns: PKGameProgress                                               */
/* Effects:                                                              */
/*************************************************************************/
    PKGameProgress
MAINGame::getProgress()
{
    unimplemented("Why do we need this?");
    PKGameProgress prog;
    if (_userArray[0]) {
        prog.setCreatorName(_userArray[0]->username());
    } else {
        // Creator of game is dead... game is gonna go away soon
        prog.setCreatorName("Dead game");
    }
    int players=0;
    for (int i=0;i<PLAYERS_PER_GAME;i++) {
        if (_userArray[i]) {
            players++;
        }
    }
    prog.setNumPlayers(players);
    return prog;
}

/*************************************************************************/
/* Function Name: MAINGame::dealWithUserDied                             */
/* Parameters: MAINUser *theUser                                         */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINGame::dealWithUserDied(MAINUser *theUser)
{
    dprintGame(("dealing with a dead user.\n"));
    dprintGame(("Creator %d ; dead user %d\n",
            _userArray[0]->getID(), theUser->getID()));

    if (_userArray[0]->getID() != theUser->getID()) {
        removeDeadUser(theUser->getID());
    } else {
        // if user is the one who created the game, the game has got to go
        dprintGame(("Creator destroying game\n"));

        // we're gonna just clear out _userArray[0]
        _userArray[0] = 0; // it's dead
        announceGameCanceled();

        for (int i=1;i<PLAYERS_PER_GAME;i++) { // note i = 1
            if (_userArray[i]) {
                if(!_userArray[i]->isAI()) {
                    _mainServer->addUser(_userArray[i]);
                }
            }
        }
        _mainServer->deleteGame(getID());
    }
}

boolean
MAINGame::gameFull() const {
    for (int i = 0; i < PLAYERS_PER_GAME; i++) {
        if (!_userArray[i]) {
            return false;
        }
    }
    return true;
}


void
MAINGame::clearPlayer(int i) {
    dprintGame(("Clearing player %d\n", i));
    if(_userArray[i]->isAI()) delete _userArray[i];
    _userArray[i] = null;
    _gameParms.getPlayer(i).setPlayerNumber(-1);
    _gameParms.getPlayer(i).setPaddle(PK_TYPE_INVALID);
}
