/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKGameGatheringGUI.h                                */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 21:27:22 1997                            */
/****************************************************************/


#ifndef PKGAMEGATHERINGGUI_HEADER
#define PKGAMEGATHERINGGUI_HEADER

#include <PKids.h>
#include <gtk/gtk.h>
#include <glib.h>

class PKPlayerInfo;
class PKClientNetworkInterface;
class PKPlayerPanel;
class PKClient;

const int NUMPLAYERS = 4 ;
class PKGameGatheringGUI {
public:
  PKGameGatheringGUI(PKClientNetworkInterface* net,
		     PKClient* client, int num,
		     const char* user, const char* acct, const char* host,
		     const char* defpaddle, int defteam);
  virtual ~PKGameGatheringGUI();
  void realize() ;

  void setPaddle(int player, PKTypeID paddle);
  void addPlayer(int player, const PKPlayerInfo& info);
  void removePlayer(int player);
  void rejectPlayer(int player);
  void setTeam(int player, int team);


private:
  
  static void startCB(GtkWidget *widget, gpointer thus) {
    ((PKGameGatheringGUI*)thus)->start() ;
  }
  static void quitCB(GtkWidget *widget, gpointer thus) {
    ((PKGameGatheringGUI*)thus)->quit() ;
  }
  static void cancelJoinCB(GtkWidget *widget, gpointer thus) {
    ((PKGameGatheringGUI*)thus)->cancelJoin() ;
  }
  static void cancelGameCB(GtkWidget *widget, gpointer thus) {
    ((PKGameGatheringGUI*)thus)->cancelGame() ;
  }

  void start() ;
  void quit() ;
  void cancelJoin() ;
  void cancelGame() ;
  
protected:
  GtkWidget *window_;
  GtkWidget *row_;
  GtkWidget *column_[3];
  GtkWidget *start_button_;
  GtkWidget *quit_button_;
  GtkWidget *cancel_button_;
  PKPlayerPanel *panel_[NUMPLAYERS] ;
  PKClientNetworkInterface* network_;
  PKClient* client_;
  int playerNumber_;
};
#endif
