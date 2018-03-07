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
    OSTM();
    /*!
     * \brief OSTM Custom Constructor
     */
    OSTM(int _version_number_, int _unique_id_);
    /*!
     * \brief De-constructor
     */
    virtual ~OSTM();
    /*!
     * \brief OSTM required virtual method for deep copy
     */ 
    virtual void copy(std::shared_ptr<OSTM> from, std::shared_ptr<OSTM> to){};  
     /*!
     * \brief OSTM required virtual method for returning a pointer that is copy of the original pointer
     */
    virtual std::shared_ptr<OSTM> getBaseCopy(std::shared_ptr<OSTM> object){};//std::cout << "[OSTM GETBASECOPY]" << std::endl;};
     /*!
     * \brief OSTM required virtual method for display object
     */
    virtual void toString(){};
    /*!
     * \brief setter for unique id
     */
    void Set_Unique_ID(int uniqueID);
    /*!
     * \brief getter for unique id
     */
    int Get_Unique_ID() const;
    /*!
     * \brief setter for version number
     */
    void Set_Version(int version);
    /*!
     * \brief getter for version number
     */
    int Get_Version() const;
    /*!
     * \brief commit time increase version number to child object
     */
    void increase_VersionNumber();
    /*!
     * \brief return boolean
     */
    bool Is_Can_Commit() const;
    /*!
     * \brief set boolean
     */
    void Set_Can_Commit(bool canCommit);
    /*!
     * \brief set boolean
     */
    void Set_Abort_Transaction(bool abortTransaction);
    /*!
     * \brief return boolean
     */
    bool Is_Abort_Transaction() const;
    /*!
     * \brief object unique lock, locks mutex
     */
    void lock_Mutex();
    /*!
     * \brief object unique lock, unlocks mutex
     */
    void unlock_Mutex();
    /*!
     * \brief object unique lock, try locks mutex return boolean value depends on the lock state 
     */
    bool is_Locked();

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
