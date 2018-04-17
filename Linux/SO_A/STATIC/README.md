Usage of the STM library on Linux.
In order to use the O_STM library with any C++ application, it need to be placed to the same folder where is the application.
1. Copy lib_o_stm.a file to to your C++ application directory
2. Include the TM.h TX.h and the OSTM.h files in your application.
3. Create Makefile :

EXE =Test
CC = g++
PROGRAM = app
CFLAGS =-std=c++14 -pthread 
CFILES = <YOUR  CPP  FILES>
HFILES = TM.h TX.h OSTM.h <YOUR HEADER FILES>

all:$(PROGRAM)

###Rule for STATIC linking
$(PROGRAM):$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp lib_o_stm.a  -o $(EXE)
clean:
	rm -f *.o<br>

4. Run the application/executable file : ./Test

