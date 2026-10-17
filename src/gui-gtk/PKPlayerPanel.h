/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKPlayerPanel.h                                     */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 22:13:44 1997                            */
/****************************************************************/


#ifndef PKPLAYERPANEL_HEADER
#define PKPLAYERPANEL_HEADER
#include <gtk/gtk.h>
#include <glib.h>
#include <PKids.h>
class PKClientNetworkInterface;
class PKPlayerInfo;

// columns used by the panel
class PKPaddleColumn ;
class PKInfoColumn ;

class PKPlayerPanel {
public:
  PKPlayerPanel(GtkWidget *parent, PKClientNetworkInterface* net,
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

private:
  static void rejectButtonCB(GtkWidget *widget, gpointer thus) {
    //((PKPlayerPanel*)thus)->reject();
  }

  static void team1CB(GtkWidget *widget, gpointer thus) {
    ((PKPlayerPanel*)thus)->setTeam(1);
  }

  static void team2CB(GtkWidget *widget, gpointer thus) {
    ((PKPlayerPanel*)thus)->setTeam(2);
  }

  static void paddleCB(GtkWidget *widget, gpointer thus) {
    //((PKPlayerPanel*)thus)->paddle();
  }
    
  static void compButtonCB(GtkWidget *widget, gpointer thus) {
    //((PKPlayerPanel*)thus)->computerize();
  }

  void reject();
  void team(int number); // team number is 1 or 2
  void computerize();
    
protected:
  PKClientNetworkInterface* network_;
  PKPaddleColumn *paddleColumn_ ;
  PKInfoColumn *infoColumn_ ;
  GtkWidget *frame_ ;
  GtkWidget *row_; // inset in the frame
};

#endif
