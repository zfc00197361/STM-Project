/* 
 * File:   OSTM.h
 * Author: Zoltan FUzesi
 *
 * Created on December 18, 2017, 2:09 PM
 * OSTM header file fields and  methods declarations
 */

#ifndef OSTM_H
#define OSTM_H
#include <mutex>
#include <memory>
#include <string>
#include <iostream>
#include <string>

class OSTM {
public:
    /*!
     * \brief OSTM Constructor
     */
	__declspec(dllexport) OSTM();
    /*!
     * \brief OSTM Custom Constructor
     */
	__declspec(dllexport) OSTM(int _version_number_, int _unique_id_);
    /*!
     * \brief De-constructor
     */
    virtual ~OSTM();
    /*!
     * \brief OSTM required virtual method for deep copy
     */ 
	__declspec(dllexport) virtual void copy(std::shared_ptr<OSTM> from, std::shared_ptr<OSTM> to){};
     /*!
     * \brief OSTM required virtual method for returning a pointer that is copy of the original pointer
     */
	__declspec(dllexport) virtual std::shared_ptr<OSTM> getBaseCopy(std::shared_ptr<OSTM> object) = 0;//std::cout << "[OSTM GETBASECOPY]" << std::endl;};
     /*!
     * \brief OSTM required virtual method for display object
     */
	__declspec(dllexport) virtual void toString(){};
    /*!
     * \brief setter for unique id
     */
	__declspec(dllexport) void Set_Unique_ID(int uniqueID);
    /*!
     * \brief getter for unique id
     */
	__declspec(dllexport) int Get_Unique_ID() const;
    /*!
     * \brief setter for version number
     */
	__declspec(dllexport) void Set_Version(int version);
    /*!
     * \brief getter for version number
     */
	__declspec(dllexport) int Get_Version() const;
    /*!
     * \brief commit time increase version number to child object
     */
	__declspec(dllexport) void increase_VersionNumber();
    /*!
     * \brief NOT USED YET
     */
	__declspec(dllexport) bool Is_Can_Commit() const;
    /*!
     * \brief NOT USED YET
     */
	__declspec(dllexport) void Set_Can_Commit(bool canCommit);
    /*!
     * \brief NOT USED YET
     */
	__declspec(dllexport) void Set_Abort_Transaction(bool abortTransaction);
    /*!
     * \brief NOT USED YET
     */
	__declspec(dllexport) bool Is_Abort_Transaction() const;
    /*!
     * \brief object unique lock, locks mutex
     */
	__declspec(dllexport) void lock_Mutex();
    /*!
     * \brief object unique lock, unlocks mutex
     */
	__declspec(dllexport) void unlock_Mutex();
    /*!
     * \brief object unique lock, try locks mutex return boolean value depends on the lock state 
     */
	__declspec(dllexport) bool is_Locked();

private:
    /*
     * \brief Object version number
     */
    int version;
    /*
     * \brief Object unique identifier
     */
    int uniqueID;
    /*
     * \brief Boolean value to check any other thread failed to commit
     */
    bool canCommit;
    /*
     * \brief Abort the transaction
     */
    bool abort_Transaction;
    /*!
     * \brief Unique object number increase at object creation
     */
    static int global_Unique_ID_Number;
    /*!
     * \brief Meaningful display for value 0
     */
    const int ZERO = 0;
    /*!
     * \brief Object built in lock
     */
    std::mutex mutex;
    /*!
     * Returning global_Unique_ID_Number to the constructor
     */
    int Get_global_Unique_ID_Number();

};

#endif /* OSTM_H */
