/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: InternetSocket.h                                    */
/*    ASGN:                                                     */
/*    DATE: Sun Apr 20 15:30:53 1997                            */
/****************************************************************/


#ifndef INTERNETSOCKET_HEADER
#define INTERNETSOCKET_HEADER

#include <netinet/in.h>
#include <sys/socket.h>
#include "Vector.h"

class InternetSocket {
protected:
  sockaddr_in socketName_; // from in.h, socket name struct for TCP/IP sockets
  int socket_ ;

  // doesn't do anything
  InternetSocket() {}
  
  // gets a socket file descriptor and sets up part of socketName_
  void init(unsigned short port);

  // closes the socket
  virtual ~InternetSocket();

  void getsockname() {
    int size = sizeof(socketName_);
    ::getsockname(socket_, (sockaddr*)&socketName_, &size);
  }
  
  int portNumber() const {
    return socketName_.sin_port;
  }
  int fileDescriptor() const { return socket_; }
  
public:
  static const int SOCKET_FAMILY ;
  static const int PACKET_SIZE ;
} ;
  
#endif
