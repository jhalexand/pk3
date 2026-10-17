/***********************************************************************
 * AUTHOR: Benoit Hudson <bh>
 *   FILE: GUIXpmTable.C
 *   DATE: Mon Oct 20 18:26:06 1997
 *  DESCR: 
 ***********************************************************************/
#include "GUIXpmTable.h"

#include "GUIXpmImage.h"

struct ImageStruct {
  GUIXpmImage *image ;
  int refcount ;
} ;

// for readability
inline ImageStruct *IS(const void* v) { return (ImageStruct*)v; }

const int HTSIZE = 13 ; // assume fewer than that many paddles

/***********************************************************************
 * Method : GUIXpmTable::h
 * Params : const char *
 * Returns: unsigned int
 * Effects: map the string to an int
 ***********************************************************************/
unsigned int
GUIXpmTable::h(const char *str) 
{
  // assume short, unique filenames.  Use last 8 chars (most likely to be
  // unique)
  union {
    unsigned long long ll;
    char str[sizeof(long long)] ;
  } hashinfo;
  int len = strlen(str);

  hashinfo.ll = -1 ;

  // use all chars if fewer than 8; only last 8 if more than 8
  if(len<sizeof(hashinfo)) strncpy(hashinfo.str, str, sizeof(long long));
  else strncpy(hashinfo.str, str+len-sizeof(hashinfo), sizeof(long long));

  return hashinfo.ll % HTSIZE ;
}


/***********************************************************************
 * Method : GUIXpmTable::getImage
 * Params : const char * filename
 * Returns: GUIXpmImage *
 * Effects: 
 ***********************************************************************/
GUIXpmImage *
GUIXpmTable::getImage(const char * filename, Widget parent) 
{
  if(hash_.isset(filename)) {
    ImageStruct *is = IS(hash_.get(filename));
    is->image->addCallback(parent);
    return is->image;
  }
  else {
    GUIXpmImage *image = new GUIXpmImage(filename, parent);
    ImageStruct *is = new ImageStruct;
    is->image = image ;
    is->image->addCallback(parent);
    is->refcount = 0 ;
    hash_.set(filename, is);
    return image ;
  }
  assert(false);
}


/***********************************************************************
 * Method : GUIXpmTable::delImage
 * Params : const char * filename
 * Returns: void
 * Effects: search by name, decrement refcount; if 0, remove it
 ***********************************************************************/
void
GUIXpmTable::delImage(const char * filename, Widget parent) 
{
  if(hash_.isset(filename)) {
    ImageStruct *is = IS(hash_.get(filename));
    is->image->remCallback(parent);
    is->refcount--;
  }
}


/***********************************************************************
 * Method : GUIXpmTable::delImage
 * Params : GUIXpmImage * image
 * Returns: void
 * Effects: search by GUIXpmImage*, decrement refcount; if 0, remove it
 ***********************************************************************/
void
GUIXpmTable::delImage(GUIXpmImage * image, Widget parent) 
{
  HTIterator it(hash_);

  // go while image is not found, until end of hash table
  while(it.curdata() && (IS(it.curdata())->image != image)) { it.next() ; }

  if(!it.curdata()) { return ; /* not found */ }

  ImageStruct *is = IS(it.curdata());
  assert(is->image==image);

  is->refcount--;
  is->image->remCallback(parent);
}


/***********************************************************************
 * Method : GUIXpmTable::GUIXpmTable
 * Params : 
 * Effects: 
 ***********************************************************************/
GUIXpmTable::GUIXpmTable()
  : hash_(GUIXpmTable::h, HTSIZE)
{
}


/***********************************************************************
 * Method : GUIXpmTable::~GUIXpmTable
 * Params : 
 * Effects: 
 ***********************************************************************/
GUIXpmTable::~GUIXpmTable()
{
  HTIterator it(hash_);

  while(it.curdata()) {
    delete IS(it.curdata());
    it.setdata(null);
  }
}


