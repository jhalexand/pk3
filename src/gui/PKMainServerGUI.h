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
#include <Xm/Xm.h>
class PKClientNetworkInterface;
class PKClient;
class PKGame;
class PKUser;
class PKChatBox;

class PKMainServerGUI {
public:
  PKMainServerGUI(Widget& parent,
		  PKClientNetworkInterface* net,
		  const char *name,
		  PKClient* client);
  ~PKMainServerGUI() ;
  void addUser(int ID, const char* user, const char* account, const char* host);
  void removeUser(int ID);
  void addGame(const char* game, int gameID);
  void removeGame(int ID);
  void sendText(const char *t) ;
  int getGameID(const char* game);
  char* getCurrentGame() { return current_;}
  void setCurrent(const char* cur) {
    if(current_) free(current_) ;
    current_ = strdup(cur) ;
  }

private:
  static void joinButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKMainServerGUI*)thus)->join();
  }
  static void quitButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKMainServerGUI*)thus)->quit();
  }
    
  static void createButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKMainServerGUI*)thus)->create();
  }
  static void listCB(Widget, XtPointer thus, XtPointer calldata) {
    ((PKMainServerGUI*)thus)->list((XmListCallbackStruct*)calldata);
  }

  void join() ;
  void quit() ;
  void create();
  void list(XmListCallbackStruct *data);
    
protected:
  PKClientNetworkInterface* network_;
  PKClient* client_;
  Widget form_;
  Widget game_list_;
  Widget user_list_;
  Widget join_button_;
  Widget create_button_;
  Widget quit_button_;
  PKChatBox* chat_;
  PKGame* top_;
  PKUser* users_;
  char* current_;
};
#endif
