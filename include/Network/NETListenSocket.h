/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: ListenSocket.h                                      */
/*    ASGN:                                                     */
/*    DATE: Sun Apr 20 15:19:50 1997                            */
/****************************************************************/


#ifndef LISTENSOCKET_HEADER
#define LISTENSOCKET_HEADER
#include <netinet/in.h>

#include "InternetSocket.h"

class NETReadWriteSocket;


class NETListenSocket : private InternetSocket {
public:
  NETListenSocket(unsigned short port, int numConnections);
  virtual ~NETListenSocket();

  // returns a new ReadWriteSocket -- remember to delete it
  virtual NETReadWriteSocket *accept();

  // returns port or file descriptor of socket
  virtual int portNumber() { return socketName_.sin_port; }
  virtual int fileDescriptor() { return socket_; }
} ;  

#endif
