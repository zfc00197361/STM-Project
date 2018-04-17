MAC OSx Static library<br>
<br>
The standard locations for header files are:<br>
<br>
In order to use the O_STM library with any C++ application, it need to be placed to the operation system<br>
1. Copy lib_o_stm.a file to the working directory<br>
<br>
2. Create Makefile :<br>
<br>
### Makefile.mk Documentation<br>
EXE =app<br>
CC = g++ -lstdc++<br>
#DOXYGEN = doxygen<br>
PROGRAM = app<br>
CFLAGS =-std=c++14 -pthread -o$(EXE)<br>
CFILES = <YOUR *.cpp FILES><br>
HFILES = <YOUR *.h FILES><br>
<br>
# working more advanced<br>
all:$(PROGRAM)<br>
<br>
#Rule for static linking ASSUME the .a file in the same directory<br>
$(PROGRAM):$(CFILES) $(HFILES)<br>
	$(CC) $(CFLAGS) *.cpp -I -L lib_o_stm.a  -o $(EXE)<br>
<br>
clean:<br>
	rm -f *.o<br>
<br>
.PHONY: all clean<br>
<br>
3. Run the application ./app<br>

