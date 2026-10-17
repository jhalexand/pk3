/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKGameClientInterface.h                             */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 23 03:07:33 1997                            */
/****************************************************************/


#ifndef PKGAMECLIENTINTERFACE_HEADER
#define PKGAMECLIENTINTERFACE_HEADER

class NETReadWriteSocket ;
#include <PKids.h>

class PKGameClientInterface {
private:
  NETReadWriteSocket *server_;
public:
  // we'll most likely need more params here
  PKGameClientInterface() ;

  // send the action ID for processing by the server
  // We have to tell who did the action so that the server
  // knows who to tell to do the action
  void sendAction(PKID id, PKActionID);

  // poll the socket for activity; deal with any such activity
  // throws a NETHangupException on an error or hangup
  void receive();  
} ;

#endif
