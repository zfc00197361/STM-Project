C++ Software Transactional Memory (STM)

This documentation includes all the project specific files that required to build the STM library and the
client code to use the library. The client code is demostrate the usage of the STM API (Application Programming Interface).
The STM library is a object based implementation, where the client need to inherite from the library on order to
achieve the polymorphic Object Oriented Programming (OOP) behaviour. 

The client application use a middle class to declare the child (Classes inherite from BANK) specific behaviour as a virtual methods. 
Whit this implementation the client application need to casting back the OSTM object to BANK object to use the child class
implemented speciffic behaviours.  





