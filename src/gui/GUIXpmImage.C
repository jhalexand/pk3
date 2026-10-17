/*************************************************************************
 *    NAME: David Akers
 *    USER: dla, modified slightly by bh
 *    FILE: GUIXpmImage.cxx
 *    DATE: Tue Apr 22 21:27:24 US/Eastern 1997
 *************************************************************************/
#include "GUIXpmImage.h"

#include <debug.h>

#include <X11/Xlib.h>
#include <xpm.h>
#include <stdio.h>

/*************************************************************************
 * Function Name: GUIXpmImage::GUIXpmImage
 * Parameters: const char *xpmfile
 * Effects: opens the Xpm
 *************************************************************************/

GUIXpmImage::GUIXpmImage(const char *xpmfile, Widget drawingwindow)
{
  XpmAttributes attributes;
  attributes.closeness = 65535; // colors can be way off if need be
  attributes.valuemask = XpmCloseness;

  dsp_ = XtDisplay(drawingwindow);

  int success = XpmReadFileToPixmap (dsp_,
				     DefaultRootWindow (dsp_),
				     (char *) xpmfile,
				     &image_, &mask_, &attributes);

  width_ = attributes.width ;
  height_ = attributes.height ;
  dprintf(("GUIXpmImage: loaded %s, which is %dx%d\n",
	   xpmfile, width_, height_));

  gc_ = XCreateGC (dsp_,
		   RootWindowOfScreen (XtScreen (drawingwindow)), 0, NULL);

  XSetClipMask(dsp_, gc_, mask_);

  switch (success) {
    case -1: fprintf(stderr, "Error opening %s\n", xpmfile); break;
    case -4: fprintf(stderr, "Color error on Xpm %s\n", xpmfile); break;
  }
}


/*************************************************************************
 * Function Name: GUIXpmImage::addCallback
 * Parameters: 
 * Returns: void
 * Effects: adds an expose callback to redraw the image
 *************************************************************************/
void
GUIXpmImage::addCallback(Widget w)
{
  XtAddCallback(w,
		XmNexposeCallback, GUIXpmImage::static_redrawCallback, this);
}

/*************************************************************************
 * Function Name: GUIXpmImage::remCallback
 * Parameters: 
 * Returns: void
 * Effects: adds an expose callback to redraw the image
 *************************************************************************/
void
GUIXpmImage::remCallback(Widget w)
{
  XtRemoveCallback(w,
		   XmNexposeCallback, GUIXpmImage::static_redrawCallback, this);
}

/*************************************************************************
 * Function Name: GUIXpmImage::~GUIXpmImage
 * Parameters: 
 * Returns: void
 * Effects: draws the pixmap in its widget
 *************************************************************************/
void
GUIXpmImage::draw(Widget w)
{
  Window window = XtWindow(w);
  XCopyArea(dsp_, image_, window, gc_,
		 0, 0, width_, height_,
		 0, 0);
}

/*************************************************************************
 * Function Name: GUIXpmImage::~GUIXpmImage
 * Parameters: 
 * Effects: destroys the Xpm and deallocates all resources it uses
 *************************************************************************/

GUIXpmImage::~GUIXpmImage()
{
  if (image_) XFreePixmap (dsp_, image_);
  if (mask_)  XFreePixmap (dsp_, mask_);
  if (gc_) XFreeGC (dsp_, gc_);
}


