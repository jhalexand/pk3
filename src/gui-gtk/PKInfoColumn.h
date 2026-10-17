#ifndef PKINFOCOLUMN_HEADER
#define PKINFOCOLUMN_HEADER

#include <gtk/gtk.h>
#include <glib.h>

class PKPlayerInfo ;
class PKPlayerPanel ;
class PKClientNetworkInterface ;

class PKInfoColumn {
private:
  PKPlayerPanel *panel_ ;
  PKClientNetworkInterface *network_ ;
  int playerNumber_ ;
  GtkWidget *column_ ; // the top-level widget for this class
  GtkWidget *name_; // nickname
  GtkWidget *info_; // user@host
  GtkWidget *teamToggle_[2]; // make this a radio column
  GtkWidget *reject_;
  GtkWidget *computerize_;
public:
  PKInfoColumn(GtkWidget *parent, PKPlayerPanel *panel,
	       PKClientNetworkInterface *network,
	       int playerNumber,
	       const char *name,
	       const char *acct,
	       const char *host);
  void realize();
  virtual ~PKInfoColumn();

  void setTeam(int teamnum) ; // teamnum is 1 or 2
  void addPlayer(const PKPlayerInfo& player);
  void addAI();
  void removePlayer();
  
  void hideCreatorButtons();
  void desensitizeToggles();

private:
  static void static_computerize(GtkWidget *widget, gpointer thus)  {
    ((PKInfoColumn*)thus)->computerize();
  }
  static void static_reject(GtkWidget *widget, gpointer thus)  {
    ((PKInfoColumn*)thus)->reject();
  }
  static void static_team1(GtkWidget *widget, gpointer thus)  {
    ((PKInfoColumn*)thus)->teamTo1();
  }
  static void static_team2(GtkWidget *widget, gpointer thus) {
    ((PKInfoColumn*)thus)->teamTo2();
  }
  
  void computerize();
  void reject();
  void teamToggle(int teamnumber); // 1 or 2
  void teamTo1(); // These are added to attempt to fix team bug -mip.
  void teamTo2();
} ;

#endif
