Usage of the STM library on Linux.<br>
In order to use the O_STM library with any C++ application, it need to be placed to the same folder where is the application.<br>
1. Copy lib_o_stm.a file to to your C++ application directory<br>
2. Include the TM.h TX.h and the OSTM.h files in your application.<br>
3. Create Makefile :<br>
<br>
EXE =Test<br>
CC = g++<br>
PROGRAM = app<br>
CFLAGS =-std=c++14 -pthread <br>
CFILES = <YOUR  CPP  FILES><br>
HFILES = TM.h TX.h OSTM.h <YOUR HEADER FILES><br>
<br>
all:$(PROGRAM)<br>
<br>
###Rule for STATIC linking
$(PROGRAM):$(CFILES) $(HFILES)<br>
	$(CC) $(CFLAGS) *.cpp lib_o_stm.a  -o $(EXE)<br>
clean:<br>
	rm -f *.o<br><br>
<br>
4. Run the application/executable file : ./Test<br>

