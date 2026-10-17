/****************************************************************/
/*    NAME: David Akers                                         */
/*    ACCT: dla                                                 */
/*    FILE: GREngine.H                                          */
/*    ASGN: FINAL PROJECT                                       */
/*    DATE: Sat Apr 19 14:10:06 1997                            */
/****************************************************************/


#ifndef GRENGINE_HEADER
#define GRENGINE_HEADER
#include <rw7/rw/tpslist.h>
#include <rw7/rw/tvslist.h>
#include <Xm/Xm.h>
#include <PKids.h>
#include <VectorMath.h>
#include <PKKey.h>
#include <PKGameClasses.h>
#include <PKClientInterface.h>
#include <PKClientObject.h>
#include "GROnscreenGraphic.h"
#include "GRGraphicManager.h"
#include "GRGraphicType.h"
#include "GRFrame.h"
#include "GRKeyMap.h"
#include "GRLetterWriter.h"
#include "GRLifeDisplay.h"

class GRLifeDisplay;
class GRLetterWriter;
class GRGraphicType;
class PKClient;

typedef RWTPtrSlist<GROnscreenGraphic> OnscreenGraphicList;

typedef RWTPtrSlist<GRKeyMap> KeyMapList;

class GREngine {

public:

  GREngine(PKClientInterface *client, Widget parent, PKBackgroundID id, XtAppContext *app, int numplayers, PKTypeID *players);
  ~GREngine();

  // Interface code (these calls come from the client):
  
  virtual void addObject(PKID id, PKTypeID grId, PKPoint pos);
  virtual void removeObject(PKID id);
  virtual void defineKeyMap (PKKey key, KeySym value); 

  // Need to be able to handle keyboard input:
  static void keyCallback (Widget, void *, void *);
  void handleKeyCallback (KeySym key, int pressed);
  
  // Need to get called back every 30 ms or so for smooth animation..
  static void graphicsCallback(void *client_data, XtIntervalId *id);
  virtual void handleGraphicsCallback();
  // Used XtAppAddTimeOut to do this!! p. 743 of 6a

  static void exposeCallback (Widget, void *, void *);
  virtual void handleExposeCallback();

  virtual void loadXPM (char *, Pixmap *, Pixmap *);
  virtual void loadBackground(PKBackgroundID id);
  virtual void copyFrame (GRFrame *frame, Pixmap src, Drawable dest);

  virtual void updateGameStatus (PKGameStatus *gamestatus);
private:

  PKTypeID *player_types;
  int num_players;
  
  GC graphics_context;
  XtAppContext *app_;

  PKClientInterface *client_;
  // Link to client (interface?!?!?)

  // Note: Until further notice, the screen size will be 516x432

  Widget drawing_window; // The actual onscreen image
  
  Pixmap work_area; // Work area -- always contains most updated image for
                    // refresh purposes.
  
  Pixmap background_; // Stores only the background image. We never
                      // edit this after it is first initialized.

  GRGraphicManager *graphic_manager; // Manage & load all the spiffy graphics.
  
  GRGraphicType **graphic_types; // indexed by PKTypeID

  //int number_of_ids; // Size of the GRGraphicType array

  OnscreenGraphicList onscreen_graphics; // linked list of onscreen graphics.

  KeyMapList key_mappings; // Linked list of key mappings (keysym->pkkey)

  GRLifeDisplay *life_display;

  XtIntervalId timeout_id;

};
  
#endif
