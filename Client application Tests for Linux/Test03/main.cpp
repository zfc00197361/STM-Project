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
 * \brief _warehouse_transfer_ function, takes two std::shared_ptr<OSTM> pointer, the Transaction manager, and the amount to use in the transaction and transfer the _amount value from one account to the another account
 * \param  std::shared_ptr<TX> tx, Transaction Object
 * \param std::shared_ptr<WAREHOUSE> type, _TO_SHOP_ & _FROM_DIST_
 * \param std::shared_ptr<OSTM> type, _TO_OSTM_ & _FROM_OSTM_
 */
void _warehouse_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /*!
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_from_);
    /*!
     * Declare required pointers 
     */
    std::shared_ptr<WAREHOUSE> _TO_SHOP_, _FROM_DIST_;
    std::shared_ptr<OSTM> _TO_OSTM_, _FROM_OSTM_;

    bool done = false;
    try {
        while (!done) {
            /*!
             * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
             */
            _TO_SHOP_ = std::dynamic_pointer_cast<WAREHOUSE> (tx->load(_to_));
            _FROM_DIST_ = std::dynamic_pointer_cast<WAREHOUSE> (tx->load(_from_));
            /*!
             * Make changes with the objects
             */
            _TO_SHOP_->SetNumber_of_nokia(_TO_SHOP_->GetNumber_of_nokia() + _amount);
            _FROM_DIST_->SetNumber_of_nokia(_FROM_DIST_->GetNumber_of_nokia() - _amount);

            _TO_SHOP_->SetNumber_of_samsung(_TO_SHOP_->GetNumber_of_samsung() + _amount);
            _FROM_DIST_->SetNumber_of_samsung(_FROM_DIST_->GetNumber_of_samsung() - _amount);

            _TO_SHOP_->SetNumber_of_iphones(_TO_SHOP_->GetNumber_of_iphones() + _amount);
            _FROM_DIST_->SetNumber_of_iphones(_FROM_DIST_->GetNumber_of_iphones() - _amount);

            _TO_SHOP_->SetNumber_of_sony(_TO_SHOP_->GetNumber_of_sony() + _amount);
            _FROM_DIST_->SetNumber_of_sony(_FROM_DIST_->GetNumber_of_sony() - _amount);
            /*!
             * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
             */
            _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_SHOP_);
            _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_DIST_);
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
 * main method to run test
 */
int main(void) {
    /*!
     * Get the Transaction Manager<br>
     * TM& tm = TM::Instance();<br>
     */
    TM& tm = TM::Instance();

    /*!
     * Create objects type of WAREHOUSE. All object will have unique ID by default<br>
     * std::shared_ptr<OSTM> w_dist = new CARPHONE_WAREHOUSE();<br>
     * std::shared_ptr<OSTM> c_shop = new CARLOW_W();<br>
     * std::shared_ptr<OSTM> k_shop = new KILKENNY_W();<br>
     * std::shared_ptr<OSTM> t_shop = new TALLAGH_W();<br>
     * std::shared_ptr<OSTM> d_shop = new DUNDALK_W();<br>
     * std::shared_ptr<OSTM> s_shop = new SLIGO_W();<br>
     */

    std::shared_ptr<OSTM> w_dist(new CARPHONE_WAREHOUSE());
    std::shared_ptr<OSTM> c_shop(new CARLOW_W());
    std::shared_ptr<OSTM> k_shop(new KILKENNY_W());
    std::shared_ptr<OSTM> t_shop(new TALLAGH_W());
    std::shared_ptr<OSTM> d_shop(new DUNDALK_W());
    std::shared_ptr<OSTM> s_shop(new SLIGO_W());

    /*
     * TEST 3 : object requirements
     */
        w_dist->toString();
        c_shop->toString();
        k_shop->toString();
        t_shop->toString();
        d_shop->toString();
        s_shop->toString();

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
    int threadArraySize = 300;
    std::thread thArray[threadArraySize];

    /*!
     * Creating threads^n -> threadArraySize<br>
     * for (int i = 0; i < threadArraySize; ++i)<br>
     */
    for (int i = 0; i < threadArraySize; ++i) {


        /*!
         * \brief TEST 3 : Testing WAREHOUSE type pointers within transactions<br>
         * thArray[i] = std::thread(_phone_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);
         */
       // thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);

        if (i % 3 == 0)
            thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);
        else if (i % 2 == 0)
            thArray[i] = std::thread(_warehouse_transfer_, k_shop, w_dist, std::ref(tm), transferAmount);
        else if (i % 1 == 0)
            thArray[i] = std::thread(_warehouse_transfer_, t_shop, w_dist, std::ref(tm), transferAmount);

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
     * TEST 3 : object requirements
     */
        w_dist->toString();
        c_shop->toString();
        k_shop->toString();
        t_shop->toString();
        d_shop->toString();
        s_shop->toString();
                
    std::cout << "\nMAIN PROCESS EXIT !!!! " << std::endl;
    /*!
     * Extra tx to call and display ROLLBACK value<br>
     * std::shared_ptr<TX> tx = tm._get_tx();<br>
     */
    std::shared_ptr<TX> tx = tm._get_tx();

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
