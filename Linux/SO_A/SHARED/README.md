Usage of the STM library on Linux.<br>
In order to use the O_STM library with any C++ application, it need to be placed to the operation system /usr/lib directory.<br>
1. Copy lib_o_stm.so file to /usr/lib: sudo cp lib_o_stm.so /usr/lib<br>
2. Include the TM.h TX.h and the OSTM.h files in your application.<br>
3. Create Makefile :<br>
<br>
### Makefile.mk Documentation<br>
EXE =Test<br>
CC = g++<br>
PROGRAM = app<br>
CFLAGS =-std=c++14 -pthread <br>
CFILES = <YOUR  CPP  FILES><br>
HFILES = TM.h TX.h OSTM.h  <YOUR HEADER FILES><br>
<br>
all:$(PROGRAM)<br>
<br>
###Rule for SHARED linking<br>
$(PROGRAM):$(CFILES) $(HFILES)<br>
	$(CC) $(CFLAGS) *.cpp -I -L /usr/lib/lib_o_stm.so  -o $(EXE)	<br>
clean:<br>
	rm -f *.o<br>
<br>
4. Run the application/executable file : ./Test<br>


