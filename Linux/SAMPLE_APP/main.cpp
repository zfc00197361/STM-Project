/*
 * File:   main.cpp
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

#include <cstdlib>
#include <iostream>
#include <thread>
#include "TM.h"
#include "AIB.h"   
#include "BOI.h"    
#include <mutex>
#include <memory>
#include <condition_variable>
#include <vector>

/*!
 * \brief _two_account_transfer_ function, takes two OSTM type shared pointer, the Transaction manager, and the amount to use in the transaction
 * \param  _tm TM, transaction Manager
 * \param _to std::shared_ptr<BANK> 
 * \param _from std::shared_ptr<OSTM> 
 * \param _amount double value
 */
void _two_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount) {
    /* @34 Request for transaction object with the transaction manager*/
    std::shared_ptr<TX> tx = _tm._get_tx();
    /* @36-37 Register the two OSTM type shared pointer to the library : _to_ and _from_ */
    tx->_register(_to_);
    tx->_register(_from_);
    /*  @39-40 We need to create local pointers to use the temporary pointers in the transaction */
    std::shared_ptr<BANK> _TO_BANK_, _FROM_BANK_;
    std::shared_ptr<OSTM> _TO_OSTM_, _FROM_OSTM_;
    /* @42 Declare boolean variable to control the transaction with the while loop*/
    bool done = false;
    /* @44 Use try catch blocks ! If you try to use exidantly any nullpointer to register,save or load in the libaray, then the library wil throw a runtime execption*/
    try {
        /* @46 Declare the WHILE loop with the boolean variable */
        while (!done) {
            /* @48-49 Retrieve the copy OSTM type pointers you registered (_to_ and _from_) from the library, and cast it back to BANK type. In this way you can used the BANK virtual methods to access the AIB and BOI objects values*/
            _TO_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
          
            /* @52-53 Makes changes with the local pointers. Remove value from the first object and add to the second object ! TRANSFER ! */
            _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
            _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
            /* @55-56 Cast back the BANK type pointers to OSTM type before try to store the changes with the objetcs */
            _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
            _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
            /* @58-59 Store changes has made with the local pointers */
            tx->store(_TO_OSTM_);
            tx->store(_FROM_OSTM_);
            /* @62 Commit changes with the nested transaction*/
            done = tx->commit();
        }
    /* @64-65 Catch block to catch runtime errors. Print error to console*/
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

/*!
 * \brief _nesting_ function, takes two std::shared_ptr<OSTM> pointer, the Transaction manager, and the amount to use in the transaction and transfer the _amount value from one account to the another account
 * This function create nested transactions inside the transaction, and call other function to nesting the transaction as well  
 * \param  _tm TM, transaction Manager
 * \param _to std::shared_ptr<BANK> 
 * \param _from std::shared_ptr<OSTM> 
 * \param _amount double value
 */
void _nesting_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount) {
    /* @79 Request fro transaction object with the transaction manager*/
    std::shared_ptr<TX> tx = _tm._get_tx();
    /* @81-82 Register the two OSTM type shared pointer to the library : _to_ and _from_ */
    tx->_register(_to_);
    tx->_register(_from_);
    /*  @84-85 We need to create local pointers to use the temporary pointers in the transaction */
    std::shared_ptr<BANK> _TO_BANK_, _FROM_BANK_;
    std::shared_ptr<OSTM> _TO_OSTM_, _FROM_OSTM_;
    /* @87 Declare boolean variable to control the transaction with the while loop*/
    bool done = false;
     /* @89 Use try catch blocks ! If you try to use exidantly any nullpointer to register,save or load in the libaray, then the library wil throw a runtime execption*/
    try {
        /* @91 Declare the WHILE loop with the boolean variable */
        while (!done) {
            /* @93-94 Retrieve the copy OSTM type pointers you registered (_to_ and _from_) from the library, and cast it back to BANK type. In this way you can used the BANK virtual methods to access the AIB and BOI objects values*/
            _TO_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
            
            /* @97-98 make changes with the local pointers */
            _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
            _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
            /* @100-101 Cast back the BANK type pointers to OSTM type before try to store the changes with the objetcs */
            _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
            _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
            /* @103-104 Store changes has made with the local pointers */
            tx->store(_TO_OSTM_);
            tx->store(_FROM_OSTM_);
            
            /* @107 Retrieve a Transaction object to used in the NESTED TRANSACTION. Because the same thread request the transaction object the transaction manager will return back the same transaction object, and increase the nesting associated with the transaction */
            std::shared_ptr<TX> txTwo = _tm._get_tx();
             /* @109 Declare boolean variable to control the nested transaction with the while loop*/
            bool nestedDone = false;
            /* @111 Declare the WHILE loop with the boolean variable */
            while (!nestedDone) {
            
                /* @114-115Retrieve the copy OSTM type pointers you registered (_to_ and _from_) from the library, and cast it back to BANK type. In this way you can used the BANK virtual methods to access the AIB and BOI objects values*/
                _TO_BANK_ = std::dynamic_pointer_cast<BANK> (txTwo->load(_to_));
                _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (txTwo->load(_from_));
                /* @117-118 make changes with the local pointers */
                _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
                _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
                /* @120-121 Cast back the BANK type pointers to OSTM type before try to store the changes with the objetcs */
                _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
                _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
                /* @123-124 Store changes has made with the local pointers */
                txTwo->store(_TO_OSTM_);
                txTwo->store(_FROM_OSTM_);
                /* @126 Call other function that will nesting the transaction to the next level */
                _two_account_transfer_(_to_, _from_, _tm, _amount);
                /* @128 Commit changes with the nested transaction*/
                nestedDone = txTwo->commit();
            }
            /* @131 Commit changes with the outer transaction*/
            done = tx->commit();
        }
    /* @134-135 Catch block to catch runtime errors. Print error to console*/
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

/*!
 * \fn main function to run test
 */
int main(void) {
    
     /* @146 Get the Transaction Manager */
     
    TM& tm = TM::Instance();
    
     /* @151-152 Create BANK object OSTM type. All object will get the unique ID generated by default*/
     
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Mark", "darcy", "Main street, CArlow, Co.Carlow"));

     
     /* @155-156 Display BANK objects before transaction*/
    aib_ptr->toString();
    boi_ptr->toString();
    
     
     /* @160 transferAmount in the transaction, control the value in the transaction between objetcs*/
    int transferAmount = 1;
    /** @162 threadArraySize control number of threads will be created in the main function */
    int threadArraySize = 300;
    /* @164 Create a thread array with the threadArraySize declared before  */
    std::thread thArray[threadArraySize];
    /* @166 Creating the threads with the loop */
    for (int i = 0; i < threadArraySize; ++i) {
            /* @168 with the new thread created call the function _nesting_*/
            thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
            /* @170 with the new thread created call the function _two_account_transfer_*/
            thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
    }
    /* @173-175 Join all the threads created */
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }

    /* @178-179 Display objects after all transactions are finished */
    aib_ptr->toString();
    boi_ptr->toString();

    /* @182 For testing purpose create a new transaction object to print out the rollback counter */
    std::shared_ptr<TX> tx = tm._get_tx();

    /* @185 Display the rollback number from the transaction class*/
    std::cout << "Rollback counter is : " << tx->getTest_counter() << std::endl;

    /* @188 Clean up Transaction Manager from all main process associated transactions */
    tm._TX_EXIT();
    /* @190 Display all Transactions associated with the main process. It should be empty after _TX_EXIT() function call!!! */
    tm.print_all();

    return 0;
}
