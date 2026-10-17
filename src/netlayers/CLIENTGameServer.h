/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: CLIENTGameServer.h                                  */
/*    ASGN:                                                     */
/*    DATE: Thu May  1 00:18:24 1997                            */
/****************************************************************/


#ifndef CLIENTGAMESERVER_HEADER
#define CLIENTGAMESERVER_HEADER

#include <Network/NETStream.h>
class PKClientInterface;
class PKClientNetworkImplementation;
#include <PKids.h>
#include <Xm/Xm.h>


class CLIENTGameServer {
private:
  PKClientInterface *client_;
  PKClientNetworkImplementation *ntwrk_;
  NETStream stream_;
  int playerNum_;
  XtInputId callbackID_;
  boolean paused_;
  int errno_;
  
public:
  CLIENTGameServer(PKClientInterface* client, XtAppContext app,
		   const char *hostname, int port,
		   int playerNum, PKClientNetworkImplementation *ntwrk) ;
  virtual ~CLIENTGameServer();
  void ready(); // tell the game server that we're ready
  
  void hangup();

  void sendAction(PKActionID id);
private:
  static void static_receive(void *thus,int*,XtInputId*) {
    ((CLIENTGameServer*)thus)->receive();
  }
  void receive();

  static void static_readException(void *thus) {
    ((CLIENTGameServer*)thus)->readException();
  }
  void readException();

  static void static_brokenPipe(void *thus) {
    ((CLIENTGameServer*)thus)->brokenPipe();
  }
  void brokenPipe() ;

  void handleNoData() ;
  void handlePipe() ;
    
  
  void update();
  void gameStatus();
  void addObject();
  void removeObject();
  void animateObject();
  void playSound();
  void connectAck();
  void doStartPlay();
  void pauseGame();

} ;
#endif
