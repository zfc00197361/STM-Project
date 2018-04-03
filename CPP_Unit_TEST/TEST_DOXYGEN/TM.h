/* 
 * File:   TM.h
 * Author: Zoltan Fuzesi
 * 
 * Created on December 18, 2017, 2:09 PM
 * Transaction Manager class fields and methods declarations
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
    TM(const TM&); //Modified for testing (= delete) removed 
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
    //std::map< std::thread::id, int > get_thread_Map();
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
    /*
     * Added for testing
     */
    bool operator==(const TM &rhs) const {
        return &rhs == this;
    }
    //moved from private to public for testing purpose
    std::map< std::thread::id, int > get_thread_Map();
  
    
   
    

};


#endif // TM_H