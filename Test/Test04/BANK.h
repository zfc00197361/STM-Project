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
    virtual void SetAddress(std::string address){};
    virtual std::string GetAddress() const{};
    virtual void SetBalance(double balance){};
    virtual double GetBalance() const{};
    virtual void SetAccountNumber(int accountNumber){};
    virtual int GetAccountNumber() const{};
    virtual void SetLastName(std::string lastName){};
    virtual std::string GetLastName() const{};
    virtual void SetFirstName(std::string firstName){};
    virtual std::string GetFirstName() const{};
    virtual void SetFullname(std::string fullname){};
    virtual std::string GetFullname() const{};
    
private:

};

#endif /* BANK_H */

