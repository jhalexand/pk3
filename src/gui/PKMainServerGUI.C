/*************************************************************************
 *    NAME: Michael Pellauer
 *    USER: cs032082
 *    FILE: PKMainServerGUI.cxx
 *    DATE: Sat Apr 26 22:25:56 US/Eastern 1997
 *************************************************************************/
#include "PKMainServerGUI.h"
#include "PKClient.h"
#include "PKGame.h"
#include "PKUser.h"
#include "PKChatBox.h"
#include <PKClientNetworkInterface.h>
#include <PKGameClasses.h>
#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/List.h>
#include <Xm/RowColumn.h>

#include <stdlib.h>

/*************************************************************************
 * Function Name: PKMainServerGUI::PKMainServerGUI
 * Parameters: XtAppContext parent, PKClientNetworkInterface* net
 * Effects: 
 *************************************************************************/

PKMainServerGUI::PKMainServerGUI(Widget& parent, PKClientNetworkInterface* net, const char* name, PKClient* client)
{
  network_ = net;
  client_ = client;
  top_ = null;
  users_ = null;
  current_ = null ;

  
  Widget row = XtVaCreateManagedWidget("row", xmRowColumnWidgetClass, parent,
				       XmNorientation, XmHORIZONTAL,
				       XmNnumColumns, 3, NULL);
  Widget col = XtVaCreateManagedWidget("col", xmRowColumnWidgetClass, row,
				       XmNorientation, XmVERTICAL, NULL);
  Widget col2 = XtVaCreateManagedWidget("col", xmRowColumnWidgetClass, row,
				       XmNorientation, XmVERTICAL, NULL);
  Widget col3 = XtVaCreateManagedWidget("col", xmRowColumnWidgetClass, row,
				       XmNorientation, XmVERTICAL, NULL);
  
  game_list_ = XtVaCreateManagedWidget("games", xmListWidgetClass, col,
				       XmNselectionPolicy, XmSINGLE_SELECT,
				       XmNvisibleItemCount, 20,
				       XmNscrollBarDisplayPolicy, XmSTATIC,
				       XmNlistSizePolicy, XmCONSTANT,
				       XmNleftAttachment, XmATTACH_FORM,
				       XmNtopAttachment, XmATTACH_FORM,
				       XmNbottomAttachment, XmATTACH_FORM,
				       NULL);
  user_list_ = XtVaCreateManagedWidget("users", xmListWidgetClass, col2,
				       XmNselectionPolicy, XmSINGLE_SELECT,
				       XmNvisibleItemCount, 20,
				       XmNscrollBarDisplayPolicy, XmSTATIC,
				       XmNlistSizePolicy, XmCONSTANT,
				       XmNleftAttachment, XmATTACH_WIDGET,
				       XmNtopAttachment, XmATTACH_FORM,
				       XmNbottomAttachment, XmATTACH_FORM,
				       XmNleftWidget, game_list_,
				       NULL);
  form_ = XtVaCreateWidget("form", xmFormWidgetClass, col3,
				 NULL);  
  chat_ = new PKChatBox(form_, network_, name);
  join_button_ = XtVaCreateManagedWidget("join", xmPushButtonWidgetClass,
					 form_,
					 XmNleftAttachment, XmATTACH_WIDGET,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNleftWidget, user_list_,
					 XmNtopWidget, chat_->input_,
					 NULL);
  create_button_ = XtVaCreateManagedWidget("create", xmPushButtonWidgetClass,
					 form_,
					 XmNleftAttachment, XmATTACH_WIDGET,
					 XmNtopAttachment, XmATTACH_WIDGET,
					   // XmNrightAttachment, XmATTACH_FORM,
					 XmNleftWidget, join_button_,
					 XmNtopWidget, chat_->input_,
					 NULL);
  quit_button_ = XtVaCreateManagedWidget("quit", xmPushButtonWidgetClass,
					 form_,
					 XmNleftAttachment, XmATTACH_WIDGET,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 // XmNrightAttachment, XmATTACH_FORM,
					 XmNleftWidget, create_button_,
					 XmNtopWidget, chat_->input_,
					 NULL);
  XtAddCallback(join_button_, XmNactivateCallback,
		PKMainServerGUI::joinButtonCB,
                (XtPointer) this);
  XtAddCallback(create_button_, XmNactivateCallback,
		PKMainServerGUI::createButtonCB,
                (XtPointer) this);  
  XtAddCallback(quit_button_, XmNactivateCallback,
		PKMainServerGUI::quitButtonCB,
                (XtPointer) this);
  XtAddCallback(game_list_, XmNsingleSelectionCallback,
		PKMainServerGUI::listCB,
                (XtPointer) this);  
  XtManageChild(form_);
}


/*************************************************************************
 * Function Name: PKMainServerGUI::~PKMainServerGUI
 * Parameters: 
 * Returns: void
 * Effects: destroys form and all its children, frees current_
 *************************************************************************/

PKMainServerGUI::~PKMainServerGUI()
{
  XtDestroyWidget(form_) ;
  free(current_) ;
}

/*************************************************************************
 * Function Name: PKMainServerGUI::join
 * Parameters: 
 * Returns: void
 * Effects: Joins a game
 *************************************************************************/
void
PKMainServerGUI::join()
{
  char *curgame = getCurrentGame();
  int id = getGameID(curgame);
  if (id) {
    network_->joinGame(id);
  }
    
  else client_->error("Error! No game selected!");
}


/*************************************************************************
 * Function Name: PKMainServerGUI::quitButtonCB
 * Parameters: Widget widget, XtPointer client_data, XtPointer call_data
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKMainServerGUI::quit()
{
  ::exit(0);
}


/*************************************************************************
 * Function Name: PKMainServerGUI::createButtonCB
 * Parameters: Widget widget, XtPointer client_data, XtPointer call_data
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKMainServerGUI::create()
{
  network_->createGame();
}

void
PKMainServerGUI::list(XmListCallbackStruct *data)
{
  char* string;
  XmStringGetLtoR(data->item, XmSTRING_DEFAULT_CHARSET,
		  &string);
  setCurrent(string);
  XtFree(string);
}

/*************************************************************************
 * Function Name: PKMainServerGUI::addUser
 * Parameters: char* user
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKMainServerGUI::addUser(int ID, const char* user, 
                         const char* account, const char* host)
{
  if (users_) {
    PKUser* newuser = new PKUser(ID, user, account, host);
    newuser->setNext(users_);
    users_ = newuser;
  } else {
    users_ = new PKUser(ID, user, account, host);
  }
  XmListAddItemUnselected(user_list_, XmStringCreateSimple((char*)user), 0);
}


/*************************************************************************
 * Function Name: PKMainServerGUI::removeUser
 * Parameters: char* user
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKMainServerGUI::removeUser(int ID)
{
  dprintf(("PKMainServerGUI: told to remove user %d (%s)\n",
	   ID, users_->getUser(ID) ? users_->getUser(ID) : "nil"));

  if (users_) {
    XmString Xtext = XmStringCreateSimple(users_->getUser(ID));
    XmListDeleteItem(user_list_, Xtext);
    XmStringFree(Xtext);
    users_ = users_->removeUser(ID);
  }
}


/*************************************************************************
 * Function Name: PKMainServerGUI::addGame
 * Parameters: char* game
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKMainServerGUI::addGame(const char* game, int gameID)
{
  dprintf(("PKMainServerGUI: told to add game %d (%s)\n",
	   gameID, game));


  if (top_) {
    if(top_->getGame(gameID)) {
      dprintf(("PKMainServerGUI: warning: game %d already exists\n", gameID));
      return ;
    }
    PKGame* temp = new PKGame(game, gameID);
    temp->setNext(top_);
    top_ = temp;
  } else top_ = new PKGame(game, gameID);

  XmString Xgame = XmStringCreateSimple((char*)game);
  XmListAddItemUnselected(game_list_, Xgame, 0);
  XmStringFree(Xgame);

}


/*************************************************************************
 * Function Name: PKMainServerGUI::removeGame
 * Parameters: char* game
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKMainServerGUI::removeGame(int ID)
{
  dprintf(("PKMainServerGUI: told to remove game %d (%s)\n",
	   ID, top_->getGame(ID) ? top_->getGame(ID) : "nil"));

  if(top_) {
    XmString Xgame = XmStringCreateSimple((char*)top_->getGame(ID));
    XmListDeleteItem(game_list_, Xgame);
    XmStringFree(Xgame);
    top_ = top_->removeGame(ID);
  }
}

int
PKMainServerGUI::getGameID(const char* game) {
  if (game && top_) {
    return top_->getID(game);
  }
  return 0 ;
}
void
PKMainServerGUI::sendText(const char * t)
{
    if (chat_) chat_->addText(t);
}
