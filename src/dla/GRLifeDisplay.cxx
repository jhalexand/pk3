/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GRLifeDisplay.cxx
 *    DATE: Tue Apr 29 15:32:00 US/Eastern 1997
 *************************************************************************/
#include "GRLifeDisplay.h"
#include <PKDimensions.h>

/*************************************************************************
 * Function Name: GRLifeDisplay::GRLifeDisplay
 * Parameters: Pixmap workarea, Widget drawingwindow, GC graphicscontext, PKTypeID *players, int numplayers
 * Effects: 
 *************************************************************************/

GRLifeDisplay::GRLifeDisplay(Pixmap workarea, Widget drawingwindow, GC graphicscontext, PKTypeID *players, int numplayers)
{
  work_area = workarea;
  drawing_window = drawingwindow;
  graphics_context = graphicscontext;
  letter_writer = new GRLetterWriter (drawing_window, work_area, graphics_context);

  int leftmostavailableslot = 23;
  int rightmostavailableslot = 516-123;
  for (int player = 0; player < numplayers; player++)
    {
      if (players[player] %2 == 1)
	{
	  position_[player] = leftmostavailableslot;
	  leftmostavailableslot += 123;
	}
      if (players[player] %2 == 0)
	{
	  position_[player] = rightmostavailableslot;
	  rightmostavailableslot -= 123;
	}
      
      letter_writer->printString ( position_[player], 60, toString (players[player]));
    }
  String health = "Blue";
  String death = "Red";
  Colormap cmap = DefaultColormapOfScreen (XtScreen (drawing_window));
  XColor unused;
  if (!XAllocNamedColor (XtDisplay (drawing_window), cmap, health, &health_color, &unused))
    {
      cout << "Cannot allocate " << health << endl;
    }
  if (!XAllocNamedColor (XtDisplay (drawing_window), cmap, death, &death_color, &unused))
    {
      cout << "Cannot allocate " << death << endl;
    }
  life_ = new int [numplayers];
  for (int i = 0; i < numplayers; i++)
    {
    life_[i] = 100;
    updateImage (i);
    }
}


/*************************************************************************
 * Function Name: GRLifeDisplay::~GRLifeDisplay
 * Parameters: 
 * Effects: 
 *************************************************************************/

GRLifeDisplay::~GRLifeDisplay()
{
  delete letter_writer;
  delete[] life_;
}


/*************************************************************************
 * Function Name: GRLifeDisplay::update
 * Parameters: PKGameStatus *status
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GRLifeDisplay::update(PKGameStatus *status)
{

  int *newlife = status->life();
  int pcount = 0;
  for (int i = 0; i < 4; i++)
    {
      if (newlife[i] >= 0)
	{
	  if (life_[pcount] != newlife[i])
	    {                                                                
	      life_[pcount] = newlife[i];
	      updateImage (pcount);
	      copyToScreen (pcount);
	    }
	  pcount++;
	}
    }
}


/*************************************************************************
 * Function Name: GRLifeDisplay::updateImage
 * Parameters: int player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GRLifeDisplay::updateImage(int player)
{

  //int xcoord = 23 + 123*player;
  // ycoordinate is something like 30??
  XSetClipMask(XtDisplay(drawing_window), graphics_context, None);
  
  XSetForeground (XtDisplay (drawing_window), graphics_context, health_color.pixel);
  XFillRectangle (XtDisplay (drawing_window), work_area, graphics_context, position_[player], 30, life_[player], 20);
  XSetForeground (XtDisplay (drawing_window), graphics_context, death_color.pixel);
  XFillRectangle (XtDisplay (drawing_window), work_area, graphics_context, position_[player]+life_[player], 30,100-life_[player], 20);
}





/*************************************************************************
 * Function Name: GRLifeDisplay::copyToScreen
 * Parameters: int player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GRLifeDisplay::copyToScreen(int player)
{
  
  XSetClipMask(XtDisplay(drawing_window), graphics_context, None);
  
  XCopyArea (XtDisplay (drawing_window), work_area, XtWindow(drawing_window), graphics_context, position_[player], 30, 100, 20, position_[player], 30);

}


/*************************************************************************
 * Function Name: GRLifeDisplay::toString
 * Parameters: PKTypeID id
 * Returns: char *
 * Effects: 
 *************************************************************************/
char *
GRLifeDisplay::toString(PKTypeID id)
{
  int index = (id-1)/2;
  return characternames[index]; // Change this!!
}


