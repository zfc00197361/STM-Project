/* 
 * File:   BOA.cpp
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#include "BOA.h"


BOA::BOA(const BOA& orig) {
}

BOA::~BOA() {
}
/*!
 * \brief getBaseCopy function, make deep copy of the object/pointer and Return a new std::shared_ptr<BANK> type object
 * \param objTO is a BANK type pointer for casting
 * \param obj is a std::shared_ptr<BANK> return type
 */
std::shared_ptr<OSTM> BOA::getBaseCopy(std::shared_ptr<OSTM> object)
{
        std::shared_ptr<BANK> objTO = std::dynamic_pointer_cast<BANK>(object);
	std::shared_ptr<BANK> obj(new BOA(objTO,object->Get_Version(),object->Get_Unique_ID())); 
        std::shared_ptr<OSTM> ostm_obj = std::dynamic_pointer_cast<OSTM>(obj);
	return ostm_obj;
}
/*!
 * \brief copy function, make deep copy of the object/pointer
 * \param objTO is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 * \param objFROM is a std::shared_ptr<BANK> type object casted back from std::shared_ptr<OSTM>
 */
void BOA::copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from){

	std::shared_ptr<BOA> objTO = std::dynamic_pointer_cast<BOA>(to);
	std::shared_ptr<BOA> objFROM = std::dynamic_pointer_cast<BOA>(from);
	objTO->Set_Unique_ID(objFROM->Get_Unique_ID());
	objTO->Set_Version(objFROM->Get_Version());
	objTO->SetAccountNumber(objFROM->GetAccountNumber());
	objTO->SetBalance(objFROM->GetBalance());
        
}
/*!
 * \brief _cast, is use to cast bak the std::shared_ptr<OSTM> to the required type
 */
//std::shared_ptr<BOA> BOA::_cast(std::shared_ptr<OSTM> _object){
//
//    return std::static_pointer_cast<BOA>(_object);
//}
/*!
 *  \brief toString function, displays the object values in formatted way
 */
void BOA::toString()
{
   // std::cout << "\nUnique ID : " << this->GetUniqueID() << "\nInt value : " << this->GetV_int() << "\nDouble value : " << this->GetV_double() << "\nFloat value : " << this->GetV_float() << "\nString value : " << this->GetV_string()  << "\nVersion number : " << this->GetVersion() << "\nLoad Counter : "<< this->GetLoadCounter() << "\nWrite Counter : "<< this->GetWriteCounter() << std::endl;
	 std::cout << "\nBOA BANK" << "\nUnique ID : " << this->Get_Unique_ID() << "\nInt account : " << this->GetAccountNumber() << "\nDouble value : " << this->GetBalance() << "\nFirst name: " << this->GetFirstName() << "\nLast name : " << this->GetLastName()  << "\nVersion number : " << this->Get_Version() << std::endl;
}

void BOA::SetAddress(std::string address) {
    this->address = address;
}

std::string BOA::GetAddress() const {
    return address;
}

void BOA::SetBalance(double balance) {
    this->balance = balance;
}

double BOA::GetBalance() const {
    return balance;
}

void BOA::SetAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

int BOA::GetAccountNumber() const {
    return accountNumber;
}

void BOA::SetLastName(std::string lastName) {
    this->lastName = lastName;
}

std::string BOA::GetLastName() const {
    return lastName;
}

void BOA::SetFirstName(std::string firstName) {
    this->firstName = firstName;
}

std::string BOA::GetFirstName() const {
    return firstName;
}

void BOA::SetFullname(std::string fullname) {
    this->fullname = fullname;
}

std::string BOA::GetFullname() const {
    return fullname;
}

