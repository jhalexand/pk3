#
#     NAME: Makefile
#   AUTHOR: Mike Shapiro (mws)
#    DESCR: Makefile for DoorsNT client stubs library.
#
#           Note that the LIBOBJ macro contains the .o files
#           corresponding to all of the .C source files provided to
#           you in /course/cs169/asgn/stubs. As you write new stub and
#           reference classes, such as TermDev.C or TermDevRef.C, you
#           will need to add the name of the corresponding object
#           file, TermDev.o and TermDevRef.o to the LIBOBJ macro.
#
#           Note again that the compiler is set to /opt/SUNWspro4.0/bin/CC
#           and you SHOULD NOT USE ANY OTHER COMPILER.
#
#           Later in the course, when all your stubs are written and
#           debugged, you can add -DNDEBUG to the CXXFLAGS macro to compile
#           your stubs library without debugging code.
#
# $Id$
#

#//////////////////////////////////////////////////////////////////////

LIBNAME	= pkgraphics
LIBRARY	= lib$(LIBNAME).so

LIBOBJ	= PKGraphicsInterface.o GREngine.o GROnscreenGraphic.o \
GRGraphicType.o GRFrame.o GRAnimationSequence.o GRGraphicManager.o \
GRXpmImage.o GRLetterWriter.o GRLifeDisplay.o

#//////////////////////////////////////////////////////////////////////

SHELL	= /bin/sh
CXX	= /opt/SUNWspro4.2/SC4.2/bin/CC
AR	= /usr/ccs/bin/ar ruc
RM	= /bin/rm -rf

IFLAGS    = -I/cs/src/pk3/include/ -I/cs/include -I/usr/dt/include \
            -I/opt/SUNWspro4.2/SC4.2/include/CC/

LDFLAGS   = -L/cs/src/pk3/lib/ -L/cs/include \
        -L/opt/SUNWspro4.2/SC4.2/lib/rw7 \
        -L/course/cs032/lib \
        -L/opt/SUNWspro/lib -L/cs/lib \
        -L/cs/src/pk3/lib


CXXFLAGS  = -g

all: $(LIBRARY)

$(LIBRARY): $(LIBOBJ) 
#	$(AR) $@ $? Templates.DB/*.o
	$(LD) -G -o $(LIBRARY) $(LDFLAGS) $(LIBOBJ) Templates.DB/*.o 
#-lXm -lXt -lX11 -lrwtool -lXpm -lXpm


.SUFFIXES: .cxx .h

%.cxx: %.h

.cxx.o:
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $<

clean:
	$(RM) $(LIBRARY) *.o Templates.DB core

install: $(LIBRARY)
	/cs/src/pk3/lib/lib_install $(LIBRARY)
