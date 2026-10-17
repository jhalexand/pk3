/*************************************************************************
 *    NAME: Michael Pellauer
 *    USER: cs032082
 *    FILE: PKKonnectGUI.cxx
 *    DATE: Sat Apr 26 22:25:57 US/Eastern 1997
 *************************************************************************/
#include "PKKonnectGUI.h"
#include "PKClient.h"
#include <PKResources.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <stdlib.h>


/*************************************************************************
 * Function Name: PKKonnectGUI::PKKonnectGUI
 * Parameters: Widget parent, PKClient* client
 * Effects: 
 *************************************************************************/

PKKonnectGUI::PKKonnectGUI(Widget parent, PKClient* client)
{
  client_ = client;
  form_ = XtVaCreateWidget("form", xmFormWidgetClass, parent,
			   NULL);
  name_field_ = XtVaCreateManagedWidget("name", xmTextFieldWidgetClass,
					form_,
					XmNtopAttachment, XmATTACH_FORM,
					XmNleftAttachment, XmATTACH_FORM,
					NULL);
  XmTextFieldSetString(name_field_, (char*)pk3rc.nickname());// cast away const
  name_ = XtVaCreateManagedWidget("User Name", xmLabelWidgetClass,
				  form_,
				  XmNtopAttachment, XmATTACH_WIDGET,
				  XmNleftAttachment, XmATTACH_FORM,
				  XmNtopWidget, name_field_,
				  NULL);
  host_field_ = XtVaCreateManagedWidget("host", xmTextFieldWidgetClass,
					form_,
					XmNtopAttachment, XmATTACH_WIDGET,
					XmNleftAttachment, XmATTACH_FORM,
					XmNtopWidget, name_,
					NULL);
  XmTextFieldSetString(host_field_, (char*)pk3rc.server());
  host_ = XtVaCreateManagedWidget("Host Address", xmLabelWidgetClass,
				  form_,
				  XmNtopAttachment, XmATTACH_WIDGET,
				  XmNleftAttachment, XmATTACH_FORM,
				  XmNtopWidget, host_field_,
				  NULL);
  port_field_ = XtVaCreateManagedWidget("port", xmTextFieldWidgetClass,
					form_,
					XmNtopAttachment, XmATTACH_WIDGET,
					XmNleftAttachment, XmATTACH_FORM,
					XmNtopWidget, host_,
					NULL);
  port_ = XtVaCreateManagedWidget("Port", xmLabelWidgetClass,
				  form_,
				  XmNtopAttachment, XmATTACH_WIDGET,
				  XmNleftAttachment, XmATTACH_FORM,
				  XmNtopWidget, port_field_,
				  NULL);
  if (pk3rc.port() == 0) XmTextFieldSetString(port_field_, "4380");
  else {
    char portstr[7]; // port is unsigned short, so 6 digits + '\0'
    sprintf(portstr, "%hu", pk3rc.port()) ;
    XmTextFieldSetString(port_field_, portstr);
  }
  join_button_ = XtVaCreateManagedWidget("Konnect!", xmPushButtonWidgetClass,
					 form_,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNleftAttachment, XmATTACH_FORM,
					 XmNtopWidget, port_,
					 NULL);
  quit_button_ = XtVaCreateManagedWidget("Quit", xmPushButtonWidgetClass,
					 form_,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNleftAttachment, XmATTACH_WIDGET,
					 XmNtopWidget, port_,
					 XmNleftWidget, join_button_,
					 NULL);

  XtAddCallback(join_button_, XmNactivateCallback, PKKonnectGUI::joinButtonCB,
                (XtPointer) this);
  XtAddCallback(quit_button_, XmNactivateCallback, PKKonnectGUI::quitButtonCB,
                (XtPointer) this);  
  XtManageChild(form_);
}

/*************************************************************************
 * Function Name: PKKonnectGUI::~PKKonnectGUI
 * Parameters:
 * Effects: 
 *************************************************************************/

PKKonnectGUI::~PKKonnectGUI()
{
  dprintf(("PKCLIENT: Destroying opening GUI\n"));
  XtDestroyWidget(form_);
}

/*************************************************************************
 * Function Name: PKKonnectGUI::join
 * Parameters:
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKKonnectGUI::join()
{
  client_->enterMainServer(XmTextGetString(host_field_),
			   XmTextGetString(name_field_),
			   XmTextGetString(port_field_));
}


/*************************************************************************
 * Function Name: PKKonnectGUI::quit
 * Parameters:
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKKonnectGUI::quit()
{
  ::exit(0);
}


