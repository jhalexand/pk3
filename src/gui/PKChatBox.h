
#ifndef PKCHATBOX_HEADER
#define PKCHATBOX_HEADER

#include <Xm/Xm.h>

class PKClientNetworkInterface;

class PKChatBox {
 public:
  PKChatBox(Widget parent, PKClientNetworkInterface *net, const char *n);
  virtual ~PKChatBox();
  void addText(const char *text);
  void sendText();

  Widget input_;
 private:
  static void typeCB(Widget, XtPointer thus, XtPointer t) {
    ((PKChatBox*)thus)->sendText();
  } 

 protected:
  PKClientNetworkInterface* network_;
  Widget output_t;
  XmTextPosition pos_;
  char name_[256];
};

#endif
