MAC OSx Shared library<br>
<br>
The standard locations for header files are:<br>
~/include<br>
/usr/local/include<br>
/usr/include<br>
<br>
The standard locations for dynamic libraries (.dylib) are:<br>
~/lib<br>
/usr/local/lib<br>
/usr/lib<br>
<br>
You may also place the .dylib file at a nonstandard location in your file system, but you must add that location to one of these environment variables:<br>
<br>
LD_LIBRARY_PATH<br>
DYLD_LIBRARY_PATH<br>
DYLD_FALLBACK_LIBRARY_PATH<br>
<br>
In order to use the O_STM library with any C++ application, it need to be placed to the operation system<br>
1. Copy lib_o_stm.dylib file to /usr/lib: sudo cp lib_o_stm.dylib /usr/lib<br>
2. Include the TM.h TX.h and the OSTM.h files in your application.<br>
3. Create Makefile :<br>
<br>
### Makefile.mk Documentation<br>
EXE =app<br>
CC = g++ -lstdc++<br>
#DOXYGEN = doxygen<br>
PROGRAM = app<br>
CFLAGS =-std=c++14 -pthread -o$(EXE)<br>
CFILES = <YOUR *.cpp files><br>
HFILES = <YOUR *.h files><br>
<br>
# working more advanced<br>
all:$(PROGRAM)<br>
<br>
#Rule for shared linking ASSUME THE .dylib files is in the /usr/lib/ location<br>
$(PROGRAM):$(CFILES) $(HFILES)<br>
	$(CC) $(CFLAGS) *.cpp -I -L /usr/lib/lib_o_stm.dylib  -o $(EXE)<br>
<br>
clean:<br>
	rm -f *.o<br>
<br>
4. Run the application/executable file : ./app<br>