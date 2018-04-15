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
 * \param vector_number control the size of the vector to store std::shared_ptr<OSTM> pointer
 */
static int vector_number = 30;

/*!
 * \brief _six_account_transfer_ function, takes six std::shared_ptr<OSTM> pointer, the Transaction manager, and the amount to use in the transaction and transfer the _amount value from five account to one account
 * \param  std::shared_ptr<TX> tx, Transaction Object
 * \param std::shared_ptr<BANK> type, _TO_ & _FROM_ONE_ & _FROM_TWO_ & _FROM_THREE_ & _FROM_FOUR_ & _FROM_FIVE_
 * \param std::shared_ptr<OSTM> type, _TO_OSTM & _FROM_ONE_OSTM & _FROM_TWO_OSTM & _FROM_THREE_OSTM & _FROM_FOUR_OSTM & _FROM_FIVE_OSTM
 */
void _six_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_one_, std::shared_ptr<OSTM> _from_two_, std::shared_ptr<OSTM> _from_three_, std::shared_ptr<OSTM> _from_four_, std::shared_ptr<OSTM> _from_five_, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /*!
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_from_one_);
    tx->_register(_from_two_);
    tx->_register(_from_three_);
    tx->_register(_from_four_);
    tx->_register(_from_five_);

    /*!
     * Required pointers to use in transaction
     */
    std::shared_ptr<OSTM> _TO_OSTM, _FROM_ONE_OSTM, _FROM_TWO_OSTM, _FROM_THREE_OSTM, _FROM_FOUR_OSTM, _FROM_FIVE_OSTM;
    std::shared_ptr<BANK> _TO_, _FROM_ONE_, _FROM_TWO_, _FROM_THREE_, _FROM_FOUR_, _FROM_FIVE_;
    try {
        bool done = false;
        while (!done) {
            /*!
             * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
             */
            _TO_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            _FROM_ONE_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_one_));
            _FROM_TWO_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_two_));
            _FROM_THREE_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_three_));
            _FROM_FOUR_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_four_));
            _FROM_FIVE_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_five_));
            /*!
             * Make changes with the objects
             */
            _TO_->SetBalance(_TO_->GetBalance() + (_amount * 5));
            _FROM_ONE_->SetBalance(_FROM_ONE_->GetBalance() - _amount);
            _FROM_TWO_->SetBalance(_FROM_TWO_->GetBalance() - _amount);
            _FROM_THREE_->SetBalance(_FROM_THREE_->GetBalance() - _amount);
            _FROM_FOUR_->SetBalance(_FROM_FOUR_->GetBalance() - _amount);
            _FROM_FIVE_->SetBalance(_FROM_FIVE_->GetBalance() - _amount);
            /*!
             * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
             */
            _TO_OSTM = std::dynamic_pointer_cast<OSTM> (_TO_);
            _FROM_ONE_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_ONE_);
            _FROM_TWO_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_TWO_);
            _FROM_THREE_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_THREE_);
            _FROM_FOUR_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_FOUR_);
            _FROM_FIVE_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_FIVE_);
            /*!
             * Store changes
             */
            tx->store(_TO_OSTM);
            tx->store(_FROM_ONE_OSTM);
            tx->store(_FROM_TWO_OSTM);
            tx->store(_FROM_THREE_OSTM);
            tx->store(_FROM_FOUR_OSTM);
            tx->store(_FROM_FIVE_OSTM);
            /*!
             * Commit changes
             */
                 /*!
             * NESTED TRANSACTION
             */
            std::shared_ptr<TX> txTwo = _tm._get_tx();

            bool nestedDone = false;
            while (!nestedDone) {
                _TO_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
                _FROM_ONE_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_one_));
                /*!
                 * Make changes with the objects
                 */
                _TO_->SetBalance(_TO_->GetBalance() + (_amount * 5));
                _FROM_ONE_->SetBalance(_FROM_ONE_->GetBalance() - _amount);
                /*!
                 * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
                 */
                _TO_OSTM = std::dynamic_pointer_cast<OSTM> (_TO_);
                _FROM_ONE_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_ONE_);
                /*!
                 * Store changes
                 */
                txTwo->store(_TO_OSTM);
                txTwo->store(_FROM_ONE_OSTM);
                /*!
                 * Commit changes
                 */
                nestedDone = txTwo->commit();
            }
            done = tx->commit();
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

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
             * NESTED TRANSACTION
             */
//            std::shared_ptr<TX> txTwo = _tm._get_tx();
//
//            bool nestedDone = false;
//            while (!nestedDone) {
//                _TO_BANK_ = std::dynamic_pointer_cast<BANK> (txTwo->load(_to_));
//                _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (txTwo->load(_from_));
//                /*!
//                 * Make changes with the objects
//                 */
//                _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
//                _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
//                /*!
//                 * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
//                 */
//                _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
//                _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
//                /*!
//                 * Store changes
//                 */
//                txTwo->store(_TO_OSTM_);
//                txTwo->store(_FROM_OSTM_);
//                /*!
//                 * Commit changes
//                 */
//                nestedDone = txTwo->commit();
//            }
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
 * \brief _complex_transfer_ function, takes two std::shared_ptr<OSTM> pointer, a vector of std::shared_ptr<OSTM> pointers, the Transaction manager, and the amount to use in the transaction, and transfer the _amount value from booth single
 * objects to the objects to the vector collection
 * \param  std::shared_ptr<TX> tx, Transaction Object
 * \param std::shared_ptr<BANK> type, _FROM_ & _FROM_TWO_ & _TO_
 * \param std::shared_ptr<OSTM> type, _FROM_OSTM_ONE_ & _FROM_OSTM_TWO_ & _TO_OSTM_
 */
void _complex_transfer_(std::shared_ptr<OSTM> _from_, std::shared_ptr<OSTM> _from_two_, std::vector<std::shared_ptr<OSTM>> _customer_vec, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /** Register the two single account*/
    tx->_register(_from_);
    tx->_register(_from_two_);
    /** Declare required pointers */
    std::shared_ptr<OSTM> _FROM_OSTM_ONE_, _FROM_OSTM_TWO_, _TO_OSTM_;
    std::shared_ptr<BANK> _FROM_, _FROM_TWO_, _TO_;

    bool done = false;
    try {
        while (!done) {
            for (auto&& obj : _customer_vec) {
                /** Register customers accounts from the collection (vector) */
                tx->_register(obj);
                /** From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods  */
                _FROM_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
                _FROM_TWO_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_two_));
                _TO_ = std::dynamic_pointer_cast<BANK> (tx->load(obj));
                /** Make changes with the objects */
                _FROM_->SetBalance(_FROM_->GetBalance() - _amount);
                _FROM_TWO_->SetBalance(_FROM_TWO_->GetBalance() - _amount);
                _TO_->SetBalance(_TO_->GetBalance() + (_amount * 2));
                /** From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces */
                _FROM_OSTM_ONE_ = std::dynamic_pointer_cast<OSTM> (_FROM_);
                _FROM_OSTM_TWO_ = std::dynamic_pointer_cast<OSTM> (_FROM_TWO_);
                _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_);
                /** Store changes */
                tx->store(_FROM_OSTM_ONE_);
                tx->store(_FROM_OSTM_TWO_);
                tx->store(_TO_OSTM_);
            }
            /** Commit changes */
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
     * Create vector to store std::shared_ptr<OSTM> pointers. All object will have unique ID by default<br>
     *  std::vector<std::shared_ptr<OSTM>> _customer_vec(vector_number);<br>
     *  std::vector<std::shared_ptr<OSTM>> _warehouse_vec(vector_number);<br>
     */

    std::vector<std::shared_ptr < OSTM>>_customer_vec; //(vector_number);

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
     * Create vector of std::shared_ptr<OSTM> WAREHOUSE pointers<br>
     * vector_number is 100 at the moment<br>
     * for(int i=0;i<vector_number;++i)
     */
    for (int i = 0; i < vector_number; ++i) {
        if (i % 6 == 0) {
            std::shared_ptr<OSTM> sharedptr(new AIB(i, 50, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 5 == 0) {
            std::shared_ptr<OSTM> sharedptr(new BOI(i, 50, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 4 == 0) {
            std::shared_ptr<OSTM> sharedptr(new BOA(i, 50, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 3 == 0) {
            std::shared_ptr<OSTM> sharedptr(new SWBPLC(i, 50, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 2 == 0) {
            std::shared_ptr<OSTM> sharedptr(new ULSTER(i, 50, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 1 == 0) {
            std::shared_ptr<OSTM> sharedptr(new UNBL(i, 50, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        }
    }


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
     * TEST 2 : object requirements 
     */
        aib_ptr->toString();
        boi_ptr->toString();
        boa_ptr->toString();
        swplc_ptr->toString();
        ulster_ptr->toString();
        unbl_ptr->toString();
//        for(int i=0; i<vector_number; ++i){
//            _customer_vec[i]->toString();
//        }

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
    int threadArraySize = 8;
    std::thread thArray[threadArraySize];

    /*!
     * Creating threads^n -> threadArraySize<br>
     * for (int i = 0; i < threadArraySize; ++i)<br>
     */
    for (int i = 0; i < threadArraySize; ++i) {


        /*!
         * \brief TEST 2 :Three different type of function call where the objects are participating in multiple type of transactions<br>
         * thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);<br>
         * thArray[i] = std::thread(_six_account_transfer_, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, aib_ptr, unbl_ptr, std::ref(tm), transferAmount)<br>
         * thArray[i] = std::thread(_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);
         */
    //    thArray[i] = std::thread(_six_account_transfer_, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, aib_ptr, unbl_ptr, std::ref(tm), transferAmount);
    
        //thArray[i] = std::thread(_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);
//            if (i % 3 == 0) 
 //              thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
//            else if (i % 2 == 0)
//                thArray[i] = std::thread(_six_account_transfer_, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, aib_ptr, unbl_ptr, std::ref(tm), transferAmount);
//            else if (i % 1 == 0)
                thArray[i] = std::thread(_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);

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
     * TEST 2 : object requirements 
     */
        aib_ptr->toString();
        boi_ptr->toString();
        boa_ptr->toString();
        swplc_ptr->toString();
        ulster_ptr->toString();
        unbl_ptr->toString();
//        for(int i=0; i<vector_number; ++i){
//            _customer_vec[i]->toString();
//        }


    std::cout << "\nMAIN PROCESS EXIT !!!! " << std::endl;
    /*!
     * Extra tx to call and display ROLLBACK value<br>
     * std::shared_ptr<TX> tx = tm._get_tx();<br>
     */
    std::shared_ptr<TX> tx = tm._get_tx();

    /*!
     * Display the number of ROLLBACK by all the threads <br>
     * std::cout << "Rollback counter is : " << tx->getTest_counter() << std::endl;
     */
    std::cout << "Rollback counter is : " << tx->getTest_counter() << std::endl;

    /*!
     * Clean up Transaction Manager from all main process associated transactions<br>
     * tm._TX_EXIT();
     */
    tm._TX_EXIT();
    std::cout << "\nPRINT ALL FROM TM !!!! SHOULD BE EMPTY AFTER _TX_EXIT() !!" << std::endl;
    /*!
     * Display all Transactions associated with the main process. It should be empty after _TX_EXIT() function call!!!<br>
     * tm.print_all();
     */
    tm.print_all();

    return 0;
}
