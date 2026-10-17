/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: NETReadWriteSocket.C
 *    DATE: Sun Apr 20 15:37:22 US/Eastern 1997
 *************************************************************************/
#include "NETReadWriteSocket.h"

#include "NetworkException.h"
#include <signal.h> // sigset, sigignore
#include <sys/types.h> // hostent
#include <sys/socket.h> // connect, getsockname, recv, send
#include <netdb.h> // gethostbyname
#include <unistd.h> // write(2)

/*************************************************************************
 * Function Name: NETReadWriteSocket::NETReadWriteSocket
 * Parameters: const char *rhost, unsigned short port
 * Effects: 
 *************************************************************************/

NETReadWriteSocket::NETReadWriteSocket(const char *rhost, unsigned short port)
  : buffer_(0, PACKET_SIZE)
{
  init(rhost, port);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::NETReadWriteSocket
 * Parameters: int fileDescriptor
 * Effects: 
 *************************************************************************/

NETReadWriteSocket::NETReadWriteSocket(int fileDescriptor)
  : buffer_(0, PACKET_SIZE)
{
  memset(xcpHandler_, 0, MAXNETERR*sizeof(NETxcpfunc)) ;
  memset(xcpData_, 0, MAXNETERR*sizeof(void*)) ;
  setXcpHandler(NETERR::READ_TOO_LITTLE,
		NETReadWriteSocket::ignore,
		this);
  buffered_ = false ;
  socket_ = fileDescriptor;
  int size = sizeof(socketName_);
  InternetSocket::getsockname();
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
  return getInt(retBuf);
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
  if(!getStruct((char*)&retBuf, sizeof(int))) return 0;
  else return retBuf;
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
  return getDouble(retBuf);
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
  if(!getStruct((char*)&retBuf, sizeof(double))) return 0;
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
  if(len<=0) return null;
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
  if(len<=0) return null;
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
  dprintf(("reading %d-byte struct into buffer at %x...\n", size, retBuf));
  boolean allocated ;

  if(!retBuf) {
      allocated = true;
    retBuf = malloc(size) ;
  } else {
      allocated = false;
  }

  dprintfLevelUp();

  int numRead = 0;
  int retval = read (socket_, (char*)retBuf, size);
  if(retval==0) {
    dprintfLevelDown();
    throwXcp(NETERR::READ_NONE);
    if(allocated) free(retBuf);
    return null;
  }

  numRead+=retval;
  while (numRead<size) {
    dprintf(("%d bytes read (%2.2f%%)\n",
	     numRead, ((double)numRead)/((double)size)));
    retval = recv(socket_, (char*)(retBuf)+numRead, size-numRead, 0);
    throwXcp(NETERR::READ_TOO_LITTLE);
    numRead+=retval ;
  }

  dprintfLevelDown();
  return retBuf ;
}





/*************************************************************************
 * Function Name: NETReadWriteSocket::sendString
 * Parameters: const char *toSend
 * Returns: void
 * Effects: sends a string -- (length,null-term'd bytestream) pair
 *************************************************************************/
boolean
NETReadWriteSocket::sendString(const char *toSend) 
{
  if(toSend) {
    int len = strlen(toSend)+1;
    if(!sendInt(len)) return false;
    if(!sendStruct(toSend, len)) return false;
  }
  else {
    if(!sendInt(0)) return false;
  }
  return true ;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::sendInt
 * Parameters: int toSend
 * Returns: void
 * Effects: sends an integer
 *************************************************************************/
boolean
NETReadWriteSocket::sendInt(int toSend) 
{
  return sendStruct((char*)&toSend, sizeof(int));
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::sendChar
 * Parameters: char toSend
 * Returns: void
 * Effects: 
 *************************************************************************/
boolean
NETReadWriteSocket::sendChar(char toSend) 
{
  return sendStruct((char*)&toSend, sizeof(char));
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::sendDouble
 * Parameters: double toSend
 * Returns: void
 * Effects: 
 *************************************************************************/
boolean
NETReadWriteSocket::sendDouble(double toSend) 
{
  return sendStruct((char*)&toSend, sizeof(double));
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::sendStruct
 * Parameters: const char *toSend, size_t size
 * Returns: void
 * Effects: 
 *************************************************************************/
boolean
NETReadWriteSocket::sendStruct(const void *toSend, size_t size) 
{
  if(!buffered_) {
    return doSendStruct(toSend, size);
  }
  else {
    buffer_.append((const char*)toSend, size);
    return true ;
  }
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::doSendStruct
 * Parameters: const char *toSend, size_t size
 * Returns: void
 * Effects: 
 *************************************************************************/
boolean
NETReadWriteSocket::doSendStruct(const void *toSend, size_t size) 
{
  dprintf(("sending %d bytes from %x\n", size, toSend));
  if( 0 > write(socket_, (const char*)toSend, size) ) {
    if(errno==EPIPE) {
//      sigignore(SIGPIPE);
      dprintf(("NET [%d]: got SIGPIPE\n", socket_));
      throwXcp(NETERR::SIGPIPE_RCVD);
      return false ;
    }
    return false ;
  }

  // else it succeeded
  return true ;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::startRequest
 * Parameters: int request
 * Returns: void
 * Effects: 
 *************************************************************************/
boolean
NETReadWriteSocket::startRequest(int request)
{
  if(buffered_) { dprintf(("already buffered; flushing\n")); flush(); }
  buffer_.setIndex(0);
  buffered_ = true ;
  return sendInt(request);
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::flush
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
boolean
NETReadWriteSocket::flush()
{
  dprintf(("flushing %d bytes\n", buffer_.size()));
  boolean retval = doSendStruct(&buffer_[0], buffer_.size());

  // don't let the buffer get too big
  if(buffer_.size() > 5*PACKET_SIZE) { buffer_.resize(5*PACKET_SIZE); }
  buffer_.setIndex(0);

  return retval ;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::endRequest
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
boolean
NETReadWriteSocket::endRequest()
{
  boolean retval = flush();
  buffered_ = false;

  return retval ;
}


/*************************************************************************
 * Function Name: NETReadWriteSocket::init
 * Parameters: const char *rhost, unsigned short port
 * Returns: void
 * Effects: 
 *************************************************************************/
void
NETReadWriteSocket::init(const char *rhost, unsigned short port)
{
  memset(xcpHandler_, 0, MAXNETERR*sizeof(NETxcpfunc)) ;
  memset(xcpData_, 0, MAXNETERR*sizeof(void*)) ;

  sigset(SIGPIPE, SIG_IGN); // this way, write(2) will return EPIPE

  InternetSocket::init(port);

  buffered_ = false ;


  // get the host from its name
  char *hostname = strdup(rhost);
  struct hostent *remote_host = gethostbyname(hostname);
  free(hostname);
  
  if ( remote_host == null ) {
    throwXcp(NETERR::CONNECTFAILED);
  }

  // copy the h_addr into sin_addr
  // whatever this does, it works
  memcpy(&socketName_.sin_addr, remote_host->h_addr,
	 remote_host->h_length );

  // go and connect
  int result = connect ( socket_, (struct sockaddr*) &socketName_, 
			 sizeof (socketName_) );
  if (result<0) {
    throwXcp(NETERR::CONNECTFAILED);
  }

  InternetSocket::getsockname();
  
  dprintf(("client finished setting up socket to %s port %d\n",
	 rhost, portNumber()));
}


