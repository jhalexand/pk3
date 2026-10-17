PKMODULE=netlayers
PKLIBFILES = libpkgameserver.so libpkclientnetwork.so
PKBINFILES = pkgameserver
PKINCFILES = PKClientNetworkInterface.h PKGameServerInterface.h
PKBAKFILES = *.C *.h Makefile
PKCFLAGS+=-pic
include /cs/src/pk3/include/Makefile.pk3

# for module libraries, we only need interface and implementation
# (rest is linked in as the objectsocket library)
PKSERVFILES = PKGameServerInterface.o PKGameServerImplementation.o \
	PKGameServerConnection.o

PKCLIEFILES = PKClientNetworkInterface.o PKClientNetworkImplementation.o \
	CLIENTGameServer.o CLIENTMainServer.o

# for real executables
PKGAMESERVERFILES = PKGameServer.o

#########################################
# lists of libraries
LIBS = -lobjectsocket -lnetstream -lsocket -lnsl -lintl -ldebug

# make the pkgameserver shared object
libpkgameserver.so: $(PKSERVFILES)
	$(LD) -G -o $@ $(PKSERVFILES)

# make the pkclientnetwork shared object
libpkclientnetwork.so: $(PKCLIEFILES)
	$(LD) -G -o $@ $(PKCLIEFILES)

# make the pkgameserver executable
pkgameserver: $(PKGAMESERVERFILES)
	$(PKCC) -o $@ $(PKGAMESERVERFILES) $(PKLFLAGS) $(PKRFLAGS)  \
		$(LIBS) -lpkgameengine -lpkgameserver \
		-lpkphysics -lrwtool
