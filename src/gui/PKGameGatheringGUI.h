/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKGameGatheringGUI.h                                */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 21:27:22 1997                            */
/****************************************************************/


#ifndef PKGAMEGATHERINGGUI_HEADER
#define PKGAMEGATHERINGGUI_HEADER
#include <Xm/Xm.h>
#include <PKids.h>
class PKPlayerInfo;
class PKClientNetworkInterface;
class PKPlayerPanel;
class PKClient;

const int NUMPLAYERS = 4 ;
class PKGameGatheringGUI {
public:
  PKGameGatheringGUI(Display *dsp, PKClientNetworkInterface* net,
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
  
  static void startCB(Widget, XtPointer thus, XtPointer) {
    ((PKGameGatheringGUI*)thus)->start() ;
  }
  static void quitCB(Widget, XtPointer thus, XtPointer) {
    ((PKGameGatheringGUI*)thus)->quit() ;
  }
  static void cancelJoinCB(Widget, XtPointer thus, XtPointer) {
    ((PKGameGatheringGUI*)thus)->cancelJoin() ;
  }
  static void cancelGameCB(Widget, XtPointer thus, XtPointer) {
    ((PKGameGatheringGUI*)thus)->cancelGame() ;
  }

  void start() ;
  void quit() ;
  void cancelJoin() ;
  void cancelGame() ;
  
protected:
  Widget shell_;
  Widget form_;
  Widget start_button_;
  Widget quit_button_;
  Widget cancel_button_;
  PKPlayerPanel *panel_[NUMPLAYERS] ;
  PKClientNetworkInterface* network_;
  PKClient* client_;
  int playerNumber_;
};
#endif
