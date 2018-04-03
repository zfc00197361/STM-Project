/* 
 * File:   UNBL.cpp
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#include "UNBL.h"

UNBL::UNBL(const UNBL& orig) {
}

UNBL::~UNBL() {
}
/*!
 * \brief getBaseCopy function, make deep copy of the object/pointer and Return a new std::shared_ptr<BANK> type object
 * \param objTO is a BANK type pointer for casting
 * \param obj is a std::shared_ptr<BANK> return type
 */
std::shared_ptr<OSTM> UNBL::getBaseCopy(std::shared_ptr<OSTM> object)
{
    std::shared_ptr<BANK> objTO = std::dynamic_pointer_cast<BANK>(object);
    std::shared_ptr<BANK> obj(new UNBL(objTO,object->Get_Version(),object->Get_Unique_ID())); 
    std::shared_ptr<OSTM> ostm_obj = std::dynamic_pointer_cast<OSTM>(obj);                                  
    return ostm_obj;
}
/*!
 * \brief copy function, make deep copy of the object/pointer
 * \param objTO is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 * \param objFROM is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 */
void UNBL::copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from){

	std::shared_ptr<UNBL> objTO = std::dynamic_pointer_cast<UNBL>(to);
	std::shared_ptr<UNBL> objFROM = std::dynamic_pointer_cast<UNBL>(from);
	objTO->Set_Unique_ID(objFROM->Get_Unique_ID());
	objTO->Set_Version(objFROM->Get_Version());
	objTO->SetAccountNumber(objFROM->GetAccountNumber());
	objTO->SetBalance(objFROM->GetBalance());
   
}
/*!
 * \brief _cast, is use to cast bak the std::shared_ptr<OSTM> to the required type
 */
//std::shared_ptr<UNBL> UNBL::_cast(std::shared_ptr<OSTM> _object){
//
//    return static_cast<std::shared_ptr<UNBL>>(_object);
//}
/*!
 *  \brief toString function, displays the object values in formatted way
 */
void UNBL::toString()
{
   std::cout << "\nUNBL BANK" << "\nUnique ID : " << this->Get_Unique_ID() << "\nInt account : " << this->GetAccountNumber() << "\nDouble value : " << this->GetBalance() << "\nFirst name: " << this->GetFirstName() << "\nLast name : " << this->GetLastName()  << "\nVersion number : " << this->Get_Version() << std::endl;
}

void UNBL::SetAddress(std::string address) {
    this->address = address;
}

std::string UNBL::GetAddress() const {
    return address;
}

void UNBL::SetBalance(double balance) {
    this->balance = balance;
}

double UNBL::GetBalance() const {
    return balance;
}

void UNBL::SetAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

int UNBL::GetAccountNumber() const {
    return accountNumber;
}

void UNBL::SetLastName(std::string lastName) {
    this->lastName = lastName;
}

std::string UNBL::GetLastName() const {
    return lastName;
}

void UNBL::SetFirstName(std::string firstName) {
    this->firstName = firstName;
}

std::string UNBL::GetFirstName() const {
    return firstName;
}

void UNBL::SetFullname(std::string fullname) {
    this->fullname = fullname;
}

std::string UNBL::GetFullname() const {
    return fullname;
}

