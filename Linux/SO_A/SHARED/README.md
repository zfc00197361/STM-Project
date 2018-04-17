Usage of the STM library on Linux.
In order to use the O_STM library with any C++ application, it need to be placed to the operation system /usr/lib directory.
1. Copy lib_o_stm.so file to /usr/lib: sudo cp lib_o_stm.so /usr/lib
2. Include the TM.h TX.h and the OSTM.h files in your application.
3. Create Makefile :

### Makefile.mk Documentation
EXE =Test
CC = g++
PROGRAM = app
CFLAGS =-std=c++14 -pthread 
CFILES = <YOUR  CPP  FILES>
HFILES = TM.h TX.h OSTM.h  <YOUR HEADER FILES>

all:$(PROGRAM)

###Rule for SHARED linking<br>
$(PROGRAM):$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -I -L /usr/lib/lib_o_stm.so  -o $(EXE)	<br>
clean:
	rm -f *.o<br>

4. Run the application/executable file : ./Test


