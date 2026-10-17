PKMODULE=netlib
PKBAKFILES =*.C *.h Makefile
PKBINFILES=
PKLIBFILES=libobjectsocket.so libnetstream.so
PKINCFILES=NetworkException.h Vector.h \
	InternetSocket.h \
	NETReadWriteSocket.h NETListenSocket.h \
	NETStream.h NETRequestID.h NETids.h
include ./Makefile.pk3

# for objectsocket library, we need all these
SOCKETFILES = Vector.o \
		InternetSocket.o \
		NETReadWriteSocket.o NETListenSocket.o NetworkException.o

STREAMFILES = NETStream.o

#########################################
# lists of libraries
CSOCKETLIBS = -lsocket -lnsl
LIBS = $(CSOCKETLIBS) -ldebug


libobjectsocket.so: $(SOCKETFILES)
	$(LD) -G -o $@ $(SOCKETFILES)


libnetstream.so: $(STREAMFILES)
	$(LD) -G -o $@ $(STREAMFILES)

# install anything that needs installing
install: all
	$(PKINSTALLBIN) $(PKBINFILES)
	$(PKINSTALLLIB) $(PKLIBFILES)
	cp -f $(PKINCFILES) $(PKINC)/Network

