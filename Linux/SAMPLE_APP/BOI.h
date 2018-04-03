
/* 
 * File:   BOI.h
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

#ifndef BOI_H
#define BOI_H
#include "BANK.h"
#include <string>
#include <memory>
#include <iostream>
/*!
 * Class BOI Inherit from BANK class
 */
class BOI: public BANK {
public:
    /*!
     * Constructor
     */
    BOI(): BANK()
    {
        this->accountNumber = 0;
        this->balance = 50;
        this->firstName = "Joe";
        this->lastName = "Blog";
        this->address = "High street, Carlow";
        this->fullname = firstName + " " + lastName;
        
    }
    /*!
     * Custom constructor
     * @param accountNumber integer
     * @param balance double
     * @param firstName string
     * @param lastName string
     * @param address string
     */
    BOI(int accountNumber, double balance, std::string firstName, std::string lastName, std::string address): BANK()
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
     * @param obj std::shared_ptr<BANK>
     * @param _version integer
     * @param _unique_id integer
     */
    BOI(std::shared_ptr<BOI> obj, int _version, int _unique_id): BANK(_version, _unique_id)
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
    BOI(const BOI& orig);
    /*!
     * Operator
     */
    BOI operator=(const BOI& orig){};
    /*!
     * de-constructor
     */
    virtual ~BOI();

    /*
     * Implement OSTM virtual methods
     */
    virtual std::shared_ptr<OSTM> getBaseCopy(std::shared_ptr<OSTM> object);
    virtual void copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from);
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
    /**
    * fullname string object private filed
    */
    std::string fullname;
    /**
    * firstName string object private filed
    */
    std::string firstName;
    /**
    * lastName string object private filed
    */
    std::string lastName;
    /**
    * accountNumber int object private filed
    */
    int accountNumber;
    /**
    * balance double object private filed
    */
    double balance;
    /**
    * address string object private filed
    */
    std::string address;

};

#endif /* BOI_H */