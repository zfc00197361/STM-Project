
/* 
 * File:   BOI.cpp
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#include "BOI.h"

BOI::~BOI() {
}

BOI::BOI(const BOI& orig) {
}
/*!
 * \brief getBaseCopy function, make deep copy of the object/pointer and Return a new BANK* type object
 * \param objTO is a BANK type pointer for casting
 * \param obj is a BANK* return type
 */
std::shared_ptr<OSTM> BOI::getBaseCopy(std::shared_ptr<OSTM> object)
{

    std::shared_ptr<BOI> objTO = std::dynamic_pointer_cast<BOI>(object);
    std::shared_ptr<BOI> obj(new BOI(objTO,object->Get_Version(),object->Get_Unique_ID())); 
    std::shared_ptr<OSTM> ostm_obj = std::dynamic_pointer_cast<OSTM>(obj);
    return ostm_obj;
}
/*!
 * \brief copy function, make deep copy of the object/pointer
 * \param objTO is a BANK* type object casted back from std::shared_ptr<OSTM>
 * \param objFROM is a BANK* type object casted back from std::shared_ptr<OSTM>
 */
void BOI::copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from){

    std::shared_ptr<BOI> objTO = std::dynamic_pointer_cast<BOI>(to);
    std::shared_ptr<BOI> objFROM = std::dynamic_pointer_cast<BOI>(from);
    objTO->Set_Unique_ID(objFROM->Get_Unique_ID());
    objTO->Set_Version(objFROM->Get_Version());
    objTO->SetAccountNumber(objFROM->GetAccountNumber());
    objTO->SetBalance(objFROM->GetBalance());
}
/*!
 * \brief _cast, is use to cast bak the std::shared_ptr<OSTM> to the required type
 */
//std::shared_ptr<BOI> BOI::_cast(std::shared_ptr<OSTM> _object){
//
//    return std::static_pointer_cast<BOI>(_object);
//}
/*!
 *  \brief toString function, displays the object values in formatted way
 */
void BOI::toString()
{
   std::cout << "\nBOI BANK" << "\nUnique ID : " << this->Get_Unique_ID() << "\nInt account : " << this->GetAccountNumber() << "\nDouble value : " << this->GetBalance() << "\nFirst name: " << this->GetFirstName() << "\nLast name : " << this->GetLastName()  << "\nVersion number : " << this->Get_Version() << std::endl;
}
void BOI::SetAddress(std::string address) {
    this->address = address;
}

std::string BOI::GetAddress() const {
    return address;
}

void BOI::SetBalance(double balance) {
    this->balance = balance;
}

double BOI::GetBalance() const {
    return balance;
}

void BOI::SetAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

int BOI::GetAccountNumber() const {
    return accountNumber;
}

void BOI::SetLastName(std::string lastName) {
    this->lastName = lastName;
}

std::string BOI::GetLastName() const {
    return lastName;
}

void BOI::SetFirstName(std::string firstName) {
    this->firstName = firstName;
}

std::string BOI::GetFirstName() const {
    return firstName;
}

void BOI::SetFullname(std::string fullname) {
    this->fullname = fullname;
}

std::string BOI::GetFullname() const {
    return fullname;
}

