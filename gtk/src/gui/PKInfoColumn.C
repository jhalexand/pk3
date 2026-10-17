/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKInfoColumn.C
 *    DATE: Wed Oct  8  2:46:34 US/Eastern 1997
 *************************************************************************/
#include "PKInfoColumn.h"

#include <debug.h>

// project-wide includes
#include <PKClientNetworkInterface.h>
#include <PKGameClasses.h>
#include <PKids.h>

// GUI-specific includes
#include "PKPlayerPanel.h"


/*************************************************************************
 * Function Name: PKInfoColumn::PKInfoColumn
 * Parameters: Widget parent, PKPlayerPanel *panel, const char *name, const char *host, const char *acct
 * Effects: 
 *************************************************************************/

PKInfoColumn::PKInfoColumn(GtkWidget *parent, PKPlayerPanel *panel,
			   PKClientNetworkInterface *network,
			   int playerNumber,
			   const char *name,
			   const char *acct,
			   const char *host)

{
  panel_ = panel ;
  network_ = network ;
  playerNumber_ = playerNumber ;

  column_ = gtk_vbox_new(FALSE, 0);
  gtk_container_add (GTK_CONTAINER (parent), column_);
  gtk_widget_show(column_);

  name_ = gtk_label_new (name);
  gtk_box_pack_start(GTK_BOX(column_), name_, TRUE, TRUE, 0);
  gtk_widget_show(name_);
   
  info_ = gtk_label_new (strcat(acct, strcat("@",host)));
  gtk_box_pack_start(GTK_BOX(column_), info_, TRUE, TRUE, 0);
  gtk_widget_show(info_);
   
  // add the team toggles
  teamToggle_[0] = gtk_toggle_button_new_with_label("Team 1"); 
  gtk_box_pack_start(GTK_BOX(column_), teamToggle_[0], TRUE, TRUE, 0);
  gtk_signal_connect (GTK_OBJECT (teamToggle_[0]), "toggled",
		      GTK_SIGNAL_FUNC (PKInfoColumn::static_team1), this);
  gtk_widget_show(teamToggle_[0]);


  teamToggle_[1] = gtk_toggle_button_new_with_label("Team 2"); 
  gtk_box_pack_start(GTK_BOX(column_), teamToggle_[1], TRUE, TRUE, 0);
  gtk_signal_connect (GTK_OBJECT (teamToggle_[1]), "toggled",
		      GTK_SIGNAL_FUNC (PKInfoColumn::static_team2), this);
  gtk_widget_show(teamToggle_[1]);

  // add the computerize button
  computerize_ = gtk_button_new_with_label("Computerize");
  gtk_box_pack_start(GTK_BOX(column_), computerize_, TRUE, TRUE, 0);
  gtk_signal_connect (GTK_OBJECT (computerize_), "clicked",
		      GTK_SIGNAL_FUNC (PKInfoColumn::static_computerize), this);
  gtk_widget_show(computerize_);
  
  // add the reject button
  reject_ = gtk_button_new_with_label("Reject");
  gtk_box_pack_start(GTK_BOX(column_), reject_, TRUE, TRUE, 0);
  gtk_signal_connect (GTK_OBJECT (reject_), "clicked",
		      GTK_SIGNAL_FUNC (PKInfoColumn::static_reject), this);
  gtk_widget_show(reject_);

  // all done now
}


/*************************************************************************
 * Function Name: PKInfoColumn::realize
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::realize()
{
  dprintf(("PKInfoColumn: realizing\n"));
  dprintf(("PKInfoColumn: done realizing\n"));
}


/*************************************************************************
 * Function Name: PKInfoColumn::~PKInfoColumn
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKInfoColumn::~PKInfoColumn()
{
  gtk_widget_destroy(column_);
}


/*************************************************************************
 * Function Name: PKInfoColumn::setTeam
 * Parameters: int teamnum
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::setTeam(int teamnum) 
{
  teamnum--;
  if (teamnum) {
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[1]), True);
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[0]), False);
  } else {
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[0]), True);
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[1]), False);
  }
}


/*************************************************************************
 * Function Name: PKInfoColumn::addPlayer
 * Parameters: const PKPlayerInfo& player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::addPlayer(const PKPlayerInfo& player)
{
  char buf[STRLEN];

  sprintf(buf, "%.16s", player.username());
  gtk_label_set(GTK_LABEL(name_), buf);
    
  sprintf(buf, "%.8s@%.7s", player.account(), player.hostname());
  gtk_label_set(GTK_LABEL(info_), buf);
}


/*************************************************************************
 * Function Name: PKInfoColumn::addAI
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::addAI()
{
  network_->addAIPlayer(playerNumber_, PK_AI_DUMB);
  PKPlayerInfo tp;
  tp.setUsername("Computer");
  tp.setAccount("itself");
  tp.setHostname("itself");
  gtk_widget_set_sensitive(teamToggle_[0], 1);
  gtk_widget_set_sensitive(teamToggle_[1], 1);
  panel_->addPlayer(tp);
}


/*************************************************************************
 * Function Name: PKInfoColumn::removePlayer
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::removePlayer()
{
  gtk_label_set(GTK_LABEL (name_), " ");
  gtk_label_set(GTK_LABEL (info_), " ");
}


/*************************************************************************
 * Function Name: PKInfoColumn::hideCreatorButtons
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::hideCreatorButtons()
{ 
  gtk_widget_unmap(reject_);
  gtk_widget_unmap(computerize_);
}


/*************************************************************************
 * Function Name: PKInfoColumn::desensitizeToggles
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::desensitizeToggles()
{
  dprintf(("PKInfoColumn: desensitizing toggles\n"));
  gtk_widget_set_sensitive(teamToggle_[0], 0);
  gtk_widget_set_sensitive(teamToggle_[1], 0);
  dprintf(("PKInfoColumn: done desensitizing toggles\n"));
}


/*************************************************************************
 * Function Name: PKInfoColumn::computerize
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::computerize()
{
  addAI();
}


/*************************************************************************
 * Function Name: PKInfoColumn::reject
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::reject()
{
  network_->rejectPlayer(playerNumber_);
}


/*************************************************************************
 * Function Name: PKInfoColumn::teamToggle
 * Parameters: int teamnumber
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKInfoColumn::teamToggle(int teamnum)
{
  // the toggle button will be already set correctly, but make sure
  // it's right
  if (GTK_TOGGLE_BUTTON (teamToggle_[teamnum-1])->active) {
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[teamnum-1]), 1);
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[teamnum-1]), 0);
    network_->setTeam(playerNumber_, teamnum);
  } else {
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[teamnum-1]), 0);
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[teamnum-1]), 1);
    network_->setTeam(playerNumber_, teamnum);
  }
}

void
PKInfoColumn::teamTo1()
{
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[0]), 1);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[1]), 0);
  network_->setTeam(playerNumber_, 1);
}
  
void
PKInfoColumn::teamTo2()
{
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[1]), 1);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(teamToggle_[0]), 0);
  network_->setTeam(playerNumber_, 2);
}
  
