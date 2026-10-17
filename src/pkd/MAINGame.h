
/*************************************************************************/
/*    NAME: Jeff Alexander                                               */
/*    FILE: MAINGame.h                                                   */
/*    ASGN: Final Project, silly                                         */
/*    DATE: Mon Apr 28 17:33:58 1997                                     */
/*************************************************************************/


#ifndef MAINGAME_HEADER
#define MAINGAME_HEADER

//#include "MAINServer.h"
//#include "MAINUser.h"
#include <Network/NETReadWriteSocket.h>
#include <PKids.h>
#include <PKGameClasses.h>

class MAINServer;
class MAINUser;

class MAINGame {
public:
    MAINGame(MAINServer *server);
    virtual ~MAINGame();

    int addUser(MAINUser *user);
    void removeUser(int userID);
    void removeDeadUser(int userID);
    void rejectUser(int playerNum);

    void setID(int gameID) { _gameID = gameID; }
    int  getID() const { return _gameID; }

    void setGameSocket(NETReadWriteSocket *socket);
    NETReadWriteSocket *getGameSocket() {return _serverSocket;}
    const PKGameParameters& getParams() const ;

    void respondToRequest();
    void announceAddAIPlayer(int whichUser, PKAILevel whichLevel);
    void announceSetTeam(int whichUser, int whichTeam);
    void announceSetPaddle(int whichUser, PKTypeID whichPaddle);
    void announceSetKombatKode(int whichUser, char *whichKode);
    void announceSetText(int whichUser, char *text);

    void announceGameCanceled();
    void announceGameStarted(const PKGameParameters& params);

    void attachUsersToGameServer(char *host, int port);
    void dumpAllUsers();

    PKGameProgress getProgress();

    void dealWithUserDied(MAINUser *theUser);

    MAINGame* getNext() const {return _next;}
    void setNext(MAINGame *game) {_next = game;}

protected:
    NETReadWriteSocket        *_serverSocket;
    int                        _gameID;
    MAINUser                 **_userArray;
    PKBackgroundID             _bgID;
    MAINGame                  *_next;
    MAINServer                *_mainServer;
    PKGameParameters           _gameParms;

private:
    boolean gameFull() const ;
    boolean gameStarted() const { return _serverSocket!=null; }
    void clearPlayer(int i);
};

#endif
