#ifndef PKGameServerConnection_HEADER
#define PKGameServerConnection_HEADER

#include <Network/NETStream.h>

class PKGameServerConnection : public NETStream {
private:
  int socketNum_ ; // NOT a file descriptor
  int errno_;
public:
  PKGameServerConnection() {} // must call init
  PKGameServerConnection(const char *host, unsigned short port, int socketnum) ;
  void init(const char *host, unsigned short port, int socketnum);
  void attachTo(NETReadWriteSocket *socket, int socketNum) ;
    
  virtual ~PKGameServerConnection();
  void detach();

  int errno() { return errno_; }
  int socketNum() { return socketNum_; }


private:
  static void static_readZero(void *thus) {
    ((PKGameServerConnection*)thus)->errno_ = ENODATA ;
  }
  static void static_sigpipe(void *thus) {
    ((PKGameServerConnection*)thus)->errno_ = EPIPE ;
  }
} ;


#endif
