PKMODULE=bh_misc
PKCFLAGS+=-pic
PKLIBFILES = libdebug.so libpkresources.so
PKINCFILES = PKGameClasses.h PKResources.h
PKBAKFILES = *.C *.h Makefile
include /cs/src/pk3/include/Makefile.pk3

libdebug.so: debug.o
	$(LD) -G -o $@ debug.o

libpkresources.so: PKResources.o
	$(LD) -G -o $@ PKResources.o
