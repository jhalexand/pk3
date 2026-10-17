PKMODULE = audio
PKBAKFILES = *.C *.h Makefile
PKLIBFILES = libpkaudio.so
PKSRCFILES = PKAudioClass.C PKAudioPlayer.C
PKCFLAGS+=-pic
include /cs/src/pk3/include/Makefile.pk3


OBJECTS=$(PKSRCFILES:%.C=%.o)

libpkaudio.so: $(OBJECTS)
	$(LD) -G -o $@ $(OBJECTS) Templates.DB/*.o
