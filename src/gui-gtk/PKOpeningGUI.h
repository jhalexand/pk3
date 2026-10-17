/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKOpeningGUI.h                                      */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 21:02:52 1997                            */
/****************************************************************/


#ifndef PKOPENINGGUI_HEADER
#define PKOPENINGGUI_HEADER
#include <gtk/gtk.h>
class PKClient;

class PKOpeningGUI {
public:
  PKOpeningGUI(PKClient* client);
  ~PKOpeningGUI() ;

private:
  static void joinButtonCB(GtkWidget *widget, gpointer thus) {
    ((PKOpeningGUI*)thus)->join() ;
  }
  static void quitButtonCB(GtkWidget *widget, gpointer thus) {
    ((PKOpeningGUI*)thus)->quit() ;
  }

  void join() ;
  void quit() ;

protected:
  GtkWidget *box_;
  GtkWidget *name_field_;
  GtkWidget *name_;
  GtkWidget *host_field_;
  GtkWidget *host_;
  GtkWidget *port_field_;
  GtkWidget *port_;  
  GtkWidget *join_button_;
  GtkWidget *quit_button_;
  GtkWidget *window_;

  PKClient* client_;
};
#endif
