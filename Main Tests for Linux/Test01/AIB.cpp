/* 
 * File:   AIB.cpp
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#include <math.h>

#include "AIB.h"


AIB::AIB(const AIB& orig) {
}

AIB::~AIB() {
}
/*!
 * \brief getBaseCopy function, make deep copy of the object/pointer and Return a new std::shared_ptr<BANK> type object
 * \param objTO is a BANK type pointer for casting
 * \param obj is a std::shared_ptr<BANK> return type
 */
std::shared_ptr<OSTM> AIB::getBaseCopy(std::shared_ptr<OSTM> object)
{

    std::shared_ptr<BANK> objTO = std::dynamic_pointer_cast<BANK>(object);
    std::shared_ptr<BANK> obj(new AIB(objTO, object->Get_Version(),object->Get_Unique_ID()));
    std::shared_ptr<OSTM> ostm_obj = std::dynamic_pointer_cast<OSTM>(obj);
    return ostm_obj;
}
/*!
 * \brief copy function, make deep copy of the object/pointer
 * \param objTO is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 * \param objFROM is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 */
void AIB::copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from){

    std::shared_ptr<AIB> objTO = std::dynamic_pointer_cast<AIB>(to);
    std::shared_ptr<AIB> objFROM = std::dynamic_pointer_cast<AIB>(from);
    objTO->Set_Unique_ID(objFROM->Get_Unique_ID());
    objTO->Set_Version(objFROM->Get_Version());
    objTO->SetAccountNumber(objFROM->GetAccountNumber());
    objTO->SetBalance(objFROM->GetBalance());
}
/*!
 * \brief _cast, is use to cast bak the std::shared_ptr<OSTM> to the required type
 */
//std::shared_ptr<AIB> AIB::_cast(std::shared_ptr<OSTM> _object){
//    
//    return std::static_pointer_cast<AIB>(_object);
//}
/*!
 *  \brief toString function, displays the object values in formatted way
 */
void AIB::toString()
{
    std::cout << "\nAIB BANK" << "\nUnique ID : " << this->Get_Unique_ID() << "\nInt account : " << this->GetAccountNumber() << "\nDouble value : " << this->GetBalance() << "\nFirst name: " << this->GetFirstName() << "\nLast name : " << this->GetLastName()  << "\nVersion number : " << this->Get_Version() << std::endl;
}

void AIB::SetAddress(std::string address) {
    this->address = address;
}

std::string AIB::GetAddress() const {
    return address;
}

void AIB::SetBalance(double balance) {
    this->balance = balance;
}

double AIB::GetBalance() const {
    return balance;
}

void AIB::SetAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

int AIB::GetAccountNumber() const {
    return accountNumber;
}

void AIB::SetLastName(std::string lastName) {
    this->lastName = lastName;
}

std::string AIB::GetLastName() const {
    return lastName;
}

void AIB::SetFirstName(std::string firstName) {
    this->firstName = firstName;
}

std::string AIB::GetFirstName() const {
    return firstName;
}

void AIB::SetFullname(std::string fullname) {
    this->fullname = fullname;
}

std::string AIB::GetFullname() const {
    return fullname;
}
