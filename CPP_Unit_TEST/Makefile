PROGRAM = app
CXX = g++ -std=c++14 -pthread
INCLUDES= -I./
CXXFLAGS = -g $(INCLUDES)
SRCM= main.cpp client.cpp TM.cpp TX.cpp OSTM.cpp BANK.cpp AIB.cpp ULSTER.cpp BOA.cpp UNBL.cpp SWBPLC.cpp BOI.cpp
OBJM = $(SRCM:.cpp=.o)
LINKFLAGS= -lcppunit

app: MyTestCAse.cpp $(OBJM)
	$(CXX) $(CXXFLAGS) -o $@ MyTestCAse.cpp $(OBJM) $(LINKFLAGS) $(LINKFLAGSLOG4) $(LIBLOG)

# Default compile

#.cpp.o:
#	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f *.o
