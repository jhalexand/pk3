/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: NETListenSocket.C
 *    DATE: Sun Apr 20 15:37:23 US/Eastern 1997
 *************************************************************************/
#include "NETListenSocket.h"

#include "NetworkException.h"
#include "NETReadWriteSocket.h"
#include <sys/types.h>  // INADDR_ANY and the such
#include <sys/socket.h> // bind(.), listen(.)

/*************************************************************************
 * Function Name: NETListenSocket::NETListenSocket
 * Parameters: unsigned short port, int numConnections
 * Effects: 
 *************************************************************************/

NETListenSocket::NETListenSocket(unsigned short port, int numConnections)
{
  InternetSocket::init(port);
  
  // allow anyone to call in
  socketName_.sin_addr.s_addr = INADDR_ANY;

// print gobs of debugging (uncomment when things go wrong)
/*
    printf(
"struct sockaddr_in {\n\
    sin_family          = %d\n\
    sin_addr.s_addr     = %d\n\
    sin_port            = %d\n\
} sockaddr;\n"
, socketName_.sin_family
, socketName_.sin_addr.s_addr
, ntohs(socketName_.sin_port)
    );
*/

  // register socket
  int result = bind ( socket_, (struct sockaddr*) &socketName_, 
		      sizeof (socketName_) );

  if (result<0) {
    throw NetworkException(socket_, NETERR::BINDFAILED, "server failed to bind socket");
  }

  // start accepting connections (only numConnections clients at a time)  
  listen(socket_, numConnections);

  InternetSocket::getsockname();
  
  dprintf(("server finished setting up socket on port %d, %d connections\n",
	  portNumber(), numConnections));
}


/*************************************************************************
 * Function Name: NETListenSocket::~NETListenSocket
 * Parameters: 
 * Effects: nothing the superclass destructor doesn't do
 *************************************************************************/

NETListenSocket::~NETListenSocket()
{
}


/*************************************************************************
 * Function Name: NETListenSocket::accept
 * Parameters: 
 * Returns: ReadWriteSocket *
 * Effects: creates a new ReadWriteSocket connected to a client.
 *************************************************************************/
NETReadWriteSocket *
NETListenSocket::accept()
{
  return new NETReadWriteSocket(::accept(socket_, null, 0));
}
