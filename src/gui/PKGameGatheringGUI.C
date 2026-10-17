/*************************************************************************
 *    NAME: Michael Pellauer
 *    USER: cs032082
 *    FILE: PKGameGatheringGUI.cxx
 *    DATE: Sat Apr 26 22:25:56 US/Eastern 1997
 *************************************************************************/
#include "PKGameGatheringGUI.h"
#include "PKPlayerPanel.h"
#include "PKClient.h"
#include <PKids.h>
#include <PKGameClasses.h>
#include <PKClientNetworkInterface.h>
#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>

/*************************************************************************
 * Function Name: PKGameGatheringGUI::PKGameGatheringGUI
 * Parameters: XtAppContext parent, PKClientNetworkInterface* net
 * Effects: 
 *************************************************************************/

PKGameGatheringGUI::PKGameGatheringGUI(Display *dsp,
				       PKClientNetworkInterface* net,
				       PKClient* client, int num,
				       const char* name,
				       const char* acct,
				       const char* host,
				       const char* defpaddle,
				       int defteam)
{
  dprintf(("PKGameGatheringGUI: initializing with num=%d\n", num));

  shell_ = XtVaAppCreateShell("Game", "PK", topLevelShellWidgetClass,
			       dsp, NULL);

  network_ = net;
  client_ = client;
  playerNumber_ = num;

  Widget row = XtVaCreateManagedWidget("row", xmRowColumnWidgetClass, shell_,
				       XmNorientation, XmHORIZONTAL,
				       XmNnumColumns, 3, NULL);

  Widget column[3] ;
  column[0] = XtVaCreateManagedWidget("column0", xmRowColumnWidgetClass, row,
				   XmNorientation, XmVERTICAL, NULL);
  column[1] = XtVaCreateManagedWidget("column1", xmRowColumnWidgetClass, row,
				   XmNorientation, XmVERTICAL, NULL);
  column[2] = XtVaCreateManagedWidget("column2", xmRowColumnWidgetClass, row,
				   XmNorientation, XmVERTICAL, NULL);
  if (!defteam) defteam = 1;

  // create PKPlayerPanels on appropriate column, with appropriate
  // values
  for(int i=0; i<NUMPLAYERS; i++) {
    if(i==num) {
      panel_[i] = new PKPlayerPanel(column[i/2], network_, name, acct, host,
				    defteam, i); // i == num
    }
    else {
      panel_[i] = new PKPlayerPanel(column[i/2], network_,
				    null, null, null,
				    1, i);
      panel_[i]->show("blank");
    }
  }

  form_ = XtVaCreateManagedWidget("form", xmFormWidgetClass, column[2], NULL);
  start_button_ = XtVaCreateManagedWidget("Start", xmPushButtonWidgetClass,
					  form_,
					  XmNleftAttachment, XmATTACH_FORM,
					  XmNrightAttachment, XmATTACH_FORM,
					  XmNtopAttachment, XmATTACH_FORM,
					  NULL);
  if (num) XtSetSensitive(start_button_, False);
  cancel_button_ = XtVaCreateManagedWidget("Cancel", xmPushButtonWidgetClass,
					   form_,
					   XmNleftAttachment, XmATTACH_FORM,
					   XmNrightAttachment, XmATTACH_FORM,
					   XmNtopAttachment, XmATTACH_WIDGET,
					   XmNtopWidget, start_button_,
					   NULL);
  quit_button_ = XtVaCreateManagedWidget("Quit", xmPushButtonWidgetClass,
					 form_,
					 XmNleftAttachment, XmATTACH_FORM,
					 XmNrightAttachment, XmATTACH_FORM,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNtopWidget, cancel_button_,
					 NULL);

  XtAddCallback(start_button_, XmNactivateCallback,
		PKGameGatheringGUI::startCB,
                (XtPointer) this);

  // if we're the creator, cancel destroys the game; if not, we just reject
  // ourself (cancel joining)
  if (num==0) XtAddCallback(cancel_button_, XmNactivateCallback,
			    PKGameGatheringGUI::cancelGameCB,
			    (XtPointer) this);
  else XtAddCallback(cancel_button_, XmNactivateCallback,
		     PKGameGatheringGUI::cancelJoinCB,
		     (XtPointer) this);

  XtAddCallback(quit_button_, XmNactivateCallback,
		PKGameGatheringGUI::quitCB,
                (XtPointer) this);
}


/*************************************************************************
 * Function Name: PKGameGatheringGUI::realize
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameGatheringGUI::realize()
{
  XtRealizeWidget(shell_);
  int i ;
  // disable the panels
  dprintf(("PKGameGatheringGUI: disabling panels\n"));
  dprintfLevelUp();
  if(playerNumber_==0) {
    // creator
    for(i=1; i<NUMPLAYERS; i++) {
      panel_[i]->disableAsCreator();
    }
    panel_[0]->disableAsSelf() ;
  }
  else {
    // joiner
    for(i=0; i<NUMPLAYERS; i++) {
      if(i!=playerNumber_) panel_[i]->disableAsJoiner();
      else panel_[i]->disableAsSelf();
    }
  }
  dprintfLevelDown();
  dprintf(("PKGameGatheringGUI: done disabling panels\n"));

  // realize the panels
  for(i=0; i<NUMPLAYERS; i++) {
    panel_[i]->realize();
  }
}


/*************************************************************************
 * Function Name: PKGameGatheringGUI::~PKGameGatheringGUI
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKGameGatheringGUI::~PKGameGatheringGUI()
{
  XtUnmapWidget(shell_);
  for(int i=0; i<NUMPLAYERS; i++) {
    delete panel_[i];
  }
  XtDestroyWidget(shell_);
}

/*************************************************************************
 * Function Name: PKGameGatheringGUI::start
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameGatheringGUI::start()
{
  network_->startGame();
}

void
PKGameGatheringGUI::cancelGame()
{
  network_->cancelGame();
}

void
PKGameGatheringGUI::cancelJoin()
{
  network_->rejectPlayer(playerNumber_) ;
}

/*************************************************************************
 * Function Name: PKGameGatheringGUI::quitButtonCB
 * Parameters: Widget widget, XtPointer client_data, XtPointer call_data
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameGatheringGUI::quit()
{
  ::exit(0);
}


/*************************************************************************
 * Function Name: PKGameGatheringGUI::setPaddle
 * Parameters: int player, PKTypeID paddle
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameGatheringGUI::setPaddle(int player, PKTypeID paddle)
{
  panel_[player]->setPaddle(paddle);
}


/*************************************************************************
 * Function Name: PKGameGatheringGUI::removePlayer
 * Parameters: int player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameGatheringGUI::removePlayer(int player)
{
  panel_[player]->removePlayer() ;
}


void
PKGameGatheringGUI::rejectPlayer(int player)
{
  if(playerNumber_ == player) {
    client_->returnToMainScreen();
  }
  else {
    panel_[player]->removePlayer();
  }
}


/*************************************************************************
 * Function Name: PKGameGatheringGUI::setTeam
 * Parameters: int player, int team
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameGatheringGUI::setTeam(int player, int team)
{
  panel_[player]->setTeam(team) ;
}

void
PKGameGatheringGUI::addPlayer(int player, const PKPlayerInfo& info)
{
  panel_[player]->addPlayer(info) ;
}


