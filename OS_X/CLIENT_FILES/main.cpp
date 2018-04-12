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
                 * Commit changes
                 */
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
 * \brief _complex_transfer_ function, takes two std::shared_ptr<OSTM> pointer, a vector of std::shared_ptr<OSTM> pointers, the Transaction manager, and the amount to use in the transaction, and transfer the _amount value from booth single
 * objects to the objects to the vector collection
 * \param  std::shared_ptr<TX> tx, Transaction Object
 * \param std::shared_ptr<BANK> type, _FROM_ & _FROM_TWO_ & _TO_
 * \param std::shared_ptr<OSTM> type, _FROM_OSTM_ONE_ & _FROM_OSTM_TWO_ & _TO_OSTM_
 */
void _complex_transfer_(std::shared_ptr<OSTM> _from_, std::shared_ptr<OSTM> _from_two_, std::vector<std::shared_ptr<OSTM>> _customer_vec, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /*!
     * Register the two single account
     */
    tx->_register(_from_);
    
    tx->_register(_from_two_);
    /*!
     * Declare required pointers 
     */
    std::shared_ptr<OSTM> _FROM_OSTM_ONE_, _FROM_OSTM_TWO_, _TO_OSTM_;
    std::shared_ptr<BANK> _FROM_, _FROM_TWO_, _TO_;

    bool done = false;
    try {
        while (!done) {
            // for (int i = 0; i < vector_number; ++i) {
            for (auto&& obj : _customer_vec) {
                /*!
                 * Register customers accounts from the collection (vector) 
                 */
                // auto&& obj = _customer_vec.at(i);
                tx->_register(obj);
                /*!
                 * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
                 */
                _FROM_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
                _FROM_TWO_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_two_));
                _TO_ = std::dynamic_pointer_cast<BANK> (tx->load(obj));
                /*!
                 * Make changes with the objects
                 */
                _FROM_->SetBalance(_FROM_->GetBalance() - _amount);
                _FROM_TWO_->SetBalance(_FROM_TWO_->GetBalance() - _amount);
                _TO_->SetBalance(_TO_->GetBalance() + (_amount * 2));
                /*!
                 * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
                 */
                _FROM_OSTM_ONE_ = std::dynamic_pointer_cast<OSTM> (_FROM_);
                _FROM_OSTM_TWO_ = std::dynamic_pointer_cast<OSTM> (_FROM_TWO_);
                _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_);
                /*!
                 * Store changes
                 */
                tx->store(_FROM_OSTM_ONE_);
                tx->store(_FROM_OSTM_TWO_);
                tx->store(_TO_OSTM_);
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
     *  std::vector<std::shared_ptr<OSTM>> _customer_vec(vector_number);<br>
     *  std::vector<std::shared_ptr<OSTM>> _warehouse_vec(vector_number);<br>
     */

    std::vector<std::shared_ptr < OSTM>>_customer_vec; //(vector_number);
    std::vector<std::shared_ptr < OSTM>>_warehouse_vec; //(vector_number);

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
     * Display WAREHOUSE objects before transaction<br>
     * w_dist->toString();<br>
     * c_shop->toString();<br>
     * k_shop->toString();<br>
     * t_shop->toString();<br>
     * d_shop->toString();<br>
     * s_shop->toString();<br>
     */
    //    w_dist->toString();
    //    c_shop->toString();
    //    k_shop->toString();
    //    t_shop->toString();
    //    d_shop->toString();
    //    s_shop->toString();

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

    /*
     * TEST 2 : object requirements 
     */
    //    aib_ptr->toString();
    //    boi_ptr->toString();
    //    boa_ptr->toString();
    //    swplc_ptr->toString();
    //    ulster_ptr->toString();
    //    unbl_ptr->toString();
    //    for(int i=0; i<vector_number; ++i){
    //        _customer_vec[i]->toString();
    //    }

    /*
     * TEST 3 : object requirements
     */
    //    w_dist->toString();
    //    c_shop->toString();
    //    k_shop->toString();
    //    t_shop->toString();

    /*
     * TEST 4 : objects requirements
     */
    //        w_dist->toString();
    //        c_shop->toString();
    //        k_shop->toString();
    //        t_shop->toString();
    //        d_shop->toString();
    //        s_shop->toString();


    /*
     * TEST 5 : objects requirements
     */
    //        w_dist->toString();
    //        c_shop->toString();
    //        k_shop->toString();
    //        t_shop->toString();
    //        d_shop->toString();
    //        s_shop->toString();

    //        for(auto&& elem: _warehouse_vec){
    //            elem->toString(); // virtual dispatch
    //            
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
    int threadArraySize = 30;
    std::thread thArray[30];

    /*!
     * Creating threads^n -> threadArraySize<br>
     * for (int i = 0; i < threadArraySize; ++i)<br>
     */
    for (int i = 0; i < threadArraySize; ++i) {

        /*!
         * \brief TEST 1 : Nested transaction Test<br>
         * thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
         */
        thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
 //       if (i % 3 == 0)
 //           thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
 //       else if (i % 2 == 0)
 //           thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
 //       else if (i % 1 == 0)
 //           thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);

        /*!
         * \brief TEST 2 :Three different type of function call where the objects are participating in multiple type of transactions<br>
         * thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);<br>
         * thArray[i] = std::thread(_six_account_transfer_, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, aib_ptr, unbl_ptr, std::ref(tm), transferAmount)<br>
         * thArray[i] = std::thread(_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);
         */
        //    if (i % 3 == 0) 
        //        thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
        //    else if (i % 2 == 0)
        //        thArray[i] = std::thread(_six_account_transfer_, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, aib_ptr, unbl_ptr, std::ref(tm), transferAmount);
        //    else if (i % 1 == 0)
        //        thArray[i] = std::thread(_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);


        /*!
         * \brief TEST 3 : Testing WAREHOUSE type pointers within transactions<br>
         * thArray[i] = std::thread(_phone_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);
         */
        //        if (i % 3 == 0)
        //            thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);
        //        else if (i % 2 == 0)
        //            thArray[i] = std::thread(_warehouse_transfer_, k_shop, w_dist, std::ref(tm), transferAmount);
        //        else if (i % 1 == 0)
        //            thArray[i] = std::thread(_warehouse_transfer_, t_shop, w_dist, std::ref(tm), transferAmount);

        /*!
         * \brief TEST 4 : Testing WAREHOUSE type pointers within nested transactions<br>
         * thArray[i] = std::thread(_nested_warehouse_transfer_, c_shop, d_shop, k_shop, w_dist, std::ref(tm), transferAmount);
         */
        //        if (i % 3 == 0)
        //            thArray[i] = std::thread(_nested_warehouse_transfer_, c_shop, d_shop, k_shop, w_dist, std::ref(tm), transferAmount);
        //        else if (i % 2 == 0)
        //            thArray[i] = std::thread(_nested_warehouse_transfer_, k_shop, s_shop, t_shop, w_dist, std::ref(tm), transferAmount);
        //        else if (i % 1 == 0)
        //            thArray[i] = std::thread(_nested_warehouse_transfer_, t_shop, c_shop, s_shop, w_dist, std::ref(tm), transferAmount);

        /*!
         * \brief TEST 5 : Testing WAREHOUSE type pointers within mixed and nested transactions<br>
         * thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);<br>
         * thArray[i] = std::thread(_nested_warehouse_transfer_, c_shop, d_shop, k_shop, w_dist, std::ref(tm), transferAmount);<br>
         * thArray[i] = std::thread(_complex_warehouse_transfer_, d_shop, c_shop, std::ref(_warehouse_vec), w_dist, std::ref(tm), transferAmount);<br>
         * 
         */

        //        if (i % 3 == 0)
        //            thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);
        //        else if (i % 2 == 0)
        //            thArray[i] = std::thread(_nested_warehouse_transfer_, k_shop, s_shop, t_shop, w_dist, std::ref(tm), transferAmount);
        //        else if (i % 1 == 0)
        //            thArray[i] = std::thread(_complex_warehouse_transfer_, d_shop, s_shop, c_shop, std::ref(_warehouse_vec), w_dist, std::ref(tm), transferAmount);


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

    /*
     * TEST 2 : object requirements 
     */
    //    aib_ptr->toString();
    //    boi_ptr->toString();
    //    boa_ptr->toString();
    //    swplc_ptr->toString();
    //    ulster_ptr->toString();
    //    unbl_ptr->toString();
    //    for(int i=0; i<vector_number; ++i){
    //        _customer_vec[i]->toString();
    //    }

    /*
     * TEST 3 : object requirements
     */
    //            w_dist->toString();
    //            c_shop->toString();
    //            k_shop->toString();
    //            t_shop->toString();

    /*
     * TEST 4 : objects requirements
     */
    //        w_dist->toString();
    //        c_shop->toString();
    //        k_shop->toString();
    //        t_shop->toString();
    //        d_shop->toString();
    //        s_shop->toString();

    /*
     * TEST 5 : objects requirements
     */
    //        w_dist->toString();
    //        c_shop->toString();
    //        k_shop->toString();
    //        t_shop->toString();
    //        d_shop->toString();
    //        s_shop->toString();

    //        for(auto&& elem: _warehouse_vec){
    //            elem->toString(); // virtual dispatch
    //            
    //        }

    /* TEST 5 FINISH */
    return 0;
}
