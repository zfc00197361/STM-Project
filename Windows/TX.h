/* 
 * File:   TX.h
 * Author: Zoltan Fuzesi
 * 
 * Created on December 18, 2017, 2:09 PM
 * Transaction class fields and methods declarations
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
    /*!
     * \brief Constructor
     */
    TX(std::thread::id id);
    /*!
     * \brief De-constructor
     */
    ~TX();
    /*!
     * \brief Default copy constructor
     */
    TX(const TX& orig);
    /*!
     * \brief Delete all map entries associated with the main process
     */
    void ostm_exit();
    
    /*!
     * \brief Register OSTM pointer into STM library 
     */
    void _register(std::shared_ptr<OSTM>  object);
    /*!
     * Register OSTM pointer into STM library 
     */
    std::shared_ptr<OSTM>  load(std::shared_ptr<OSTM>  object);
    /*!
     * \brief Store transactional changes
     */
    void store(std::shared_ptr<OSTM>  object);
    /*!
     * \brief Commit transactional changes
     */
    bool commit();
    /*!
     * \brief Add TX nesting level by one
     */
    void _increase_tx_nesting();
    /*!
     * \brief Remove TX nesting level by one
     */
    void _decrease_tx_nesting();
    /*!
     * Only TM Transaction Manager can create instance of TX Transaction
     */
    friend class TM;
    /*
     * \brief ONLY FOR TESTING!!! returning the number of rollback happened during transactions
     */
    int getTest_counter();
    /*!
     * \param test_counter int ONLY FOR TESTING!!!
     */
    static int test_counter;
    /*
     * TESTING ONLY
     */
    void _print_all_tx() ;


private:
    /*!
     * \brief MAP Collection to store OSTM* parent based pointers to make invisible changes during isolated transaction
     * \param working_Map_collection std::map
     */
    std::map< int, std::shared_ptr<OSTM>  > working_Map_collection;
    /*!
     * \brief Returning the transaction number
     * \param  transaction_Number std::thread::id
     *  NOT USED YET
     */
    std::thread::id transaction_Number;
    /*!
     * \param _tx_nesting_level int
     */
    int _tx_nesting_level;
    
    /*!
     * \brief STATIC GLOBAL MAP Collection to store OSTM* parent based pointers to control/lock and compare objects version number within transactions
     * \param main_Process_Map_collection std::map
     */
    static std::map<int, std::shared_ptr<OSTM>  >main_Process_Map_collection;
    /*!
     * \brief STATIC GLOBAL MAP Collection to store all process associated keys to find when deleting transactions 
     * \param process_map_collection std::map
     */
    static std::map<pid_t, std::map< int, int >> process_map_collection;
    /*!
     * \brief get_thread_Map returning and map to insert to the process_map_collection as an inner value
     */
    std::map< int , int > get_thread_Map();
    /*!
     * \param register_Lock std::mutex to control shared access on MAIN MAP
     */
    static std::mutex register_Lock;
    /*!
     * \brief _get_tx_number returning the transaction uniqe identifier
     */
    const std::thread::id _get_tx_number() const;
   
    /*!
     * Release the locks in objects with transaction associated collection  
     */
    void _release_object_lock();
    /*!
     * \brief Clean up all associated values by the thread delete from working_Map_collection, it is an automated function
     */
    void th_exit();
    
    

};
#endif // _TX_H_
