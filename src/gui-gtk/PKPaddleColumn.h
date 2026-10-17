#ifndef PKPaddleColumn_HEADER
#define PKPaddleColumn_HEADER

#include <gtk/gtk.h>

class PKPlayerPanel ;

class PKPaddleColumn {
private:
  GtkWidget *form_;
  GtkWidget *listPulldownMenu_;
  GtkWidget *listOptionMenu_ ;
  GtkWidget *picture_;
  PKPlayerPanel *panel_ ;
  int  hasRealized_; 
  int  hide_ ; 

public:
  PKPaddleColumn(GtkWidget *parent, PKPlayerPanel *panel);
  void realize() ;
  virtual ~PKPaddleColumn() ;

  void append(const char *paddlename);

  GtkWidget *widget() { return form_; } // returns the top widget
  GtkWidget *optionMenu() { return listOptionMenu_; }
  GtkWidget *pulldownMenu() { return listPulldownMenu_; }
  GtkWidget *picture() { return picture_; }

  void showXpm(const char *paddleName) ;

  void hideSelect() ;
  void showSelect() ;
} ;



class PKPaddleButton {
private:
  GtkWidget *button_ ;
  const char *name_;
  PKPlayerPanel *panel_;
  PKPaddleColumn *column_; 

public:
  PKPaddleButton(GtkWidget *parent, PKPlayerPanel *panel, PKPaddleColumn *column,
		 const char *name);
  virtual ~PKPaddleButton() ;

  const char *paddle() const { return name_; }

private:
  static void selectedCallback(GtkWidget *widget, gpointer thus) {
    ((PKPaddleButton*)thus)->selected();
  }

  void selected();
} ;



#endif
