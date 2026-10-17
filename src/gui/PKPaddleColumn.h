#ifndef PKPaddleColumn_HEADER
#define PKPaddleColumn_HEADER

#include <Xm/Xm.h>
#include <ULDict.h>

class GUIXpmImage ;
class GUIXpmTable ;
class PKPlayerPanel ;

class PKPaddleColumn {
private:
  UnsortedListDict names_;
  Widget form_;
  Widget listPulldownMenu_;
  Widget listOptionMenu_ ;
  Widget picture_;
  PKPlayerPanel *panel_ ;
  GUIXpmImage *xpmImage_ ;
  boolean hasRealized_; // a hack: need to draw after realize
  boolean hide_ ; // hack: need to hide after realize

  static GUIXpmTable *table_ ;
  
public:
  PKPaddleColumn(Widget parent, PKPlayerPanel *panel);
  void realize() ;
  virtual ~PKPaddleColumn() ;

  void append(const char *paddlename);

  Widget widget() { return form_; } // returns the top widget
  Widget optionMenu() { return listOptionMenu_; }
  Widget pulldownMenu() { return listPulldownMenu_; }
  Widget picture() { return picture_; }

  void showXpm(const char *paddleName) ;

  void hideSelect() ;
  void showSelect() ;
} ;



class PKPaddleButton {
private:
  Widget button_ ;
  const char *name_;
  PKPlayerPanel *panel_;
  PKPaddleColumn *column_; 

public:
  PKPaddleButton(Widget parent, PKPlayerPanel *panel, PKPaddleColumn *column,
		 const char *name);
  virtual ~PKPaddleButton() ;

  const char *paddle() const { return name_; }

private:
  static void selectedCallback(Widget, void *thus, void*) {
    ((PKPaddleButton*)thus)->selected();
  }

  void selected();
} ;



#endif
