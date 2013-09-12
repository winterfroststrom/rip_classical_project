# Another really simple makefile

CC = cxx
CFLAGS = -g
DEBUG = 
#-DDEBUG
EXTRAFLAGS = -DOUTLINE

INCLUDE = -I. 
LIB =
ILD = ild

OBJECTS = ldriver.o

GSRC=utility.h utility.cc
GOBJ=utility.o

LISTSRC=$(GSRC) list.h ldriver.cc list.cc listiter.cc
LISTOBJ=ldriver.o $(GOBJ) objects.o list.o listiter.o
LSDR=ldriver

BITSRC=$(GSRC) bitstring.h bitstring.cc bdriver.cc
BITOBJ=bitstring.o $(GOBJ) bdriver.o
BITDR=bdriver

VSRC=$(GSRC) varset.h varset.cc vdriver.cc
VOBJ=$(GOBJ) varset.o vdriver.o bitstring.o objects.o
VDR=vdriver

TSRC=$(GSRC) table.h tdriver.cc table.cc
TOBJ=$(GOBJ) tdriver.o table.o
TDR=tdriver

TMSRC=$(GSRC) temlist.h temlist.cc temlist.icc
TMOBJ=$(GOBJ) temlist.o tldriver.o
TMDR=tldriver

PSRC=$(GSRC) read.l

.SUFFIXES: .o .cc .h .icc
.cc.o:
	$(COMPILE) -c $<

COMPILE=$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) $(EXTRAFLAGS) $(LIB) 

temlist.o: temlist.h temlist.cc temlist.icc
tldriver.o: temlist.o
tldriver: temlist.o tldriver.o utility.o

tldriver:
	$(COMPILE) $(TMOBJ) -o $(TMDR)

objects.o: objects.cc objects.h
list.o: list.h list.icc list.cc
ldriver.o: $(LISTSRC)
ldriver: $(LISTOBJ)

ldriver: $(LISTOBJ)
	$(COMPILE) $(LISTOBJ) -o $(LSDR)

bitstring.o: utility.h bitstring.cc bitstring.h
bdriver.o: bdriver.cc bitstring.o
bdriver: bdriver.o 

bdriver: $(BITOBJ)
	$(COMPILE) $(BITOBJ) -o $(BITDR)

table.o: table.h table.cc
tdriver.o: table.h tdriver.cc table.o
tdriver: tdriver.o

tdriver: $(TOBJ)
	$(COMPILE) $(TOBJ) -o $(TDR)


varset.o: utility.h varset.cc varset.h
vdriver.o: vdriver.cc varset.o
vdriver: vdriver.o 

vdriver: $(VOBJ)
	$(COMPILE) $(VOBJ) -o $(VDR)

parser: ucpop.l ucpop.y objects.o table.o

parser: 
	rm -f $@
	yacc ucpop.y
	flex ucpop.l
	mv lex.yy.c lex.yy.cc
	mv y.tab.c y.tab.cc
#	$(COMPILE) -c lex.yy.cc
	$(COMPILE) -c y.tab.cc
	$(COMPILE) y.tab.o table.o objects.o -ly -o parser


clean:
	rm -f *~ *.o ldriver vdriver bdriver parser driver tdriver
# DO NOT DELETE THIS LINE -- make depend depends on it.

