/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GRLetterWriter.cxx
 *    DATE: Mon Apr 28 22:13:17 US/Eastern 1997
 *************************************************************************/
#include "GRLetterWriter.h"

/*************************************************************************
 * Function Name: GRLetterWriter::GRLetterWriter
 * Parameters: Widget drawingwindow, Pixmap work_area, GREngine *engine
 * Effects: 
 *************************************************************************/

GRLetterWriter::GRLetterWriter(Widget drawingwindow, Pixmap workarea, GC graphicscontext)
{
  graphics_context = graphicscontext;
  drawing_window = drawingwindow;
  work_area = workarea;
  xpm_image = new GRXpmImage ("/cs/src/pk3/graphics/objects/phrases2.xpm", drawing_window);
}


/*************************************************************************
 * Function Name: GRLetterWriter::~GRLetterWriter
 * Parameters: 
 * Effects: 
 *************************************************************************/

GRLetterWriter::~GRLetterWriter()
{
  delete xpm_image;
}


char upcase (char c)
{
  if (c >= 97 && c <= 122) return c-32; else return c;
}

/*************************************************************************
 * Function Name: GRLetterWriter::printString
 * Parameters: int x, int y, const char *
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GRLetterWriter::printString(int x, int y, const char *mystring)
{
  int xscreenposition = x;
  int yposition;
  int count = 0;
  char c;
  do
    {
      c = upcase(mystring[count]) - (char) 'A';
      if (c != - (char) 'A')
	{
	  if (c == (char) ' ' - (char) 'A') {xscreenposition += 5; count++;continue;}
	  int width = letterxposition[c+1] - letterxposition[c] + 1;
	  if (width < 0) width = 10; // Special case when letter is R
	  printChar (xscreenposition, y, c);
	  xscreenposition += width + 2; // Allow a little extra space between
        }                            // chars
      count ++;
    } while (c != - (char) 'A');
}


/*************************************************************************
 * Function Name: GRLetterWriter::printChar
 * Parameters: int x, int y, char
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GRLetterWriter::printChar(int x, int y, char c)
{
  
  Pixmap image = xpm_image->getImage();
  Pixmap mask = xpm_image->getMask();
  int width = letterxposition[c+1] - letterxposition[c]-2;
  if (width < 0) width = 7;
  int height = 9;

  cout << "char is " << (int) c << endl;
  cout << "width is " << (int) width << endl;
  
  XSetClipMask(XtDisplay(drawing_window), graphics_context, mask);
  
  XSetClipOrigin(XtDisplay(drawing_window), graphics_context,
x-letterxposition[c], y - letteryposition[c]);

  XCopyArea (XtDisplay (drawing_window), image , work_area, graphics_context, letterxposition[c], letteryposition[c], width, height, x, y);

  // XCopyArea (XtDisplay (drawing_window), work_area, XtWindow (drawing_window), graphics_context, x, y, width, height, x, y);
  
}


