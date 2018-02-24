### Makefile.mk Documentation
EXE =Test01
CC = g++
#DOXYGEN = doxygen
PROGRAM = app
CFLAGS =-std=c++14 -pthread 
CFILES = main.cpp AIB.cpp ULSTER.cpp BOA.cpp UNBL.cpp SWBPLC.cpp
HFILES = TM.h TX.h OSTM.h AIB.h ULSTER.h BOA.h UNBL.h SWBPLC.h

# working simple
#all:$(CFILES) $(HFILES)
#	$(CC) $(CFLAGS) *.cpp -o $(EXE)
#	$(DOXYGEN) Doxyfile

# working more advanced
all:$(PROGRAM)

#Rule for STATIC linking
#$(PROGRAM):$(CFILES) $(HFILES)
#	$(CC) $(CFLAGS) *.cpp lib_o_stm.a  -o $(EXE) 

#Rule for SHARED linking
$(PROGRAM):$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -I -L /usr/lib/lib_o_stm.so  -o $(EXE)	
clean:
	rm -f *.o


