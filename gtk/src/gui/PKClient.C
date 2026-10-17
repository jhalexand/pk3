/*************************************************************************
 *    NAME: Michael Pellauer
 *    USER: cs032082
 *    FILE: PKClient.cxx
 *    DATE: Sat Apr 26 22:25:56 US/Eastern 1997
 *************************************************************************/
#include "PKClient.h"
#include "PKOpeningGUI.h"
#include "PKMainServerGUI.h"
#include "PKGameGatheringGUI.h"
#include "PKObjectList.h"
#include "PKPaddleKeys.h"
#include "PKClientObject.h"
#include <PKids.h>
#include <PKGameClasses.h>
#include <PKObject.h>
#include <PKKey.h>
#include <PKClientNetworkInterface.h>
#include <PKResources.h>
#include <PKGraphicsInterface.h>
#include <PKAudioPlayer.h>
#include <VectorMath.h>
#include <stdlib.h>
#include <fstream.h>
#include <keysym.h>
#include <keysymdef.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/time.h>
#include <Exception.h>
#include <gtk/gtk.h>
#include <glib.h>


#include "PKCyraxLeftKeys.h"
#include "PKCyraxRightKeys.h"

#include "PKJadeLeftKeys.h"
#include "PKJadeRightKeys.h"

#include "PKKabalLeftKeys.h"
#include "PKKabalRightKeys.h"

#include "PKLiuKangLeftKeys.h"
#include "PKLiuKangRightKeys.h"

#include "PKReptileLeftKeys.h"
#include "PKReptileRightKeys.h"

#include "PKScorpionLeftKeys.h"
#include "PKScorpionRightKeys.h"

#include "PKSmokeLeftKeys.h"
#include "PKSmokeRightKeys.h"

#include "PKSonyaLeftKeys.h"
#include "PKSonyaRightKeys.h"

#include "PKSubZeroLeftKeys.h"
#include "PKSubZeroRightKeys.h"


//include count = 50!!


// define & initialize (so at this point, it sets defaults)
PKResources pk3rc = PKResources() ;


// an X error handler: 
int
PK_XErrorHandler(Display *dsp,XErrorEvent *err)
{
  // taken from Xlib 2 p435
  char msg[STRLEN];
  XGetErrorText(dsp, err->error_code, msg, STRLEN);
  fprintf(stderr, "XError %d : %s\n", err->error_code, msg);
  fprintf(stderr, "\tresource: %x\n"
 		  "\tserial:   %ld\n"
		  "\trequest:  %x\n"
		  "\tminor:    %x\n",
	  err->resourceid, err->serial, err->request_code, err->minor_code);
  assert(false);
  return 0 ;
}

/*************************************************************************
 * Function Name: PKClient::PKClient
 * Parameters: int argc, char** argv
 * Effects: 
 *************************************************************************/

void
PKClient::fileCB(GtkWidget *widget, GdkEvent *event ) 
{
  ::exit(0);
}



PKClient::PKClient(int argc, char** argv)
{
  is_paused_ = 0;
  gather_ = '\0';
  
  startSound() ;
  pk3rc.readFile() ;
  pk3rc.readCommandLine(argc, argv) ;

  top_ = '\0';



  // log X errors, synchronize X requests
  XSetErrorHandler(PK_XErrorHandler) ;
  XSynchronize(XtDisplay(
			 XtAppInitialize(&app_context_,
					 "PK",
					 (XrmOptionDescList)0,
					 0,
					 &argc,
					 argv,
					 (String*) 0,
					 0, 0)), True);

  gtk_init (&argc, &argv);
  opening_ = new PKOpeningGUI(this);
  gtk_main();
}


/*************************************************************************
 * Function Name: PKClient::~PKClient
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKClient::~PKClient()
{
  if (network_) delete(network_);
  if (graphics_) delete(graphics_);
  if (top_) delete(top_);
  if (keys_) delete(keys_);
  if (opening_) delete(opening_);
  if (main_) delete(main_);
  if (gather_) delete(gather_);
}


/*************************************************************************
 * Function Name: PKClient::getStateOfObject
 * Parameters: PKID id
 * Returns: PKObject*
 * Effects: 
 *************************************************************************/
PKClientObject*
PKClient::getStateOfObject(PKID id)
{
  PKClientObject* object;
  if (top_) {
    object = top_->getObject(id);
    if (!is_paused_) {
      PKPoint prev = object->getPosition();
      PKVector velocity = object->getVector();
      hrtime_t timenow = gethrtime();
      hrtime_t timeold = object->getTime();
      hrtime_t elapsed = timenow - timeold;
      PKPoint newpos = prev + (elapsed*velocity*.00000001);
      object->setPosition(newpos);
      object->setTime(timenow);
    }
    return object;
  }
  else return '\0';
}


/*************************************************************************
 * Function Name: PKClient::handleKeyPress
 * Parameters: PKKey key
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::handleKeyPress(PKKey key)
{
  keys_->keyPress(key);
}


/*************************************************************************
 * Function Name: PKClient::handleKeyRelease
 * Parameters: PKKey key
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::handleKeyRelease(PKKey key)
{
  keys_->keyRelease(key);
}


void
PKClient::enterMainServer(const char* host, const char* name, const char* port) {
  // get the hostname
  struct utsname unstruct;
  uname(&unstruct);
  cout << "Beginning Connection" << endl;
  try {
    network_ = new PKClientNetworkInterface(this, app_context_,
					  host, atoi(port), name,
					  getpwuid(getuid())->pw_name,
					  unstruct.nodename);
  } catch (Exception& ex) {
    error("Could not connect to server!");
    return;
  }
  cout << "About to delete opening" << endl;
  
  if (opening_) delete (opening_);
  cout << "Opening new window" << endl;
  main_ = new PKMainServerGUI(network_, name, this);
  audio_->playAudio(PK_SOUND_TOASTY);
}

/*************************************************************************
 * Function Name: PKClient::addUser
 * Parameters: userID id, char* user, char* account, char* host
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::addUser(int userID, const char* user, const char* account, const char* host)
{
  main_->addUser(userID,(char *)  user, (char *) account, (char *) host);
}


/*************************************************************************
 * Function Name: PKClient::removeUser
 * Parameters: userID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::removeUser(int userID)
{
  main_->removeUser(userID);
}


/*************************************************************************
 * Function Name: PKClient::addGame
 * Parameters: gameID id, garmParms parms
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::addGame(int gameID, const PKGameProgress& prog)
{
  main_->addGame(prog.creatorName(), gameID);
}


/*************************************************************************
 * Function Name: PKClient::removeGame
 * Parameters: gameID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::removeGame(int gameID)
{
  main_->removeGame(gameID);
}

/*************************************************************************
 * Function Name: PKClient::enterGameSetup
 * Parameters: gameID id, GameParameters parms
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::enterGameSetup(int gameID, const PKGameParameters& parms, int playerNum)
{
  setPause(false);
  dprintf(("PKClient: entering game setup with player number %d\n",
	   playerNum));
  if (playerNum >= 0) {
    if (main_) delete (main_);

    player_ = playerNum;
    PKPlayerInfo playerInfo = parms.getPlayer(player_);

    if(gather_) delete gather_; gather_ = '\0' ;
    gather_ = new PKGameGatheringGUI(network_, this, playerNum,
				     playerInfo.username(),
				     playerInfo.account(),
				     playerInfo.hostname(),
				     pk3rc.paddle(),
				     pk3rc.team());

    for (int i = 0; i < parms.numPlayers();i++) {
      PKPlayerInfo playerInfo = parms.getPlayer(i);
      int n = playerInfo.playerNumber();
      if (n != -1) { // then n==i
	gather_->addPlayer(i, playerInfo); // add player at index i
	gather_->setTeam(i,playerInfo.team());  // change player at index i
	gather_->setPaddle(i, playerInfo.paddle()); // change player at index i
      } //else gather_->removePlayer(i);
    }
    gather_->realize();
  }
  else if (playerNum == -1) error("Selected game is full!");
  else if (playerNum == -2) error("Can not join a game in progress!");
  else if(playerNum = -3) error("Selected game is invalid!");
}


/*************************************************************************
 * Function Name: PKClient::addPlayer
 * Parameters: playerNum num, playerInfo info
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::addPlayer(int playerNum, const PKPlayerInfo& info)
{
  gather_->addPlayer(playerNum, info);
}


/*************************************************************************
 * Function Name: PKClient::removePlayer
 * Parameters: playerNum num
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::removePlayer(int playerNum)
{
  gather_->removePlayer(playerNum);
}

void
PKClient::rejectPlayer(int playerNum)
{
  gather_->rejectPlayer(playerNum);
}


/*************************************************************************
 * Function Name: PKClient::setPaddle
 * Parameters: playerNum num, PKTypeID paddle
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::setPaddle(int playerNum, PKTypeID paddle)
{
  gather_->setPaddle(playerNum, paddle);
}


/*************************************************************************
 * Function Name: PKClient::setTeam
 * Parameters: playerNum num, int team
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::setTeam(int playerNum, int team)
{
  gather_->setTeam(playerNum, team);
}


void
PKClient::returnToMainScreen()
{
  if (gather_) delete(gather_); gather_ = '\0';
  /* Need more here */
}

/*************************************************************************
 * Function Name: PKClient::enterGamePlay
 * Parameters: GameParameters parms, int numObjects, PKObject[] objects
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::enterGamePlay(const PKGameParameters& parms)
{
  int i ;

  // throw up a gui with File menu, Quit button
  if(gather_) delete gather_ ; gather_ = '\0' ;

  window_ = gtk_window_new(GTK_WINDOW_DIALOG);
  gtk_widget_show(window_);
  
  GtkWidget *file_menu = gtk_menu_new();    /* Don't need to show menus */

  /* Create the menu items */
  GtkWidget *quit_item = gtk_menu_item_new_with_label("Quit");

  /* Add them to the menu */
  gtk_menu_append( GTK_MENU(file_menu), quit_item);
  
  /* We can attach the Quit menu item to our exit function */
  gtk_signal_connect_object( GTK_OBJECT(quit_item), "activate",
			     GTK_SIGNAL_FUNC(PKClient::fileCB), GTK_OBJECT(quit_item));

  /* We do need to show menu items */
  gtk_widget_show( quit_item );

  GtkWidget *menu_bar = gtk_menu_bar_new();
  gtk_container_add( GTK_CONTAINER(window_), menu_bar);
  gtk_widget_show( menu_bar );

  GtkWidget *file_item = gtk_menu_item_new_with_label("File");
  gtk_widget_show(file_item);

  gtk_menu_item_set_submenu( GTK_MENU_ITEM(file_item), file_menu );

  gtk_menu_bar_append( GTK_MENU_BAR (menu_bar), file_item );

  // deal with the game parameters
  int pcount = 0;  // actual number of clients playing the game.

  PKPlayerInfo* info = parms.players();
  int n = parms.numPlayers();

  PKTypeID paddle = info[player_].paddle();
  paddle_ = paddle; 

  PKTypeID* typeIDs = new PKTypeID[n];
  PKTypeID compactArray[4];

  for (i = 0; i < n; i++) {
    typeIDs[i] = info[i].paddle();
    if (info[i].playerNumber() != -1) { // compact the array
	compactArray[pcount] = typeIDs[i];
	pcount++;
    }
    else {
      dprintf(("PKClient: Throwing out player %d\n", i));
    }
  }

  GtkWidget *rowc = gtk_hbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window_), rowc);
  gtk_widget_show(rowc);

  /*Widget rowc = XtVaCreateManagedWidget ("da", xmRowColumnWidgetClass,
					 window_,
					 XmNorientation, XmHORIZONTAL,
					 NULL);
					 */

  //NOTE, NULLS were rowc
  if (pk3rc.background() == (PKBackgroundID)-1)
    graphics_ = new PKGraphicsInterface(this, '\0',
					parms.background(),
					&app_context_, pcount, typeIDs);
  else
    graphics_ = new PKGraphicsInterface(this, '\0',
					pk3rc.background(),
					&app_context_, pcount, typeIDs);

  graphics_->defineKeyMap(PK_KEY_UP, XK_Up);
  graphics_->defineKeyMap(PK_KEY_DOWN, XK_Down);
  graphics_->defineKeyMap(PK_KEY_LEFT, XK_Left);
  graphics_->defineKeyMap(PK_KEY_RIGHT, XK_Right);
  graphics_->defineKeyMap(PK_KEY_PUNCH, XK_a);
  graphics_->defineKeyMap(PK_KEY_KICK, XK_s);
  graphics_->defineKeyMap(PK_KEY_BLOCK, XK_d);
  graphics_->defineKeyMap(PK_KEY_PAUSE, XK_p);

  //Put in a big, nasty switch here.
  switch(paddle) {
  case PK_TYPE_CYRAX_1: keys_ = new PKCyraxLeftKeys(network_, this); break;
  case PK_TYPE_CYRAX_2: keys_ = new PKCyraxRightKeys(network_, this); break;
  case PK_TYPE_JADE_1: keys_ = new PKJadeLeftKeys(network_, this); break;
  case PK_TYPE_JADE_2: keys_ = new PKJadeRightKeys(network_, this); break;
  case PK_TYPE_KABAL_1: keys_ = new PKKabalLeftKeys(network_, this); break;
  case PK_TYPE_KABAL_2: keys_ = new PKKabalRightKeys(network_, this); break;
  case PK_TYPE_LIU_KANG_1: keys_ = new PKLiuKangLeftKeys(network_, this); break;
  case PK_TYPE_LIU_KANG_2: keys_ = new PKLiuKangRightKeys(network_, this); break;
  case PK_TYPE_REPTILE_1: keys_ = new PKReptileLeftKeys(network_, this); break;
  case PK_TYPE_REPTILE_2: keys_ = new PKReptileRightKeys(network_, this); break;
  case PK_TYPE_SCORPION_1: keys_ = new PKScorpionLeftKeys(network_, this); break;
  case PK_TYPE_SCORPION_2: keys_ = new PKScorpionRightKeys(network_, this); break;
  case PK_TYPE_SMOKE_1: keys_ = new PKSmokeLeftKeys(network_, this); break;
  case PK_TYPE_SMOKE_2: keys_ = new PKSmokeRightKeys(network_, this); break;
  case PK_TYPE_SONYA_1: keys_ = new PKSonyaLeftKeys(network_, this); break;
  case PK_TYPE_SONYA_2: keys_ = new PKSonyaRightKeys(network_, this); break;
  case PK_TYPE_SUB_ZERO_1: keys_ = new PKSubZeroLeftKeys(network_, this); break;
  case PK_TYPE_SUB_ZERO_2: keys_ = new PKSubZeroRightKeys(network_, this); break;
  default:
    dprintf(("pk3: error: unexpected paddle value %d at %d of %s\n",
	     paddle, __LINE__, __FILE__));
    assert(false) ;
  }

  // make everything appear

  // the graphics have been loaded; tell the gameserver we're ready
  network_->ready();
}


/*************************************************************************
 * Function Name: PKClient::cancel
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::cancel()
{
  returnToMainScreen();
}


/*************************************************************************
 * Function Name: PKClient::addObject
 * Parameters: PKID unique, PKTypeID type, PKPoint pos
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::addObject(const PKObject& obj)
{
  PKClientObject* sub = new PKClientObject(obj.getUniqueID(), obj.getTypeID(),
					   obj.getPosition(), obj.getVector());
  sub->setTime(gethrtime());
  if (top_) {
    PKObjectList* temp = new PKObjectList(sub);
    temp->setNext(top_);
    top_ = temp;
  }
  else top_ = new PKObjectList(sub);

  graphics_->addObject(obj.getUniqueID(), obj.getTypeID(), obj.getPosition());
}


/*************************************************************************
 * Function Name: PKClient::removeObject
 * Parameters: PKID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::removeObject(PKID id)
{
  if (top_) {
    PKObjectList* temp = top_->removeObject(id);
    if (top_ != temp) {
      delete(top_);
      top_ = temp;
    }
  }
  graphics_->removeObject(id);
}


/*************************************************************************
 * Function Name: PKClient::update
 * Parameters: int numElements, PKStatus[] updates
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::update(const PKObject& obj)
{
  PKClientObject* sub = new PKClientObject(obj.getUniqueID(), obj.getTypeID(),
					   obj.getPosition(), obj.getVector());
  sub->setTime(gethrtime());
  if (top_) top_->update(sub);
}


/*************************************************************************
 * Function Name: PKClient::updateAnimation
 * Parameters: PKID unique, PKAnimID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::updateAnimation(PKID unique, PKAnimID id)
{
  PKClientObject* object = top_->getObject(unique);

  // if being set to invisible, make sure we don't hide ourself
  if (id == PK_ANIM_INVISIBLE) {
    if (unique != player_) object->setAnimation(PK_ANIM_INVISIBLE);
  }
  // if being set to visible, set it to not animating
  else if (id == PK_ANIM_VISIBLE) {
    object->setAnimation(PK_ANIM_NOT);
  }
  // otherwise, if the object is not invisible, make it animate
  else if (object->getAnimation() != PK_ANIM_INVISIBLE) {
    object->setAnimation(id);
  }
  // if the object is invisible, ignore
}


/*************************************************************************
 * Function Name: PKClient::gameStatus
 * Parameters: PKGameStatus
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKClient::gameStatus(const PKGameStatus& stat)
{
  status_ = stat;
  graphics_->updateGameStatus(&status_);
}


/*************************************************************************
 * Function Name: PKClient::error
 * Parameters: const char *error 
 * Returns: void
 * Effects: create a new dialog; the dialog is unreferenced, and is therefore
 *          free to unallocate itself
 *************************************************************************/
void
PKClient::error(const char* err)
{
  printf("***ERROR***\t%s\t***ERROR***\n", err);
  //  new PKErrorDialog(parent_, err) ;
}

void
PKClient::endGame()
{
  gtk_widget_unmap(window_); // delete the graphics window
  if (graphics_) delete(graphics_); // kill the graphics themselves
  graphics_ = '\0';

  returnToMainScreen();
}


void
PKClient::playSound(PKSoundID id)
{
  audio_->playAudio (id);
}

void
PKClient::setPause(boolean paused)
{
  is_paused_ = paused; 
  dprintf(("PKClient: togglePause: pause is now %s\n",
	   is_paused_? "true" : "false"));
}

void
PKClient::rejectMe()
{
  network_->rejectPlayer(player_);
  ::exit(0);
}


void
PKClient::setKombatKode(int playerNum, const char* kode)
{
  unimplemented("PKClientImplementation::setKombatKode(.)");
}

void
PKClient::setChatText(int playerNum, const char* text)
{
  if (main_) main_->sendText((char *) text);
}






void PKClient::startSound() {
  PKSoundID sounds[] = {
    PK_SOUND_TOASTY,
    PK_SOUND_FIGHT,
    PK_SOUND_REPTILE_INVIS,
    PK_SOUND_SUB_PROJ_THROW,
    PK_SOUND_SUB_PROJ_HIT,
    PK_SOUND_BLOCK,
    PK_SOUND_UNBLOCK,
    PK_SOUND_CYRAX_BOMB_EXPLODE,
    PK_SOUND_CYRAX_BOMB_DROP,
    PK_SOUND_GUY_HIT,
    PK_SOUND_GIRL_HIT,
    PK_SOUND_KANG_HIT,
    PK_SOUND_GUY_DEATH,
    PK_SOUND_GIRL_DEATH,
    PK_SOUND_KANG_DEATH,
	PK_SOUND_ROUND,
	PK_SOUND_ONE,
	PK_SOUND_TWO,
	PK_SOUND_THREE
  } ;

  char *names[] = {
    "/cs/src/pk3/sounds/toasty",
    "/cs/src/pk3/sounds/fight",
    "/cs/src/pk3/sounds/skull",
    "/cs/src/pk3/sounds/freeze",
    "/cs/src/pk3/sounds/frozen",
    "/cs/src/pk3/sounds/donut",
    "/cs/src/pk3/sounds/morph",
    "/cs/src/pk3/sounds/bombexplode",
    "/cs/src/pk3/sounds/bomb",
    "/cs/src/pk3/sounds/hitGuy",
    "/cs/src/pk3/sounds/hitGirl",
    "/cs/src/pk3/sounds/hitKang",
    "/cs/src/pk3/sounds/guyDeath",
    "/cs/src/pk3/sounds/girlDeath",
    "/cs/src/pk3/sounds/kangDeath",
	"/cs/src/pk3/sounds/round",
	"/cs/src/pk3/sounds/one",
	"/cs/src/pk3/sounds/two",
	"/cs/src/pk3/sounds/three"
  } ;

  audio_ = new PKAudioPlayer(this, 15, sounds, names);
}  



