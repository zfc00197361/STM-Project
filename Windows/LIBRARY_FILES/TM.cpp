/*
* File:   TM.cpp
* Author: Zoltan Fuzesi
*
* Created on December 18, 2017, 2:09 PM
* Transaction Manager class methods implementation
*/
#include "TM.h"
#include <thread>
//#include <unistd.h>
#include <process.h> 
#include <sys/types.h>
#include <iostream>

/*!
* \param _tm_id pid_t, process id determine the actual process between process in the shared OSTM library
*/
int TM::_tm_id;
/*!
* \param static Global std::map process_map_collection store all transactional objects/pointers
*/
std::map<int, std::map< std::thread::id, int >> TM::process_map_collection;
/*!
* \brief Instance TM, return the same singleton object to any process
* \param _instance TM, static class reference to the instance of the Transaction Manager class
* \param _instance ppid, assigning the process id whoever created the Singleton instance
*/
TM& TM::Instance() {
	static TM _instance;
	_instance._tm_id = _getpid();

	return _instance;
}

//TM Transaction managger checking the Process ID existence in the map
//If not in the map then register
/*!
* \brief registerTX void, register a new TX Transaction object into ythe txMap/Transaction Map to manage all the transactions within the shared library
* \param txMap std::map, collection to store all transaction created by the Transaction Manager
* \param register_Lock std::mutex, used by the lock_guard to protect shared map from race conditions
* \param guard std::lock_guard, locks the register_Lock mutex, unlock automatically when goes out of the scope
*/
void TM::registerTX()
{
	std::lock_guard<std::mutex> guard(register_Lock);
	int ppid = _getpid();
	std::map<int, std::map< std::thread::id, int >>::iterator process_map_collection_Iterator = TM::process_map_collection.find(ppid);
	if (process_map_collection_Iterator == TM::process_map_collection.end()) {
		/*
		* Register main process/application to the global map
		*/
		std::map< std::thread::id, int >map = get_thread_Map();
		TM::process_map_collection.insert({ ppid, map });

	}
	std::map<std::thread::id, std::shared_ptr < TX>>::iterator it = txMap.find(std::this_thread::get_id());
	if (it == txMap.end()) {
		std::shared_ptr<TX> _transaction_object(new TX(std::this_thread::get_id()));
		txMap.insert({ std::this_thread::get_id(), _transaction_object });
		/*
		* Get the map if registered first time
		*/
		process_map_collection_Iterator = TM::process_map_collection.find(ppid);
		/*
		* Insert to the GLOBAL MAP as a helper to clean up at end of main process
		*/
		process_map_collection_Iterator->second.insert({ std::this_thread::get_id(), 1 });

	}

}

/*!
* \brief _get_tx std::shared_ptr<TX>, return a shared_ptr with the Transaction object, if TX not exists then create one, else increasing the nesting level
* \get_Lock std::mutex, protect shared collection from critical section
* \param guard std::lock_guard, locks the register_Lock mutex, unlock automatically when goes out of the scope
*/
std::shared_ptr<TX>const TM::_get_tx()
{
	std::lock_guard<std::mutex> guard(get_Lock);

	std::map<std::thread::id, std::shared_ptr<TX>>::iterator it = txMap.find(std::this_thread::get_id());
	if (it == txMap.end())
	{
		registerTX();
		it = txMap.find(std::this_thread::get_id());

	}
	else {
		it->second->_increase_tx_nesting();
	}
	//it = txMap.find(std::this_thread::get_id());


	return it->second;

}
/*!
* \brief _TX_EXIT void, the thread calls the ostm_exit function in the transaction, and clear all elements from the shared global collection associated with the main process
* \params tx TX, local object to function in transaction
*/
void TM::_TX_EXIT() {
	TX tx(std::this_thread::get_id());
	int ppid = _getpid();
	std::map<int, std::map< std::thread::id, int >>::iterator process_map_collection_Iterator = TM::process_map_collection.find(ppid);
	if (process_map_collection_Iterator != TM::process_map_collection.end()) {

		for (auto current = process_map_collection_Iterator->second.begin(); current != process_map_collection_Iterator->second.end(); ++current) {
			/*
			* Delete all transaction associated with the actual main process
			*/
			txMap.erase(current->first);
		}
		TM::process_map_collection.erase(ppid);

	}
	tx.ostm_exit();
}
/*!
* \brief ONLY FOR TESTING print_all void, print out all object key from txMAP collection
*/
void TM::print_all() {
	get_Lock.lock();
	for (auto current = txMap.begin(); current != txMap.end(); ++current) {
		std::cout << "KEY : " << current->first << std::endl;
	}
	get_Lock.unlock();
}

/*!
* \brief get_thread_Map std::map, returning  a map to store all unique ID from all objects from all transactions within the main process
* \param thread_Map std::map< int, int >,
*/
std::map< std::thread::id, int > TM::get_thread_Map() {
	std::map< std::thread::id, int > thread_Map;
	return thread_Map;
}