/* 
 * File:   AIB.cpp
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

#include <math.h>

#include "AIB.h"


AIB::~AIB() {
}
/*!
 * \brief getBaseCopy function, make deep copy of the object/pointer and Return a new std::shared_ptr<BANK> type object
 * \param object is a OSTM type shared pointer use to create a new copy of the pointer
 */
std::shared_ptr<OSTM> AIB::getBaseCopy(std::shared_ptr<OSTM> object)
{
    /** Dynamic cast from OSTM to BANK type*/
    std::shared_ptr<BANK> objTO = std::dynamic_pointer_cast<BANK>(object);
    /** BANK type Instance creation shared pointer*/
    std::shared_ptr<BANK> obj(new AIB(objTO, object->Get_Version(),object->Get_Unique_ID()));
    /** Dynamic cast from BANK to OSTM type*/
    std::shared_ptr<OSTM> ostm_obj = std::dynamic_pointer_cast<OSTM>(obj);
    /** Return new OSTM copy onject*/
    return ostm_obj;
}
/*!
 * \brief copy function, make deep copy of the object/pointer
 * \param to std::shared_ptr<OSTM>, BANK type shared pointer used to copy into the values
 * \param from std::shared_ptr<OSTM>, BANK type shared ponter used to get object values tfrom copy
 */
void AIB::copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from){

    /** Dynamic cast from OSTM to AIB*/
    std::shared_ptr<AIB> objTO = std::dynamic_pointer_cast<AIB>(to);
    /** Dynamic cast from OSTM to AIB */
    std::shared_ptr<AIB> objFROM = std::dynamic_pointer_cast<AIB>(from);
    /** Set values fro object to object*/
    objTO->Set_Unique_ID(objFROM->Get_Unique_ID());
    /** Set values fro object to object*/
    objTO->Set_Version(objFROM->Get_Version());
    /** Set values fro object to object*/
    objTO->SetAccountNumber(objFROM->GetAccountNumber());
    /** Set values fro object to object*/
    objTO->SetBalance(objFROM->GetBalance());
}
/*!
 *  \brief toString function, displays the object values in formatted way
 */
void AIB::toString()
{
    std::cout << "\nAIB BANK" << "\nUnique ID : " << this->Get_Unique_ID() << "\nInt account : " << this->GetAccountNumber() << "\nDouble value : " << this->GetBalance() << "\nFirst name: " << this->GetFirstName() << "\nLast name : " << this->GetLastName()  << "\nVersion number : " << this->Get_Version() << std::endl;
}
/*!
 *  \brief SetAddress setter for address private field
 */
void AIB::SetAddress(std::string address) {
    this->address = address;
}
/*!
 *  \brief GetAddress getter for address private field
 */
std::string AIB::GetAddress() const {
    return address;
}
/*!
 *  \brief SetBalance setter for balance private field
 */
void AIB::SetBalance(double balance) {
    this->balance = balance;
}
/*!
 *  \brief GetBalance getter for balance private field
 */
double AIB::GetBalance() const {
    return balance;
}
/*!
 *  \brief SetAccountNumber setter for accountNumber private field
 */
void AIB::SetAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}
/*!
 *  \brief GetAccountNumber getter for accountNumber private field
 */
int AIB::GetAccountNumber() const {
    return accountNumber;
}
/*!
 *  \brief SetLastName setter for lastName private field
 */
void AIB::SetLastName(std::string lastName) {
    this->lastName = lastName;
}
/*!
 *  \brief GetLastName getter for lastName private field
 */
std::string AIB::GetLastName() const {
    return lastName;
}
/*!
 *  \brief SetFirstName setter for firstName private field
 */
void AIB::SetFirstName(std::string firstName) {
    this->firstName = firstName;
}
/*!
 *  \brief GetFirstName getter for firstName private field
 */
std::string AIB::GetFirstName() const {
    return firstName;
}
/*!
 *  \brief SetFullname setter for fullname private field
 */
void AIB::SetFullname(std::string fullname) {
    this->fullname = fullname;
}
/*!
 *  \brief GetFullname getter for fullname private field
 */
std::string AIB::GetFullname() const {
    return fullname;
}