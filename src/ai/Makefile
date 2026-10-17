.SUFFIXES: .C .h

PKTARGETS =
PKMODULE = ai
PKBAKFILES= *.C *.h Makefile # and readme
PKBINFILES= pkaiclient
PKLIBFILES=
PKINCFILES=
PKTOCLEAN =
PKSRCFILES = PKAIClient.C PKAIClientMain.C

include /cs/src/pk3/include/Makefile.pk3

EXEC	= pkaiclient
OFILES	= $(PKSRCFILES:%.C=%.o)

LIBS	= -lpkclientnetwork \
	-lnetstream -lobjectsocket -ldebug -lds \
	-lsocket -lnsl -lXt -libmil

pkaiclient: $(OFILES)
	$(PKCC_WFLAGS) -o $@ $(OFILES) $(LIBS) 
	@echo "make finished at " `date`


# DO NOT DELETE

PKAIClient.o: PKAIClient.h /cs/src/pk3/include/PKClientInterface.h
PKAIClient.o: /cs/src/pk3/include/PKids.h /cs/src/pk3/include/PKGameClasses.h
PKAIClient.o: /cs/src/pk3/include/debug.h /usr/include/stdio.h
PKAIClient.o: /usr/include/sys/feature_tests.h /usr/include/sys/va_list.h
PKAIClient.o: /usr/include/assert.h /usr/include/stdlib.h
PKAIClient.o: /usr/include/string.h /cs/src/pk3/include/PKObject.h
PKAIClient.o: /cs/src/pk3/include/VectorMath.h /usr/include/math.h
PKAIClient.o: /cs/src/pk3/include/PKKey.h
PKAIClient.o: /cs/src/pk3/include/PKClientObject.h /usr/include/sys/time.h
PKAIClient.o: /usr/include/sys/types.h /usr/include/sys/isa_defs.h
PKAIClient.o: /usr/include/sys/machtypes.h /usr/include/sys/int_types.h
PKAIClient.o: /usr/include/sys/select.h /usr/include/sys/time.h
PKAIClient.o: /cs/src/pk3/include/HashTable.h /cs/src/pk3/include/Array.h
PKAIClient.o: /usr/dt/include/Xm/Xm.h /usr/include/X11/Intrinsic.h
PKAIClient.o: /usr/include/X11/Xlib.h /usr/include/X11/X.h
PKAIClient.o: /usr/include/X11/Xfuncproto.h /usr/include/X11/Xosdefs.h
PKAIClient.o: /usr/include/stddef.h /usr/include/X11/Xutil.h
PKAIClient.o: /usr/include/X11/Xresource.h /usr/include/X11/Core.h
PKAIClient.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
PKAIClient.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
PKAIClient.o: /usr/include/X11/Shell.h /usr/include/X11/SM/SMlib.h
PKAIClient.o: /usr/include/X11/SM/SM.h /usr/include/X11/ICE/ICElib.h
PKAIClient.o: /usr/include/X11/ICE/ICE.h /usr/include/X11/Xatom.h
PKAIClient.o: /usr/dt/include/Xm/XmStrDefs.h /usr/include/X11/StringDefs.h
PKAIClient.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
PKAIClient.o: /cs/src/pk3/include/PKClientNetworkInterface.h
PKAIClientMain.o: PKAIClient.h /cs/src/pk3/include/PKClientInterface.h
PKAIClientMain.o: /cs/src/pk3/include/PKids.h
PKAIClientMain.o: /cs/src/pk3/include/PKGameClasses.h
PKAIClientMain.o: /cs/src/pk3/include/debug.h /usr/include/stdio.h
PKAIClientMain.o: /usr/include/sys/feature_tests.h /usr/include/sys/va_list.h
PKAIClientMain.o: /usr/include/assert.h /usr/include/stdlib.h
PKAIClientMain.o: /usr/include/string.h /cs/src/pk3/include/PKObject.h
PKAIClientMain.o: /cs/src/pk3/include/VectorMath.h /usr/include/math.h
PKAIClientMain.o: /cs/src/pk3/include/PKKey.h
PKAIClientMain.o: /cs/src/pk3/include/PKClientObject.h
PKAIClientMain.o: /usr/include/sys/time.h /usr/include/sys/types.h
PKAIClientMain.o: /usr/include/sys/isa_defs.h /usr/include/sys/machtypes.h
PKAIClientMain.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
PKAIClientMain.o: /usr/include/sys/time.h /cs/src/pk3/include/HashTable.h
PKAIClientMain.o: /cs/src/pk3/include/Array.h /usr/dt/include/Xm/Xm.h
PKAIClientMain.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
PKAIClientMain.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
PKAIClientMain.o: /usr/include/X11/Xosdefs.h /usr/include/stddef.h
PKAIClientMain.o: /usr/include/X11/Xutil.h /usr/include/X11/Xresource.h
PKAIClientMain.o: /usr/include/X11/Core.h /usr/include/X11/Composite.h
PKAIClientMain.o: /usr/include/X11/Constraint.h /usr/include/X11/Object.h
PKAIClientMain.o: /usr/include/X11/RectObj.h /usr/include/X11/Shell.h
PKAIClientMain.o: /usr/include/X11/SM/SMlib.h /usr/include/X11/SM/SM.h
PKAIClientMain.o: /usr/include/X11/ICE/ICElib.h /usr/include/X11/ICE/ICE.h
PKAIClientMain.o: /usr/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
PKAIClientMain.o: /usr/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
PKAIClientMain.o: /usr/dt/include/Xm/VendorS.h
