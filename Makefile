# Makefile for Leaf Brawl
# On Mac, use the Xcode project
# On Linux, use this Makefile to compile Leaf Brawl
# On Windows, use the Visual Studio project
# You need to have a compiled version of Orx for your platform in the lib/ folder
# You may need to change the compiler if you don't have g++ in your PATH
ODIR=obj
OUTDIR=Build
OUTPUT=$(OUTDIR)/Leaf\ Brawl

CC=g++
FLAGS=-std=c++11 -c -o $(ODIR)/$(@F)
LD=-I inc/ -L lib/
LIB=-l orx

OBJS=Main.o StandAlone.o
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

ifdef DEBUG
	FLAGS += -g -O0
endif

leafbrawl: copyassets $(_OBJS)
	$(CC) $(LD) $(_OBJS) $(LIB) -o $(OUTPUT)

copyassets:
	mkdir -p $(OUTDIR) $(ODIR)
	cp -u bin/*.ini $(OUTDIR)

$(ODIR)/Main.o:
	$(CC) $(FLAGS) $(LD) Leaf\ Brawl/App/Main.cpp

$(ODIR)/StandAlone.o:
	$(CC) $(FLAGS) $(LD) Leaf\ Brawl/App/StandAlone.cpp

clean:
	rm -f $(ODIR)/*.o $(OUTPUT)

squeakyclean:
	rm -rf $(OUTDIR) $(ODIR)
