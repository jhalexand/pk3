/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKPaddleColumn.C
 *    DATE: Mon Oct  6 21:50:46 US/Eastern 1997
 *************************************************************************/
#include "PKPaddleColumn.h"

#include <PKPaths.h>
#include <string.h>
#include "PKPlayerPanel.h"

/*************************************************************************
 * Function Name: PKPaddleColumn::PKPaddleColumn
 * Parameters: Widget parent
 * Effects: 
 *************************************************************************/

PKPaddleColumn::PKPaddleColumn(GtkWidget *parent, PKPlayerPanel *panel)
{
  panel_ = panel ;
  hasRealized_ = FALSE ;
  hide_ = FALSE ;
  form_ = gtk_vbox_new(FALSE, 0);
  gtk_container_add (GTK_CONTAINER (parent), form_);
  gtk_widget_show(form_);

  /*  Arg args[20];
  Cardinal n = 0;
  XmString Xstr = XmStringCreateSimple("");

  XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);n++;
  listPulldownMenu_ = XmCreatePulldownMenu(form_, "pulldown", args, n);

  n = 0 ;
  XtSetArg(args[n], XmNsubMenuId, listPulldownMenu_);n++;
  XtSetArg(args[n], XmNlabelString, Xstr);n++;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);n++;
  listOptionMenu_ = XmCreateOptionMenu(form_, "option", args, n);

  XmStringFree(Xstr);
  

  picture_ = XtVaCreateManagedWidget("picture", xmDrawingAreaWidgetClass,
				     form_,
				     XmNshadowType, XmSHADOW_ETCHED_OUT,
//				     XmNwidth, 123,
//				     XmNheight, 155,
                                     XmNwidth, 200,
                                     XmNheight, 200,
				     XmNtopAttachment, XmATTACH_WIDGET,
				     XmNtopWidget, listOptionMenu_,
				     XmNbottomAttachment, XmATTACH_FORM,
				     NULL);
				     */
  //dprintf(("PKPaddleColumn: done initializing\n"));
}


/*************************************************************************
 * Function Name: PKPaddleColumn::~PKPaddleColumn
 * Parameters:
 * Returns: void
 * Effects: Don't draw the XPM until you've realized, which happens here
 *************************************************************************/
void
PKPaddleColumn::realize()
{
  //dprintf(("PKPaddleColumn: realizing\n"));
  hasRealized_ = TRUE ;
  /* if(xpmImage_) xpmImage_->draw(picture_);
  XtManageChild(optionMenu());*/
  if(hide_) {
    hideSelect();
  }
  //dprintf(("PKPaddleColumn: done realizing\n"));
}

/*************************************************************************
 * Function Name: PKPaddleColumn::~PKPaddleColumn
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKPaddleColumn::~PKPaddleColumn() 
{
  /*
  ULDIterator it(names_) ;
  while(it.current()) {
    delete (PKPaddleButton*)it.curdata();
    names_.set(it.current(), null);
    it.next();
  }
  */
  gtk_widget_destroy(form_);
}


/*************************************************************************
 * Function Name: PKPaddleColumn::append
 * Parameters: const char *paddlename
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKPaddleColumn::append(const char *paddlename)
{
  //dprintf(("PKPaddleColumn: appending %s\n", paddlename));
  /*names_.set(paddlename, new PKPaddleButton(listPulldownMenu_,
					    panel_, this,
					    paddlename));*/
}



/*************************************************************************
 * Function Name: PKPaddleColumn::append
 * Parameters: const char *paddlename
 * Returns: void
 * Effects: show the spec'd xpm, unless we haven't realized yet
 *************************************************************************/
void
PKPaddleColumn::showXpm(const char *name)
{
  /*if(xpmImage_) table_->delImage(xpmImage_, picture_);
  char filename[STRLEN];
  sprintf(filename, "%s/%s.xpm", PKSTARTUPPADDLEPATH, name);
  xpmImage_ = table_->getImage(filename, picture_) ;
  if(hasRealized_) {
    xpmImage_->draw(picture_);
  }
  */
}

/*************************************************************************
 * Function Name: PKPaddleButton::hide
 * Parameters: 
 * Effects: 
 *************************************************************************/
void
PKPaddleColumn::hideSelect()
{
  //dprintf(("PKPaddleColumn: hiding select\n"));
  if(hasRealized_) {
    /* gtk_widget_unmap(optionMenu());*/
  }
  else {
    hide_ = TRUE ;
  }
  //dprintf(("PKPaddleColumn: done hiding select\n"));
}


/*************************************************************************
 * Function Name: PKPaddleButton::show
 * Parameters: 
 * Effects: 
 *************************************************************************/
void
PKPaddleColumn::showSelect()
{
  if(hasRealized_) {
    /* XtMapWidget(optionMenu());*/
  }
  else {
    hide_ = FALSE ;
  }
}





/*************************************************************************
 * Function Name: PKPaddleButton::PKPaddleButton
 * Parameters: Widget parent, const char *name
 * Effects: 
 *************************************************************************/

PKPaddleButton::PKPaddleButton(GtkWidget *parent,
			       PKPlayerPanel* panel, PKPaddleColumn *column,
			       const char *name)
{
  panel_  = panel ; 
  column_ = column ;
  name_   = strdup(name);
  /* 
  XmString tempStr = XmStringCreateSimple((char*)name);
  button_ = XtVaCreateManagedWidget(name, xmPushButtonWidgetClass,
				    parent,
				    XmNlabelString, tempStr,
				    NULL);
  XtAddCallback(button_, XmNactivateCallback, PKPaddleButton::selectedCallback,
		(XtPointer) this);

  XmStringFree(tempStr);*/
}


/*************************************************************************
 * Function Name: PKPaddleButton::~PKPaddleButton
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKPaddleButton::~PKPaddleButton() 
{
  gtk_widget_destroy(button_);
  //free((char*)name_);
}


/*************************************************************************
 * Function Name: PKPaddleButton::selected
 * Parameters: 
 * Effects: 
 *************************************************************************/
void
PKPaddleButton::selected()
{
  column_->showXpm(name_);
  panel_->newPaddleSelected(name_);
}


