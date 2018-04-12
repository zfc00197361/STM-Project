all: run

run:library


TM.o: TM.cpp
	g++ -std=c++17 -c "TM.cpp" -o TM.o

TX.o: TX.cpp
	g++ -std=c++17 -c "TX.cpp" -o TX.o 

OSTM.o: OSTM.cpp
	g++ -std=c++17 -c "OSTM.cpp" -o OSTM.o

library: TM.o TX.o OSTM.o
	@echo "** Building the O_STM library"
	ar rcs lib_o_stm.a TM.o TX.o OSTM.o

clean:
	@echo "** Removing object files and executable..."
	rm -f *.o

.PHONY: all clean
#-c -Wall -Werror -fpic