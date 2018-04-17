/*!
 * File:   TM.h
 * Author: Zoltan Fuzesi C00197361, 
 * IT Carlow, Software Engineering, 
 *
 * Supervisor : Joe Kehoe, 
 *
 * C++ Software Transactional Memory, 

 * 
 * Created on December 18, 2017, 2:09 PM
 * Transaction Manager class fields and methods declarations
 *
 * \mainpage C++ Software Transactional Memory
 *
 * \section OSTM Object Based Software Transactional Memory.
 *      
 *
 * OSTM is a polymorphic solution to store and manage shared memory spaces within c++ programming context.<br>
 * You can store and managed any kind of object in transactional environment as a shared and protected memory space, if your class
 * inherited from the OSTM base class, and follows the required steps.
 *
 * \subsection install_sec Installation of the Shared library on Linux platform.
 * Download the zip file from the provided (Windows, Linux, MAC OSX)link in the web-site, 
 * that contains the libostm.so, TM.h, TX.h, OSTM.h files.Unzip the archive file to the desired destination possibly where 
 * you program is stored. Copy the library (Shared, Static) to the destination directory. Implement the inheritance from the base class.
 * Create an executable, and run the application.  
 *
 * \subsection step1 Step 1: Download the archive file.
 * Go to the website <a href="http://serversite.info/ostm/#tutorial" target="_blank">Tutorial</a> and download the library to the required
 * operating system platform. (Linux, Windows, Mac OSX) 
 * 
 * 
 * \subsection step2 Step 2: Unzip in to the target destination.
 * Unzip the downloaded rar file. You can find the Shared, Static library and the *.h files in the unzipped folder.
 * Copy the *.h files to the same folder where is the other C++ files are  stored.
 * 
 * \subsection step3 Step 3: Copy the shared library.
 * The Shared library is a libostm.so file, that you need copy to the operating system directory where the other shared library are stored.
 * It will be different destination folder on different platforms. (Linux, Windows, Mac OS) <a href="http://serversite.info/ostm/#tutorial" target="_blank">More Information</a> 
 * 
 * \subsection step4 Step 4: Achieve the required class hierarchy.
 * To achieve the required class hierachy between the OSTM library and your own class structure, you need to implement few steps
 * to inherite from the OSTM base class. Go to website <a href="http://serversite.info/ostm/#tutorial" target="_blank">Tutorial</a> for more details.
 * Details and instruction of class hierarchy requirements can be found on the web-site. www.serversite.info/ostm
 * 
 * \subsection step5 Step 5: Create an executable file.
 *  You can create an executable file using the provided Makefile as you linking together the library (libostm.so), and the *.h files with your own files. 
 * 
 * \subsection step6 Step 6: Transactional Environment.
 * Now your application use transactional environment, that guarantees the consistency between object transactions.  
 * 
 * \subsection step7 Step 7: Run the application.
 * Go to the directory where the executable was created, and used the following line in the terminal to run the application :
 * ./EXECUTABLE_NAME
 * 
 */

#ifndef TM_H
#define TM_H

#include <thread>
#include <unistd.h>//used for pid_t
#include <mutex>
#include <unordered_map>
#include <utility>
#include <map>
#include "TX.h"

class TM {
private:
    /*
     * TM constructor, prevent from multiple instantiation
     */
    TM() = default; 
    /*
     * TM de-constructor, prevent from deletion
     */
    ~TM() = default;
    /*!
     * \brief TM copy constructor, prevent from copying the Transaction Manager
     */
    TM(const TM&) = delete; 
    /*!
     * \brief TM copy operator, prevent from copying the Transaction Manager
     */
    TM& operator=(const TM&) = delete; 
    /*
     * txMap std::map, store all transactional objects created with Transaction Manager
     */
    std::map<std::thread::id, std::shared_ptr<TX>>txMap;
    /*
     * STATIC GLOBAL MAP Collection to store all process associated keys to find when deleting transactions 
     */
    static std::map<pid_t, std::map< std::thread::id, int >> process_map_collection;
    /*
     * get_thread_Map returning and map to insert to the process_map_collection as an inner value
     */
    std::map< std::thread::id, int > get_thread_Map();
    /*
     * registerTX void, register transaction into txMap
     */
    void registerTX(); 
    /*
     * register_Lock std::mutex, used in the registerTX function
     */
    std::mutex register_Lock;
    /*
     * register_Lock std::mutex, used in the _get_tx function
     */
    std::mutex get_Lock;
    /*
     * _tm_id pid_t, process id determine the actual process between process in the shared OSTM library
     */
    static pid_t _tm_id;

public:
    /**
     * Scott Meyer's Singleton creation, thread safe Transaction Manager instance creation. 
     */
    static TM& Instance();
    /**
     * _get_tx std::shared_ptr<TX>, returning a shared pointer transaction object
     */
    std::shared_ptr<TX>const _get_tx(); 
    /**
     * _TX_EXIT void function, the thread (TX object) calls the ostm_exit function from the transaction, 
     * and clear all elements from the shared global collection associated with the main process
     */
    void _TX_EXIT();
    /**
     * ONLY FOR TESTING!  print_all void function, prints all object in the txMap
     */
    void print_all();
};


#endif // TM_H