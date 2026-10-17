/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: InternetSocket.C
 *    DATE: Sun Apr 20 15:37:23 US/Eastern 1997
 *************************************************************************/
#include "InternetSocket.h"

#include "NetworkException.h"
#include <fcntl.h> // fcntl(.)
#include <sys/types.h> // AF_INET and the such
#include <sys/socket.h> // socket(.)
#include <unistd.h> // close(.)

const int InternetSocket::SOCKET_FAMILY = AF_INET;
const int InternetSocket::PACKET_SIZE   = 100 ;

/*************************************************************************
 * Function Name: init
 * Parameters: unsigned short port
 * Effects: 
 *************************************************************************/
void
InternetSocket::init(unsigned short port)
{
  socket_ = socket (SOCKET_FAMILY, SOCK_STREAM, 0);

  if (socket_ < 0) {
    throw NetworkException(socket_, NETERR::OPENFAILED, "Couldn't open a socket");
  }

  // we want forks to close the socket (otherwise, forked processes will
  // keep the port busy)
  fcntl(socket_, F_SETFD, ~0);

  // set up a valid socket name for an internet socket connection;
  socketName_.sin_family = SOCKET_FAMILY;

  // set the port; if 0, os chooses; otherwise, use "port"
  socketName_.sin_port = port;
}


/*************************************************************************
 * Function Name: InternetSocket::~InternetSocket
 * Parameters: 
 * Effects: 
 *************************************************************************/

InternetSocket::~InternetSocket()
{
  close(socket_);
}


