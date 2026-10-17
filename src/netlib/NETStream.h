/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: NETClasses.h                                        */
/*    ASGN:                                                     */
/*    DATE: Sun Apr 27 03:47:47 1997                            */
/****************************************************************/


#ifndef NETCLASSES_HEADER
#define NETCLASSES_HEADER


#include <Network/NETids.h>
#include <Network/NETReadWriteSocket.h>
#include <PKGameClasses.h>
#include <PKObject.h>
#include <VectorMath.h>

class NETStream {
protected:
  NETReadWriteSocket *socket_;
public:
  NETStream() { socket_ = null; }
  NETStream(NETReadWriteSocket *socket) { socket_ = socket; }
  NETStream(const NETStream& other) { *this = other; }

  NETReadWriteSocket *attachedTo() const { return socket_; }
  void attachTo(NETReadWriteSocket* socket) { socket_ = socket; }
  void release() { socket_ = null; }
  void detach() { release(); }
  NETStream& operator = (const NETStream& other) {
    attachTo(other.attachedTo());
    return *this;
  }

  // just calls that on the socket
  void startRequest(int reqnum) { socket_->startRequest(reqnum); }
  void endRequest() { socket_->endRequest(); }
  
  // write to the socket
  NETStream& operator << (const double& eger);
  NETStream& operator << (const int& eger);
  NETStream& operator << (const char *string);
  NETStream& operator << (const NETPort::NETPortID& id);
  NETStream& operator << (const PKActionID& id);
  NETStream& operator << (const PKAILevel& lvl);
  NETStream& operator << (const PKAnimID& id);
  NETStream& operator << (const PKBackgroundID& id);
  NETStream& operator << (const PKGameParameters& obj);
  NETStream& operator << (const PKGameProgress& obj);
  NETStream& operator << (const PKGameStatus& obj);
  NETStream& operator << (const PKObject& obj);
  NETStream& operator << (const PKPlayerInfo& obj);
  //  NETStream& operator << (const PKID& id); // "multiple declaration"
  NETStream& operator << (const PKPoint& id);
  NETStream& operator << (const PKSoundID& id);
  NETStream& operator << (const PKTypeID& id);
  NETStream& operator << (const PKVector& id);


  // read from the socket
  int get() { return socket_->getInt(); } // provided for ease of use
  NETStream& operator >> (double& eger);
  NETStream& operator >> (int& eger);
  NETStream& operator >> (char *string);
  NETStream& operator >> (char **string); // allocates using malloc
  NETStream& operator >> (NETPort::NETPortID& id);
  NETStream& operator >> (PKActionID& id);
  NETStream& operator >> (PKAILevel& lvl);
  NETStream& operator >> (PKAnimID& id);
  NETStream& operator >> (PKBackgroundID& id);
  NETStream& operator >> (PKGameParameters& obj);
  NETStream& operator >> (PKGameProgress& obj);
  NETStream& operator >> (PKGameStatus& obj);
  NETStream& operator >> (PKObject& obj);
  NETStream& operator >> (PKPlayerInfo& obj);
  //  NETStream& operator >> (PKID& id); // "multiple declaration" with int
  NETStream& operator >> (PKPoint& id);
  NETStream& operator >> (PKSoundID& id);
  NETStream& operator >> (PKTypeID& id);
  NETStream& operator >> (PKVector& id);


} ;



#endif
