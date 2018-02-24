all: run

run:library


TM.o: TM.cpp
	g++ -fPIC -c "TM.cpp" -o TM.o

TX.o: TX.cpp
	g++ -fPIC -c "TX.cpp" -o TX.o 

OSTM.o: OSTM.cpp
	g++ -fPIC -c "OSTM.cpp" -o OSTM.o

library: TM.o TX.o OSTM.o
	@echo "** Building the game Wator Simulation"
	g++ -shared -o lib_o_stm.so TM.o TX.o OSTM.o

clean:
	@echo "** Removing object files and executable..."
	rm -f *.o



.PHONY: all clean
#CFLAGS := -fPIC -O3 -g -Wall -Werror
#CC := g++
#MAJOR := 0
#MINOR := 1
#NAME := foo
#VERSION := $(MAJOR).$(MINOR)
#
#lib: lib$(NAME).so.$(VERSION)
#
#lib$(NAME).so.$(VERSION): $(NAME).o
#	$(CC) -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@
#
#clean:
#	$(RM) *.o *.so*


#CFLAGS := -fPIC -O3 -g -Wall -Werror
#CC := g++
#MAJOR := 0
#MINOR := 1
#NAME := o_stm
#VERSION := $(MAJOR).$(MINOR)
#
#lib: lib$(NAME).so.$(VERSION)
#
#lib$(NAME).so.$(VERSION): $(NAME).o
#	$(CC) -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@
#
#clean:
#    $(RM) *.o


#.PHONY : clean
#
#CPPFLAGS= -fPIC -g
#LDFLAGS= -shared
#
#SOURCES = $(shell echo *.cpp)
#HEADERS = $(shell echo *.h)
#OBJECTS=$(SOURCES:.cpp=.o)
#
#FIKSENGINE_LIBDIR=../../../../lib
#FIKSENGINE_INCDIR=../../../../include
#
#TARGET=$(FIKSENGINE_LIBDIR)/tinyxml.so
#
#all: $(TARGET)
#
#clean:
#    rm -f $(OBJECTS) $(TARGET)
#
#$(TARGET) : $(OBJECTS)
#    $(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)


#### Makefile.mk Documentation
#EXE =app
#CC = g++ -g
##DOXYGEN = doxygen
#PROGRAM = app
#CFLAGS =-std=c++14 -pthread -fgnu-tm -o$(EXE)
#CFILES = main.cpp TM.cpp TX.cpp OSTM.cpp AIB.cpp ULSTER.cpp BOA.cpp UNBL.cpp SWBPLC.cpp
#HFILES = TM.h TX.h OSTM.h AIB.h ULSTER.h BOA.h UNBL.h SWBPLC.h
#
## working simple
##all:$(CFILES) $(HFILES)
##	$(CC) $(CFLAGS) *.cpp -o $(EXE)
##	$(DOXYGEN) Doxyfile
#
## working more advanced
#all:$(PROGRAM)
#
##Rule for linking
#$(PROGRAM):$(CFILES) $(HFILES)
#	$(CC) $(CFLAGS) *.cpp -o $(EXE)
#
## debug:
## 	g++ -g signal.cpp -o barrierDebug
#
#clean:
#	rm -f *.o
