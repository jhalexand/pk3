#ifndef PKINFOCOLUMN_HEADER
#define PKINFOCOLUMN_HEADER

#include <Xm/Xm.h>
class PKPlayerInfo ;
class PKPlayerPanel ;
class PKClientNetworkInterface ;

class PKInfoColumn {
private:
  PKPlayerPanel *panel_ ;
  PKClientNetworkInterface *network_ ;
  int playerNumber_ ;
  Widget column_ ; // the top-level widget for this class
  Widget name_; // nickname
  Widget info_; // user@host
  Widget teamToggle_[2]; // make this a radio column
  Widget reject_;
  Widget computerize_;
public:
  PKInfoColumn(Widget parent, PKPlayerPanel *panel,
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
  static void static_computerize(Widget, void *thus, void*) {
    ((PKInfoColumn*)thus)->computerize();
  }
  static void static_reject(Widget, void *thus, void*) {
    ((PKInfoColumn*)thus)->reject();
  }
  static void static_team1(Widget, void *thus, void*) {
    ((PKInfoColumn*)thus)->teamTo1();
  }
  static void static_team2(Widget, void *thus, void*) {
    ((PKInfoColumn*)thus)->teamTo2();
  }
  
  void computerize();
  void reject();
  void teamToggle(int teamnumber); // 1 or 2
  void teamTo1(); // These are added to attempt to fix team bug -mip.
  void teamTo2();
} ;

#endif
