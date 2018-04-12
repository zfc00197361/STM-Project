Usage of the STM library on Linux.<br>
In order to use the O_STM library with any C++ application, it need to be placed to the same folder where is the application.<br>
1. Copy lib_o_stm.a file to to your C++ application directory<br>
2. Include the TM.h TX.h and the OSTM.h files in your application.<br>
3. CReate Makefile :
<br><br>
### Makefile.mk Documentation<br><br>
EXE =Test<br>
CC = g++<br>
PROGRAM = app<br>
CFLAGS =-std=c++14 -pthread <br>
CFILES = main.cpp AIB.cpp ULSTER.cpp BOA.cpp UNBL.cpp SWBPLC.cpp<br>
HFILES = TM.h TX.h OSTM.h AIB.h ULSTER.h BOA.h UNBL.h SWBPLC.h<br>
<br><br>
all:$(PROGRAM)<br>
<br><br>
###Rule for STATIC linking<br>
$(PROGRAM):$(CFILES) $(HFILES)<br>
	$(CC) $(CFLAGS) *.cpp lib_o_stm.a  -o $(EXE) 	<br>
clean:<br>
	rm -f *.o<br>
<br>
5. Run the application/executable file : ./Test

