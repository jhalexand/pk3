
#ifndef PKCHATBOX_HEADER
#define PKCHATBOX_HEADER

#include <gtk/gtk.h>
#include <glib.h>

class PKClientNetworkInterface;

class PKChatBox {
 public:
  PKChatBox(GtkWidget *parent, PKClientNetworkInterface *net, const char *n);
  virtual ~PKChatBox();
  void addText(char *text);
  void sendText();

  GtkWidget *input_;
 private:
  static void typeCB(GtkWidget *w, gpointer thus) {
    ((PKChatBox*)thus)->sendText();
  }
 protected:
  PKClientNetworkInterface* network_;
  GtkWidget *hbox_;
  GtkWidget *vscrollbar_;
  GtkWidget *output_;
  char name_[256];
};

#endif
