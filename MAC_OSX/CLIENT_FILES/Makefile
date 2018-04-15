### Makefile.mk Documentation
EXE =app
CC = g++ -lstdc++
#DOXYGEN = doxygen
PROGRAM = app
CFLAGS =-std=c++14 -pthread -o$(EXE)
CFILES = main.cpp AIB.cpp ULSTER.cpp BOA.cpp UNBL.cpp SWBPLC.cpp
HFILES = AIB.h ULSTER.h BOA.h UNBL.h SWBPLC.h

# working simple
#all:$(CFILES) $(HFILES)
#	$(CC) $(CFLAGS) *.cpp -o $(EXE)
#	$(DOXYGEN) Doxyfile

# working more advanced
all:$(PROGRAM)

#Rule for shared linking
$(PROGRAM):$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -I -L /usr/lib/lib_o_stm.dylib  -o $(EXE)
	#g++ client.cpp -L/dir/ -lutils

#Rule for static linking
#$(PROGRAM):$(CFILES) $(HFILES)
#	$(CC) $(CFLAGS) *.cpp -I -L lib_o_stm.a  -o $(EXE)
	#g++ client.cpp -L/dir/ -lutils

clean:
	rm -f *.o