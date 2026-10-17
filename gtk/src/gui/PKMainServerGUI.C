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

#include <stdlib.h>

/*************************************************************************
 * Function Name: PKMainServerGUI::PKMainServerGUI
 * Parameters: XtAppContext parent, PKClientNetworkInterface* net
 * Effects: 
 *************************************************************************/

PKMainServerGUI::PKMainServerGUI(PKClientNetworkInterface* net, const char* name, PKClient* client)
{
  network_ = net;
  client_ = client;
  top_ = '\0';
  users_ = '\0';
  current_ = '\0' ;

  window_ = gtk_window_new(GTK_WINDOW_DIALOG);

  box_ = gtk_hbox_new(FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window_), box_);

  game_list_ = gtk_clist_new(1);
  /*gtk_clist_set_border(GTK_CLIST(game_list_), GTK_SHADOW_OUT);
  gtk_clist_set_policy(GTK_CLIST(game_list_), GTK_POLICY_AUTOMATIC,
		       GTK_POLICY_AUTOMATIC);*/
  gtk_box_pack_start(GTK_BOX(box_), game_list_, TRUE, TRUE, 0);

  user_list_ = gtk_clist_new(1);
  /*gtk_clist_set_border(GTK_CLIST(user_list_), GTK_SHADOW_OUT);
  gtk_clist_set_policy(GTK_CLIST(user_list_), GTK_POLICY_AUTOMATIC,
		       GTK_POLICY_AUTOMATIC);*/
  gtk_box_pack_start(GTK_BOX(box_), user_list_, TRUE, TRUE, 0);

  vbox_ = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box_), vbox_, FALSE, TRUE, 0);

  chat_ = new PKChatBox(vbox_, network_, name);


  join_button_ = gtk_button_new_with_label("Join Game");
  gtk_signal_connect (GTK_OBJECT (join_button_), "clicked",
		      GTK_SIGNAL_FUNC (PKMainServerGUI::joinButtonCB), this);
  gtk_box_pack_start(GTK_BOX(vbox_), join_button_, FALSE, TRUE, 0);


  create_button_ = gtk_button_new_with_label("Create Game");
  gtk_signal_connect (GTK_OBJECT (create_button_), "clicked",
		      GTK_SIGNAL_FUNC (PKMainServerGUI::createButtonCB), this);
  gtk_box_pack_start(GTK_BOX(vbox_), create_button_, FALSE, TRUE, 0);


  quit_button_ = gtk_button_new_with_label("Quit");
  gtk_signal_connect (GTK_OBJECT (quit_button_), "clicked",
		      GTK_SIGNAL_FUNC (PKMainServerGUI::quitButtonCB), this);
  gtk_box_pack_start(GTK_BOX(vbox_), quit_button_, FALSE, TRUE, 0);

  gtk_widget_show(join_button_);
  gtk_widget_show(create_button_);
  gtk_widget_show(quit_button_);
  gtk_widget_show(vbox_);
  gtk_widget_show(game_list_);
  gtk_widget_show(user_list_);
  gtk_widget_show(box_);
  gtk_widget_show(window_);
}


/*************************************************************************
 * Function Name: PKMainServerGUI::~PKMainServerGUI
 * Parameters: 
 * Returns: void
 * Effects: destroys form and all its children, frees current_
 *************************************************************************/

PKMainServerGUI::~PKMainServerGUI()
{
  gtk_widget_destroy(window_);
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

/*************************************************************************
 * Function Name: PKMainServerGUI::addUser
 * Parameters: char* user
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKMainServerGUI::addUser(int ID, char* user, char* account, char* host)
{
  if (users_) {
    PKUser* newuser = new PKUser(ID, user, account, host);
    newuser->setNext(users_);
    users_ = newuser;
  } else {
    users_ = new PKUser(ID, user, account, host);
  }
  cout << "Adding a user to the list!" << endl;
  gtk_clist_append(GTK_CLIST(user_list_), &user);
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
  /*dprintf(("PKMainServerGUI: told to remove user %d (%s)\n",
	   ID, users_->getUser(ID) ? users_->getUser(ID) : "nil"));*/

  if (users_) {
    int k = 0, not_done = 1;
    char *user_gtk = new char[256];
    char *user = new char[256];
    user = users_->getUser(ID);
    while (not_done) {
      gtk_clist_get_text(GTK_CLIST(user_list_), k, 0, &user_gtk);
      not_done = strcmp(user, user_gtk);
      if (!not_done) {
	gtk_clist_remove(GTK_CLIST(user_list_), k);
      }
      k++;
    }
    users_ = users_->removeUser(ID);
    delete user_gtk;
    delete user;
  }
}


/*************************************************************************
 * Function Name: PKMainServerGUI::addGame
 * Parameters: char* game
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKMainServerGUI::addGame(char* game, int gameID)
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
  cout << "Adding a game to the list." << endl;
  gtk_clist_append(GTK_CLIST(game_list_), &game);
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
    int k = 0, not_done = 1;
    char *game_gtk = new char[256];
    char *game = new char[256];
    game = (char*) top_->getGame(ID);
    while (not_done) {
      gtk_clist_get_text(GTK_CLIST(game_list_), k, 0, &game_gtk);
      not_done = strcmp(game, game_gtk);
      if (!not_done) {
	gtk_clist_remove(GTK_CLIST(game_list_), k);
      }
      k++;
    }
    top_ = top_->removeGame(ID);
    delete game_gtk;
    delete game;
  }
}

int
PKMainServerGUI::getGameID(char* game) {
  if (game && top_) {
    return top_->getID(game);
  }
  return 0 ;
}
void
PKMainServerGUI::sendText(char * t)
{
    if (chat_) chat_->addText(t);
}
