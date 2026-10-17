/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKMainServerGUI.h                                   */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 21:18:43 1997                            */
/****************************************************************/


#ifndef PKMAINSERVERGUI_HEADER
#define PKMAINSERVERGUI_HEADER

#include <stdlib.h> // free
#include <string.h> // strdup
#include <gtk/gtk.h>
#include <glib.h>
class PKClientNetworkInterface;
class PKClient;
class PKGame;
class PKUser;
class PKChatBox;

class PKMainServerGUI {
public:
  PKMainServerGUI(PKClientNetworkInterface* net,
		  const char *name,
		  PKClient* client);
  ~PKMainServerGUI() ;
  void addUser(int ID, char* user, char* account, char* host);
  void removeUser(int ID);
  void addGame(char* game, int gameID);
  void removeGame(int ID);
  void sendText(char *t) ;
  int getGameID(char* game);
  char* getCurrentGame() { return current_;}
  void setCurrent(char* cur) {
    if(current_) free(current_) ;
    current_ = strdup(cur) ;
  }

private:
  static void joinButtonCB(GtkWidget *w, gpointer thus) {
    ((PKMainServerGUI*)thus)->join();
  }
  static void quitButtonCB(GtkWidget *w, gpointer thus) {
    ((PKMainServerGUI*)thus)->quit();
  }
    
  static void createButtonCB(GtkWidget *w, gpointer thus) {
    ((PKMainServerGUI*)thus)->create();
  }
  static void listCB(GtkWidget *clist, gint row, gint column,
		     GdkEventButton *event, gpointer thus) {
    char *text = new char[255];
    gtk_clist_get_text(GTK_CLIST(clist), row, column, &text);
    ((PKMainServerGUI*)thus)->setCurrent(text);
    delete text;
  }

  void join() ;
  void quit() ;
  void create();
    
protected:
  PKClientNetworkInterface* network_;
  PKClient* client_;
  GtkWidget *window_;
  GtkWidget *box_;
  GtkWidget *vbox_;
  GtkWidget *game_list_;
  GtkWidget *user_list_;
  GtkWidget *join_button_;
  GtkWidget *create_button_;
  GtkWidget *quit_button_;
  PKChatBox* chat_;
  PKGame* top_;
  PKUser* users_;
  char* current_;
};
#endif
