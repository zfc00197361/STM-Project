/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: zoltan
 *
 * Created on November 27, 2017, 9:26 PM
 */

#include <cstdlib>
#include <iostream>
#include <thread>
//#include <unistd.h>//used for pid_t

//STM library requirement
#include "TM.h"
#include "AIB.h"    //Bank Account
#include "BOI.h"    //Bank Account
#include "BOA.h"    //Bank Account
#include "SWBPLC.h" //Bank Account
#include "ULSTER.h" //Bank Account
#include "UNBL.h"   //Bank Account
#include "WAREHOUSE.h"   //WAREHOUSE
#include "CARPHONE_WAREHOUSE.h" //WAREHOUSE
#include "CARLOW_W.h"    //WAREHOUSE
#include "KILKENNY_W.h"  //WAREHOUSE
#include "TALLAGH_W.h"   //WAREHOUSE
#include "DUNDALK_W.h"   //WAREHOUSE
#include "SLIGO_W.h"     //WAREHOUSE
#include <mutex>
#include <memory>
#include <condition_variable>
#include <vector>

/*!
 * \brief _two_account_transfer_ function, takes two std::shared_ptr<OSTM> pointer, the Transaction manager, and the amount to use in the transaction and transfer the _amount value from one account to the another account
 * \param  std::shared_ptr<TX> tx, Transaction Object
 * \param std::shared_ptr<BANK> type, _TO_BANK_ & _FROM_BANK_
 * \param std::shared_ptr<OSTM> type, _TO_OSTM_ & _FROM_OSTM_
 */
void _two_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /*!
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_from_);
    /*!
     * Declare required pointers 
     */
    std::shared_ptr<BANK> _TO_BANK_, _FROM_BANK_;
    std::shared_ptr<OSTM> _TO_OSTM_, _FROM_OSTM_;

    bool done = false;
    try {
        while (!done) {
            /*!
             * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
             */
            _TO_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
            /*!
             * Make changes with the objects
             */
            _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
            _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
            /*!
             * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
             */
            _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
            _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
            /*!
             * Store changes
             */
            tx->store(_TO_OSTM_);
            tx->store(_FROM_OSTM_);

            /*!
             * Commit changes
             */
            done = tx->commit();
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

/*!
 * \brief _nesting_ function, takes two std::shared_ptr<OSTM> pointer, the Transaction manager, and the amount to use in the transaction and transfer the _amount value from one account to the another account
 * This function create nested transactions inside the transaction, and call other function to nesting the transaction as well  
 * \param  std::shared_ptr<TX> tx, Transaction Object
 * \param std::shared_ptr<BANK> type, _TO_BANK_ & _FROM_BANK_
 * \param std::shared_ptr<OSTM> type, _TO_OSTM_ & _FROM_OSTM_
 */
void _nesting_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /*!
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_from_);
    /*!
     * Declare required pointers 
     */
    std::shared_ptr<BANK> _TO_BANK_, _FROM_BANK_;
    std::shared_ptr<OSTM> _TO_OSTM_, _FROM_OSTM_;


    bool done = false;
    try {
        while (!done) {
            /*!
             * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
             */
            _TO_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
            /*!
             * Make changes with the objects
             */
            _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
            _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
            /*!
             * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
             */
            _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
            _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
            /*!
             * Store changes
             */
            tx->store(_TO_OSTM_);
            tx->store(_FROM_OSTM_);

            /*!
             * NESTED TRANSACTION
             */
            std::shared_ptr<TX> txTwo = _tm._get_tx();

            bool nestedDone = false;
            while (!nestedDone) {
                _TO_BANK_ = std::dynamic_pointer_cast<BANK> (txTwo->load(_to_));
                _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (txTwo->load(_from_));
                /*!
                 * Make changes with the objects
                 */
                _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
                _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
                /*!
                 * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
                 */
                _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
                _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
                /*!
                 * Store changes
                 */
                txTwo->store(_TO_OSTM_);
                txTwo->store(_FROM_OSTM_);
                /*!
                 * NESTED TRANSACTION IN THE NESTED TRANSACTION
                 * _two_account_transfer_ function call
                 */
                _two_account_transfer_(_to_, _from_, _tm, _amount);

                nestedDone = txTwo->commit();
            }

            /*!
             * Commit changes
             */
            done = tx->commit();
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

/*!
 * main method to run test
 */
int main(void) {
    /*!
     * Get the Transaction Manager<br>
     * TM& tm = TM::Instance();<br>
     */
    TM& tm = TM::Instance();


    /*!
     * Create objects type of BANK. All object will have unique ID by default<br>
     * std::shared_ptr<OSTM> aib_ptr    = new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny");<br>
     * std::shared_ptr<OSTM> boi_ptr    = new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny");<br>
     * std::shared_ptr<OSTM> boa_ptr    = new BOA(300, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny");<br>
     * std::shared_ptr<OSTM> swplc_ptr  = new SWBPLC(400, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny");<br>
     * std::shared_ptr<OSTM> ulster_ptr = new ULSTER(500, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny");<br>
     * std::shared_ptr<OSTM> unbl_ptr   = new UNBL(600, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny");<br>
     */
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boa_ptr(new BOA(300, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> swplc_ptr(new SWBPLC(400, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> ulster_ptr(new ULSTER(500, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> unbl_ptr(new UNBL(600, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));

 
    /*!
     * Display BANK objects before transaction<br>
     * aib_ptr->toString();<br>
     * boi_ptr->toString();<br>
     * boa_ptr->toString();<br>
     * swplc_ptr->toString();<br>
     * ulster_ptr->toString();<br>
     * unbl_ptr->toString();<br>
     */

    /*
     * TEST 1 : object requirements
     */
    aib_ptr->toString();
    boi_ptr->toString();
    boa_ptr->toString();
    swplc_ptr->toString();
    ulster_ptr->toString();
    unbl_ptr->toString();

    /*!
     * \param transferAmount in the transaction, control the value in the transaction between objetcs
     */
    int transferAmount = 1;
    /*!
     * \param threadArraySize control number of threads <br>
     * The logic in the IF ELSE statement distribute the threads between three different thread creating option.<br>
     * If the threadArraySize is divisible with three, the threads will be distributed between function.<br>
     * However, you can creates any number of threads, but to follow the correct output should increase the IF ELSE statement to distribute the threads in equal number. 
     */
    int threadArraySize = 3000;
    std::thread thArray[3000];

    /*!
     * Creating threads^n -> threadArraySize<br>
     * for (int i = 0; i < threadArraySize; ++i)<br>
     */
    for (int i = 0; i < threadArraySize; ++i) {

        /*!
         * \brief TEST 1 : Nested transaction Test<br>
         * thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
         * thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
         * thArray[i] = std::thread(_six_account_transfer_, aib_ptr, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, unbl_ptr, std::ref(tm), transferAmount);
         */
//		thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
//      thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
 //       if (i % 3 == 0)
//			thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
			//thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
//        else if (i % 2 == 0)
//            thArray[i] = std::thread(_nesting_, boa_ptr, swplc_ptr, std::ref(tm), transferAmount);
//       else if (i % 1 == 0)
//            thArray[i] = std::thread(_nesting_, ulster_ptr, unbl_ptr, std::ref(tm), transferAmount);

       if (i % 3 == 0)
			thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
		//thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
	   else if (i % 2 == 0)
		   thArray[i] = std::thread(_two_account_transfer_, boa_ptr, swplc_ptr, std::ref(tm), transferAmount);
		//            thArray[i] = std::thread(_nesting_, boa_ptr, swplc_ptr, std::ref(tm), transferAmount);
       else if (i % 1 == 0)
		   thArray[i] = std::thread(_two_account_transfer_, aib_ptr, unbl_ptr, std::ref(tm), transferAmount);
		//            thArray[i] = std::thread(_nesting_, ulster_ptr, unbl_ptr, std::ref(tm), transferAmount);

    }
    /*
     * Join threads^n -> threadArraySize<br>
     * thArray[i].join();
     */
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }


    std::cout << "\nMain process print " << std::endl;
    /*!
     * Display objects after all transactions are finished<br>
     * Uncomment the required corresponding TEST to display results
     */

    /*
     * TEST 1 : object requirements
     */
    aib_ptr->toString();
    boi_ptr->toString();
    boa_ptr->toString();
    swplc_ptr->toString();
    ulster_ptr->toString();
    unbl_ptr->toString();
   
	std::cout << "\nMain process exit " << std::endl;
	int t = 0;
	std::cin >> t;
    return 0;
}
