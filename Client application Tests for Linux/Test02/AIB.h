/* 
 * File:   AIB.h
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#ifndef AIB_H
#define AIB_H
#include "BANK.h"
#include <string>
#include <memory>
#include <iostream>
/*!
 * Inherit from BANK
 */
class AIB : public BANK {
public:
    /*!
     * Constructor
     */
    AIB(): BANK()
    {
        this->accountNumber = 0;
        this->balance = 50;
        this->firstName = "Joe";
        this->lastName = "Blog";
        this->address = "High street, Carlow";
        this->fullname = firstName + " " + lastName;
    
    };
    /*!
     * Custom constructor
     */
    AIB(int accountNumber, double balance, std::string firstName, std::string lastName, std::string address): BANK()
    {
        this->accountNumber = accountNumber;
        this->balance = balance;
        this->firstName = firstName;
        this->lastName = lastName;
        this->address = address;
        this->fullname = firstName + " " + lastName;
    }; 
    /*!
     * Custom constructor, used by the library for deep copying
     */
    AIB(std::shared_ptr<BANK> obj, int _version, int _unique_id): BANK(_version, _unique_id)
    {
        
        this->accountNumber = obj->GetAccountNumber();
        this->balance = obj->GetBalance();
        this->firstName = obj->GetFirstName();
        this->lastName = obj->GetLastName();
        this->address = obj->GetAddress();
        this->fullname = obj->GetFirstName() + " " + obj->GetLastName(); 
        
    };
    /*!
     * Copy constructor
     */
    AIB(const AIB& orig);
    /*!
     * Operator
     */
    AIB operator=(const AIB& orig){};
    /*!
     * de-constructor
     */
    virtual ~AIB();
    
    /*
     * Implement OSTM virtual methods
     */
   // virtual std::shared_ptr<AIB> _cast(std::shared_ptr<OSTM> _object);
    virtual void copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from);
    virtual std::shared_ptr<OSTM> getBaseCopy(std::shared_ptr<OSTM> object);
    virtual void toString();
    
    /*
     * Implement BANK virtual methods
     */
    virtual void SetAddress(std::string address);
    virtual std::string GetAddress() const;
    virtual void SetBalance(double balance);
    virtual double GetBalance() const;
    virtual void SetAccountNumber(int accountNumber);
    virtual int GetAccountNumber() const;
    virtual void SetLastName(std::string lastName);
    virtual std::string GetLastName() const;
    virtual void SetFirstName(std::string firstName);
    virtual std::string GetFirstName() const;
    virtual void SetFullname(std::string fullname);
    virtual std::string GetFullname() const;
    
private:
    std::string fullname;
    std::string firstName;
    std::string lastName;
    int accountNumber;
    double balance;
    std::string address;


};

#endif /* AIB_H */
