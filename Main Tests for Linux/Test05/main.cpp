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
static int vector_number = 600;

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
 * \brief _nested_warehouse_transfer_ function, takes three std::shared_ptr<OSTM> pointer, the Transaction manager, and the amount to use in the transaction and transfer the _amount value from one account to the another account
 * \param  std::shared_ptr<TX> tx, Transaction Object
 * \param std::shared_ptr<WAREHOUSE> type, _TO_SHOP_ & _FROM_DIST_
 * \param std::shared_ptr<OSTM> type, _TO_OSTM_ & _FROM_OSTM_
 */
void _nested_warehouse_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _to_two, std::shared_ptr<OSTM> _to_three, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /*!
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_to_two);
    tx->_register(_to_three);
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
             * NESTED WAREHOUSE TEST _to_two
             */
            std::shared_ptr<TX> txTwo = _tm._get_tx();
            bool nestedDone = false;
            while (!nestedDone) {
                _TO_SHOP_ = std::dynamic_pointer_cast<WAREHOUSE> (txTwo->load(_to_two));
                _FROM_DIST_ = std::dynamic_pointer_cast<WAREHOUSE> (txTwo->load(_from_));
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
                txTwo->store(_TO_OSTM_);
                txTwo->store(_FROM_OSTM_);

                /*
                 * NESTED TRANSACTION TEST _to_three
                 */
                _warehouse_transfer_(_to_three, _from_, _tm, _amount);


                nestedDone = tx->commit();
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

void _complex_warehouse_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _to_two, std::shared_ptr<OSTM> _to_three, std::vector<std::shared_ptr<OSTM>> _warehouse_vec, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /*!
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_to_two);
    tx->_register(_to_three);
    tx->_register(_from_);
    /*!
     * Declare required pointers 
     */
    std::shared_ptr<WAREHOUSE> _TO_SHOP_, _TO_SHOP_TWO, _TO_SHOP_VEC, _FROM_DIST_;
    std::shared_ptr<OSTM> _TO_OSTM_, _TO_OSTM_TWO, _TO_OSTM_VEC, _FROM_OSTM_;

    bool done = false;
    try {
        while (!done) {

            // for (int i = 0; i < vector_number; ++i) {
            for (auto&& obj : _warehouse_vec) {
                /*!
                 * Register customers accounts from the collection (vector) 
                 */
                //auto&& obj = _warehouse_vec.at(i);
                tx->_register(obj);
                /*!
                 * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
                 */
                _TO_SHOP_ = std::dynamic_pointer_cast<WAREHOUSE> (tx->load(_to_));
                _TO_SHOP_TWO = std::dynamic_pointer_cast<WAREHOUSE> (tx->load(_to_two));
                _TO_SHOP_VEC = std::dynamic_pointer_cast<WAREHOUSE> (tx->load(obj));
                _FROM_DIST_ = std::dynamic_pointer_cast<WAREHOUSE> (tx->load(_from_));

                /*!
                 * Make changes with the objects
                 */
                _TO_SHOP_->SetNumber_of_nokia(_TO_SHOP_->GetNumber_of_nokia() + _amount);
                _TO_SHOP_TWO->SetNumber_of_nokia(_TO_SHOP_TWO->GetNumber_of_nokia() + _amount);
                _TO_SHOP_VEC->SetNumber_of_nokia(_TO_SHOP_VEC->GetNumber_of_nokia() + _amount);
                _FROM_DIST_->SetNumber_of_nokia(_FROM_DIST_->GetNumber_of_nokia() - (_amount * 3));

                _TO_SHOP_->SetNumber_of_samsung(_TO_SHOP_->GetNumber_of_samsung() + _amount);
                _TO_SHOP_TWO->SetNumber_of_samsung(_TO_SHOP_TWO->GetNumber_of_samsung() + _amount);
                _TO_SHOP_VEC->SetNumber_of_samsung(_TO_SHOP_VEC->GetNumber_of_samsung() + _amount);
                _FROM_DIST_->SetNumber_of_samsung(_FROM_DIST_->GetNumber_of_samsung() - (_amount * 3));

                _TO_SHOP_->SetNumber_of_iphones(_TO_SHOP_->GetNumber_of_iphones() + _amount);
                _TO_SHOP_TWO->SetNumber_of_iphones(_TO_SHOP_TWO->GetNumber_of_iphones() + _amount);
                _TO_SHOP_VEC->SetNumber_of_iphones(_TO_SHOP_VEC->GetNumber_of_iphones() + _amount);
                _FROM_DIST_->SetNumber_of_iphones(_FROM_DIST_->GetNumber_of_iphones() - (_amount * 3));

                _TO_SHOP_->SetNumber_of_sony(_TO_SHOP_->GetNumber_of_sony() + _amount);
                _TO_SHOP_TWO->SetNumber_of_sony(_TO_SHOP_TWO->GetNumber_of_sony() + _amount);
                _TO_SHOP_VEC->SetNumber_of_sony(_TO_SHOP_VEC->GetNumber_of_sony() + _amount);
                _FROM_DIST_->SetNumber_of_sony(_FROM_DIST_->GetNumber_of_sony() - (_amount * 3));

                /*!
                 * From std::shared_ptr<WAREHOUSE> to std::shared_ptr<OSTM> to store the memory spaces
                 */
                _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_SHOP_);
                _TO_OSTM_TWO = std::dynamic_pointer_cast<OSTM> (_TO_SHOP_TWO);
                _TO_OSTM_VEC = std::dynamic_pointer_cast<OSTM> (_TO_SHOP_VEC);
                _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_DIST_);
                /*!
                 * Store changes
                 */
                tx->store(_TO_OSTM_);
                tx->store(_TO_SHOP_TWO);
                tx->store(_TO_SHOP_VEC);
                tx->store(_FROM_OSTM_);



            }
            /*!
             * NESTED WAREHOUSE TEST _to_two
             */
            std::shared_ptr<TX> txTwo = _tm._get_tx();
            bool nestedDone = false;
            while (!nestedDone) {
                _TO_SHOP_ = std::dynamic_pointer_cast<WAREHOUSE> (txTwo->load(_to_two));
                _FROM_DIST_ = std::dynamic_pointer_cast<WAREHOUSE> (txTwo->load(_from_));
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
                txTwo->store(_TO_OSTM_);
                txTwo->store(_FROM_OSTM_);

                /*
                 * NESTED TRANSACTION TEST _to_three
                 */
                _warehouse_transfer_(_to_three, _from_, _tm, _amount);
                _nested_warehouse_transfer_(_to_, _to_two, _to_three, _from_, _tm, _amount);

                nestedDone = tx->commit();
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
     * Create vector to store std::shared_ptr<OSTM> pointers. All object will have unique ID by default<br>
     *  std::vector<std::shared_ptr<OSTM>> _warehouse_vec(vector_number);<br>
     */

    std::vector<std::shared_ptr < OSTM>>_warehouse_vec; //(vector_number);


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

    /*!
     * Create vector of std::shared_ptr<OSTM> BANK pointers<br>
     * vector_number is 100 at the moment<br>
     * for(int i=0;i<vector_number;++i)
     */
    for (int i = 0; i < vector_number; ++i) {
        if (i % 5 == 0) {
            std::shared_ptr<OSTM> sharedptr(new CARLOW_W());
            _warehouse_vec.push_back(std::move(sharedptr));
        } else if (i % 4 == 0) {
            std::shared_ptr<OSTM> sharedptr(new KILKENNY_W());
            _warehouse_vec.push_back(std::move(sharedptr));
        } else if (i % 3 == 0) {
            std::shared_ptr<OSTM> sharedptr(new TALLAGH_W());
            _warehouse_vec.push_back(std::move(sharedptr));
        } else if (i % 2 == 0) {
            std::shared_ptr<OSTM> sharedptr(new DUNDALK_W());
            _warehouse_vec.push_back(std::move(sharedptr));
        } else if (i % 1 == 0) {
            std::shared_ptr<OSTM> sharedptr(new SLIGO_W());
            _warehouse_vec.push_back(std::move(sharedptr));
        }
    }

    /*
     * TEST 5 : objects requirements
     * Display WAREHOUSE objects before transaction<br>
     * w_dist->toString();<br>
     * c_shop->toString();<br>
     * k_shop->toString();<br>
     * t_shop->toString();<br>
     * d_shop->toString();<br>
     * s_shop->toString();<br>
     */
     
            w_dist->toString();
            c_shop->toString();
            k_shop->toString();
            t_shop->toString();
            d_shop->toString();
            s_shop->toString();

//            for(auto&& elem: _warehouse_vec){
//                elem->toString(); // virtual dispatch
//                
//            }



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
         * \brief TEST 5 : Testing WAREHOUSE type pointers within mixed and nested transactions<br>
         * thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);<br>
         * thArray[i] = std::thread(_nested_warehouse_transfer_, c_shop, d_shop, k_shop, w_dist, std::ref(tm), transferAmount);<br>
         * thArray[i] = std::thread(_complex_warehouse_transfer_, d_shop, c_shop, std::ref(_warehouse_vec), w_dist, std::ref(tm), transferAmount);<br>
         * 
         */
       // thArray[i] = std::thread(_complex_warehouse_transfer_, d_shop, s_shop, c_shop, std::ref(_warehouse_vec), w_dist, std::ref(tm), transferAmount);

                if (i % 3 == 0)
                    thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);
                else if (i % 2 == 0)
                    thArray[i] = std::thread(_nested_warehouse_transfer_, k_shop, s_shop, t_shop, w_dist, std::ref(tm), transferAmount);
                else if (i % 1 == 0)
                    thArray[i] = std::thread(_complex_warehouse_transfer_, d_shop, s_shop, c_shop, std::ref(_warehouse_vec), w_dist, std::ref(tm), transferAmount);


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
     * TEST 5 : objects requirements
     */
            w_dist->toString();
            c_shop->toString();
            k_shop->toString();
            t_shop->toString();
            d_shop->toString();
            s_shop->toString();

//            for(auto&& elem: _warehouse_vec){
//                elem->toString(); // virtual dispatch
//                
//            }
            _warehouse_vec[200]->toString();
    /* TEST 5 FINISH */


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
