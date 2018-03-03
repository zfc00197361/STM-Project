MAC OSx Shared library solution.<br>
Makefile create the .dylib shared library file.<br>
<br>
all: run<br>
<br>
run:library<br>
<br>
TM.o: TM.cpp<br>
	g++ -std=c++14 -fPIC -c "TM.cpp" -o TM.o<br>
<br>
TX.o: TX.cpp<br>
	g++ -std=c++14  -fPIC -c "TX.cpp" -o TX.o <br>
<br>
OSTM.o: OSTM.cpp<br>
	g++ -std=c++14  -fPIC -c "OSTM.cpp" -o OSTM.o<br>
<br>
library: TM.o TX.o OSTM.o<br>
	@echo "** Building the O_STM library"<br>
	g++ -dynamiclib -o lib_o_stm.dylib TM.o TX.o OSTM.o<br>
<br>
clean:<br>
	@echo "** Removing object files and executable..."<br>
	rm -f *.o<br>
<br>
.PHONY: all clean<br>
<br>