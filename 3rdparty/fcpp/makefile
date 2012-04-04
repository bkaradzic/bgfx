##############################################################################
##                              FREXXWARE
##############################################################################
##
## Project: Frexx C Preprocessor
## $Source: /home/user/start/cpp/RCS/makefile,v $
## $Revision: 1.3 $
## $Date: 1994/06/02 09:11:24 $
## $Author: start $
## $State: Exp $
## $Locker:  $
##
##############################################################################
## $Log: makefile,v $
# Revision 1.3  1994/06/02  09:11:24  start
# Now uses 'gcc' and -O!
#
# Revision 1.2  1993/11/11  07:16:39  start
# New stuff
#
# Revision 1.1  1993/11/03  09:19:28  start
# Initial revision
#
##
##############################################################################

# Frexx PreProcessor Makefile

#HOST		=-tp -B/home/danne/code/cpp/ -Wp\,-Q\,-Dunix\,-Ddpc\,-DAIX
#DEFINES    = -Dunix -Dpdc -DAIX -DUNIX -DDEBUG
DEFINES     = -Dunix -Dpdc -DUNIX -DDEBUG
DEBUGFLAG	= -g
LD	        = ld
LDFLAGS		=
LIB         = libfpp.a
CPP         = fpp
FILECPP     = fcpp
TEMP		= templib.o
EXPORT		= fpp.exp
CC          = gcc
CFLAGS		= $(DEBUGFLAG) $(DEFINES)
AR      	= ar
ARFLAGS 	= rv
.SUFFIXES: .o .c .c~ .h .h~ .a .i
OBJS 		= cpp1.o cpp2.o cpp3.o cpp4.o cpp5.o cpp6.o
FILEOBJS 		= cpp1.o cpp2.o cpp3.o cpp4.o cpp5.o cpp6.o usecpp.o

# ** compile cpp
#

#all: $(LIB) $(CPP)
all: $(FILECPP)

$(LIB) : $(OBJS) $(EXPORT)
	$(LD) $(OBJS) -o $(TEMP) -bE:$(EXPORT) -bM:SRE -T512 -H512 -lc
	rm -f $(LIB)
	$(AR) $(ARFLAGS) $(LIB) $(TEMP)
	rm $(TEMP)

$(CPP) : usecpp.c
	$(CC) $(CFLAGS) -o $(CPP) usecpp.c -L. -lfpp

$(FILECPP) : $(FILEOBJS)
	$(CC) $(FILEOBJS) -o $(FILECPP)

.c.o:
	$(CC) $(CFLAGS) -c $<

cpp1.o:cpp1.c
cpp2.o:cpp2.c
cpp3.o:cpp3.c
cpp4.o:cpp4.c
cpp5.o:cpp5.c
cpp6.o:cpp6.c
memory.o:memory.c

usecpp.o:usecpp.c

clean :
	rm -f *.o $(FILECPP)

tgz:
	rm -f makefile*~
	(dir=`pwd`;name=`basename $$dir`;echo Creates $$name.tar.gz; cd .. ; \
	tar -cf $$name.tar `ls $$name/*.[ch] $$name/*.exp $$name/*.fd $$name/makefile*` ; \
	gzip $$name.tar ; chmod a+r $$name.tar.gz ; mv $$name.tar.gz $$name/)
