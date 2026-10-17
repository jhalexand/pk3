.KEEP_STATE: 
.SUFFIXES: .C .h

EXEC	= pkclient
OFILES	= \
	PKOpeningGUI.o \
	PKChatBox.o \
	PKMainServerGUI.o \
	PKPlayerPanel.o \
	PKGameGatheringGUI.o \
	PKPaddleKeys.o \
	PKPaddleColumn.o \
	PKInfoColumn.o \
	PKClient.o \
	main.o



# for make install, the destination of executables
BINDIR  = /cs/src/pk3/bin
BACKUPDIR = backups

# Compiler specifications
#CCC = /opt/SUNWspro/bin/CC
CCC = egcc

# compiler flags
CFLAGS  = -g -DDEBUG

# Includes
IFLAGS	= -I/cs/include -I/usr/include/X11 -I/usr/dt/include \
		-I/cs/src/pk3/include -I/usr/include \
		`gtk-config --cflags` 
LFLAGS	= -xildoff -L/cs/src/pk3/lib -L/usr/dt/lib -L/cs/lib \
		`gtk-config --libs` -L/cs/include \
        	-L/opt/SUNWspro4.2/SC4.2/lib/rw7 \
        	-L/course/cs032/lib \
        	-L/opt/SUNWspro/lib

		

LIBS	= -lpkclientnetwork -lpkgraphics -lpkaudio -lpkresources \
	-lnetstream -lobjectsocket -lsocket -lnsl -lintl -ldebug -lrplay\
	-lsocket -lnsl \
	-lgtk -lglib -lgdk -lX11 -lgmodule -lC

RFLAGS  = -R/cs/src/pk3/lib -R/usr/dt/lib -R/cs/lib

#
# These are different make options.  You can invoke them by typing 
# the label name.  For example to time your make, type 'make time' -- 
# 'make' being the name of this command and 'time' being the label used 
# below to define the result.  
#
# Standard make, it makes everything.  You can type 'make all' or 
# just 'make', since all is the first rule

all:	$(EXEC)

$(EXEC)	: $(OFILES)
	$(CCC) $(CFLAGS) -o $(EXEC) $(OFILES) $(LFLAGS) $(RFLAGS) $(LIBS) 
	@echo "make finished at " `date`

# All .C files depend on their headers
%.C:    %.h

# Define a rule for building .o from .C files
.C.o:
	$(CCC) -c $< $(CFLAGS)  $(IFLAGS)

# Clean up after making. 
clean:
	@echo $(RM) *.o $(EXEC) core a.out
	@$(RM) -f *.o $(EXEC) core a.out

# install the executable into the bin directory
install:
	-cp $(EXEC) $(BINDIR)

# backup all your files 
backup:
	tar cvf - *.C *.h Makefile README | gzip > $(BACKUPDIR)/"`date`.tar.gz"

# remove tilde-files
tidy:
	@echo $(RM) *~
	@-$(RM) *~

# Time your make.
time:
	/usr/bin/time $(MAKE)
