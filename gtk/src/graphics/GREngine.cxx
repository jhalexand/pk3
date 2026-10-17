/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GREngine.cxx
 *    DATE: Sun Apr 20 19:02:58 US/Eastern 1997
 *************************************************************************/
#include "GREngine.h"
#include <Xm/DrawingA.h>
#include <xpm.h>
#include <unistd.h>
#include <stdlib.h>
#include <PKClientInterface.h>
#include <PKDimensions.h>

/*************************************************************************
 * Function Name: GREngine::GREngine
 * Parameters: PKClient *client, Widget parent
 * Effects: 
 *************************************************************************/

GREngine::GREngine(PKClientInterface *client, Widget parent, PKBackgroundID id, XtAppContext *app, int numplayers, PKTypeID *players)
{

  client_ = client;

  app_ = app;

  num_players = numplayers;
  player_types = players;

  cout << "Background ID is: " << id << endl;
  
  drawing_window = XtVaCreateManagedWidget ("drawing",
					    xmDrawingAreaWidgetClass,
					    parent, XmNwidth,
					    PK_DIM_SCREEN_WIDTH,
					    XmNheight,PK_DIM_SCREEN_HEIGHT ,
					    XmNresizePolicy, XmRESIZE_NONE, 
					    NULL);

  work_area = XCreatePixmap (XtDisplay (drawing_window),
			     RootWindowOfScreen (XtScreen (drawing_window)),
			     PK_DIM_SCREEN_WIDTH, PK_DIM_SCREEN_HEIGHT,
			     DefaultDepthOfScreen (XtScreen (drawing_window)));

  background_ = XCreatePixmap (XtDisplay (drawing_window),
			     RootWindowOfScreen (XtScreen (drawing_window)),
			     PK_DIM_SCREEN_WIDTH, PK_DIM_SCREEN_HEIGHT,
			     DefaultDepthOfScreen (XtScreen (drawing_window)));

  // Set up the expose callback:
  
  XtAddCallback (drawing_window, XmNexposeCallback, exposeCallback, this);

  // Set up a callback for handling key events:
  
  XtAddCallback (drawing_window, XmNinputCallback, keyCallback, this);

  // Set up the GC and attach it to the drawing window:
  
  graphics_context = XCreateGC (XtDisplay (drawing_window), RootWindowOfScreen (XtScreen (drawing_window)), 0, NULL);
  
  XtVaSetValues (drawing_window, XmNuserData, graphics_context, NULL);

  // Now load the background onto its pixmap:
  loadBackground(id);                                                                
  graphic_manager = new GRGraphicManager("/cs/src/pk3/bin/pkgraphics.dat",
num_players, player_types, drawing_window, graphics_context);

  graphic_types = graphic_manager->parseFile();
  
  // Call back our graphics callback every 30 ms:
  
  XtAppAddTimeOut (*app, 2000L, graphicsCallback, this);
  
  if (!graphic_types) { cout << "Error in parsing file!" << endl; }

  system ("xset -r");

  life_display = new GRLifeDisplay ( work_area, drawing_window, graphics_context, players, numplayers);

  
}


/*************************************************************************
 * Function Name: GREngine::~GREngine
 * Parameters: 
 * Effects: 
 *************************************************************************/

GREngine::~GREngine()
{

  XtRemoveTimeOut (timeout_id);
  XtRemoveAllCallbacks (drawing_window, XmNexposeCallback);
  XtRemoveAllCallbacks (drawing_window, XmNinputCallback);
  XSync(XtDisplay (drawing_window), True);
  XFlush (XtDisplay (drawing_window));
  
  XFreePixmap (XtDisplay (drawing_window), work_area);
  XFreePixmap (XtDisplay (drawing_window), background_);
  XFreeGC (XtDisplay (drawing_window), graphics_context);
  delete life_display;
  delete graphic_manager;
  key_mappings.clearAndDestroy();
  onscreen_graphics.clearAndDestroy();
  system ("xset r");
  
  
}


/*************************************************************************
 * Function Name: GREngine::addObject
 * Parameters: PKID id, PKTypeID grId, PKPoint pos
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::addObject(PKID id, PKTypeID grId, PKPoint pos)
{

  GROnscreenGraphic *newgraphic;
  cout << "Graphics: about to add object of type ID: " << grId << endl;
  if (!graphic_types[grId]) 
    {
    cout << "Fatal error! Type ID " << grId << "'s image was not loaded!" << endl;
    cout << "Aborting. Please inform dla@cs.brown.edu of this error." << endl;
    exit (0);
    }
  newgraphic = new GROnscreenGraphic (graphic_types[grId], id, GRScreenPoint (pos));
  onscreen_graphics.insert (newgraphic);
  
}


/*************************************************************************
 * Function Name: GREngine::removeObject
 * Parameters: PKID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::removeObject(PKID id)
{
   for (RWTPtrSlistIterator <GROnscreenGraphic> iter(onscreen_graphics);iter();)
    {
      GROnscreenGraphic *graphic = iter.key();
      if (id == graphic->getID())
	{
	  GRFrame *frame = graphic->getFrame();
	  copyFrame (frame, background_, work_area);
	  //delete frame;
	  //onscreen_graphics.remove (graphic);
	   for (RWTPtrSlistIterator <GROnscreenGraphic> iter2(onscreen_graphics);iter2();)
	    {
	      GROnscreenGraphic *objectcompare;
	      objectcompare = iter2.key();
              if (objectcompare != graphic)
	      {
	      GRFrame *frame2 = objectcompare->getFrame();
	      if (frame2->intersect(frame))
		{
		  //cout << "Intersection with other object detected." << endl;
		  objectcompare->draw(work_area);
		  frame->mergeFrame (frame2);
		  
		}
	      delete frame2;
	      }
              }
	   copyFrame (frame, work_area, XtWindow (drawing_window));
	   delete frame;

	   onscreen_graphics.remove (graphic);
	   delete graphic;
	   return;
	}
      
    }
}


/*************************************************************************
 * Function Name: GREngine::defineKeyMap
 * Parameters: PKKey key, KeySym value
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::defineKeyMap(PKKey key, KeySym value)
{

  GRKeyMap *keymap = new GRKeyMap (value, key);
  key_mappings.insert (keymap);
  
}


/*************************************************************************
 * Function Name: GREngine::graphicsCallback
 * Parameters: Widget, void *, void *
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::graphicsCallback(void *client_data, XtIntervalId *id)
{

  ((GREngine *) client_data)->handleGraphicsCallback();
  
}


/*************************************************************************
 * Function Name: GREngine::handleGraphicsCallback
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::handleGraphicsCallback()
{

  timeout_id = XtAppAddTimeOut (*app_, 30L, graphicsCallback, this);

  typedef RWTPtrSlist<GRFrame> FrameList;

  FrameList framesToCopy;
  
  GROnscreenGraphic *graphic;
  PKClientObject *objectstate = NULL;

  for (RWTPtrSlistIterator <GROnscreenGraphic> iter(onscreen_graphics);iter();)
    {
      graphic = iter.key();

      if (!graphic->isDrawn())
      {
      //cout << "Drawing for the first time" << endl;
      graphic->draw (work_area);
      copyFrame (graphic->getFrame(), work_area,
      XtWindow(drawing_window));
      graphic->initialize();
      }

      if (client_) objectstate = client_->getStateOfObject (graphic->getID());
      GRFrame *frame = graphic->getFrame();
      int changed_frames = graphic->animate(objectstate);
      int object_moved_or_changed_animations = graphic->updateStatus(objectstate);
      if (object_moved_or_changed_animations || changed_frames)
	{
	  //cout << "Object changed pos/anim state" << endl;
	  copyFrame (frame, background_, work_area);
	  for (RWTPtrSlistIterator <GROnscreenGraphic> iter2(onscreen_graphics);iter2();)
	    {
	      GROnscreenGraphic *objectcompare;
	      objectcompare = iter2.key();
              if (objectcompare != graphic)
	      {
	      GRFrame *frame2 = objectcompare->getFrame();
	      if (frame2->intersect(frame))
		{
		  //cout << "Intersection with other object detected." << endl;
		  objectcompare->draw(work_area);
		  frame->mergeFrame (frame2);
		  
		}
	      delete frame2;
	      }
              }
	  graphic->draw (work_area);
	  GRFrame *newframe = graphic->getFrame();
	  frame->mergeFrame (newframe); // Merge the two into one.
	  delete newframe;
	  framesToCopy.insert (frame);
	}
      else delete frame;
    }
  for (RWTPtrSlistIterator <GRFrame>
frameiter(framesToCopy);frameiter();)
    {
      copyFrame (frameiter.key(), work_area, XtWindow (drawing_window));
    }
  framesToCopy.clearAndDestroy();
  //XSync(XtDisplay (drawing_window), 0);
  
}


/*************************************************************************
 * Function Name: GREngine::exposeCallback
 * Parameters: Widget, void *, void *
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::exposeCallback(Widget, void *engineclass, void *client_data)
{

  ((GREngine *) engineclass)->handleExposeCallback();

}


/*************************************************************************
 * Function Name: GREngine::handleExposeCallback
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::handleExposeCallback()
{
  XSetClipMask(XtDisplay(drawing_window), graphics_context, None);
  //cout << "Exposing" << endl;
  XCopyArea (XtDisplay (drawing_window), work_area, XtWindow
(drawing_window), graphics_context, 0, 0, PK_DIM_SCREEN_WIDTH,
PK_DIM_SCREEN_HEIGHT, 0, 0);
  //cout << "Done exposing" << endl;
}


/*************************************************************************
 * Function Name: GREngine::loadXPM
 * Parameters: PKBackgroundID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::loadXPM(char *filename, Pixmap *pmap, Pixmap *mask)
{

  XpmAttributes attributes;

  attributes.closeness = 65535;
  attributes.valuemask = XpmCloseness;

  int success = XpmReadFileToPixmap (XtDisplay (drawing_window),
				     DefaultRootWindow (XtDisplay (drawing_window)),
				     filename,
pmap, mask, &attributes);

  switch (success)
    {
    case -1: cout << "Error opening file: " << filename << endl; break;
    case -4: cout << "Color error: " << filename << endl; break;
    }
}


/*************************************************************************
 * Function Name: GREngine::loadBackground
 * Parameters: PKBackgroundID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::loadBackground(PKBackgroundID id)
{

  char base[40] = "/cs/src/pk3/graphics/backgrounds";

  char fullpath[255];

  char fname[50];

  if (id == PK_BACKGROUND_LAVA)
    {
      strcpy (fname, "lava.xpm");
    }

  if (id == PK_BACKGROUND_MAC)
    {
      strcpy (fname, "mac.xpm");
    }

  if (id == PK_BACKGROUND_SPACE)
    {
      strcpy (fname, "space.xpm");
    }

  if (id == PK_BACKGROUND_PETER)
    {
      strcpy (fname, "peter.xpm");
    }

  if (id == PK_BACKGROUND_BOWLING)
    {
      strcpy (fname, "bowling.xpm");
    }

  if (id == PK_BACKGROUND_SUNNY)
    {
      strcpy (fname, "sunny.xpm");
    }
 
  if (id == PK_BACKGROUND_SWIRL)
    {
      strcpy (fname, "swirl.xpm");
    }

  if (id == PK_BACKGROUND_FIRE)
    { 
      strcpy (fname, "fire.xpm");
    }

  if (id == PK_BACKGROUND_MOUNTAINS)
    {
      strcpy (fname, "mountains.xpm");
    }

  sprintf (fullpath, "%s/%s", base, fname);
  loadXPM ((char *) fullpath, &background_, NULL);

  ;
  XCopyArea (XtDisplay (drawing_window), background_,work_area,
graphics_context, 0, 0, PK_DIM_SCREEN_WIDTH, PK_DIM_SCREEN_HEIGHT, 0, 0);
  
}


/****************************************************************/
/*                                                              */
/* Function Name: GREngine::copyFrame()                         */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/

void
GREngine::copyFrame (GRFrame *frame, Pixmap src, Drawable dest)
{
  GRScreenPoint start = frame->getStart();
  GRScreenPoint end = frame->getEnd();

  XSetClipMask(XtDisplay(drawing_window), graphics_context, None);

  //cout << (unsigned long) src << endl;
  //cout << (unsigned long) dest << endl;
  //cout << (int) start[0] << " " << (int) start[1] << " " << (int) end[0]<< " " << (int) end[1] << endl;
  
  XCopyArea (XtDisplay (drawing_window), src, dest, graphics_context, start[0], start[1], end[0]-start[0], end[1]-start[1], start[0], start[1]);

}
/*************************************************************************
 * Function Name: GREngine::keyCallback
 * Parameters: Widget, void *, void *
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::keyCallback(Widget, void *clientdata, void *calldata)
{
  XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *)
calldata;

XEvent *event = cbs->event;

  if (event->xany.type == KeyPress || event->xany.type == KeyRelease)
	{
        KeySym keysym;
        XComposeStatus compose_status;
        char keypress[10];
        int length = XLookupString ((XKeyEvent *) event, keypress, 9,
&keysym,
&compose_status);
        if (length > 0 && length <= 9) {keypress[length] = 0;}
        char *mychar = XKeysymToString (keysym);
	if (mychar == NULL) {strcpy (keypress, "Benoit");} else
        strcpy (keypress, mychar);
        cout << keypress << endl;
	if (event->xany.type == KeyPress)
	  {
	    //cout << " was pressed!" << endl;
	    ((GREngine *) clientdata)->handleKeyCallback (keysym, TRUE);
	  }
	if (event->xany.type == KeyRelease)
	  {
	    //cout << " was released!" << endl;
	    ((GREngine *) clientdata)->handleKeyCallback (keysym, FALSE);
	  }
        }
}

KeySym upcase (KeySym ksym)
{
  if (ksym > 65 && ksym < 92) return ksym + 32;
else
return ksym;
}

/*************************************************************************
 * Function Name: GREngine::handleKeyCallback
 * Parameters: KeySym key, int pressed
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::handleKeyCallback(KeySym key, int pressed)
{
  for (RWTPtrSlistIterator <GRKeyMap> iter(key_mappings);iter();)
    {
      GRKeyMap *keymap = iter.key();
      if (upcase(keymap->sym_) == upcase(key))
	{
	  //cout << "Telling client to handle key: " << (int) keymap->key_ << endl;
	  if (pressed) client_->handleKeyPress (keymap->key_);
	  else client_->handleKeyRelease (keymap->key_);
	  return;
	}
    }
  
}


/*************************************************************************
 * Function Name: GREngine::updateGameStatus
 * Parameters: PKGameStatus *gamestatus
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GREngine::updateGameStatus(PKGameStatus *gamestatus)
{
  cout << "Mike is updating my game status" << endl;
  int *life = gamestatus->life();
  int numPlayers = gamestatus->numPlayers();
  int displaylife = 1;
  if (life)
    {
  for (int i = 0; i < 4; i++)
    {
      if (life[i] > 100 || life[i] < -1) displaylife = 0;
    }
  cout << "Life of player 0 is " << life[0] << endl;
  cout << "Player numbers: " << numPlayers << endl;
  if (displaylife) life_display->update (gamestatus);
    }
  else {cout << "Life is null" << endl; }
  
}


