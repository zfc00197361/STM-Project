/* 
 * File:   BANK.h
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#ifndef BANK_H
#define BANK_H
#include "OSTM.h"
/*!
 * BANK inherit from the OSTM library. It is declares the common functions in the child classes as a virtual  function.
 * 
 */
class BANK : public OSTM {

    
public:
    /*!
     * Constructor
     */
    BANK(): OSTM(){
        
    };
    /*!
     * Custom Constructor
     */
    BANK(int _version, int _unique_id) : OSTM(_version, _unique_id){
        
    };
    /*!
     * Copy constructor
     */
    BANK(const BANK& orig);
    /*!
     * de-constructor
     */
    virtual ~BANK();
    
    /*
     * Bank specific virtual functions
     */
    virtual void SetAddress(std::string address) = 0;
    virtual std::string GetAddress() const = 0;
    virtual void SetBalance(double balance) = 0;
    virtual double GetBalance() const = 0;
    virtual void SetAccountNumber(int accountNumber) = 0;
    virtual int GetAccountNumber() const = 0;
    virtual void SetLastName(std::string lastName) = 0;
    virtual std::string GetLastName() const = 0;
    virtual void SetFirstName(std::string firstName) = 0;
    virtual std::string GetFirstName() const = 0;
    virtual void SetFullname(std::string fullname) = 0;
    virtual std::string GetFullname() const = 0;
    
private:

};

#endif /* BANK_H */

