/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: NETReadWriteSocket.h                                */
/*    ASGN:                                                     */
/*    DATE: Sun Apr 20 15:23:49 1997                            */
/****************************************************************/


#ifndef NETReadWriteSocket_HEADER
#define NETReadWriteSocket_HEADER

#include <debug.h>
#include "InternetSocket.h"
#include "NetworkException.h"

class NETReadWriteSocket : private InternetSocket {
private:
  Vector buffer_ ; // a buffer for buffered i/o
  boolean buffered_;

  // function pointers to use in cases when exceptions fail
  // if the pointers are null, throws an exception instead
  typedef void (*NETxcpfunc)(void*) ;
  NETxcpfunc xcpHandler_[MAXNETERR] ;
  void *xcpData_[MAXNETERR] ;
public:
  // opens a connection to rhost:port, or takes an open connection
  NETReadWriteSocket(const char *rhost, unsigned short port);
  NETReadWriteSocket(int fileDescriptor);
  virtual ~NETReadWriteSocket();

  // useful as an exeption handler if you don't care
  static void ignore(void*) {} ;

  virtual void setReadZero(NETxcpfunc func, void *clientData) {
    setXcpHandler(NETERR::READ_NONE, func, clientData);
  }
  virtual void setReadLittle(NETxcpfunc func, void *clientData)  {
    setXcpHandler(NETERR::READ_TOO_LITTLE, func, clientData);
  }
  virtual void setBrokenPipe(NETxcpfunc func, void *clientData) {
    setXcpHandler(NETERR::SIGPIPE_RCVD, func, clientData);
  }
  virtual void setXcpHandler(NETERR::NETErrID id, NETxcpfunc func, void *clientData) {
    dprintf(("NET [%d]: setting exception handler %u (for %s)\n",
	     socket_, id, NETERR::errname_[id])) ;
    xcpHandler_[id] = func ;
    xcpData_[id] = clientData;
  }

  virtual int portNumber() { return InternetSocket::portNumber(); }
  virtual int fileDescriptor() { return InternetSocket::fileDescriptor(); }


  // read the appropriate data type from the socket.  These are implemented
  // as calls to getStruct(.) with sizeof(type).
  // Note the no-buffer getString and getStruct return a pointer to a
  // newly malloc'd buffer; remember to free them.
  virtual char getChar() ;
  virtual char getChar(char& retBuf) ;

  virtual int getInt() ;
  virtual int getInt(int& retBuf) ;

  virtual double getDouble() ;
  virtual double getDouble(double& retBuf);

  virtual char *getString() ;
  virtual char *getString(char *retBuf) ;

  virtual void *getStruct(size_t size) ;
  virtual void *getStruct(void *retBuf, size_t size) ;

  
  // sends the thing over to the other side of the connection;
  // if buffered_, buffers the send until a flush is called
  virtual boolean sendString(const char *toSend) ;
  virtual boolean sendInt(int toSend) ;
  virtual boolean sendChar(char toSend) ;
  virtual boolean sendDouble(double toSend) ;
  virtual boolean sendStruct(const void *toSend, size_t size) ;

  // buffered i/o
  // To send a request, say startRequest(<requestID>), send whatever
  // info the request should have, then endRequest().  Everything will
  // be sent in one fell swoop on endRequest() or flush().
  virtual boolean startRequest(int request); // until end, add to buffer
  virtual boolean flush(); // actually send, but keep buffering
  virtual boolean endRequest(); // actually send the request, and stop buffering

private:
  void init(const char *rhost, unsigned short port);

  // actually send the data, used in unbuffered writes, and when flushing
  virtual boolean doSendStruct(const void *toSend, size_t size);

  // throw an exception, or call the exception handler
  void throwXcp(NETERR::NETErrID id) {
    if(xcpHandler_[id]) {
      xcpHandler_[id](xcpData_[id]) ;
    }
    else {
      throw NetworkException(socket_, id, NETERR::errname_[id]);
    }
  }

} ;  

#endif
