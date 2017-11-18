/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <STM.h>

class Tobj{
	private:

	public:

}
class Account : public Tobj{
	private:
			int amount;
			int accountID;
			string accountHolder;
	public:
		void addAmount(double amount);
		void removeAmount(double amount);

}
int main(){
 	 //Create a Transaction manager
	 TM transactionManager;
	 //Create a transaction object
	 TX transaction;

	 //Create two bank account to work with
	 Account from, to;
	 from = Account(100,1234,"JOE");
	 to = Account(50,2345,"BOB");
 
 	//add the thread to the TM manager HasMap and return the transaction
 	transaction = transactionManager.createTX(Thread);

 	//transaction add the account object to the transaction HasMap read and write sets and return the local copy 
 	auto copyFrom = transaction.startTransaction(from);
	auto copyTo = transaction.startTransaction(to);

	// //get a copy of the two accont objects from the transaction library collection
 // 	auto copyFrom = transaction.get(from);
 // 	auto copyTo = transaction.get(to);

 	//Create boolean value to check the transaction state
 	bool done = false;

 	while(!done){

  		copyFrom.
 		//The transaction try to update the values in the transaction
 		//if the values update then return true otherwise return false
 		done = TX.updateTransaction();
  	}
	
	//remove ad destroy transactional associations with the Thread
	transactionManager.destroTX(Thread);

	foreach
	return 0;
}

START(0, RW);

		for(int i = 0; i < INCREMENT; i++)
		{
			int tmp = (int) LOAD(&this->value);
			tmp = tmp + 1;

			STORE(&this->value, tmp);
		}

		COMMIT;