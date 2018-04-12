
/* 
 * File:   ULSTER.cpp
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#include "ULSTER.h"


ULSTER::ULSTER(const ULSTER& orig) {
}

ULSTER::~ULSTER() {
}
/*
 * \brief getBaseCopy function, make deep copy of the object/pointer and Return a new std::shared_ptr<BANK> type object
 * \param objTO is a BANK type pointer for casting
 * \param obj is a std::shared_ptr<BANK> return type
 */
std::shared_ptr<OSTM> ULSTER::getBaseCopy(std::shared_ptr<OSTM> object)
{
    std::shared_ptr<BANK> objTO = std::dynamic_pointer_cast<BANK>(object);
    std::shared_ptr<BANK> obj(new ULSTER(objTO,object->Get_Version(),object->Get_Unique_ID())); 
    std::shared_ptr<OSTM> ostm_obj = std::dynamic_pointer_cast<OSTM>(obj);                                  
    return ostm_obj;
}
/*
 * \brief copy function, make deep copy of the object/pointer
 * \param objTO is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 * \param objFROM is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 */ 
void ULSTER::copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from){

	std::shared_ptr<ULSTER> objTO = std::dynamic_pointer_cast<ULSTER>(to);
	std::shared_ptr<ULSTER> objFROM = std::dynamic_pointer_cast<ULSTER>(from);
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
void ULSTER::toString()
{
   std::cout << "\nULSTER BANK" << "\nUnique ID : " << this->Get_Unique_ID() << "\nInt account : " << this->GetAccountNumber() << "\nDouble value : " << this->GetBalance() << "\nFirst name: " << this->GetFirstName() << "\nLast name : " << this->GetLastName()  << "\nVersion number : " << this->Get_Version() << std::endl;
}

void ULSTER::SetAddress(std::string address) {
    this->address = address;
}

std::string ULSTER::GetAddress() const {
    return address;
}

void ULSTER::SetBalance(double balance) {
    this->balance = balance;
}

double ULSTER::GetBalance() const {
    return balance;
}

void ULSTER::SetAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

int ULSTER::GetAccountNumber() const {
    return accountNumber;
}

void ULSTER::SetLastName(std::string lastName) {
    this->lastName = lastName;
}

std::string ULSTER::GetLastName() const {
    return lastName;
}

void ULSTER::SetFirstName(std::string firstName) {
    this->firstName = firstName;
}

std::string ULSTER::GetFirstName() const {
    return firstName;
}

void ULSTER::SetFullname(std::string fullname) {
    this->fullname = fullname;
}

std::string ULSTER::GetFullname() const {
    return fullname;
}

