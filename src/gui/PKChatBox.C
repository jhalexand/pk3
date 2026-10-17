#include <stdio.h>
#include "PKChatBox.h"
#include "PKClientNetworkInterface.h"
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/TextF.h>
#include <Xm/Text.h>


PKChatBox::PKChatBox(Widget parent, PKClientNetworkInterface *net, const char *n) : network_(net) {
  output_t = XtVaCreateManagedWidget("OutputT", xmTextWidgetClass,
				     parent,
				     XmNeditMode, XmMULTI_LINE_EDIT,
				     XmNeditable, False,
				     XmNrows, 10,
				     XmNcolumns, 80,
				     XmNtopAttachment, XmATTACH_FORM,
				     NULL);
  input_ = XtVaCreateManagedWidget("Input", xmTextFieldWidgetClass,
				   parent,
				   XmNrows, 1,
				   XmNcolumns, 80,
				   XmNtopAttachment, XmATTACH_WIDGET,
				   XmNtopWidget, output_t,
				   NULL);
  strcpy(name_, n);
  XtAddCallback(input_, XmNactivateCallback, typeCB, this);
}

 
PKChatBox::~PKChatBox() {
  XtDestroyWidget(output_t) ;
  XtDestroyWidget(input_) ;
}

void
PKChatBox::addText(const char *text) {
  XmTextInsert(output_t,
	       pos_,
	       (char*)text);
  pos_ += strlen(text);
  XmTextShowPosition(output_t,
		 pos_);
}

void
PKChatBox::sendText() {
  char tmp[256];
  sprintf(tmp, "%s: %s\n",name_,XmTextGetString(input_));
  network_->sendChatText(tmp);
  XmTextSetString(input_, NULL);
}
