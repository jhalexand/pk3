
/*************************************************************************
 *    NAME: Michael Pellauer
 *    USER: cs032082
 *    FILE: PKPlayerPanel.cxx
 *    DATE: Sat Apr 26 22:25:57 US/Eastern 1997
 *************************************************************************/
#include "PKPlayerPanel.h"

#include <debug.h>
#include <PKClientNetworkInterface.h>
#include <PKGameClasses.h>
#include <PKids.h>
#include "PKInfoColumn.h"
#include "PKPaddleColumn.h"
#include <string.h>


/*************************************************************************
 * Function Name: PKPlayerPanel::PKPlayerPanel
 * Parameters: Widget parent, PKClientNetworkInterface* net
 * Effects: 
 *************************************************************************/

PKPlayerPanel::PKPlayerPanel(GtkWidget *parent, PKClientNetworkInterface* net,
			     const char* name,
			     const char* acct,
			     const char* host,
			     int team, int num)
{
  network_ = net;

  frame_ = gtk_frame_new("frame");
  gtk_frame_set_shadow_type (GTK_FRAME(frame_), GTK_SHADOW_OUT); 
  gtk_container_add(GTK_CONTAINER (parent), frame_);
  gtk_widget_show(frame_);

  row_ = gtk_hbox_new(FALSE, 0);
  gtk_container_add (GTK_CONTAINER (frame_), row_);
  gtk_widget_show(row_);

  /* the setup is:
     
    row(  paddlecol  infocol  )
         ---------------------
	 | paddles    name   |
	 | i        user@host| (user@host is info_)
	 |  m                |
	 |   a      team1    |
	 |    g     team2    |
	 |     e    reject   |
	 |          computer |
	 ---------------------
  */

  paddleColumn_ = new PKPaddleColumn(row_, this);
  infoColumn_ = new PKInfoColumn(row_, this, net, num, name, acct, host);

  // set the toggle to the appropriate state
  infoColumn_->setTeam(team);

  // add the paddles
  paddleColumn_->append("Cyrax"); 
  paddleColumn_->append("Jade");
  paddleColumn_->append("Kabal");
  paddleColumn_->append("Liu Kang");
  paddleColumn_->append("Reptile");
  paddleColumn_->append("Sub Zero");

  dprintf(("PKPlayerPanel: constructor done\n"));
}


/*************************************************************************
 * Function Name: PKPlayerPanel::realize
 * Parameters: 
 * Effects: 
 *************************************************************************/
void
PKPlayerPanel::realize()
{
  dprintf(("PKPlayerPanel: realizing\n"));
  dprintfLevelUp();
  paddleColumn_->realize();
  infoColumn_->realize();
  dprintfLevelDown();
  dprintf(("PKPlayerPanel: done realizing\n"));
}  

/*************************************************************************
 * Function Name: PKPlayerPanel::~PKPlayerPanel
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKPlayerPanel::~PKPlayerPanel()
{
  dprintf(("PKPlayerPanel: deleting panel\n"));
  delete paddleColumn_ ;
  delete infoColumn_ ;
  gtk_widget_destroy(row_);
  gtk_widget_destroy(frame_);
}

/*************************************************************************
 * Function Name: PKPlayerPanel::disableAsJoiner
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKPlayerPanel::disableAsJoiner()
{
  dprintf(("PKPlayerPanel: disabling as joiner\n"));
  dprintfLevelUp();
  infoColumn_->desensitizeToggles();
  infoColumn_->hideCreatorButtons();
  paddleColumn_->hideSelect();
  dprintfLevelDown();
  dprintf(("PKPlayerPanel: done disabling as joiner\n"));
}


/*************************************************************************
 * Function Name: PKPlayerPanel::disableAsCreator
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKPlayerPanel::disableAsCreator()
{
  dprintf(("PKPlayerPanel: disabling as creator\n"));
  dprintfLevelUp();
  infoColumn_->desensitizeToggles();
  paddleColumn_->hideSelect();
  dprintfLevelDown();
  dprintf(("PKPlayerPanel: done disabling as creator\n"));
}


/*************************************************************************
 * Function Name: PKPlayerPanel::disableAsSelf
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKPlayerPanel::disableAsSelf()
{
  dprintf(("PKPlayerPanel: disabling as self\n"));
  dprintfLevelUp();
  infoColumn_->hideCreatorButtons();
  dprintfLevelDown();
  dprintf(("PKPlayerPanel: done disabling as self\n"));
}


/*************************************************************************
 * Function Name: PKPlayerPanel::setPaddle
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKPlayerPanel::setPaddle(PKTypeID paddle) {
  char text[STRLEN];
  char *name ;

  switch(paddle) {
  case PK_TYPE_CYRAX_1:
  case PK_TYPE_CYRAX_2:    name = "Cyrax"; break;
  case PK_TYPE_JADE_1:
  case PK_TYPE_JADE_2:     name = "Jade" ; break;
  case PK_TYPE_KABAL_1:
  case PK_TYPE_KABAL_2:    name = "Kabal"; break;
  case PK_TYPE_LIU_KANG_1:
  case PK_TYPE_LIU_KANG_2: name = "Liu Kang"; break;
  case PK_TYPE_REPTILE_1:
  case PK_TYPE_REPTILE_2:  name = "Reptile"; break;
  case PK_TYPE_SCORPION_1:
  case PK_TYPE_SCORPION_2: name = "Scorpion"; break;
  case PK_TYPE_SMOKE_1:
  case PK_TYPE_SMOKE_2:    name = "Smoke"; break;
  case PK_TYPE_SONYA_1:
  case PK_TYPE_SONYA_2:    name = "Sonya"; break;
  case PK_TYPE_SUB_ZERO_1:
  case PK_TYPE_SUB_ZERO_2: name = "Sub Zero"; break;
  default: name = "blank";
  }

  paddleColumn_->showXpm(name);
}

/*************************************************************************
 * Function Name: PKPlayerPanel::show
 * Parameters: 
 * Returns: void
 * Effects: display a paddle's XPM
 *************************************************************************/
void
PKPlayerPanel::show(const char *paddlename) {
  paddleColumn_->showXpm(paddlename);
}



/*************************************************************************
 * Function Name: PKPlayerPanel::removePlayer
 * Parameters: 
 * Returns: void
 * Effects: null out the entries for the player
 *************************************************************************/
void
PKPlayerPanel::removePlayer()
{
  infoColumn_->removePlayer();
  paddleColumn_->showXpm("blank");
}

/*************************************************************************
 * Function Name: PKPlayerPanel::removePlayer
 * Parameters: 
 * Returns: void
 * Effects: null out the entries for the player
 *************************************************************************/
void
PKPlayerPanel::addPlayer(const PKPlayerInfo& info) {
  infoColumn_->addPlayer(info);
  setPaddle(info.paddle());
  setTeam(info.team());
}


/*************************************************************************
 * Function Name: PKPlayerPanel::
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKPlayerPanel::newPaddleSelected(const char *name)
{
  // the paddle will already have been graphically set
  PKTypeID idToSend ;

  if (!strcmp(name, "Cyrax"))         idToSend = PK_TYPE_CYRAX_1;
  else if (!strcmp(name, "Jade"))     idToSend = PK_TYPE_JADE_1;
  else if (!strcmp(name, "Kabal"))    idToSend = PK_TYPE_KABAL_1;
  else if (!strcmp(name, "Liu Kang")) idToSend = PK_TYPE_LIU_KANG_1;
  else if (!strcmp(name, "Reptile"))  idToSend = PK_TYPE_REPTILE_1;
  else if (!strcmp(name, "Scorpion")) idToSend = PK_TYPE_SCORPION_1;
  else if (!strcmp(name, "Smoke"))    idToSend = PK_TYPE_SMOKE_1;
  else if (!strcmp(name, "Sonya"))    idToSend = PK_TYPE_SONYA_1;
  else if (!strcmp(name, "Sub Zero")) idToSend = PK_TYPE_SUB_ZERO_1;

  network_->setPaddle(idToSend);
}



/*************************************************************************
 * Function Name: PKPlayerPanel::setTeam
 * Parameters: int team
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKPlayerPanel::setTeam(int team)
{
  infoColumn_->setTeam(team);
}
