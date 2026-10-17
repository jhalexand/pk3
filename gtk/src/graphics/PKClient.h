#ifndef PK_CLIENT_HEADER
#define PK_CLIENT_HEADER

#include <PKids.h>
#include <PKKey.h>
#include "DAVEPKObject.h"

class PKObject;

class PKClient {

public:

PKClient();
~PKClient();

  PKObject *getStateOfObject (PKID id);
  void handleKeyPress (PKKey key);
  void handleKeyRelease (PKKey key);
 
private:
  PKObject object_[4];
};
#endif
