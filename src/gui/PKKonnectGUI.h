/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKKonnectGUI.h                                      */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 21:02:52 1997                            */
/****************************************************************/


#ifndef PKKONNECTGUI_HEADER
#define PKKONNECTGUI_HEADER
#include <Xm/Xm.h>
class PKClient;

class PKKonnectGUI {
public:
  PKKonnectGUI(Widget parent, PKClient* client);
  ~PKKonnectGUI() ;

private:
  static void joinButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKKonnectGUI*)thus)->join() ;
  }
  static void quitButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKKonnectGUI*)thus)->quit() ;
  }

  void join() ;
  void quit() ;

protected:
  Widget form_;
  Widget name_field_;
  Widget name_;
  Widget host_field_;
  Widget host_;
  Widget port_field_;
  Widget port_;  
  Widget join_button_;
  Widget quit_button_;

  PKClient* client_;
};
#endif
