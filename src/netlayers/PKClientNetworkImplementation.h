/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKGameClientImplementation.h                        */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 23 03:07:33 1997                            */
/****************************************************************/


#ifndef PKGAMECLIENTIMPLEMENTATION_HEADER
#define PKGAMECLIENTIMPLEMENTATION_HEADER

class CLIENTGameServer;
class CLIENTMainServer;
class NETReadWriteSocket;
#include <Network/NETStream.h>
class PKClientInterface;
#include <PKids.h>
#include <Xm/Xm.h>

class PKClientNetworkImplementation {
private:
  int playerNum_;
  CLIENTGameServer *game_;
  CLIENTMainServer *main_;
  PKClientInterface *client_;
  XtAppContext app_;
public:
  // construct the client
  PKClientNetworkImplementation(PKClientInterface* client, XtAppContext app,
				const char *hostname, int port,
				const char *name, const char *acct, const char *local) ;

  // construct connecting only to the game server
  PKClientNetworkImplementation(PKClientInterface *client, XtAppContext app,
				const char *hostname, int port,
				int playerNum);

  void setPlayerNumber(int pn) { playerNum_ = pn; }
  void hangup(); // called at any time, for example at C-c
  void hangupOnGameServer();
  void hangupOnMainServer();
  
  // functions to call during game setup (when you're first connected)
  void createGame(); // tell the server to create a new game
  void joinGame(int gameID); // try to join the given game
  void addAIPlayer(int playerNum, PKAILevel aiLevel);
  void setTeam(int teamID); // change the team
  void setPaddle(PKTypeID paddle); // the paddle id
  void sendKombatKode(const char *kode);
  void sendChatText(const char *text);
  void rejectPlayer(int playerNum); // 0-3
  void cancelGame(); // cancel the game in progress
  void startGame(); // start playing
  void endGame(); // end the game
  void ready(); // FIGHT!!


  // functions to call on ai clients
  void setTeam(int playerNum, int teamID); // change the team
  void setPaddle(int playerNum, PKTypeID paddle); // the paddle id
  void sendKombatKode(int playerNum, const char *kode);
  void sendChatText(int playerNum, const char *text);

  // send the action ID for processing by the server
  // We have to tell who did the action so that the server
  // knows who to tell to do the action (but we know that)
  void sendAction(PKActionID id);

  // open the game_ connection
  void attachToGameServer(const char *host, int port);
} ;

#endif
