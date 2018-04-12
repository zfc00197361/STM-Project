/*
* File:   TX.cpp
* Author: Zoltan Fuzesi
*
* Created on December 18, 2017, 2:09 PM
* TX cpp file methods implementations
*/
#include "TX.h"
#include <iostream>
/*!
* \param static Global std::map main_Process_Map_collection store all transactional objects/pointers
*/
std::map<int, std::shared_ptr<OSTM> >TX::main_Process_Map_collection;
/*!
* \param static Global std::map process_map_collection store all transactional objects/pointers
*/
std::map<int, std::map< int, int >> TX::process_map_collection;
/*!
* \param static shared std:mutex register_Lock to protect writes into shared global collection
*/
std::mutex TX::register_Lock;

/*!
* \brief Constructor
* \param transaction_Number int, to store associated thread
* \param _tx_nesting_level int, to store and indicate nesting level of transactions within transaction
*/
TX::TX(std::thread::id id) {
	this->transaction_Number = id;
	this->_tx_nesting_level = 0;
}
/*!
* \brief De-constructor
*/
TX::~TX() {

}
/*!
* \brief Default copy constructor
*/
TX::TX(const TX& orig) {

}

/*!
* \brief th_exit void, delete all std::shared_ptr<OSTM> elements from  working_Map_collection, that store pointers to working objects
* \param working_Map_collection std::map, store std::shared_ptr<OSTM> transaction pointers
*/
void TX::th_exit() {

	if (this->_tx_nesting_level > 0) {
		/*
		* Active nested transactions running in background, do not delete anything yet
		*/
	}
	else {
		/*
		* Remove all elements map entries from transaction and clear the map
		*/
		working_Map_collection.clear();
	}
}

/*!
* \brief ostm_exit void, clear all elements from the shared global collections associated with the main process
* \param main_Process_Map_collection std::map, store all std::shared_ptr<OSTM> from all transaction shared between multiple processes
* \param process_map_collection std::map, store all unique id from all transaction within main process
* DO NOT CALL THIS METHOD EXPLICITLY!!!!!! WILL DELETE ALL PROCESS  ASSOCIATED ELEMENTS!!!!
*/
void TX::ostm_exit() {
	std::map<int, std::shared_ptr<OSTM>>::iterator main_Process_Map_collection_Iterator;

	int ppid = _getpid();
	std::map<int, std::map< int, int >>::iterator process_map_collection_Iterator = TX::process_map_collection.find(ppid);
	if (process_map_collection_Iterator != TX::process_map_collection.end()) {

		for (auto current = process_map_collection_Iterator->second.begin(); current != process_map_collection_Iterator->second.end(); ++current) {
			main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find(current->first);

			if (main_Process_Map_collection_Iterator != TX::main_Process_Map_collection.end()) {
				/*
				* Delete element from shared main_Process_Map_collection by object unique key value, shared_ptr will destroy automatically
				*/
				TX::main_Process_Map_collection.erase(main_Process_Map_collection_Iterator->first);
			}
		}
		/*
		* Delete from Process_map_collection, Main process exits delete association with library
		*/
		TX::process_map_collection.erase(process_map_collection_Iterator->first);
	}
}

/*!
* \brief register void, receives an std::shared_ptr<OSTM> that point to the original memory space to protect from reca conditions
* \param working_Map_collection std::map, store all the std::shared_ptr<OSTM> pointer in the transaction
* \param main_Process_Map_collection std::map, store all std::shared_ptr<OSTM> from all transaction, used to lock and compare the objects
* \param process_map_collection std::map, store all std::shared_ptr<OSTM> unique ID from all transaction, used to delete all pointers used by the main process, from all transaction before the program exit.
* \param std::lock_guard use register_Lock(mutex) shared lock between all transaction
* \param ppid int, store main process number
*/
void TX::_register(std::shared_ptr<OSTM> object) {
	/*
	* MUST USE SHARED LOCK TO PROTECT SHARED GLOBAL MAP/COLLECTION
	*/
	std::lock_guard<std::mutex> guard(TX::register_Lock);

	/*
	* Check for null pointer !
	* Null pointer can cause segmentation fault!!!
	*/
	if (object == nullptr) {
		throw std::runtime_error(std::string("[RUNTIME ERROR : NULL POINTER IN REGISTER FUNCTION]"));
	}

	int ppid = _getpid();
	std::map<int, std::map< int, int >>::iterator process_map_collection_Iterator = TX::process_map_collection.find(ppid);
	if (process_map_collection_Iterator == TX::process_map_collection.end()) {
		/*
		* Register main process/application to the global map
		*/
		std::map< int, int >map = get_thread_Map();
		TX::process_map_collection.insert({ ppid, map });
		/*
		* Get the map if registered first time
		*/
		process_map_collection_Iterator = TX::process_map_collection.find(ppid);
	}
	std::map<int, std::shared_ptr<OSTM>>::iterator main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find(object->Get_Unique_ID());
	if (main_Process_Map_collection_Iterator == TX::main_Process_Map_collection.end()) {
		/*
		* Insert to the GLOBAL MAP
		*/
		TX::main_Process_Map_collection.insert({ object->Get_Unique_ID(), object });
		/*
		* Insert to the GLOBAL MAP as a helper to clean up at end of main process
		*/
		process_map_collection_Iterator->second.insert({ object->Get_Unique_ID(), 1 });
	}


	std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.find(object->Get_Unique_ID());
	if (working_Map_collection_Object_Shared_Pointer_Iterator == working_Map_collection.end()) {

		working_Map_collection.insert({ object->Get_Unique_ID(), object->getBaseCopy(object) });
	}

}
/*!
* \brief load std::shared_ptr<OSTM>, returning an std::shared_ptr<OSTM> copy of the original pointer, to work with during transaction life time
* \param  working_Map_collection std::map, store all the std::shared_ptr<OSTM> pointer in the transaction
*/
std::shared_ptr<OSTM> TX::load(std::shared_ptr<OSTM> object) {

	std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator;
	/*
	* Check for null pointer !
	* Null pointer can cause segmentation fault!!!
	*/
	if (object == nullptr) {
		throw std::runtime_error(std::string("[RUNTIME ERROR : NULL POINTER IN LOAD FUNCTION]"));
	}

	working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.find(object->Get_Unique_ID());

	if (working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end()) {

		return working_Map_collection_Object_Shared_Pointer_Iterator->second->getBaseCopy(working_Map_collection_Object_Shared_Pointer_Iterator->second);

	}
	else { throw std::runtime_error(std::string("[RUNTIME ERROR : NO OBJECT FOUND LOAD FUNCTION]")); }
}
/*!
* \brief store void, receive an std::shared_ptr<OSTM> object to store the changes within the transaction, depends the user action
* \param  working_Map_collection std::map, store all the std::shared_ptr<OSTM> pointer in the transaction
*/
void TX::store(std::shared_ptr<OSTM> object) {
	/*
	* Check for null pointer !
	* Null pointer can cause segmentation fault!!!
	*/
	if (object == nullptr) {
		throw std::runtime_error(std::string("[RUNTIME ERROR : NULL POINTER IN STORE FUNCTION]"));
	}

	std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator;

	working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.find(object->Get_Unique_ID());
	if (working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end()) {

		working_Map_collection_Object_Shared_Pointer_Iterator->second = object;

	}
	else { std::cout << "[ERROR STORE]" << std::endl; }
}
/*!
* \brief commit bool, returns boolean value TRUE/FALSE depends on the action taken within the function
* \param  working_Map_collection std::map, store all the std::shared_ptr<OSTM> pointer in the transaction
* \param main_Process_Map_collection std::map, store all std::shared_ptr<OSTM> from all transaction, used to lock and compare the objects
* \param can_Commit bool, helps to make decision that the transaction can commit or rollback
*/
bool TX::commit() {

	bool can_Commit = true;

	/*
	* Dealing with nested transactions first
	*/
	if (this->_tx_nesting_level > 0) {
		_decrease_tx_nesting();
		return true;
	}

	std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator;

	std::map<int, std::shared_ptr<OSTM>>::iterator main_Process_Map_collection_Iterator;
	for (working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.begin(); working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end(); working_Map_collection_Object_Shared_Pointer_Iterator++) {

		main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find(working_Map_collection_Object_Shared_Pointer_Iterator->second->Get_Unique_ID());
		/*
		* Throws runtime error if object can not find
		*/
		if (main_Process_Map_collection_Iterator == TX::main_Process_Map_collection.end())
		{
			throw std::runtime_error(std::string("[RUNTIME ERROR : CAN'T FIND OBJECT COMMIT FUNCTION]"));
		}

		/*
		* Busy wait WHILE object locked by other thread
		*/
		while (!(main_Process_Map_collection_Iterator->second)->is_Locked());
		if (main_Process_Map_collection_Iterator->second->Get_Version() > working_Map_collection_Object_Shared_Pointer_Iterator->second->Get_Version()) {

			working_Map_collection_Object_Shared_Pointer_Iterator->second->Set_Can_Commit(false);
			can_Commit = false;

		}
	}
	if (!can_Commit) {
		for (working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.begin(); working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end(); working_Map_collection_Object_Shared_Pointer_Iterator++) {

			main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find(working_Map_collection_Object_Shared_Pointer_Iterator->second->Get_Unique_ID());
			(working_Map_collection_Object_Shared_Pointer_Iterator->second)->copy(working_Map_collection_Object_Shared_Pointer_Iterator->second, main_Process_Map_collection_Iterator->second);

		}

		_release_object_lock();

		return false;
	}
	else {
		/*
		* Commit changes
		*/
		for (working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.begin(); working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end(); working_Map_collection_Object_Shared_Pointer_Iterator++) {

			main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find((working_Map_collection_Object_Shared_Pointer_Iterator->second)->Get_Unique_ID());
			if (main_Process_Map_collection_Iterator != TX::main_Process_Map_collection.end()) {

				(main_Process_Map_collection_Iterator->second)->copy(main_Process_Map_collection_Iterator->second, working_Map_collection_Object_Shared_Pointer_Iterator->second);
				main_Process_Map_collection_Iterator->second->increase_VersionNumber();


			}
			else {
				throw std::runtime_error(std::string("[RUNTIME ERROR : CAN'T FIND OBJECT COMMIT FUNCTION]"));

			}
		}


		_release_object_lock();
		this->th_exit();
		return true;
	}
}//Commit finish

 /*!
 * \brief _release_object_lock void, is get called from commit function, with the purpose to release the locks on all the objects participating in the transaction
 *  \param  working_Map_collection std::map, store all the std::shared_ptr<OSTM> pointer in the transaction
 *  \param main_Process_Map_collection std::map, store all std::shared_ptr<OSTM> from all transaction, used to release the lock on object
 */
void TX::_release_object_lock() {
	std::map< int, std::shared_ptr<OSTM> >::iterator working_Map_collection_Object_Shared_Pointer_Iterator;
	std::map<int, std::shared_ptr<OSTM>>::iterator main_Process_Map_collection_Iterator;
	for (working_Map_collection_Object_Shared_Pointer_Iterator = working_Map_collection.begin(); working_Map_collection_Object_Shared_Pointer_Iterator != working_Map_collection.end(); working_Map_collection_Object_Shared_Pointer_Iterator++) {

		main_Process_Map_collection_Iterator = TX::main_Process_Map_collection.find((working_Map_collection_Object_Shared_Pointer_Iterator->second)->Get_Unique_ID());
		if (main_Process_Map_collection_Iterator != TX::main_Process_Map_collection.end()) {
			/*
			* Release object lock
			*/
			(main_Process_Map_collection_Iterator)->second->unlock_Mutex();
		

		}

	}
}

/*!
* \brief _increase_tx_nesting increase the value stored in _tx_nesting_level by one, indicate that the transaction nested
* \param _tx_nesting_level int
*/
void TX::_increase_tx_nesting() {

	this->_tx_nesting_level += 1;
	// std::cout << "[this->_tx_nesting_level] = " << this->_tx_nesting_level << std::endl;
}
/*!
* \brief _decrease_tx_nesting decrease the value stored in _tx_nesting_level by one, when outer transactions commiting
* \param _tx_nesting_level int
*/
void TX::_decrease_tx_nesting() {
	// std::cout << "[this->_tx_nesting_level] = " << this->_tx_nesting_level << std::endl;
	this->_tx_nesting_level -= 1;
	;
}
/*!
* \brief _get_tx_number std::thread::id, returning the thread id that has assigned the given transaction
* \param transaction_Number int
*/
const std::thread::id TX::_get_tx_number() const {
	return transaction_Number;
}
/*!
* \brief get_thread_Map std::map, returning  a map to store all unique ID from all objects from all transactions within the main process
* \param thread_Map std::map< int, int >,
*/
std::map< int, int > TX::get_thread_Map() {
	std::map< int, int > thread_Map;
	return thread_Map;
}
