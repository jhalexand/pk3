/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GRGraphicManager.cxx
 *    DATE: Tue Apr 22 13:51:25 US/Eastern 1997
 *************************************************************************/
#include "GRGraphicManager.h"
#include "GRXpmImage.h"
#include "GR_local.h"
#include "GRScreenPoint.h"
#include <stdlib.h>

/*************************************************************************
 * Function Name: GRGraphicManager::GRGraphicManager
 * Parameters: const char *filename
 * Effects: 
 *************************************************************************/

GRGraphicManager::GRGraphicManager(const char *filename, int numplayers, PKTypeID *playertypes, Widget drawingwindow, GC graphicscontext)
{

  graphics_context = graphicscontext;
  drawing_window = drawingwindow;
  num_players = numplayers;
  player_types = playertypes;
  cout << "Will parse graphics definition file: " << filename << endl;
  strcpy (file_name, filename);
  
}


/*************************************************************************
 * Function Name: GRGraphicManager::~GRGraphicManager
 * Parameters: 
 * Effects: 
 *************************************************************************/

GRGraphicManager::~GRGraphicManager()
{
  for (int i = 0; i < num_xpms; i++)
    {
      if (xpm_images[i]) delete xpm_images[i];
    }
  for (int j = 0; j < num_graphics; j++)
    {
      if (graphics_list[j]) 
	{
        cout << "Destroying graphic Number: " << j << endl;
	delete graphics_list[j];
        }
    }
  cout << "About to destroy images:" << endl;
  delete[] xpm_images;
  cout << "About to destroy graphics list" << endl;
  delete[] graphics_list;
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseFile
 * Parameters: 
 * Returns: GRGraphicType **
 * Effects: 
 *************************************************************************/
GRGraphicType **
GRGraphicManager::parseFile()
{

  data_file.open(file_name);
  if (!data_file)
    {
      cout << "Error opening " << file_name << ". Aborting." << endl;
      return NULL;
    }
  ParseResult result;
  while (!data_file.eof())
    {
      result = parseLine();
      if (result == PARSE_DONE)
        {
	  data_file.close();
	  return graphics_list; 
        }
      if (result == PARSE_ERROR) {data_file.close();return NULL;}
    }
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseLine
 * Parameters: 
 * Returns: ParseResult
 * Effects: 
 *************************************************************************/
ParseResult
GRGraphicManager::parseLine()
{

  char command[255];
  data_file >> command;

  //cout << "Parsing command: " << command << endl;
 
  if (data_file.eof()) return PARSE_DONE;
 
  // Check for comments:
 
  if (command[0] == '#') {data_file.getline(command, 200, '\n'); return PARSE_SUCCESS;}

  if (strlen(command) > 1 && command[0] == '/' && command[1] == '/')
    {
      data_file.getline (command, 200, '\n'); 
      return PARSE_SUCCESS;
    }

  if (strlen (command) == 1) return PARSE_SUCCESS;

  if (!strcasecmp (command, "XPMFILE"))  
    {
      return parseXpmFile ();
    }
  
  if (!strcasecmp (command, "TYPEID"))
    {
      return parseTypeID ();
    }
      
  if (!strcasecmp (command, "DEFAULTFRAME"))
    {
      return parseDefaultFrame ();
    }
  
  if (!strcasecmp (command, "FRAME"))  
    {      
      return parseFrame ();
    }
  
  if (!strcasecmp (command, "SEQUENCE"))
    {
      return parseSequence ();
    }
      
  if (!strcasecmp (command, "NUMTYPEIDS"))
    {
      return parseNumTypeIDS ();
    }

  if (!strcasecmp (command, "NUMXPMFILES"))
    {
      return parseNumXpmFiles();
    }

  cout << "Unexpected command found: " << command << endl;
  cout << "Parsing failed." << endl;
  return PARSE_ERROR;
  
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseXpmFile
 * Parameters: 
 * Returns: ParseResult
 * Effects: 
 *************************************************************************/
ParseResult
GRGraphicManager::parseXpmFile()
{
  char filename[255];
  data_file >> filename;
  int filenum;
  data_file >> filenum;
  int paddle_dependency;
  data_file >> paddle_dependency; // Only load the file if this paddle is
                                  // in the game.
  if (paddle_dependency > 0)
    {
      if (playerExists ((PKTypeID) paddle_dependency)) xpm_images[filenum] = new GRXpmImage (filename, drawing_window); else 
        {
        xpm_images[filenum] = NULL;
        cout << "Not loading file: " << filename << endl;
        }
      return PARSE_SUCCESS;
    }
  else
    {
      xpm_images[filenum] = new GRXpmImage (filename, drawing_window);
      return PARSE_SUCCESS;
    }
  return PARSE_SUCCESS;
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseTypeID
 * Parameters: 
 * Returns: ParseResult
 * Effects: 
 *************************************************************************/
ParseResult
GRGraphicManager::parseTypeID()
{

  int idnum, filenum, numframes, numanims;
  data_file >> idnum >> filenum >> numframes >> numanims;

  //cout << "Here" << endl;
  if (!xpm_images[filenum]) 
  {
    current_typeid = PK_TYPE_INVALID;
    cout << "Skipping ID " << idnum << endl;
    return PARSE_SUCCESS; // Skip it..
  }
  current_typeid = (PKTypeID) idnum;
  current_file_number = filenum;
  
  graphics_list[idnum] = new GRGraphicType (xpm_images[filenum]->getImage(), xpm_images[filenum]->getMask(), numframes, numanims, xpm_images[filenum]->getGraphicsContext(), drawing_window);
  
  return PARSE_SUCCESS;
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseDefaultFrame
 * Parameters: 
 * Returns: ParseResult
 * Effects: 
 *************************************************************************/
ParseResult
GRGraphicManager::parseDefaultFrame()
{

  int xcenter, ycenter, xsize, ysize;
  data_file >> xcenter >> ycenter >> xsize >> ysize;

  if (current_typeid == PK_TYPE_INVALID) return PARSE_SUCCESS;

  graphics_list[current_typeid]->setDefaultFrame (new GRFrame (GRScreenPoint(xcenter-xsize/2, ycenter-ysize/2), GRScreenPoint (xcenter+xsize/2, ycenter+ysize/2)));
						  
  return PARSE_SUCCESS;
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseFrame
 * Parameters: 
 * Returns: ParseResult
 * Effects: 
 *************************************************************************/
ParseResult
GRGraphicManager::parseFrame()
{
  int framenum, xcenter, ycenter, xsize, ysize;
  data_file >> framenum >> xcenter >> ycenter >> xsize >> ysize;

  if (current_typeid == PK_TYPE_INVALID) return PARSE_SUCCESS;

  graphics_list[current_typeid]->addFrame (framenum, new GRFrame (GRScreenPoint (xcenter-xsize/2, ycenter-ysize/2), GRScreenPoint (xcenter+xsize/2, ycenter+ysize/2)));
  
  return PARSE_SUCCESS;
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseSequence
 * Parameters: 
 * Returns: ParseResult
 * Effects: 
 *************************************************************************/
ParseResult
GRGraphicManager::parseSequence()
{
  
  char frameinfo[255];

  int numframes;
  int sequencenum;
  
  data_file >> sequencenum >> numframes;

  if (current_typeid == PK_TYPE_INVALID) 

  {
    data_file.getline(frameinfo, 200, '\n'); 
    return PARSE_SUCCESS;

  }

  int *frames = new int[numframes];

  int count = 0;
  
  do
    {
      data_file >> frameinfo;
      if (frameinfo[0] == 'R')
	{frames[count] = GR_REPEAT_FRAME;
	}
      else
	if (frameinfo[0] == 'D')
	  {
	    frames[count] = GR_REVERT_TO_DEFAULT_FRAME;
	  }
      else 
        if (frameinfo[0] == 'B')
          {
            frames[count] = GR_REVERT_TO_INITIAL_FRAME;
          }
      else
	frames[count] = atoi (frameinfo);
      
      count++;
      
      if (count > numframes)
	{ cout << "Error parsing animation sequence!" << endl;
	return PARSE_ERROR;}
      
    } while (frameinfo[0] != 'R' && frameinfo[0] != 'D' && frameinfo[0]!= 'B');

    if (count != (numframes))
      {
      cout << "Error parsing animation sequence: incorrect number of frames: " << numframes << " (count = " << count << ")" << endl;
      exit (0);
      }  
    GRAnimationSequence *sequence = new GRAnimationSequence (frames,
numframes);

    delete[] frames;

    graphics_list[current_typeid]->addAnimationSequence (sequencenum, sequence);
 
  return PARSE_SUCCESS;
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseNumTypeIDS
 * Parameters: 
 * Returns: ParseResult
 * Effects: 
 *************************************************************************/
ParseResult
GRGraphicManager::parseNumTypeIDS()
{
  data_file >> num_graphics;
  graphics_list = new GRGraphicType* [num_graphics];
  for (int i = 0; i < num_graphics; i++)
    {
    graphics_list[i] = NULL;
    }
  return PARSE_SUCCESS;
}


/*************************************************************************
 * Function Name: GRGraphicManager::parseNumXpmFiles
 * Parameters: 
 * Returns: ParseResult
 * Effects: 
 *************************************************************************/
ParseResult
GRGraphicManager::parseNumXpmFiles()
{
  data_file >> num_xpms;
  xpm_images = new GRXpmImage* [num_xpms];
    for (int i = 0; i < num_xpms; i++)
	{ xpm_images[i] = NULL; }
  return PARSE_SUCCESS;
}


/*************************************************************************
 * Function Name: GRGraphicManager::playerExists
 * Parameters: PKTypeID id
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GRGraphicManager::playerExists(PKTypeID id)
{

  for (int i = 0; i < num_players; i++)
    {
      if (id == player_types[i]) return TRUE;
    }
  return FALSE;
  
}


