### Makefile.mk Documentation
EXE =app
CC = g++ -g
#DOXYGEN = doxygen
PROGRAM = app
CFLAGS =-std=c++14 -pthread -fgnu-tm -o$(EXE)
CFILES = main.cpp TM.cpp TX.cpp OSTM.cpp AIB.cpp ULSTER.cpp BOA.cpp UNBL.cpp SWBPLC.cpp
HFILES = TM.h TX.h OSTM.h AIB.h ULSTER.h BOA.h UNBL.h SWBPLC.h

# working simple
#all:$(CFILES) $(HFILES)
#	$(CC) $(CFLAGS) *.cpp -o $(EXE)
#	$(DOXYGEN) Doxyfile

# working more advanced
all:$(PROGRAM)

#Rule for linking
$(PROGRAM):$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -o $(EXE)

# debug:
# 	g++ -g signal.cpp -o barrierDebug

clean:
	rm -f *.o
