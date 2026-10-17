#ifndef PKERRORDIALOG_HEADER
#define PKERRORDIALOG_HEADER

#include <Xm/Xm.h>

class PKErrorDialog {
private:
  Widget dialog_ ;
  int dlgnumber_;
  static int instanceCount_;

public:
  PKErrorDialog(Widget parent, const char *errorMsg) ;
  ~PKErrorDialog() ;

private:
  static void okCallback(Widget, void *thus, void*) {
    ((PKErrorDialog*)thus)->ok() ;
  }

  void ok() ;
} ;
  

#endif
