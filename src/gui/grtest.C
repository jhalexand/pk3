
#include <xpm.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <Xm/MainW.h>
#include <Xm/DrawingA.h>
#include <Xm/ScrolledW.h>
#include <Xm/RowColumn.h>
#include <iostream.h>
#include <stdlib.h>
#include "/u/pongbat/src/dla/before_integration/PKGraphicsInterface.h"
#include <PKids.h>
#include <VectorMath.h>
#include <Exception.h>

static XmTextPosition wpr_position = 0;
void update_window (Widget W, char *data);

//void file_cb();

void file_cb (Widget w, XtPointer xt2, XtPointer nothing)
{
  int itemnumber = (int) xt2;
  if (itemnumber == 0) throw Exception();
}


static void callback (Widget w, XtPointer command_hist, XtPointer cbs)
{
char *filename = XmTextGetString (w);
update_window ((Widget) command_hist, filename);
//cout << filename << endl;
cout << XmTextGetString(w) << endl;
//XtFree (filename);
XmTextSetString ((Widget) w, " ");
XtFree (filename);
}

void update_window (Widget w, char *data)
{
/*char *fmt;
va_list args;
va_start(args);
fmt = va_arg (args, char *);
vsprintf (data, fmt, args);
va_end(args);*/
//cout << "Adding " << data << endl;
char *data2 = strcat (data, "\n");
XmTextInsert (w, wpr_position, data);
wpr_position += strlen (data);
XtVaSetValues (w, XmNcursorPosition, wpr_position, NULL);
XmTextShowPosition (w, wpr_position);

}

void keyup (Widget widget, XEvent *event, String *args, unsigned
*num_args) 
{
cout << "Key released!" << endl;
}

void keydown (Widget widget, XEvent *event, String *args, unsigned 
*num_args)
{
cout << "Key pressed!" << endl;
int number_args = *num_args;
cout << number_args << endl;
}

Pixmap pixmap;
GC gc;

void redraw (Widget w, XtPointer clientdata, XtPointer calldata)
{
  XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *) calldata;
  XCopyArea (cbs->event->xexpose.display, pixmap, cbs->window, gc, 0, 0, 530, 500, 0, 0);
}

int main(int argc, char **argv)

{
cout << "hi" << endl;
Widget toplevel;

XtAppContext app;

argv[0] = "Pong Kombat III";
toplevel = XtVaAppInitialize (&app, "Demos", NULL, 0, &argc, argv, NULL, NULL);

Widget main_w;

main_w = XtVaCreateManagedWidget ("main_w", xmMainWindowWidgetClass,
toplevel, NULL); 

XmString file, quit, quit_acc;

file = XmStringCreateSimple ("File");
quit = XmStringCreateSimple ("Quit");
quit_acc = XmStringCreateSimple ("Ctrl-C");

Widget menubar = XmVaCreateSimpleMenuBar (main_w, "menubar", XmVaCASCADEBUTTON, file, 'F', NULL);

XmVaCreateSimplePulldownMenu (menubar, "file_menu", 0, file_cb, XmVaPUSHBUTTON, quit, 'Q', "Ctrl<Key>c", quit_acc, NULL);


XmStringFree (file);
XmStringFree (quit);
XmStringFree (quit_acc);

XtManageChild (menubar);

Widget rowc = XtVaCreateWidget ("rowcol", xmRowColumnWidgetClass, main_w, NULL);

PKGraphicsInterface *interface;

PKTypeID *playerlist = new PKTypeID[3];

playerlist[0] = (PKTypeID) 2;
playerlist[1] = (PKTypeID) 3;
playerlist[2] = (PKTypeID) 6;

interface = new PKGraphicsInterface (NULL, rowc, PK_BACKGROUND_PETER,
&app,3, playerlist);

interface->addObject (0, 2, PKPoint (100.0, 100.0));
interface->addObject (1, 2, PKPoint (200.0, 200.0));
interface->addObject (2, 2, PKPoint (300.0, 300.0));
interface->addObject (3, 0, PKPoint (200, 100));

interface->defineKeyMap (PK_KEY_FLAT_KICK, XK_F);
interface->defineKeyMap (PK_KEY_SPIN, NULL);
interface->defineKeyMap (PK_KEY_SWEEP_KICK, XK_S);
interface->defineKeyMap (PK_KEY_UPPERCUT, XK_U);
interface->defineKeyMap (PK_KEY_BLOCK, XK_B);
interface->defineKeyMap (PK_KEY_PUNCH, XK_P);
interface->defineKeyMap (PK_KEY_KICK, XK_C);
interface->defineKeyMap (PK_KEY_UP, XK_I);
interface->defineKeyMap (PK_KEY_LEFT, XK_J);
interface->defineKeyMap (PK_KEY_RIGHT, XK_L);
interface->defineKeyMap (PK_KEY_DOWN, XK_K);
interface->defineKeyMap (PK_KEY_UPPERCUT_DOWN, XK_D);
Widget text_w = XtVaCreateManagedWidget ("textentry", xmTextWidgetClass, rowc, XmNvalue, "", NULL);

XtManageChild (rowc);

XtRealizeWidget(toplevel);

try {
XtAppMainLoop(app);
}
catch (...)
{
}
delete interface;
}



