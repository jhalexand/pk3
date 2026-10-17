#ifndef GUI_XPM_TABLE_HEADER
#define GUI_XPM_TABLE_HEADER

#include <hashtable.h>
#include <Xm/Xm.h>

class GUIXpmImage ;

class GUIXpmTable {
private:
  HashTableDict hash_;

  static unsigned int h(const char *);

public:
  GUIXpmTable() ;
  virtual ~GUIXpmTable();
  
  GUIXpmImage *getImage(const char *filename, Widget parent) ;
  void delImage(const char *filename, Widget parent) ;
  void delImage(GUIXpmImage *image, Widget parent);
} ;

#endif
