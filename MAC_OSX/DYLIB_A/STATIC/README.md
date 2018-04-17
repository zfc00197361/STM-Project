MAC OSx Static library

The standard locations for header files are:

In order to use the O_STM library with any C++ application, it need to be placed to the operation system
1. Copy lib_o_stm.a file to the working directory

2. Create Makefile :

### Makefile.mk Documentation
EXE =app
CC = g++ -lstdc++
#DOXYGEN = doxygen
PROGRAM = app
CFLAGS =-std=c++14 -pthread -o$(EXE)
CFILES = <YOUR *.cpp FILES>
HFILES = <YOUR *.h FILES>

# working more advanced
all:$(PROGRAM)

#Rule for static linking ASSUME the .a file in the same directory
$(PROGRAM):$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -I -L lib_o_stm.a  -o $(EXE)

clean:
	rm -f *.o

.PHONY: all clean

3. Run the application ./app

