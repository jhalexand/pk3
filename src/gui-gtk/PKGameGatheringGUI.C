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

/*************************************************************************
 * Function Name: PKGameGatheringGUI::PKGameGatheringGUI
 * Parameters: XtAppContext parent, PKClientNetworkInterface* net
 * Effects: 
 *************************************************************************/

PKGameGatheringGUI::PKGameGatheringGUI(PKClientNetworkInterface* net,
		     PKClient* client, int num,
		     const char* user, const char* acct, const char* host,
		     const char* defpaddle, int defteam)
{
  //dprintf(("PKGameGatheringGUI: initializing with num=%d\n", num));
  network_ = net;
  client_ = client;
  playerNumber_ = num;
  window_ = gtk_window_new(GTK_WINDOW_DIALOG);
  gtk_widget_show(window_);
  
  row_ = gtk_hbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER (window_), row_);
  gtk_widget_show(row_);
  
  column_[0] = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER (row_), column_[0]);
  gtk_widget_show(column_[0]);
 
  column_[1] = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER (row_), column_[1]);
  gtk_widget_show(column_[1]);

  column_[2] = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER (row_), column_[2]);
  gtk_widget_show(column_[2]);

  if (!defteam) defteam = 1;
  
  // create PKPlayerPanels on appropriate column, with appropriate
  // values
  for(int i=0; i<NUMPLAYERS; i++) {
    if(i==num) {
      panel_[i] = new PKPlayerPanel(column_[i/2], network_, user, acct, host,
				    defteam, i); // i == num
    }
    else {
      panel_[i] = new PKPlayerPanel(column_[i/2], network_,
				    null, null, null,
				    1, i);
      panel_[i]->show("blank");
    }
  }

  start_button_ = gtk_button_new_with_label("Start");
  gtk_signal_connect(GTK_OBJECT (start_button_), "clicked",
		     GTK_SIGNAL_FUNC (PKGameGatheringGUI::startCB), this);
  gtk_widget_show(start_button_);
  if (num) gtk_widget_set_sensitive(GTK_WIDGET(start_button_), FALSE);

  cancel_button_ = gtk_button_new_with_label("Cancel");

  // if we're the creator, cancel destroys the game; if not, we just reject
  // ourself (cancel joining)
  if (num==0) {
    gtk_signal_connect(GTK_OBJECT (cancel_button_), "clicked",
		       GTK_SIGNAL_FUNC (PKGameGatheringGUI::cancelGameCB), this);
  } else {
    gtk_signal_connect(GTK_OBJECT (cancel_button_), "clicked",
		       GTK_SIGNAL_FUNC (PKGameGatheringGUI::cancelJoinCB), this);
  }
  gtk_widget_show(cancel_button_);
 
  quit_button_ = gtk_button_new_with_label("Quit");
  gtk_signal_connect(GTK_OBJECT (quit_button_), "clicked",
		     GTK_SIGNAL_FUNC (PKGameGatheringGUI::quitCB), this);
  gtk_widget_show(quit_button_);

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
  //Figure out how GTK handles memory here.
  for(int i=0; i<NUMPLAYERS; i++) {
    delete panel_[i];
  }
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


