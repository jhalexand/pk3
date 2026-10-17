/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKGameServerConnection.C
 *    DATE: Tue Oct  7 16:51:26 US/Eastern 1997
 *************************************************************************/
#include "PKGameServerConnection.h"

#include <Network/NetworkException.h>
#include <Network/NETReadWriteSocket.h>
#include <Network/NETStream.h>

/*************************************************************************
 * Function Name: PKGameServerConnection::PKGameServerConnection
 * Parameters: const char *host, unsigned short port
 * Effects: 
 *************************************************************************/

PKGameServerConnection::PKGameServerConnection(const char *host,
					       unsigned short port,
					       int socketNum)
  : NETStream()
{
  init(host, port, socketNum);
}


/*************************************************************************
 * Function Name: PKGameServerConnection::PKGameServerConnection
 * Parameters: const char *host, unsigned short port
 * Effects: 
 *************************************************************************/
void
PKGameServerConnection::init(const char *host,
			     unsigned short port,
			     int socketNum)
{
  NETReadWriteSocket *sock = new NETReadWriteSocket(host, port);
  attachTo(sock, socketNum);
}

/*************************************************************************
 * Function Name: PKGameServerConnection::~PKGameServerConnection
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKGameServerConnection::~PKGameServerConnection()
{
  delete attachedTo();
  detach();
}


/*************************************************************************
 * Function Name: PKGameServerConnection::PKGameServerConnection
 * Parameters: const char *host, unsigned short port
 * Effects: 
 *************************************************************************/
void
PKGameServerConnection::attachTo(NETReadWriteSocket *sock,
				 int socketNum)
{
  socketNum_ = socketNum;
  errno_ = 0 ;

  if(sock) {
    sock->setXcpHandler(NETERR::READ_NONE,
			PKGameServerConnection::static_readZero,
			this);
    sock->setXcpHandler(NETERR::SIGPIPE_RCVD,
			PKGameServerConnection::static_sigpipe,
			this);
  }

  NETStream::attachTo(sock);
}


/*************************************************************************
 * Function Name: PKGameServerConnection::
 * Parameters: const char *host, unsigned short port
 * Effects: 
 *************************************************************************/
void
PKGameServerConnection::detach()
{
  errno_ = 0;
  NETStream::detach();
}
