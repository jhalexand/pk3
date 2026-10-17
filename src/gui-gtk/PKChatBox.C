#include <stdio.h>
#include "PKChatBox.h"
#include "PKClientNetworkInterface.h"


PKChatBox::PKChatBox(GtkWidget *parent, PKClientNetworkInterface *net, const char *n) : network_(net) {  
  output_ = gtk_text_new(NULL,NULL);
  gtk_text_set_editable(GTK_TEXT(output_), FALSE);
  gtk_box_pack_start(GTK_BOX(parent), output_, TRUE, TRUE, 0);
  GtkWidget *vscrollbar = gtk_vscrollbar_new (GTK_TEXT(output_)->vadj);
  gtk_box_pack_start(GTK_BOX(parent), vscrollbar, FALSE, FALSE, 0);
  gtk_widget_show (vscrollbar);
  
  input_ = gtk_entry_new_with_max_length(80);
  gtk_box_pack_start(GTK_BOX(parent),input_,TRUE,TRUE, 0);
  gtk_signal_connect(GTK_OBJECT(input_), "activate",
		     GTK_SIGNAL_FUNC(PKChatBox::typeCB),this);
  gtk_widget_show(input_);

  strcpy(name_, n);
}

 
PKChatBox::~PKChatBox() {
  //Sigh. More memory stuff.
}

void
PKChatBox::addText(char *text) {
  gtk_text_insert(GTK_TEXT(output_),NULL,NULL,NULL,text, -1);
}

void
PKChatBox::sendText() {
  char tmp[256];
  sprintf(tmp, "%s: %s\n",name_,gtk_entry_get_text(GTK_ENTRY(input_)));
  network_->sendChatText(tmp);
  gtk_entry_set_text(GTK_ENTRY(input_), NULL);
}
