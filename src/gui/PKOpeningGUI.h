/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKOpeningGUI.h                                      */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 21:02:52 1997                            */
/****************************************************************/


#ifndef PKOPENINGGUI_HEADER
#define PKOPENINGGUI_HEADER
#include <Xm/Xm.h>

class PKClient;
class GUIXpmImage;
class GUIXpmButton;

class PKOpeningGUI {
public:
  PKOpeningGUI(Widget parent, PKClient* client);
  ~PKOpeningGUI() ;
  void realize();

private:
  static void singleButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKOpeningGUI*)thus)->single() ;
  }
  static void multiButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKOpeningGUI*)thus)->multi() ;
  }
  static void quitButtonCB(Widget, XtPointer thus, XtPointer) {
    ((PKOpeningGUI*)thus)->quit() ;
  }

  void single() ;
  void multi() ;
  void quit() ;

protected:

  GUIXpmImage *title_;  
  GUIXpmImage *single_image_;
  GUIXpmImage *multi_image_;
  GUIXpmImage *quit_image_;
  Widget form_;
  Widget picture_;
  Widget single_button_;
  Widget multi_button_;
  Widget quit_button_;
  int hasRealized_;
  PKClient* client_;
};
#endif
