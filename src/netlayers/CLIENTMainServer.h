/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: CLIENTGameServer.h                                  */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 30 22:26:43 1997                            */
/****************************************************************/


#ifndef CLIENTMAINSERVER_HEADER
#define CLIENTMAINSERVER_HEADER

#include <Network/NETStream.h>
class PKClientInterface ;
class PKClientNetworkImplementation;
#include <PKids.h>
#include <Xm/Xm.h>


class CLIENTMainServer {
private:
    PKClientInterface *client_;
    PKClientNetworkImplementation *ntwrk_;
    XtAppContext app_;
    XtInputId callbackID_;
    NETStream stream_;
    int userID_;
    int gameID_;

    static int errno_;

public:
    CLIENTMainServer(PKClientInterface* client, XtAppContext app,
            const char *hostname, int port,
            const char *name, const char *acct, const char *local,
            PKClientNetworkImplementation *ntwrk) ;
    virtual ~CLIENTMainServer();

    void hangup(); // called at any time

    void createGame(); // tell the server to create a new game
    void joinGame(int gameID); // try to join the given game
    void addAIPlayer(int playerNum, PKAILevel lvl);
    void setTeam(int playerNum, int teamID); // change the team
    void setPaddle(int playerNum, PKTypeID paddle); // the paddle id
    void sendKombatKode(int playerNum, const char *kode);
    void sendChatText(int playerNum, const char *text);
    void rejectPlayer(int playerNum, int toReject); // 0-3
    void cancelGame(); // actually cancel playing
    void startGame(); // actually start playing
    void endGame(); // notify end of game

    int gameID() { return gameID_; }
    //  int playerNum() { return playerNum_; }

private:
    const static int EREADNONE;
    const static int EREADTOOLITTLE;

    static void static_receive(void *thus, int*, XtInputId*) ;
    void receive();

    static void static_readException(void *thus) ;
    void readException();

    void connectAsClientAck();
    void addUser();
    void removeUser();
    void addGame();
    void removeGame();
    void createGameAck();
    void joinGameAck();
    void addPlayer();
    void removePlayer();
    void setTeamAck();
    void setPaddleAck();
    void sendKombatKodeAck();
    void sendChatTextAck();
    void rejectPlayerAck();

    void startGameAck();
    void cancelGameAck();
    void attachToGameServer();

} ;  

#endif
