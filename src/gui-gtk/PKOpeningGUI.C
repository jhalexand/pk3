/*************************************************************************
 *    NAME: Michael Pellauer
 *    USER: cs032082
 *    FILE: PKOpeningGUI.cxx
 *    DATE: Sat Apr 26 22:25:57 US/Eastern 1997
 *************************************************************************/
#include "PKOpeningGUI.h"
#include "PKClient.h"
#include <PKResources.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>


/*************************************************************************
 * Function Name: PKOpeningGUI::PKOpeningGUI
 * Parameters: XtAppContext parent, PKClientNetworkInterface net
 * Effects: 
 *************************************************************************/

PKOpeningGUI::PKOpeningGUI(PKClient* client) : client_(client)
{
  window_ = gtk_window_new(GTK_WINDOW_DIALOG);
  box_ = gtk_vbox_new(FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window_), box_);

  name_field_ = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(name_field_), (char*)pk3rc.nickname());
  gtk_box_pack_start(GTK_BOX(box_), name_field_, TRUE, TRUE, 0);

  name_ = gtk_label_new("Nickname");
  gtk_box_pack_start(GTK_BOX(box_), name_, TRUE, TRUE, 0); 

  host_field_ = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(host_field_), (char*)pk3rc.server());
  gtk_box_pack_start(GTK_BOX(box_), host_field_, TRUE, TRUE, 0);

  host_ = gtk_label_new("Server");
  gtk_box_pack_start(GTK_BOX(box_), host_, TRUE, TRUE, 0);

  port_field_ = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box_), port_field_, TRUE, TRUE, 0);

  port_ = gtk_label_new("Port");
  gtk_box_pack_start(GTK_BOX(box_), port_, TRUE, TRUE, 0);
  if (pk3rc.port() == 0) gtk_entry_set_text(GTK_ENTRY(port_field_), "4380");
  else {
    char portstr[7]; // port is unsigned short, so 6 digits + '\0'
    sprintf(portstr, "%hu", pk3rc.port()) ;
    gtk_entry_set_text(GTK_ENTRY(port_field_), portstr);
  }

  join_button_ = gtk_button_new_with_label("Connect!");
  gtk_box_pack_start(GTK_BOX(box_), join_button_, TRUE, TRUE, 0);
  gtk_signal_connect (GTK_OBJECT (join_button_), "clicked",
		      GTK_SIGNAL_FUNC (PKOpeningGUI::joinButtonCB), this);

  quit_button_ = gtk_button_new_with_label("Quit");
  gtk_box_pack_start(GTK_BOX(box_), quit_button_, TRUE, TRUE, 0);
  gtk_signal_connect (GTK_OBJECT (join_button_), "clicked",
		      GTK_SIGNAL_FUNC (PKOpeningGUI::quitButtonCB), this);

  gtk_widget_show(name_field_);
  gtk_widget_show(name_);
  gtk_widget_show(host_field_);
  gtk_widget_show(host_);
  gtk_widget_show(port_field_);
  gtk_widget_show(port_);
  gtk_widget_show(box_);
  gtk_widget_show(window_);
}

/*************************************************************************
 * Function Name: PKOpeningGUI::~PKOpeningGUI
 * Parameters:
 * Effects: 
 *************************************************************************/

PKOpeningGUI::~PKOpeningGUI()
{
  //dprintf(("PKCLIENT: Destroying opening GUI\n"));
  //Gotta figure out how to free stuff with gtk.
  gtk_widget_destroy(window_);
}

/*************************************************************************
 * Function Name: PKOpeningGUI::join
 * Parameters:
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKOpeningGUI::join()
{
  client_->enterMainServer(gtk_entry_get_text(GTK_ENTRY(host_field_)),
			   gtk_entry_get_text(GTK_ENTRY(name_field_)),
			   gtk_entry_get_text(GTK_ENTRY(port_field_)));
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


