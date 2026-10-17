/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKErrorDialog.C
 *    DATE: Mon Oct  6 16:17:34 US/Eastern 1997
 *************************************************************************/
#include "PKErrorDialog.h"

#include <debug.h>
#include <Xm/MessageB.h>

int PKErrorDialog::instanceCount_ = 0 ;

/*************************************************************************
 * Function Name: PKErrorDialog::PKErrorDialog
 * Parameters: const char *errorMsg
 * Effects: 
 *************************************************************************/

PKErrorDialog::PKErrorDialog(Widget parent, const char *errorMsg) 
{
  Arg arg;
  dialog_ = XmCreateErrorDialog(parent, "Error", &arg, 0);
  dlgnumber_ = ++instanceCount_ ;

  // hide the help and cancel buttons
  XtUnmanageChild(XmMessageBoxGetChild(dialog_, XmDIALOG_HELP_BUTTON));
  XtUnmanageChild(XmMessageBoxGetChild(dialog_, XmDIALOG_CANCEL_BUTTON));

  // set the message string to display errorMsg
  XmString emsg = XmStringCreateSimple((char*)errorMsg); // cast away const
  XmString title= XmStringCreateSimple("Error");
  XtVaSetValues(dialog_,
		XmNmessageString, emsg,
		XmNdialogTitle, title,
		NULL);
  XmStringFree(emsg);

  // make it go away on ok
  XtAddCallback(dialog_, XmNokCallback, PKErrorDialog::okCallback,
                (XtPointer) this);

  // display everything
  XtManageChild(dialog_);
}


/*************************************************************************
 * Function Name: PKErrorDialog::~PKErrorDialog
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKErrorDialog::~PKErrorDialog() 
{
  dprintf(("PKDIALOG: dialog %d (error dialog) going away now\n", dlgnumber_));
  XtDestroyWidget(dialog_);
}


/*************************************************************************
 * Function Name: PKErrorDialog::ok
 * Parameters: 
 * Returns: void
 * Effects: commits suicide
 *************************************************************************/
void
PKErrorDialog::ok() 
{
  delete this ; // safe: no one else is holding a reference to us	   
}


