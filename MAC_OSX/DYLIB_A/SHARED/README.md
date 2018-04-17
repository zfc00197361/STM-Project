MAC OSx Shared library

The standard locations for header files are:
~/include
/usr/local/include
/usr/include

The standard locations for dynamic libraries (.dylib) are:
~/lib
/usr/local/lib
/usr/lib

You may also place the .dylib file at a nonstandard location in your file system, but you must add that location to one of these environment variables:

LD_LIBRARY_PATH
DYLD_LIBRARY_PATH
DYLD_FALLBACK_LIBRARY_PATH

In order to use the O_STM library with any C++ application, it need to be placed to the operation system
1. Copy lib_o_stm.dylib file to /usr/lib: sudo cp lib_o_stm.dylib /usr/lib
2. Include the TM.h TX.h and the OSTM.h files in your application.
3. Create Makefile :

### Makefile.mk Documentation
EXE =app
CC = g++ -lstdc++
#DOXYGEN = doxygen
PROGRAM = app
CFLAGS =-std=c++14 -pthread -o$(EXE)
CFILES = <YOUR *.cpp files>
HFILES = <YOUR *.h files>

# working more advanced
all:$(PROGRAM)

#Rule for shared linking ASSUME THE .dylib files is in the /usr/lib/ location
$(PROGRAM):$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -I -L /usr/lib/lib_o_stm.dylib  -o $(EXE)

clean:
	rm -f *.o

4. Run the application/executable file : ./app