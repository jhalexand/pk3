/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: NETReadWriteSocket.C
 *    DATE: Sun Apr 20 15:37:22 US/Eastern 1997
 *************************************************************************/
#include "NETReadWriteSocket.h"

#include "NetworkException.h"
#include <sys/types.h> // hostent
#include <sys/socket.h> // connect, getsockname, recv, send
#include <netdb.h> // gethostbyname

/*************************************************************************
 * Function Name: NETReadWriteSocket::NETReadWriteSocket
 * Parameters: const char *rhost, unsigned short port
 * Effects: 
 *************************************************************************/

NETReadWriteSocket::NETReadWriteSocket(const char *rhost, unsigned short port)
  : buffer_(0, PACKET_SIZE)
{
  InternetSocket::init(port);

  buffered_ = false ;


  // get the host from its name
  char *hostname = strdup(rhost);
  struct hostent *remote_host = gethostbyname(hostname);
  free(hostname);
  
  if ( remote_host == null ) {
    throw NetworkException(socket_, NETERR::CONNECTFAILED, "client failed to find host");
  }

  // copy the h_addr into sin_addr
  // whatever this does, it works
  memcpy(&socketName_.sin_addr, remote_host->h_addr,
	 remote_host->h_length );

  // go and connect
  int result = connect ( socket_, (struct sockaddr*) &socketName_, 
			 sizeof (socketName_) );
  if (result<0) {
    throw NetworkException(socket_, NETERR::CONNECTFAILED, "client failed to connect to host");
  }


  dprintf(("client finished setting up socket to %s port %d\n",
	 rhost, portNumber()));
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::NETReadWriteSocket
 * Parameters: int fileDescriptor
 * Effects: 
 *************************************************************************/

NETReadWriteSocket::NETReadWriteSocket(int fileDescriptor)
  : buffer_(0, PACKET_SIZE)
{
  buffered_ = false ;
  socket_ = fileDescriptor;
  int size = sizeof(socketName_);
  getsockname(socket_, (struct sockaddr*)&socketName_, &size);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::~NETReadWriteSocket
 * Parameters: 
 * Effects: 
 *************************************************************************/

NETReadWriteSocket::~NETReadWriteSocket()
{
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getChar
 * Parameters: 
 * Returns: char
 * Effects: 
 *************************************************************************/
char
NETReadWriteSocket::getChar() 
{
  char retBuf ;
  getStruct(&retBuf, sizeof(char));
  return retBuf;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getChar
 * Parameters: char& retBuf
 * Returns: char
 * Effects: 
 *************************************************************************/
char
NETReadWriteSocket::getChar(char& retBuf) 
{
  getStruct(&retBuf, sizeof(char));
  return retBuf;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getInt
 * Parameters: 
 * Returns: int
 * Effects: 
 *************************************************************************/
int
NETReadWriteSocket::getInt() 
{
  int retBuf;
  getStruct((char*)&retBuf, sizeof(int));
  return retBuf;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getInt
 * Parameters: int& retBuf
 * Returns: int
 * Effects: 
 *************************************************************************/
int
NETReadWriteSocket::getInt(int& retBuf) 
{
  getStruct((char*)&retBuf, sizeof(int));
  return retBuf;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getDouble
 * Parameters: 
 * Returns: double
 * Effects: 
 *************************************************************************/
double
NETReadWriteSocket::getDouble() 
{
  double retBuf;
  getStruct((char*)&retBuf, sizeof(double));
  return retBuf;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getDouble
 * Parameters: double& retBuf
 * Returns: double
 * Effects: 
 *************************************************************************/
double
NETReadWriteSocket::getDouble(double& retBuf)
{
  getStruct((char*)&retBuf, sizeof(double));
  return retBuf;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getString
 * Parameters: 
 * Returns: char *
 * Effects: 
 *************************************************************************/
char *
NETReadWriteSocket::getString() 
{
  int len = getInt();
  return (char*)getStruct(len);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getString
 * Parameters: char *retBuf
 * Returns: char *
 * Effects: 
 *************************************************************************/
char *
NETReadWriteSocket::getString(char *retBuf) 
{
  int len = getInt();
  return (char*)getStruct(retBuf, len);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getStruct
 * Parameters: size_t size
 * Returns: char *
 * Effects: 
 *************************************************************************/
void *
NETReadWriteSocket::getStruct(size_t size) 
{
  char *retBuf = (char*)malloc(size);
  return getStruct(retBuf, size);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::getStruct
 * Parameters: char *retBuf, size_t size
 * Returns: char *
 * Effects: reads a struct of size "size" from the socket.  Since the sender
 *          might not send it in one chunk, be nice and read in a bunch of
 *          packets.
 *************************************************************************/
void *
NETReadWriteSocket::getStruct(void *retBuf, size_t size) 
{
  if(size > PACKET_SIZE) {
    dprintf(("told to get size %d; splitting it into %d packets\n",
	     size, size / PACKET_SIZE + 1));
    dprintfLevelUp();
    int i;
    for(i=0; i<size-PACKET_SIZE; i+=PACKET_SIZE) {
      dprintf(("%d bytes (%2.2f%%) received so far\n",
	       i, 100.0 * (double)i / (double)size));
      getStruct((char*)retBuf+i, PACKET_SIZE);
    }
    // read what's left
    getStruct((char*)retBuf+i, size-i);
    dprintfLevelDown();
    return retBuf ;
  }

  int numRead = recv (socket_, (char*)retBuf, size, 0);
  if (numRead<size) {
    char buf[STRLEN];
    sprintf(buf, "error in internet-read: client sent too little data (%d/%d)",
	    numRead, size);
    throw NetworkException(socket_, NETERR::READ_TOO_LITTLE, buf);
  }

  return retBuf ;
}





/*************************************************************************
 * Function Name: NETReadWriteSocket::sendString
 * Parameters: const char *toSend
 * Returns: void
 * Effects: sends a string -- (length,null-term'd bytestream) pair
 *************************************************************************/
void
NETReadWriteSocket::sendString(const char *toSend) 
{
  int len = strlen(toSend)+1;
  sendInt(len);
  sendStruct(toSend, len);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::sendInt
 * Parameters: int toSend
 * Returns: void
 * Effects: sends an integer
 *************************************************************************/
void
NETReadWriteSocket::sendInt(int toSend) 
{
  sendStruct((char*)&toSend, sizeof(int));
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::sendChar
 * Parameters: char toSend
 * Returns: void
 * Effects: 
 *************************************************************************/
void
NETReadWriteSocket::sendChar(char toSend) 
{
  sendStruct((char*)&toSend, sizeof(char));
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::sendDouble
 * Parameters: double toSend
 * Returns: void
 * Effects: 
 *************************************************************************/
void
NETReadWriteSocket::sendDouble(double toSend) 
{
  sendStruct((char*)&toSend, sizeof(double));
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::sendStruct
 * Parameters: const char *toSend, size_t size
 * Returns: void
 * Effects: 
 *************************************************************************/
void
NETReadWriteSocket::sendStruct(const void *toSend, size_t size) 
{
  if(!buffered_) {
    doSendStruct(toSend, size);
  }
  else {
    buffer_.append((const char*)toSend, size);
  }
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::doSendStruct
 * Parameters: const char *toSend, size_t size
 * Returns: void
 * Effects: 
 *************************************************************************/
void
NETReadWriteSocket::doSendStruct(const void *toSend, size_t size) 
{
  dprintf(("sending %d bytes\n", size));
  if(size > PACKET_SIZE) {
    dprintf(("sending %d bytes as %d packets\n", size, size/PACKET_SIZE + 1));
    dprintfLevelUp();
    int sendIndex = 0;
    // send in packets of PACKET_SIZE bytes
    for(; sendIndex < size-PACKET_SIZE; sendIndex += PACKET_SIZE) {
      sendStruct((const char*)toSend+sendIndex, PACKET_SIZE);
      dprintf(("%d bytes sent (%2.2f%%) so far\n",
	       sendIndex, 100.0 * (double)sendIndex / (double)size));
    }
    // send what's left
    sendStruct((const char*)toSend+sendIndex, size-sendIndex);
    dprintfLevelDown();
    return;
  }

  // actually send the data
  send (socket_, (const char*)toSend, size, 0);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::startRequest
 * Parameters: int request
 * Returns: void
 * Effects: 
 *************************************************************************/
void
NETReadWriteSocket::startRequest(int request)
{
  if(buffered_) { dprintf(("already buffered; flushing\n")); flush(); }
  buffer_.setIndex(0);
  buffered_ = true ;
  sendInt(request);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::flush
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
NETReadWriteSocket::flush()
{
  dprintf(("flushing %d bytes\n", buffer_.size()));
  doSendStruct(&buffer_[0], buffer_.size());

  // don't let the buffer get too big
  if(buffer_.size() > 5*PACKET_SIZE) { buffer_.resize(5*PACKET_SIZE); }
  buffer_.setIndex(0);  
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::endRequest
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
NETReadWriteSocket::endRequest()
{
  flush();
  buffered_ = false;
}
