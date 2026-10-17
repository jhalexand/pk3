#
# cs032 sample C++ makefile
#
# Copy this file into the directory where you keep the source files of
# your program. Change the variables EXEC and OFILES below to reflect 
# your source. When you are ready to compile your program, just type 
# 'make' in the directory.
#

.KEEP_STATE:
.SILENT:
.SUFFIXES: .cxx .h

#
# Change EXEC to the name of the executable which you wish to
# create. Make OFILES be the name of all the .C files in your program,
# but change the .C to .o.
#

EXEC	= pkd
OFILES	= \
	MAINServer.o \
	MAINNetwork.o \
	MAINUser.o \
	MAINAIUser.o \
	MAINGame.o \
	MAINGameList.o \
	MAINUserList.o \
	main.o \


# Compiler specifications
CCC = /opt/SUNWspro/bin/CC
INSTALL = /cs/src/pk3/bin/bin_install

# Debug/Non-debug flags; debug by default (make fast to optimize)
DFLAGS  =       -g -DDEBUG
NDFLAGS =	-fast -xO5 -DNDEBUG
# Make that -DNDEBUG to get rid of the dprintf outputs
CFLAGS  =	$(DFLAGS)

# Includes
IFLAGS	=	-I/cs/include -I/usr/include -I/cs/src/pk3/include
LFLAGS	=	-L. -L/cs/src/pk3/lib
LIBS	=	-lobjectsocket -lnetstream -ldebug -lsocket -lnsl -lintl
RUNLIBS = 	-R/cs/src/pk3/lib

# Directories
BINDIR	=	/cs/src/pk3/bin


#
# These are different make options.  You can invoke them by typing 
# the label name.  For example to time your make, type 'make time' -- 
# 'make' being the name of this command and 'time' being the label used 
# below to define the result.  
#
# Standard make, it makes everything.  You can type 'make all' or 
# just 'make'

all:	$(EXEC)

$(EXEC)	: $(OFILES)
	echo "linking $@"
	$(CCC) $(CFLAGS) -o $(EXEC) $(OFILES) $(IFLAGS) $(LFLAGS) $(RUNLIBS) $(LIBS) 
	echo "make finished at " `date`

# All .C files depend on their headers
%.cxx:    %.h

# Define a rule for building .o from .C files
.cxx.o:
	echo "$(CCC) $< $(CFLAGS)"
	$(CCC) $(CFLAGS)  $(IFLAGS) -c $<


# Clean up after making. 
clean:
	echo "removing" *.o $(EXEC) core a.out
	$(RM) *.o $(EXEC) core a.out

# remove tilde-files
tidy:
	echo "removing" *~
	$(RM) *~

# Time your make.
time:
	/usr/bin/time $(MAKE)

# install into bindir
install: all
	$(INSTALL) $(EXEC)

