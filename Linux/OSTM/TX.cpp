/* 
 * File:   TX.cpp
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

#include "TX.h"
#include <iostream>
/*
  @19 main_Process_Map_collection, register static Global class level map to store all transactional objects/pointers
 */
std::map<int, std::shared_ptr<OSTM> >TX::main_Process_Map_collection;
/*
  @23 process_map_collection, register static Global class level map to store all transaction number associated with the main process
 */
std::map<pid_t, std::map< int, int >> TX::process_map_collection;
/*
  @27 egister_Lock, register static class level shared std:mutex to protect shared map during transaction registration
 */
std::mutex TX::register_Lock;
/*
  @31 test_counter, register class level Integer variable to store the umber of rollback happens, for testing purposes
 */
int TX::test_counter = 0;
/*!
 * \brief @36 Custom Constructor
 * \param id std::thread::id, represent the transaction number to the Transaction Manager
 */
TX::TX(std::thread::id id) {
    /* @38 Integer field <transaction_Number> indicates the transaction number to the Transaction manager */
    this->transaction_Number = id;
    /* @40 Integer field <_tx_nesting_level> indicates the nesting level to the transaction itself */
    this->_tx_nesting_level = 0;
}
 /*!
  * \brief @45 De-constructor
  */
TX::~TX() {
    /* Destroy the object. */
}
/*!
 * \brief @52 th_exit void, delete all std::shared_ptr<OSTM> elements from  working_Map_collection, that store pointers to working objects
 * \param working_Map_collection std::map, store std::shared_ptr<OSTM> transaction pointers
 */
void TX::th_exit() {
    /* @54 If bigger than ZERO, means active nested transactions running in background, do not delete anything yet */
    if (this->_tx_nesting_level > 0) {
        /* Active nested transactions running in background, do not delete anything yet */
    } else {
        /* Remove all elements map entries from transaction and clear the map */
        working_Map_collection.clear();
    }
}

/*!
 * \brief @68 ostm_exit void, clear all elements from the shared global collections associated with the main process
 * \param main_Process_Map_collection std::map, store all std::shared_ptr<OSTM> from all transaction shared between multiple processes
 * \param process_map_collection std::map, store all unique id from all transaction within main process
 * DO NOT CALL THIS METHOD EXPLICITLY!!!!!! WILL DELETE ALL PROCESS  ASSOCIATED ELEMENTS!!!!
 */
void TX::ostm_exit() {
    /* @70 Declare Iterator main_Process_Map_collection_Iterator */
    std::map<int, std::shared_ptr<OSTM>>::iterator main_Process_Map_collection_Iterator;
    /* @72 getppid() return the actual main process thread id, I used it to associate the Transactionas with the main processes */
    pid_t ppid = getppid();
    /* @74 process_map_collection try to find the main process by it's ppid if registred in the library */
    std::map<pid_t, std::map< int, int >>::iterator process_map_collection_Iterator = TX::process_map_collection.find(ppid);
    /* @76 Check if iterator NOT pointing to the end of the process_map_collection then remove all associated elements */
    if (process_map_collection_Iterator != TX::process_map_collection.end()) {
        /* @78 Iterate through the process_map_collection to find all transaction associated with main process */
        for (auto current = process_map_collection_Iterator->second.begin(); current != process_map_collection_Iterator->second.end(); ++current) {
            /* @80 Find the OSTM object in the Global shared map */
            main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find(current->first);
            /* @82 If object found then delete it*/
            if (main_Process_Map_collection_Iterator != TX::main_Process_Map_collection.end()){
                /* @84 Delete element from shared main_Process_Map_collection by object by the unique key, and the shaed_ptr will destroy automatically */
                TX::main_Process_Map_collection.erase(main_Process_Map_collection_Iterator->first);      
            }
        }
        /* @88 Delete main process from Process_map_collection */
        TX::process_map_collection.erase(process_map_collection_Iterator->first);
    }
}

/*!
 * \brief register void, receives an std::shared_ptr<OSTM> that point to the original memory space to protect from reca conditions
 * @param object std::shared_ptr<OSTM>, is an original shared pointer point to the object memory space
 */
void TX::_register(std::shared_ptr<OSTM> object) {
    /* @98 register_Lock(mutex) shared lock between all transaction. MUST USE SHARED LOCK TO PROTECT SHARED GLOBAL MAP/COLLECTION */
    std::lock_guard<std::mutex> guard(TX::register_Lock);
    /* @100 RUNTIME ERROR. Check for null pointer ! Null pointer can cause segmentation fault!!! */
    if(object == nullptr){
        throw std::runtime_error(std::string("[RUNTIME ERROR : NULL POINTER IN REGISTER FUNCTION]") );
    }
    /* @104 getppid() return the actual main process thread id, I used it to associate the Transactionas with the main processes */
    pid_t ppid = getppid();
    /* @106 Declare and initialize Iterator for process_map_collection, find main process*/
    std::map<pid_t, std::map< int, int >>::iterator process_map_collection_Iterator = TX::process_map_collection.find(ppid);
    /* @108 If iterator cannot find main process, then register*/
    if (process_map_collection_Iterator == TX::process_map_collection.end()) {
        /* @110 Create new empty map */
        std::map< int, int >map =  get_thread_Map();
        /* @112 Register main process/application to the global map */
        TX::process_map_collection.insert({ppid, map});
        /* @114 Get the map if registered first time */
        process_map_collection_Iterator = TX::process_map_collection.find(ppid);
    }
    /* @117 Declare and initialize Iterator for main_Process_Map_collection, find by original object */
    std::map<int, std::shared_ptr<OSTM>>::iterator main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find(object->Get_Unique_ID());
    /* @119 If object cannot find, then register */
    if (main_Process_Map_collection_Iterator == TX::main_Process_Map_collection.end()) {
        /* '121 Insert the origin object to the GLOBAL MAP shared between transactions */
        TX::main_Process_Map_collection.insert({object->Get_Unique_ID(), object});
        /* @123 Insert object ID to the GLOBAL MAP as a helper to clean up at end of main process, Second value (1) not specified yet */
        process_map_collection_Iterator->second.insert({object->Get_Unique_ID(), 1});
    } 
    /* @126 Declare and initialize Iterator for working_Map_collection, find copy of the original object */
    std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.find(object->Get_Unique_ID());
    /* @128 If copy of the object not found, then register */
    if (working_Map_collection_Object_Shared_Pointer_Iterator == working_Map_collection.end()) {
        /* @130 Register transaction own copy of the original object */
        working_Map_collection.insert({object->Get_Unique_ID(), object->getBaseCopy(object)});
    }
}
/*!
 * \brief @137 load std::shared_ptr<OSTM>, returning an OSTM type shared pointer, that is copy of the original pointer stored in the working map, to work with during transaction life time
 * \param  object std::shared_ptr<OSTM>, used as a reference to find transaction copy object by the object unique ID
 */
std::shared_ptr<OSTM> TX::load(std::shared_ptr<OSTM> object) {
    /* @139 Declare and initialize Iterator for working_Map_collection */
    std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator;
    /* @141 RUNTIME ERROR. Check for null pointer ! Null pointer can cause segmentation fault!!! */
    if(object == nullptr){
        throw std::runtime_error(std::string("[RUNTIME ERROR : NULL POINTER IN LOAD FUNCTION]") );
    }
    /* @145 Find copy object in working_Map_collection by the object unique ID*/
    working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.find(object->Get_Unique_ID());
    /* @147 If object found, then return it */
    if (working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end()) {
        /* @149 Returning a copy of the working copy object */
        return working_Map_collection_Object_Shared_Pointer_Iterator->second->getBaseCopy(working_Map_collection_Object_Shared_Pointer_Iterator->second);
    /* @151 If no object found, throw runtime error */  
    } else { throw std::runtime_error(std::string("[RUNTIME ERROR : NO OBJECT FOUND LOAD FUNCTION]") );}
}
/*!
 * \brief @157 store void, receive an OSTM type shared pointer object to store the changes with the transaction copy object
 * \param  object std::shared_ptr<OSTM>, receiving a changed shared pointer, that was returned from the load function
 */
void TX::store(std::shared_ptr<OSTM> object) {
    /* @159 RUNTIME ERROR. Check for null pointer ! Null pointer can cause segmentation fault!!! */
    if(object == nullptr){
        throw std::runtime_error(std::string("[RUNTIME ERROR : NULL POINTER IN STORE FUNCTION]") );
    }
    /* @163 Declare and initialize Iterator for working_Map_collection */
    std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator;
    /* @165 Find copy object in working_Map_collection by the object unique ID*/
    working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.find(object->Get_Unique_ID());
    /* @167 If object found, then replace it */
    if (working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end()) {
        /* @169 Replace copy object in working_Map_collection associated with the unique ID key*/
        working_Map_collection_Object_Shared_Pointer_Iterator->second = object;
    /* @171 If error happes during store procees throw runtime error */  
    } else { throw std::runtime_error(std::string("[RUNTIME ERROR : NO OBJECT FOUND STORE FUNCTION, CANNOT STORE OBJECT]") );}
}
/*!
 * \brief @176 commit function, returns boolean value TRUE/FALSE depends on the action taken within the function. if commit happens 
 * return TRUE, otherwise return FALSE, indicate the transaction muist restart.
 */
bool TX::commit() {
    /* @179 Declare can_Commit boolean variable */
    bool can_Commit = true;
    /* @182 Dealing with nested transactions first. if nesting level bigger than ZERO do not commit yet */
    if (this->_tx_nesting_level > 0) {
        /* @183 Decrease nesting level @see _decrease_tx_nesting() */
        _decrease_tx_nesting();
        return true;
    } 
    /* @187 Declare and initialize Iterator for working_Map_collection */
    std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator;
    /* @189 Declare and initialize Iterator for main_Process_Map_collectio */
    std::map<int, std::shared_ptr<OSTM>>::iterator main_Process_Map_collection_Iterator;
    /* @191 Iterate through the working_Map_collection, for all associated copy objetcs */
    for (working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.begin(); working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end(); working_Map_collection_Object_Shared_Pointer_Iterator++) {
            /* @193 Find the Original object in the Shared global colection by the copy object unique ID */
            main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find(working_Map_collection_Object_Shared_Pointer_Iterator->second->Get_Unique_ID());
            /* @195 RUNTIME ERROR. If no object found ! Null pointer can cause segmentation fault!!! */
            if(main_Process_Map_collection_Iterator == TX::main_Process_Map_collection.end())
            {
                throw std::runtime_error(std::string("[RUNTIME ERROR : CAN'T FIND OBJECT COMMIT FUNCTION]"));
            }

        /* @200 Busy waiting WHILE try_lock function return false, If the object locked by another transaction, then waith until it's get unlocked, then lock it */
        while(!(main_Process_Map_collection_Iterator->second)->try_lock());
        /* @203 Compare the original global object version number with the working object version number. If the version number not same, then it cannot coomit*/
        if (main_Process_Map_collection_Iterator->second->Get_Version() > working_Map_collection_Object_Shared_Pointer_Iterator->second->Get_Version()) {
            /* @2005 Set object boolean value to FALSE, cannot commit */
            working_Map_collection_Object_Shared_Pointer_Iterator->second->Set_Can_Commit(false);
            /* @207 Set canCommit false Indicate rollback must happen */
            can_Commit = false;
            break;
        } else {
            /* @210 If version number are has same value set object boolean value to TRUE*/ 
            working_Map_collection_Object_Shared_Pointer_Iterator->second->Set_Can_Commit(true);
        }
    }
    /* @214 IF can_Commit boolean value setted for FALSE then rollback all copy object in the transaction to the Global object values*/
    if (!can_Commit) {
        /* @217 iterate through all transaction copy objects one by one */
        for (working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.begin(); working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end(); working_Map_collection_Object_Shared_Pointer_Iterator++) {
            /* @219 Find the Global shared object by the transaction copy object unique ID */
            main_Process_Map_collection_Iterator  = TX::main_Process_Map_collection.find(working_Map_collection_Object_Shared_Pointer_Iterator->second->Get_Unique_ID());
            /* @221 Copy all Global shared original objects changed values by another transaction to the transaction copy objetcs */
            (working_Map_collection_Object_Shared_Pointer_Iterator->second)->copy(working_Map_collection_Object_Shared_Pointer_Iterator->second, main_Process_Map_collection_Iterator->second);
        }
        /* @224 When the transaction finish to change copying all values from original objects to local copy, then release all Global shared objects. @see _release_object_lock() */
        _release_object_lock();
        /* @226 Return FALSE to indicate the transaction must restart !*/
        return false;
    } else {
        /* @229 Iterate through working_map_collection. If no conflict detected in early stage in the transaction, then commit all the local changes to shared Global objects */
        for (working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.begin(); working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end(); working_Map_collection_Object_Shared_Pointer_Iterator++) {
                /* @231 Find the Global shared object by the transaction copy object unique ID */
                main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find((working_Map_collection_Object_Shared_Pointer_Iterator->second)->Get_Unique_ID());
                /* @233 If Global shared object found then commit changes */
                if (main_Process_Map_collection_Iterator != TX::main_Process_Map_collection.end()) {
                    /* @235 Copy over local transaction object values to original Global object*/
                    (main_Process_Map_collection_Iterator->second)->copy(main_Process_Map_collection_Iterator->second, working_Map_collection_Object_Shared_Pointer_Iterator->second);
                    /* @237 Increase the version number in the original pointer*/
                    main_Process_Map_collection_Iterator->second->increase_VersionNumber();
                /* @195 RUNTIME ERROR. If no object found ! Null pointer can cause segmentation fault!!! */
                } else { throw std::runtime_error(std::string("[RUNTIME ERROR : CAN'T FIND OBJECT COMMIT FUNCTION]")); }
        }
        /* @242 When the transaction finish with commit all changes, then release all Global shared objects. @see _release_object_lock() */
        _release_object_lock();
        /* @244 Transaction object clean up all associated values, clean memory. @see th_exit()*/
        this->th_exit();
        /* @246 Return TRUE, indicate the transaction has finished. */
        return true;
    }
}

/*!
 * \brief @253 _release_object_lock void function, is get called from commit function, with the purpose to release the locks on all the objects participating in the transaction
 */
void TX::_release_object_lock(){
    /* @255 Declare Iterator for working_Map_collection */
    std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator;
    /* @255 Declare Iterator for working_Map_collection */
    std::map<int, std::shared_ptr<OSTM>>::iterator main_Process_Map_collection_Iterator;
    for (working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.begin(); working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end(); working_Map_collection_Object_Shared_Pointer_Iterator++) {
            /* @260 Find Global shared original object by the transaction object unique ID*/
            main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find((working_Map_collection_Object_Shared_Pointer_Iterator->second)->Get_Unique_ID());
            /* @262 If object found, then release lock*/
            if (main_Process_Map_collection_Iterator != TX::main_Process_Map_collection.end()) {
                /* @264 Release object lock */
                (main_Process_Map_collection_Iterator)->second->unlock_Mutex();
            } 
        }
}

/*!
 * \brief @272 _increase_tx_nesting increase the value stored in _tx_nesting_level by one, indicate that the transaction was nested
 */
void TX::_increase_tx_nesting() {
    /* @274 Increase transaction nesting level */
    this->_tx_nesting_level += 1;
}
/*!
 * \brief @279 _decrease_tx_nesting decrease the value stored in _tx_nesting_level by one, when outer transactions commit
 */
void TX::_decrease_tx_nesting() {
    /* @281 Decrease transaction nesting level */
    this->_tx_nesting_level -= 1;
;
}
/*!
 * \brief @287 getTest_counter TESTING ONLY!!! returning the value of the test_counter stored, representing the number of rollbacks
 */
int TX::getTest_counter() {
    /* @289 return class level value hold by test_counter variable */
    return TX::test_counter;
}
/*!
 * \brief @294 _get_tx_number, returning the thread id that has assigned the given transaction
 */
const std::thread::id TX::_get_tx_number() const {
    /* @296 Return the transaction nuber */
    return transaction_Number;
}
/*!
 * \brief  @301 get_thread_Map, returning  a map to store all unique ID from all objects from all transactions within the main process
 */
std::map< int, int > TX::get_thread_Map() {
    /* @303 initialize empty map hold int key and values*/
    std::map< int, int > thread_Map;
    /* @305 Return the map*/
    return thread_Map;
}

/*!
 * @311 _print_all_tx, only for testing! Prints all transaction associated with the main procees.!
 */
void TX::_print_all_tx() {
    /* @313 initialise Iterator */
    std::map< int, std::shared_ptr<OSTM> >::iterator it;
    /* @315 getppid() return the actual main process thread id, I used it to associate the Transactionas with the main processes */
    pid_t ppid = getppid();
    /* '317 initialize and assign Iterator to process_map_collection, by the main process id (ppid) */
    std::map<pid_t, std::map< int, int >>::iterator process_map_collection_Iterator = TX::process_map_collection.find(ppid);
    /* @319 If there is an entry associated with the process then print out all transactions. */
    if (process_map_collection_Iterator != TX::process_map_collection.end()) {
        /* @321 Iterate through process_map_collection*/
        for (auto current = process_map_collection_Iterator->second.begin(); current != process_map_collection_Iterator->second.end(); ++current) {
            /* @323 Assign value to iterator */
            it = working_Map_collection.find(current->first);
            /* @325 If value found, then print it */
            if(it != working_Map_collection.end()){
                /* @327 print out the transaction number */
                std::cout << "[Unique number ] : " <<it->second->Get_Unique_ID() << std::endl;
            } 
        }
    }
}