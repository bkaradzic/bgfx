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

DEFINES   = -Dunix -Dpdc -DUNIX -DDEBUG
DEBUGFLAG = -g
LIB       = libfpp.a
CPP       = fpp
FILECPP   = fcpp
CFLAGS    = $(DEBUGFLAG) $(DEFINES)
ARFLAGS   = rv
O         = o
OBJS      = cpp1.$(O) cpp2.$(O) cpp3.$(O) cpp4.$(O) cpp5.$(O) cpp6.$(O)
FILEOBJS  = $(OBJS) usecpp.$(O)

all: $(FILECPP)

$(LIB) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(CPP) : usecpp.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L. -lfpp

$(FILECPP) : $(FILEOBJS)
	$(CC) $(FILEOBJS) -o $(FILECPP)

.c.$(O):
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f *.$(O) $(FILECPP) $(LIB) $(CPP)

tgz:
	rm -f makefile*~
	(dir=`pwd`;name=`basename $$dir`;echo Creates $$name.tar.gz; cd .. ; \
	tar -cf $$name.tar `ls $$name/*.[ch] $$name/*.exp $$name/*.fd $$name/makefile*` ; \
	gzip $$name.tar ; chmod a+r $$name.tar.gz ; mv $$name.tar.gz $$name/)
