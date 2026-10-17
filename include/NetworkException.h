/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: NetworkException.h                                  */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 12 17:53:36 1997                            */
/****************************************************************/


#ifndef NETWORKEXCEPTION_HEADER
#define NETWORKEXCEPTION_HEADER

#include <debug.h>
#include <Exception.h>
#include <errno.h>
#include <stdio.h>

/****************************************************************/
/* CLASS NAME :  NETERR                                         */
/* Just a bunch of scoped constants for network exceptions.     */
/*                                                              */
/****************************************************************/

class NETERR {
public:
  #define MAXNETERR 7
  enum NETErrID {
    NONE=0,
    OPENFAILED=1,
    CONNECTFAILED=2,
    BINDFAILED=3,
    READ_NONE=4,
    READ_TOO_LITTLE=5,
    SIGPIPE_RCVD=6
  };
  static const char * const errname_[];
} ;


/****************************************************************/
/* CLASS NAME :  NetworkException                               */
/* A class of exceptions thrown in the objectsocket package     */
/*                                                              */
/****************************************************************/

class NetworkException : public Exception {
protected:
  int socket_;
  NETERR::NETErrID neterr_;
public:
  NetworkException(int socket, NETERR::NETErrID neterr, const char *msg)
    : Exception(::errno, msg) {
      socket_ = socket; neterr_ = neterr;
  }
  NetworkException(char *msg)
    : Exception(::errno, msg), socket_(-1), neterr_(NETERR::NONE) {}

  ~NetworkException() {}

  boolean isBad() { return false; }

  void print() {
    if(socket_!=-1) {
      fprintf(stderr, "Network error %d on socket %d: %s",
	      neterr_, socket_, strerror(errno()));
    }
    else {
      fprintf(stderr, "Network error %d: %s",
	      neterr_, strerror(errno()));
    }
  }

  NETERR::NETErrID neterr() { return neterr_; }
  int socket() { return socket_; }
} ;




#endif
