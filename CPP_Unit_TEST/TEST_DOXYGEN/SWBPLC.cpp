
/* 
 * File:   SWBPLC.cpp
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#include "SWBPLC.h"

SWBPLC::SWBPLC(const SWBPLC& orig) {
}

SWBPLC::~SWBPLC() {
}
/*
 * \brief getBaseCopy function, make deep copy of the object/pointer and Return a new std::shared_ptr<BANK> type object
 * \param objTO is a BANK type pointer for casting
 * \param obj is a std::shared_ptr<BANK> return type
 */
std::shared_ptr<OSTM> SWBPLC::getBaseCopy(std::shared_ptr<OSTM> object)
{
    std::shared_ptr<BANK> objTO = std::dynamic_pointer_cast<BANK>(object);
    std::shared_ptr<BANK> obj(new SWBPLC(objTO,object->Get_Version(),object->Get_Unique_ID())); 
    std::shared_ptr<OSTM> ostm_obj = std::dynamic_pointer_cast<OSTM>(obj);                                  
    return ostm_obj;
}
/*
 * \brief copy function, make deep copy of the object/pointer
 * \param objTO is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 * \param objFROM is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 */
void SWBPLC::copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from){

	std::shared_ptr<SWBPLC> objTO = std::dynamic_pointer_cast<SWBPLC>(to);
	std::shared_ptr<SWBPLC> objFROM = std::dynamic_pointer_cast<SWBPLC>(from);
	objTO->Set_Unique_ID(objFROM->Get_Unique_ID());
	objTO->Set_Version(objFROM->Get_Version());
	objTO->SetAccountNumber(objFROM->GetAccountNumber());
	objTO->SetBalance(objFROM->GetBalance());

    
}
/*
 * \brief _cast, is use to cast bak the std::shared_ptr<OSTM> to the required type
 */

/*
 *  \brief toString function, displays the object values in formatted way
 */
void SWBPLC::toString()
{
     std::cout << "\nSWBPLC BANK" << "\nUnique ID : " << this->Get_Unique_ID() << "\nInt account : " << this->GetAccountNumber() << "\nDouble value : " << this->GetBalance() << "\nFirst name: " << this->GetFirstName() << "\nLast name : " << this->GetLastName()  << "\nVersion number : " << this->Get_Version() << std::endl;
}

void SWBPLC::SetAddress(std::string address) {
    this->address = address;
}

std::string SWBPLC::GetAddress() const {
    return address;
}

void SWBPLC::SetBalance(double balance) {
    this->balance = balance;
}

double SWBPLC::GetBalance() const {
    return balance;
}

void SWBPLC::SetAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

int SWBPLC::GetAccountNumber() const {
    return accountNumber;
}

void SWBPLC::SetLastName(std::string lastName) {
    this->lastName = lastName;
}

std::string SWBPLC::GetLastName() const {
    return lastName;
}

void SWBPLC::SetFirstName(std::string firstName) {
    this->firstName = firstName;
}

std::string SWBPLC::GetFirstName() const {
    return firstName;
}

void SWBPLC::SetFullname(std::string fullname) {
    this->fullname = fullname;
}

std::string SWBPLC::GetFullname() const {
    return fullname;
}

