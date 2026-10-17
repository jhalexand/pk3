/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRParser.h                                          */
/*    ASGN:                                                     */
/*    DATE: Tue Apr 22 10:27:56 1997                            */
/****************************************************************/


#ifndef GRGRAPHIC_MANAGER_HEADER
#define GRGRAPHIC_MANAGER_HEADER

#include "GRGraphicType.h"
#include "GRXpmImage.h"
#include "PKids.h"
#include <fstream.h>

enum ParseResult {

  PARSE_SUCCESS = 1,
  PARSE_ERROR= 0,
  PARSE_DONE = 2 };

class GRGraphicManager {

public:

  GRGraphicManager(const char *filename, int numplayers, PKTypeID *playertypes, Widget drawingwindow, GC graphicscontext);
  ~GRGraphicManager();

  virtual GRGraphicType **parseFile();
  virtual ParseResult parseLine();
  virtual ParseResult parseXpmFile();
  virtual ParseResult parseTypeID();
  virtual ParseResult parseDefaultFrame();
  virtual ParseResult parseFrame();
  virtual ParseResult parseSequence();
  virtual ParseResult parseNumTypeIDS();
  virtual ParseResult parseNumXpmFiles();

  int playerExists (PKTypeID id);
  
private:

  int num_players;
  PKTypeID *player_types;
  
  char file_name[255];
  PKTypeID current_typeid;
  int current_file_number;

  int num_graphics;
  int num_xpms;
  
  GRGraphicType **graphics_list;
  GRXpmImage **xpm_images;

  Widget drawing_window;

  GC graphics_context;
  
  ifstream data_file;
};

#endif
