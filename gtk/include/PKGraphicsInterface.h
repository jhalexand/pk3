#ifndef GR_ENGINE_INTERFACE
#define GR_ENGINE_INTERFACE

#include <PKids.h>
#include <PKGameClasses.h>
#include <PKClientInterface.h>
#include <VectorMath.h>
#include <PKKey.h>
#include <Xm/MainW.h>

// XpmReadFileToPixmap!!

// Forward declarations:

class GREngine;
class PKClient;


// Class GREngineInterface
//
// This is the main interface class for the graphics engine.
// The engine is a cute little model which fits snuggly into the
// bosom of the GUI, providing fast animation and dazzling graphics.

class PKGraphicsInterface {

public:

  PKGraphicsInterface (PKClientInterface *client, Widget parent, PKBackgroundID
id, XtAppContext *app, int numplayers, PKTypeID *playertypes);
  
  ~PKGraphicsInterface();
  
  virtual void addObject (PKID id, PKTypeID grId, PKPoint pos);

  virtual void removeObject (PKID id);
  
  virtual void defineKeyMap (PKKey key, KeySym keysym);

  virtual void updateGameStatus (PKGameStatus *gamestatus);

private:

  GREngine *implementation_; // The actual guts of the graphics engine

};

#endif
