/* 
 * File:   TM.h
 * Author: Zoltan Fuzesi
 * 
 * Created on December 18, 2017, 2:09 PM
 * Transaction Manager class fields and methods declarations
 */
/*! \mainpage OSTM C++ Software Transactional Memory
 *
 * \section OSTM Object Based Software Transactional Memory.
 *      
 *
 * OSTM is a polymorphic solution to store and manage shared memory spaces within c++ programming context.<br>
 * You can store and managed any kind of object in transactional environment as a shared and protected memory space.
 *
 * \subsection install_sec Brief. Download the zip file from the provided link in the web-site, that contains the libostm.so, TM.h, TX.h, OSTM.h files.
 * Unzip the archive file to the desired destination possibly where in you program is stored. 
 *
 * \subsection step1 Step 1: Download the archive file.
 * 
 * \subsection step2 Step 2: Unzip in the target destination.
 * 
 * \subsection step3 Step 3: Copy the shared library (libostm.so) to the operating system folder where the other shared library are stored.
 * It will be different destination folder on different platforms. (Linux, Windows, Mac OS) <a href="http://serversite.info/ostm/#tutorial" target="_blank">More Information</a> 
 * 
 * \subsection step4 Step 4: Achieve the required class hierarchy between the OSTM library and your own class structure.
 * Details and instruction of class hierarchy requirements can be found on the web-site. www.serversite.info/ostm
 * 
 * \subsection step5 Step 5: Create an executable file as you linking together the TM.h, TX.h, OSTM.h files with your own files. 
 * 
 * \subsection step6 Step 6: Now your application use transactional environment, that guarantees the consistency between object transactions.  
 * 
 * \subsection step7 Step 7: Run the application.
 * 
 * Abbreviation for bank names used in the test cases:<br>
 * BOA  - Bank of America<br>
 * ULSTER - Ulster Bank<br>
 * UNBL - United National Bank Limited<br>
 * SWBPLC - Scottish Windows Bank PLC<br>
 * AIB - Allied Irish Bank<br>
 * BOI - Bank of Ireland<br>
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
    /*!
     * \brief TM constructor, prevent from multiple instantiation
     */
    TM() = default; 
    /*!
     * \brief TM de-constructor, prevent from deletion
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
    /*!
     *\param txMap std::map, store all transactional objects created with Transaction Manager
     */
    std::map<std::thread::id, std::shared_ptr<TX>>txMap;
    /*!
     * \brief STATIC GLOBAL MAP Collection to store all process associated keys to find when deleting transactions 
     * \param process_map_collection std::map
     */
    static std::map<pid_t, std::map< std::thread::id, int >> process_map_collection;
     /*!
     * \brief get_thread_Map returning and map to insert to the process_map_collection as an inner value
     */
    std::map< std::thread::id, int > get_thread_Map();
    /*!
     * \brief registerTX void, register transaction into txMap
     */
    void registerTX(); 
    /*!
     * \param register_Lock std::mutex, used in the registerTX function
     */
    std::mutex register_Lock;
    /*!
     * \param register_Lock std::mutex, used in the _get_tx function
     */
    std::mutex get_Lock;
    /*!
     * \param _tm_id pid_t, process id determine the actual process between process in the shared OSTM library
     */
    static pid_t _tm_id;


public:

    /*!
     * \brief Scott Meyer's Singleton creation, what is thread safe
     */
    static TM& Instance();
    /*!
     * \brief _get_tx std::shared_ptr<TX>, returning a shared pointer with the transaction
     */
    std::shared_ptr<TX>const _get_tx(); 
    /*!
     * \brief _TX_EXIT void, the thread calls the ostm_exit function in the transaction, and clear all elements from the shared global collection associated with the main process
     */
    void _TX_EXIT();
    /*!
     * ONLY FOR TESTING print_all void, prints all object in the txMap
     */
    void print_all();
    

};


#endif // TM_H