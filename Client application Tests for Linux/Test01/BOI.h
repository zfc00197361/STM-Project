
/* 
 * File:   BOI.h
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#ifndef BOI_H
#define BOI_H
#include "BANK.h"
#include <string>
#include <memory>
#include <iostream>
/*!
 * Inherit from BANK
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
   // virtual std::shared_ptr<BOI> _cast(std::shared_ptr<OSTM> _object);
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
    std::string fullname;
    std::string firstName;
    std::string lastName;
    int accountNumber;
    double balance;
    std::string address;

};

#endif /* BOI_H */

 
    //virtual std::string get_class();
    
   // 
    //virtual bool get(std::shared_ptr<OSTM> object);
 
///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///* 
// * File:   BOI.h
// * Author: zoltan
// *
// * Created on January 19, 2018, 6:37 PM
// */
//
//#ifndef BOI_H
//#define BOI_H
//#include "OSTM.h"
//#include <string>
//#include <memory>
//#include <iostream>
//
//class BOI: public OSTM {
//public:
//    BOI(): OSTM()
//    {
//        this->accountNumber = 0;
//        this->balance = 50;
//        this->firstName = "Joe";
//        this->lastName = "Blog";
//        this->address = "High street, Carlow";
//        this->fullname = firstName + " " + lastName;
//        
//    }
//    BOI(int accountNumber, double balance, std::string firstName, std::string lastName, std::string address): OSTM()
//    {
//        this->accountNumber = accountNumber;
//        this->balance = balance;
//        this->firstName = firstName;
//        this->lastName = lastName;
//        this->address = address;
//        this->fullname = firstName + " " + lastName;
//    };
//    
//     BOI(OSTM& obj, int _version, int _unique_id): OSTM(_version, _unique_id)
//    {
////        this->accountNumber = obj->GetAccountNumber();
////        this->balance = obj->GetBalance();
////        this->firstName = obj->GetFirstName();
////        this->lastName = obj->GetLastName();
////        this->address = obj->GetAddress();
////        this->fullname = obj->GetFirstName() + " " + obj->GetLastName(); 
//          this->accountNumber = obj.GetAccountNumber();
//        this->balance = obj.GetBalance();
//        this->firstName = obj.GetFirstName();
//        this->lastName = obj.GetLastName();
//        this->address = obj.GetAddress();
//        this->fullname = obj.GetFirstName() + " " + obj.GetLastName(); 
////        this->accountNumber = obj.accountNumber;
////        this->balance = obj.balance;
////        this->firstName = obj.firstName;
////        this->lastName = obj.lastName;
////        this->address = obj.address;
////        this->fullname = obj.firstName + " " + obj.lastName;
//    };
//    
//     BOI(std::shared_ptr<OSTM> obj, int _version, int _unique_id): OSTM(_version, _unique_id)
//    {
//        this->accountNumber = obj->GetAccountNumber();
//        this->balance = obj->GetBalance();
//        this->firstName = obj->GetFirstName();
//        this->lastName = obj->GetLastName();
//        this->address = obj->GetAddress();
//        this->fullname = obj->GetFirstName() + " " + obj->GetLastName(); 
//    };
//    
//
//    BOI(const BOI& orig);
//    BOI operator=(const BOI& orig){};
//    virtual ~BOI();
//
//    virtual std::shared_ptr<BOI> _cast(std::shared_ptr<OSTM> _object);
//    virtual std::shared_ptr<BOI> getBaseCopy(OSTM& object);
//    virtual std::shared_ptr<BOI> getBaseCopy(std::shared_ptr<OSTM> object);
//    virtual void copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from);
//    virtual void toString();
//    virtual void SetAddress(std::string address);
//    virtual std::string GetAddress() const;
//    virtual void SetBalance(double balance);
//    virtual double GetBalance() const;
//    virtual void SetAccountNumber(int accountNumber);
//    virtual int GetAccountNumber() const;
//    virtual void SetLastName(std::string lastName);
//    virtual std::string GetLastName() const;
//    virtual void SetFirstName(std::string firstName);
//    virtual std::string GetFirstName() const;
//    virtual void SetFullname(std::string fullname);
//    virtual std::string GetFullname() const;
//    
//private:
//    std::string fullname;
//    std::string firstName;
//    std::string lastName;
//    int accountNumber;
//    double balance;
//    std::string address;
//
//};
//
//#endif /* BOI_H */
//
// 
//    //virtual std::string get_class();
//    
//   // 
//    //virtual bool get(std::shared_ptr<OSTM> object);
// 