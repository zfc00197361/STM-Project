/*! 
 * File:   OSTM.h
 * Author: Zoltan Fuzesi C00197361, 
 * IT Carlow, Software Engineering, 
 *
 * Supervisor : Joe Kehoe, 
 *
 * C++ Software Transactional Memory, 
 *
 * Created on December 18, 2017, 2:09 PM
 * The OSTM class is the base class to all the inherited classes that intend to used 
 * with the Software Transactional memory library
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
    /*
     * Default Constructor
     */
    OSTM();
    /*
     * Custom Constructor
     */
    OSTM(int _version_number_, int _unique_id_);
    /*
     * De-constructor
     */
    virtual ~OSTM();
     /**
     * \brief The toString function displaying/representing the object on the terminal is string format.
     * @see toString function implementation in child class
     */
    virtual void toString(){};
    /**
     * \brief The copy virtual method required for deep copy between objetcs within the transaction.
     * @see copy function implementation in inherited class class
     */ 
    virtual void copy(std::shared_ptr<OSTM> from, std::shared_ptr<OSTM> to){};  
     /**
     * \brief The getbasecopy virtual method required for create a copy of the origin object/pointer and returning a copy of the object/pointer.
     * @see getBaseCopy function implementation in child class
     */
    virtual std::shared_ptr<OSTM> getBaseCopy(std::shared_ptr<OSTM> object){};
    /*
     * Setter for object unique id
     * @param uniqueID Integer to set the uniqueId
     */
    void Set_Unique_ID(int uniqueID);
    /*
     * Getter for object unique id
     */
    int Get_Unique_ID() const;
    /*
     * Setter for object version number
     * @param version Integer to set the version number
     */
    void Set_Version(int version);
    /*
     * Getter for object version number
     */
    int Get_Version() const;
    /*
     * When transacion make changes on object at commit time increase the version number on the object.
     */
    void increase_VersionNumber();
    /*
     * Determin if the object can commit or not. Return boolean TRUE/FALSE
     */
    bool Is_Can_Commit() const;
    /*
     * Setter for canCommit boolean filed
     * @param canCommit Boolean to set the canCommit variable
     */
    void Set_Can_Commit(bool canCommit);
    /*
     * set boolean
     * @param abortTransaction boolean to set the abort_Transaction TRUE or FALSE
     */
    void Set_Abort_Transaction(bool abortTransaction);
    /*
     * Determin if the object need to abort the transaction or not. Return boolean TRUE/FALSE
     */
    bool Is_Abort_Transaction() const;
    /*
     * Function to lock the object itself
     */
    void lock_Mutex();
    /*
     * Function to unlock the object itself
     */
    void unlock_Mutex();
    /*
     * Function to try lock the object itself if it is not locked. Return boolean value TRUE/FALSE depending if it is can lock or not.
     */
    bool try_lock();

private:
    /**
     * Object private version number.
     * The verion number ZERO by default when the object created. When a transaction make changes with the object, then the version number
     * will be increased, to indicate the changes on the object.
     */
    int version;
    /**
     * Object unique identifier
     * Every object inherit from OSTM class will include a version number that is unique for every object.
     * The STM library used this value to find object within the transaction to make changes or comparism ith them.
     */
    int uniqueID;
    /**
     * Boolean value <canCommit> to determine the object can or cannot commit
     */
    bool canCommit;
    /**
     * Boolean value <abort_Transaction> to determine the object need to abort the transaction
     */
    bool abort_Transaction;
    /**
     * Unique object number start at ZERO
     * The value stored in class level <global_Unique_ID_Number> increase every OSTM type object creation.
     */
    static int global_Unique_ID_Number;
    /**
     * Integer <ZERO> meaninful string equalient to 0
     */
    const int ZERO = 0;
    /**
     * Mutex lock <mutex> use to lock the object with transaction, to make sure only
     * one transaction can access the object at the time
     */
    std::mutex mutex;
    /**
     * Returning global_Unique_ID_Number to the constructor
     */
    int Get_global_Unique_ID_Number();

};

#endif /* OSTM_H */