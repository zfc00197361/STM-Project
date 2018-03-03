/* 
 * File:   OSTM.cpp
 * Author: Zoltan Fuzesi
 * 
 * Created on December 18, 2017, 2:09 PM
 * OSTM cpp file methods implementations
 */

#include "OSTM.h"

int OSTM::global_Unique_ID_Number = 0;

/*!
 * \brief Default constructor
 * \param version indicates the version number of the inherited child pointer
 * \param uniqueID is a unique identifier assigned to every object registered in OSTM library
 * \param canCommit NOT USED YET
 * \param abort_Transaction NOT USED YET
 */
OSTM::OSTM()
{
    this->version = ZERO;
    this->uniqueID = Get_global_Unique_ID_Number(); //++global_Unique_ID_Number;
    this->canCommit = true;
    this->abort_Transaction = false;
}


/*!
 * \brief Custom Constructor Used for copy object
 * \param version indicates the version number of the inherited child pointer
 * \param uniqueID is a unique identifier assigned to every object registered in OSTM library
 * \param canCommit NOT USED YET
 * \param abort_Transaction NOT USED YET
 */
OSTM::OSTM(int _version_number_, int _unique_id_)
{
   // std::cout << "OSTM COPY CONSTRUCTOR" << global_Unique_ID_Number << std::endl;
    this->uniqueID = _unique_id_;
    this->version = _version_number_;
    this->canCommit = true;
    this->abort_Transaction = false;
}

/*!
 * De-constructor
 */
OSTM::~OSTM() {
    //std::cout << "[OSTM DELETE]" << std::endl;
}
/*!
 * If global_Unique_ID_Number equals to 10000000 then reset back to ZERO, to make sure the value of 
 * global_Unique_ID_Number never exceed the MAX_INT value
 */

int OSTM::Get_global_Unique_ID_Number() {
    if(global_Unique_ID_Number > 10000000)
        global_Unique_ID_Number = 0;
    return ++global_Unique_ID_Number;
}

/*!
 * \brief setter for unique id
 * \param uniqueID int
 */
void OSTM::Set_Unique_ID(int uniqueID) {
    this->uniqueID = uniqueID;
}
/*!
 * \brief getter for unique id
 * \param uniqueID int
 */
int OSTM::Get_Unique_ID() const
{
    return uniqueID;
}
/*!
 * \brief setter for version number
 * \param version int
 */
void OSTM::Set_Version(int version)
{
    this->version = version;
}
/*!
 * \brief getter for version number
 * \param version int
 */
int OSTM::Get_Version() const
{
    return version;
}
/*!
 * \brief commit time increase version number to child object
 * \param version int
 */
void OSTM::increase_VersionNumber()
{
    this->version += 1;
}
/*!
 * \brief NOT USED YET
 * \param canCommit boolean
 */
void OSTM::Set_Can_Commit(bool canCommit) {
    this->canCommit = canCommit;
}
/*!
 * \brief NOT USED YET
 * \param canCommit boolean
 */
bool OSTM::Is_Can_Commit() const {
    return canCommit;
}
/*!
 * \brief NOT USED YET
 * \param abort_Transaction boolean
 */
void OSTM::Set_Abort_Transaction(bool abortTransaction) {
    this->abort_Transaction = abortTransaction;
}
/*!
 * \brief NOT USED YET
 * \param abort_Transaction boolean
 */
bool OSTM::Is_Abort_Transaction() const {
    return abort_Transaction;
}
/*!
 * \brief object unique lock, locks mutex
 * \param mutex std::mutex
 */
void OSTM::lock_Mutex() {
    this->mutex.lock();
}
/*!
 * \brief object unique lock, unlocks mutex
 * \param mutex std::mutex
 */
void OSTM::unlock_Mutex() {
    this->mutex.unlock();
}
/*!
 * \brief object unique lock, try locks mutex return boolean value depends on the lock state 
 * \param mutex std::mutex
 */
bool OSTM::is_Locked(){
    return this->mutex.try_lock();
}
