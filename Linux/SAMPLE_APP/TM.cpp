/* 
 * File:   TM.cpp
 * Author: Zoltan Fuzesi C00197361, 
 * IT Carlow, Software Engineering, 
 *
 * Supervisor : Joe Kehoe, 
 *
 * C++ Software Transactional Memory, 
 * 
 * Created on December 18, 2017, 2:09 PM
 * OSTM base class function declarations.
 */

#include "TM.h"
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>

/*
   @23 _tm_id pid_t, process id determine the actual process between process in the STM library
 */
pid_t TM::_tm_id;
/*
   @27 static Global std::map process_map_collection store all transactional objects/pointers
 */
std::map<pid_t, std::map< std::thread::id, int >> TM::process_map_collection;
/*!
 * \brief @31 Instance TM, Scott Meyer's Singleton creation, thread safe Transaction Manager instance creation.
 */
TM& TM::Instance() {
   /* @33 _instance TM, static class reference to the instance of the Transaction Manager class */
    static TM _instance;
    /* @35 _instance ppid, assigning the process id whoever created the Singleton instance */
    _instance._tm_id = getpid();
    /* @37 return Singleton instance */
    return _instance;
}

/*!
 * \brief @45 registerTX void function, register a new TX Transaction object into ythe txMap/Transaction 
 * Map to manage all the transactions within the shared library. TM Transaction managger checking the Process ID existence in the 
 * process map collection, If not in the map then register.
 */
void TM::registerTX()
{
  /* @49 guard std::lock_guard, locks the register_Lock mutex, unlock automatically when goes out of the scope register_Lock std::mutex, used by the lock_guard to protect shared map from race conditions */
    std::lock_guard<std::mutex> guard(register_Lock);
    /* @51 getppid() return the actual main process thread id, I used it to associate the Transactionas with the main processes */
    pid_t ppid = getppid();

    /* @53 process_map_collection try to find the main process by it's ppid if registred in the library */
    std::map<pid_t, std::map< std::thread::id, int >>::iterator process_map_collection_Iterator = TM::process_map_collection.find(ppid);
    /* @55 Check if iterator pointing to the end of the process map then register */
    if (process_map_collection_Iterator == TM::process_map_collection.end()) {
        /* @57 Require new map to insert to the process map as a value by the ppid key  */
        std::map< std::thread::id, int >map = get_thread_Map();
        /* @59 Register main process/application to the global map  */
        TM::process_map_collection.insert({ppid, map});

    }
    /* @63 txMap std::map, collection to store all transaction created by the Transaction Manager */
    std::map<std::thread::id, std::shared_ptr < TX>>::iterator it = txMap.find(std::this_thread::get_id());
    /* @65 Check if iterator pointing to the end of the txMap then insert */
    if (it == txMap.end()) {
        /* @67 Create a new Transaction Object as a shared pointer */
        std::shared_ptr<TX> _transaction_object(new TX(std::this_thread::get_id()));
        /* @69 txMap insert the new transaction into the txMap by the threadID key */
        txMap.insert({std::this_thread::get_id(), _transaction_object});
        /* @71 Get the map if the transaction registered first time */
        process_map_collection_Iterator = TM::process_map_collection.find(ppid);
        /* @73 Insert to the GLOBAL MAP as a helper to clean up at end of main process. The value 1 is not used yet */
        process_map_collection_Iterator->second.insert({std::this_thread::get_id(), 1});
    }
}

/*!
 * \brief @81 _get_tx std::shared_ptr<TX>, return an trtansaction Object as a shared_ptr, if TX not exists then create and register.#
 *  If the transaction Object exists then increasing the nesting level within the Transaction Object.
 */
std::shared_ptr<TX>const TM::_get_tx()
{
   
    /* @85 guard std::lock_guard, locks the get_Lock mutex, unlock automatically when goes out of the scope get_Lock std::mutex, used by the lock_guard to protect txMap from race conditions */
    std::lock_guard<std::mutex> guard(get_Lock);
    /* @87 txMap try to find the TX Transaction object by it's actual thread ID if registred in the txMap */
    std::map<std::thread::id, std::shared_ptr<TX>>::iterator it = txMap.find(std::this_thread::get_id());
    /* @89 Check if iterator pointing to the end of the txMap then insert */
    if(it == txMap.end())
    {
      /* @92 If cannot find then call the register function to register the thread with a transaction */
       registerTX();
       /* @94 If it's registered first time then we need to find it after registration */
       it = txMap.find(std::this_thread::get_id());
       
    } else {
        /* @98 If transaction already registered, it means the thread participating in nested transactions, and increase the nesting */
        it->second->_increase_tx_nesting();
    }
    /* @101 Returning back the transaction (TX) object to the thread */
    return it->second;

}
 /*!
  * \brief @108 _TX_EXIT void, when the thread calls the ostm_exit function in the transaction, and it will clear all elements 
  * from the shared global collection associated with the main process
  */
void TM::_TX_EXIT(){
    /*  @110 Transaction manger create a local Transaction Object to access the TX class function without nesting any transaction */
    TX tx(std::this_thread::get_id());
    /* @112 getppid() return the actual main process thread id, I used it to associate the Transactionas with the main processes */
    pid_t ppid = getppid();
    /* @114 process_map_collection try to find the main process by it's ppid if registred in the library */
    std::map<pid_t, std::map< std::thread::id, int >>::iterator process_map_collection_Iterator = TM::process_map_collection.find(ppid);
    /* @116 Check if iterator NOT pointing to the end of the process map then register */
    if (process_map_collection_Iterator != TM::process_map_collection.end()) {
        /* @118 Iterate through the process_map_collection to find all transaction associated with main process */
        for (auto current = process_map_collection_Iterator->second.begin(); current != process_map_collection_Iterator->second.end(); ++current) {
            /* @120 Delete all transaction associated with the actual main process */
            txMap.erase(current->first);
        }
        /* @123 When all transaction deleted, delete the main process from the Transacion Manager */
        TM::process_map_collection.erase(ppid);
    }
    /* @126 TX class delete all Global Object shared between the transaction. This function calls only when the main process exists to clear out memory */
    tx.ostm_exit();
}
/*!
 * \brief @132 ONLY FOR TESTING print_all void function , print out all object key from txMAP collection associated
 * with the main process.
 */
void TM::print_all(){
    /* @134 Locking the print function */
    get_Lock.lock();
    /* @136 Iterate through the txMap to print out the thread id's*/
    for (auto current = txMap.begin(); current != txMap.end(); ++current) {
        /* @138 Print key (thread number)*/
        std::cout << "KEY : " << current->first << std::endl;
    }
    /* @140 Unlocking the print function*/
    get_Lock.unlock();
}

/*!
 * \brief @148 get_thread_Map std::map, returning a map to store all unique ID from all objects from 
 * all transactions within the main processes
 */
std::map< std::thread::id, int > TM::get_thread_Map() {
    /*  @150 thread_Map std::map< int, int > create a map to store int key and int value */ 
    std::map< std::thread::id, int > thread_Map;
    /* @152 return the map */
    return thread_Map;
}