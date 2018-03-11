/* 
 * File:   TX.h
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

#ifndef TX_H
#define TX_H
#include <cstdlib>
#include <utility>
#include <map>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <memory>
#include <stdio.h>
#include <thread>
#include "OSTM.h"

class TM;

class TX {
public:
    /*
     * Custom Constructor
     */
    TX(std::thread::id id);
    /*
     * De-constructor
     */
    ~TX();
    /*
     * Default copy constructor
     */
    TX(const TX& orig);
    /*
     * Delete all map entries associated with the main process
     */
    void ostm_exit();
    /*
     *  Register OSTM pointer into STM library 
     */
    void _register(std::shared_ptr<OSTM>  object);
    /*
     * Load a copy of OSTM shared pointer to main process 
     */
    std::shared_ptr<OSTM>  load(std::shared_ptr<OSTM>  object);
    /*
     * Store transactional changes
     */
    void store(std::shared_ptr<OSTM>  object);
    /*
     * Commit transactional changes
     */
    bool commit();
    /*
     * Increase TX (Transaction) nesting level by one
     */
    void _increase_tx_nesting();
    /*
     * Decrease TX (transaction) nesting level by one
     */
    void _decrease_tx_nesting();
    /*
     * Only TM Transaction Manager can create instance of TX Transaction
     */
    friend class TM;
    /*
     * ONLY FOR TESTING!!! returning the number of rollback happened during transactions
     */
    int getTest_counter();
    /*
     * test_counter int ONLY FOR TESTING!!! store number of rollbacks
     */
    static int test_counter;
    /*
     * TESTING ONLY print all transactions
     */
    void _print_all_tx() ;


private:
    /**
     * working_Map_collection, Collection to store copy of OSTM parent based original Global shared pointers to make invisible changes during isolated transaction
     */
    std::map< int, std::shared_ptr<OSTM>  > working_Map_collection;
    /**
     * transaction_Number, Returning the transaction number what is a registered thread number associated with the transaction
     */
    std::thread::id transaction_Number;
    /**
     * _tx_nesting_level, store integer value represent the ttransaction nesting level
     */
    int _tx_nesting_level;
    /**
     * main_Process_Map_collection, STATIC GLOBAL MAP Collection to store OSTM parent based shared pointers to control/lock and compare objects version number within transactions
     */
    static std::map<int, std::shared_ptr<OSTM>  >main_Process_Map_collection;
    /**
     * process_map_collection, STATIC GLOBAL MAP Collection to store all process associated keys to find when deleting transactions 
     */
    static std::map<pid_t, std::map< int, int >> process_map_collection;
    /**
     * get_thread_Map, returning and map to insert to the process_map_collection as an inner value
     */
    std::map< int , int > get_thread_Map();
    /**
     * register_Lock, std::mutex to control shared access on MAIN MAP
     */
    static std::mutex register_Lock;
    /**
     * _get_tx_number, returning the transaction uniqe identifier
     */
    const std::thread::id _get_tx_number() const;
    /**
     * _release_object_lock, Release the locks on all Shared global objects used by the transaction  
     */
    void _release_object_lock();
    /**
     * Clean up all associated values by the thread delete from working_Map_collection, it is an automated function by the transactions
     */
    void th_exit();
    
};
#endif // _TX_H_