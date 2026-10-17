/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GRXpmImage.cxx
 *    DATE: Tue Apr 22 21:27:24 US/Eastern 1997
 *************************************************************************/
#include "GRXpmImage.h"
#include <xpm.h>
#include <iostream.h>

/*************************************************************************
 * Function Name: GRXpmImage::GRXpmImage
 * Parameters: const char *xpmfile
 * Effects: 
 *************************************************************************/

GRXpmImage::GRXpmImage(const char *xpmfile, Widget drawingwindow)
{

  drawing_window = drawingwindow;
   XpmAttributes attributes;

  attributes.closeness = 65535;
  attributes.valuemask = XpmCloseness;

  int success = XpmReadFileToPixmap (XtDisplay (drawingwindow),
				     DefaultRootWindow (XtDisplay (drawingwindow)),
				     (char *) xpmfile,
&image_, &mask_, &attributes);

  graphics_context = XCreateGC (XtDisplay (drawingwindow), 
  RootWindowOfScreen (XtScreen (drawingwindow)), 0, NULL);

  XSetClipMask(XtDisplay(drawingwindow), graphics_context, mask_);
  
  switch (success)
    {
    case -1: cout << "Error opening file: " << xpmfile << endl; break;
    case -4: cout << "Color error: " << xpmfile << endl; break;
    }
}


/*************************************************************************
 * Function Name: GRXpmImage::~GRXpmImage
 * Parameters: 
 * Effects: 
 *************************************************************************/

GRXpmImage::~GRXpmImage()
{
  
  if (image_) XFreePixmap (XtDisplay (drawing_window), image_);
  if (mask_) XFreePixmap (XtDisplay (drawing_window), mask_);
  if (graphics_context) XFreeGC (XtDisplay (drawing_window), graphics_context);
  
}


