/*************************************************************************
 *    NAME: Michael Pellauer
 *    USER: cs032082
 *    FILE: PKOpeningGUI.cxx
 *    DATE: Sat Apr 26 22:25:57 US/Eastern 1997
 *************************************************************************/
#include "PKOpeningGUI.h"
#include "PKClient.h"
#include "GUIXpmImage.h"
#include <PKResources.h>
#include <PKPaths.h>

#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <Xm/DrawnB.h>
#include <Xm/DrawingA.h>
#include <stdlib.h>


/*************************************************************************
 * Function Name: PKOpeningGUI::PKOpeningGUI
 * Parameters: Widget parent, PKClient* client
 * Effects: 
 *************************************************************************/

PKOpeningGUI::PKOpeningGUI(Widget parent, PKClient* client) : hasRealized_(0)
{
  client_ = client;
  
  
  form_ = XtVaCreateManagedWidget("paddleCol", xmFormWidgetClass,
				    parent,
                                    XmNnumColumns, 2,
				    NULL);

  picture_ = XtVaCreateManagedWidget("picture", xmDrawingAreaWidgetClass,
				     form_,
                                     XmNwidth, 400,
                                     XmNheight, 432,
				     XmNtopAttachment, XmATTACH_FORM,
				     XmNbottomAttachment, XmATTACH_FORM,
				     NULL);

   Widget hack = XtVaCreateManagedWidget("hack", xmDrawingAreaWidgetClass,
				     form_,
                                     XmNwidth, 250,
                                     XmNheight, 90,
				     XmNtopAttachment, XmATTACH_FORM,
				     XmNrightAttachment, XmATTACH_FORM,
				     XmNleftAttachment, XmATTACH_WIDGET,
				     XmNbackground, Pixel(0),
				     XmNleftWidget, picture_,
				     NULL);

  title_ = new GUIXpmImage(strcat(PK_GRAPHICS_PATH, "misc/pk3title-large.xpm"), picture_);


  single_image_ = new GUIXpmImage(strcat(PK_BUTTON_PATH,"single.xpm"), picture_);

  single_button_ = XtVaCreateManagedWidget("Single Player", xmDrawnButtonWidgetClass,
					 form_,
					 XmNrightAttachment, XmATTACH_FORM,
					 XmNleftAttachment, XmATTACH_WIDGET,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNbackground, Pixel(0),
					 XmNleftWidget, picture_,
					 XmNtopWidget, hack,
					 XmNlabelType,    XmPIXMAP,
					 XmNlabelPixmap,  single_image_->getImage(),
					 NULL);
					 
  multi_image_ = new GUIXpmImage(strcat(PK_BUTTON_PATH,"multi.xpm"), picture_);

  multi_button_ = XtVaCreateManagedWidget("Multi-Player", xmDrawnButtonWidgetClass,
					 form_,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNtopWidget, single_button_,
					 XmNrightAttachment, XmATTACH_FORM,
					 XmNleftAttachment, XmATTACH_WIDGET,
					 XmNbackground, Pixel(0),
					 XmNleftWidget, picture_,
					 XmNlabelType,    XmPIXMAP,
					 XmNlabelPixmap,  multi_image_->getImage(),
					 NULL);

  quit_image_ = new GUIXpmImage(strcat(PK_BUTTON_PATH,"quit.xpm"), picture_);

  quit_button_ = XtVaCreateManagedWidget("Quit", xmDrawnButtonWidgetClass,
					 form_,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNrightAttachment, XmATTACH_FORM,
					 XmNbottomAttachment, XmATTACH_FORM,
					 XmNleftAttachment, XmATTACH_WIDGET,
					 XmNtopWidget, multi_button_,
					 XmNbackground, Pixel(0),
					 XmNleftWidget, picture_,
					 XmNlabelType,    XmPIXMAP,
					 XmNlabelPixmap,  quit_image_->getImage(),
					 NULL);
  
  XtAddCallback(single_button_, XmNactivateCallback, PKOpeningGUI::singleButtonCB,
                (XtPointer) this);
		
  XtAddCallback(multi_button_, XmNactivateCallback, PKOpeningGUI::multiButtonCB,
                (XtPointer) this);

  XtAddCallback(quit_button_, XmNactivateCallback, PKOpeningGUI::quitButtonCB,
                (XtPointer) this);  

}

/*************************************************************************
 * Function Name: PKOpeningGUI::~PKOpeningGUI
 * Parameters:
 * Effects: 
 *************************************************************************/

PKOpeningGUI::~PKOpeningGUI()
{
  dprintf(("PKCLIENT: Destroying opening GUI\n"));
  if (title_) delete title_;
  if (single_image_) delete single_image_;
  if (multi_image_) delete multi_image_;
  if (quit_image_) delete quit_image_;
  XtDestroyWidget(form_);
}

void
PKOpeningGUI::realize()
{
  dprintf(("PKOpeningGUI: realizing\n"));
  hasRealized_ = 1 ;
  XtManageChild(form_);
  if(title_) title_->draw(picture_);
  dprintf(("PKOpeningGUI: done realizing\n"));
}
/*************************************************************************
 * Function Name: PKOpeningGUI::single
 * Parameters:
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKOpeningGUI::single()
{
  client_->enterSinglePlayer();
}

/*************************************************************************
 * Function Name: PKOpeningGUI::join
 * Parameters:
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKOpeningGUI::multi()
{
  client_->enterKonnectScreen();
}


/*************************************************************************
 * Function Name: PKOpeningGUI::quit
 * Parameters:
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKOpeningGUI::quit()
{
  ::exit(0);
}


