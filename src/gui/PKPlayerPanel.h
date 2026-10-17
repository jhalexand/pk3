/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKPlayerPanel.h                                     */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 22:13:44 1997                            */
/****************************************************************/


#ifndef PKPLAYERPANEL_HEADER
#define PKPLAYERPANEL_HEADER
#include <Xm/Xm.h>
#include <PKids.h>
class PKClientNetworkInterface;
class PKPlayerInfo;

// columns used by the panel
class PKPaddleColumn ;
class PKInfoColumn ;

class PKPlayerPanel {
public:
  PKPlayerPanel(Widget parent, PKClientNetworkInterface* net,
		const char* name,
		const char* acct,
		const char* host,
		int team, int num);
  void realize() ;
  virtual ~PKPlayerPanel();

  void disableAsJoiner();
  void disableAsCreator();
  void disableAsSelf();
  void setPaddle(PKTypeID paddle);
  void setTeam(int team);
  void removePlayer();
  void addPlayer(const PKPlayerInfo& info);

  void newPaddleSelected(const char *name);

  void show(const char *paddleName);

  void showSelect();
private:
  static void rejectButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKPlayerPanel*)thus)->reject();
  }

  static void team1CB(Widget, XtPointer thus, XtPointer) {
    ((PKPlayerPanel*)thus)->setTeam(1);
  }

  static void team2CB(Widget, XtPointer thus, XtPointer) {
    ((PKPlayerPanel*)thus)->setTeam(2);
  }

  static void paddleCB(Widget, XtPointer thus, XtPointer) {
    ((PKPlayerPanel*)thus)->paddle();
  }
    
  static void compButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKPlayerPanel*)thus)->computerize();
  }

  void reject();
  void team(int number); // team number is 1 or 2
  void paddle();
  void computerize();
    
protected:
  PKClientNetworkInterface* network_;
  PKPaddleColumn *paddleColumn_ ;
  PKInfoColumn *infoColumn_ ;
  Widget frame_ ;
  Widget row_; // inset in the frame
};

#endif
