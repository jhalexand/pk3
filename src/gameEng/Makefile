#
#     NAME: Makefile
#   AUTHOR: Elaine Chen (eyc)
#    DESCR: Makefile for creating a shared object library
#


#//////////////////////////////////////////////////////////////////////

SOLIBNAME	= pkgameengine
SOLIBRARY	= lib$(SOLIBNAME).so

BACKUPDIR = backups

.SUFFIXES: .cxx .h

SOLIBOBJ	= PKGameEngineInterface.o PKGameEngine.o GEGameObject.o \
GEPlayer.o GEProjectile.o GEBall.o GEContainer.o GEEvent.o GEWall.o \
GEInjureTeamEvent.o GELKLeftPlayer.o GELKRightPlayer.o \
GERemoveObjectEvent.o GEExplosionProjectile.o GESZLeftPlayer.o \
GESZProjectile.o GERepRightPlayer.o GEJadeLeftPlayer.o \
GECyraxLeftPlayer.o GECyraxBomb.o GECyraxNet.o GEKabalRightPlayer.o \
GEJadeRightPlayer.o GERepLeftPlayer.o GEKabalLeftPlayer.o \
GECyraxRightPlayer.o GESZRightPlayer.o PKRoundEngine.o

#//////////////////////////////////////////////////////////////////////

SHELL	= /bin/sh
LD		= ld
CXX		= /opt/SUNWspro/bin/CC
AR		= /usr/ccs/bin/ar ruc
RM		= /bin/rm -rf

PKBASE	= /cs/src/pk3
IFLAGS    = -I$(PKBASE)/include -I.
LDFLAGS   = -G -o
CXXFLAGS  = -g

all: $(SOLIBRARY)

$(SOLIBRARY): $(SOLIBOBJ) 
	$(LD) $(LDFLAGS) $(SOLIBRARY) $(SOLIBOBJ) Templates.DB/*.o 

.cxx.o:
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $<

clean:
	$(RM) *.o Templates.DB core

install:
	cp $(SOLIBRARY) /cs/src/pk3/lib

backup:
	gtar czvf $(BACKUPDIR)/"`date +%d%m%y_%H%M%S`.tar.gz" \
		*.cxx *.h Makefile

