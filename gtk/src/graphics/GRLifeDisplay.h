/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRLifeDisplay.h                                     */
/*    ASGN:                                                     */
/*    DATE: Tue Apr 29 15:11:31 1997                            */
/****************************************************************/


#ifndef GRLIFEDISPLAY_HEADER
#define GRLIFEDISPLAY_HEADER

//#include <PKGameClasses.h>
#include "GRLetterWriter.h"

static char * characternames[] =
{
  "Liu Kang",
  "Jade",
  "Kabal",
  "Cyrax",
  "Reptile",
  "Scorpion",
  "Smoke",
  "Sonya",
  "Sub Zero" };

class GRLetterWriter;
  
class GRLifeDisplay {

public:

  GRLifeDisplay(Pixmap workarea, Widget drawingwindow, GC graphicscontext, PKTypeID *players, int numplayers);
  // Uses letter writer to draw names, calls updateimage on each.

  ~GRLifeDisplay();

  virtual void update (PKGameStatus *status); // updates life &image for each
  virtual void updateImage(int player); // updates only image for one
  virtual void copyToScreen(int player); // updates drawing area
  virtual char *toString (PKTypeID id); // Returns name assoc. with TypeID
  
private:

  int position_[4]; // Stores which slot a user is in, indexed by player num
  int num_players;
  int *life_;
  GRLetterWriter *letter_writer;
  Pixmap work_area;
  Widget drawing_window;
  GC graphics_context;
  XColor death_color, health_color;

};

#endif
