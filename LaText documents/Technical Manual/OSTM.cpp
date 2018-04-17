/* 
 * File:   OSTM.cpp
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

#include "OSTM.h"

int OSTM::global_Unique_ID_Number = 0;

/*!
 * \brief @21 Default constructor
 */
OSTM::OSTM()
{
    /* @24 Integer field <version> indicates the version number of the inherited child object */
    this->version = ZERO;
    /* @26 Integer field <uniqueID> is a unique identifier assigned to every object registered in OSTM library */
    this->uniqueID = Get_global_Unique_ID_Number();
    /* @28 Boolean value <canCommit> to determine the object can or cannot commit */
    this->canCommit = true;
    /* @30 Boolean field <abort_Transaction> to determine the object can or cannot commit */
    this->abort_Transaction = false;
}


/*!
 * \brief @39 Custom Constructor Used to copying objects
 * \param version_number  Integer value used to create a copy of the object with the actual version
 * \param unique_id Integer value used to create a copy of the object with the original unique ID
 */
OSTM::OSTM(int _version_number_, int _unique_id_)
{
    /* @42 Integer field <version> indicates the version number of the inherited child object */
    this->uniqueID = _unique_id_;
    /* @44 Integer field <uniqueID> is a unique identifier assigned to every object registered in OSTM library */
    this->version = _version_number_;
    /* @46 Boolean value <canCommit> to determine the object can or cannot commit */
    this->canCommit = true;
    /* @48 Boolean value <abort_Transaction> to determine the object can or cannot commit */
    this->abort_Transaction = false;
}

/*!
 * @54 Default De-constructor
 */
OSTM::~OSTM() {
    /* Destroy the object. */
}
/*!
 * \brief @61 Get_global_Unique_ID_Number function, If <global_Unique_ID_Number> equals to 10000000 then reset back to ZERO, to make sure the value of 
 * global_Unique_ID_Number never exceed the MAX_INT value
 */
int OSTM::Get_global_Unique_ID_Number() {
    /* @64 Checking the global_Unique_ID_Number */
    if(global_Unique_ID_Number > 10000000)
        /* @65 Reset global_Unique_ID_Number to ZERO*/
        global_Unique_ID_Number = 0;
    /* @67 return static global_Unique_ID_Number */
    return ++global_Unique_ID_Number;
}

/*!
 * \brief @75 Function <Set_Unique_ID> setter for uniqueID private field
 * \param uniqueID int Every object inherit from OSTM class will include a version number that is unique for every object.
 * The STM library used this value to find object within the transaction to make changes or comparism ith them.
 */
void OSTM::Set_Unique_ID(int uniqueID) {
    /* @77 set object uniqueID to parameter integer value */
    this->uniqueID = uniqueID;
}
/*!
 * \brief @82 Function <Get_Unique_ID> getter for uniqueID private field
 */
int OSTM::Get_Unique_ID() const
{
    /* @85 return Object uniqueID */
    return uniqueID;
}
/*!
 * \brief @92 Function <Set_Version> setter for version private filed
 * \param version integer The verion number ZERO by default when the object created. When a transaction make changes with the object, then the version number
 * will be increased, to indicate the changes on the object.
 */
void OSTM::Set_Version(int version)
{
    /* @95 set object version to parameter integer value */
    this->version = version;
}
/*!
 * \brief @100 Function <Get_Version> setter for version private filed
 */
int OSTM::Get_Version() const
{
    /* return object version number */
    return version;
}
/*!
 * \brief @108 Function <increase_VersionNumber> commit time increase the version number associated with the object
 */
void OSTM::increase_VersionNumber()
{
    /* @111 increase object version number */
    this->version += 1;
}
/*!
 * \brief @117 Function <Set_Can_Commit> setter for canCommit private filed
 * \param canCommit Boolean value to determine the object can or cannot commit
 */
void OSTM::Set_Can_Commit(bool canCommit) {
    /* @119 set canCommit object variable to parameter boolean value*/
    this->canCommit = canCommit;
}
/*!
 * \brief @124 Function <Is_Can_Commit> boolean function to determin the object can comit or need to roolback.
 */
bool OSTM::Is_Can_Commit() const {
    /* @126 return canCommit boolean value TRUE/FALSE */
    return canCommit;
}
/*!
 * \brief @132 Function <Set_Abort_Transaction> setter for abortTransaction private filed
 * \param abortTransaction Boolean to determine the object can or cannot commit
 */
void OSTM::Set_Abort_Transaction(bool abortTransaction) {
    /* @134 set abort_Transaction object variable to parameter boolean value  */
    this->abort_Transaction = abortTransaction;
}
/*!
 * \brief @140 Function <Is_Abort_Transaction> return boolean value stored in the <abortTransaction> private filed
 * \param abort_Transaction Boolean to determine the object can or cannot commit
 */
bool OSTM::Is_Abort_Transaction() const {
    /* @142 return abort_Transaction object boolean value */
    return abort_Transaction;
}
/*!
 * \brief @145 Function <lock_Mutex> setter for mutex to lock the object
 */
void OSTM::lock_Mutex() {
    /* @149 Locking the mutex*/
    this->mutex.lock();
}
/*!
 * \brief @154 Function <unlock_Mutex> setter for mutex to unlock the object
 */
void OSTM::unlock_Mutex() {
    /* @156 Locking the mutex */
    this->mutex.unlock();
}
/*!
 * \brief @162 Function <is_Locked> Boolean function to try lock the object. If the object
 * not locked then locks and return True it otherwise return False. 
 */
bool OSTM::try_lock(){
    /* @164 Try to unlock the mutex, return TRUE if the lock was acquired successfully, otherwise return FALSE */
    return this->mutex.try_lock();
}