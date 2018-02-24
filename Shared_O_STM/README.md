Usage of the STM library on Linux.<br>
In order to use the O_STM library with any C++ application, it need to be placed to the operation system /usr/lib directory.<br>
1. Copy lib_o_stm.so file to /usr/lib: sudo cp lib_o_stm.so /usr/lib
2. Include the TM.h TX.h and the OSTM.h files in your application.<br>
3. Create *.o files from the source files : g++ -c main.cpp BANK.cpp WAREHOUSE.cpp *** and all the other files ....... 
4. Compile the application and create the execurtable file : g++ -pthread -o exeName  main.o BANK.o AIB.o WAREHOUSE.o <*** and all the other files .......> lib_o_stm.so
5. Run the application ./exeName


