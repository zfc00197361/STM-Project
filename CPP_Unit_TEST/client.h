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

#include "TM.h"
#include "AIB.h"    //Bank Account
#include "BOI.h"    //Bank Account
#include "BOA.h"    //Bank Account
#include "SWBPLC.h" //Bank Account
#include "ULSTER.h" //Bank Account
#include "UNBL.h"   //Bank Account
#include <mutex>
#include <memory>
#include <condition_variable>
#include <vector>


#ifndef CLIENT_H
#define CLIENT_H

class client {
private:
      
public:
    int value = 0;
    client(int value){ this->value = value; };

    void _two_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& tm, double _amount) {

    std::shared_ptr<TX> tx = tm._get_tx();
    /*
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_from_);
    /*
     * Declare required pointers 
     */
    std::shared_ptr<BANK> _TO_BANK_, _FROM_BANK_;
    std::shared_ptr<OSTM> _TO_OSTM_, _FROM_OSTM_;

    bool done = false;
    try {
        while (!done) {
            /*
             * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
             */
            _TO_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
            /*
             * Make changes with the objects
             */
            _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
            _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
            /*
             * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
             */
            _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
            _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
            /*
             * Store changes
             */
            tx->store(_TO_OSTM_);
            tx->store(_FROM_OSTM_);

            /*
             * Commit changes
             */
            done = tx->commit();
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void _nesting_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& tm, double _amount) {
    std::shared_ptr<TX> tx = tm._get_tx();
    /*
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_from_);
    /*
     * Declare required pointers 
     */
    std::shared_ptr<BANK> _TO_BANK_, _FROM_BANK_;
    std::shared_ptr<OSTM> _TO_OSTM_, _FROM_OSTM_;


    bool done = false;
    try {
        while (!done) {
            /*
             * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
             */
            _TO_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
            /*
             * Make changes with the objects
             */
            _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
            _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
            /*
             * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
             */
            _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
            _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
            /*
             * Store changes
             */
            tx->store(_TO_OSTM_);
            tx->store(_FROM_OSTM_);

            /*
             * NESTED TRANSACTION
             */
            std::shared_ptr<TX> txTwo = tm._get_tx();

            bool nestedDone = false;
            while (!nestedDone) {
                _TO_BANK_ = std::dynamic_pointer_cast<BANK> (txTwo->load(_to_));
                _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (txTwo->load(_from_));
                /*
                 * Make changes with the objects
                 */
                _TO_BANK_->SetBalance(_TO_BANK_->GetBalance() + _amount);
                _FROM_BANK_->SetBalance(_FROM_BANK_->GetBalance() - _amount);
                /*
                 * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
                 */
                _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_BANK_);
                _FROM_OSTM_ = std::dynamic_pointer_cast<OSTM> (_FROM_BANK_);
                /*
                 * Store changes
                 */
                txTwo->store(_TO_OSTM_);
                txTwo->store(_FROM_OSTM_);
                /*
                 * NESTED TRANSACTION IN THE NESTED TRANSACTION
                 * _two_account_transfer_ function call
                 */
                _two_account_transfer_(_to_, _from_, tm, _amount);

                nestedDone = txTwo->commit();
            }

            /*
             * Commit changes
             */
            done = tx->commit();
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void _six_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_one_, std::shared_ptr<OSTM> _from_two_, std::shared_ptr<OSTM> _from_three_, std::shared_ptr<OSTM> _from_four_, std::shared_ptr<OSTM> _from_five_, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /*
     * Register the two single account
     */
    tx->_register(_to_);
    tx->_register(_from_one_);
    tx->_register(_from_two_);
    tx->_register(_from_three_);
    tx->_register(_from_four_);
    tx->_register(_from_five_);

    /*
     * Required pointers to use in transaction
     */
    std::shared_ptr<OSTM> _TO_OSTM, _FROM_ONE_OSTM, _FROM_TWO_OSTM, _FROM_THREE_OSTM, _FROM_FOUR_OSTM, _FROM_FIVE_OSTM;
    std::shared_ptr<BANK> _TO_, _FROM_ONE_, _FROM_TWO_, _FROM_THREE_, _FROM_FOUR_, _FROM_FIVE_;
    try {
        bool done = false;
        while (!done) {
            /*
             * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
             */
            _TO_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            _FROM_ONE_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_one_));
            _FROM_TWO_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_two_));
            _FROM_THREE_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_three_));
            _FROM_FOUR_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_four_));
            _FROM_FIVE_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_five_));
            /*
             * Make changes with the objects
             */
            _TO_->SetBalance(_TO_->GetBalance() + (_amount * 5));
            _FROM_ONE_->SetBalance(_FROM_ONE_->GetBalance() - _amount);
            _FROM_TWO_->SetBalance(_FROM_TWO_->GetBalance() - _amount);
            _FROM_THREE_->SetBalance(_FROM_THREE_->GetBalance() - _amount);
            _FROM_FOUR_->SetBalance(_FROM_FOUR_->GetBalance() - _amount);
            _FROM_FIVE_->SetBalance(_FROM_FIVE_->GetBalance() - _amount);
            /*
             * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
             */
            _TO_OSTM = std::dynamic_pointer_cast<OSTM> (_TO_);
            _FROM_ONE_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_ONE_);
            _FROM_TWO_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_TWO_);
            _FROM_THREE_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_THREE_);
            _FROM_FOUR_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_FOUR_);
            _FROM_FIVE_OSTM = std::dynamic_pointer_cast<OSTM> (_FROM_FIVE_);
            /*
             * Store changes
             */
            tx->store(_TO_OSTM);
            tx->store(_FROM_ONE_OSTM);
            tx->store(_FROM_TWO_OSTM);
            tx->store(_FROM_THREE_OSTM);
            tx->store(_FROM_FOUR_OSTM);
            tx->store(_FROM_FIVE_OSTM);
            /*
             * Commit changes
             */
            done = tx->commit();
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void _complex_transfer_(std::shared_ptr<OSTM> _from_, std::shared_ptr<OSTM> _from_two_, std::vector<std::shared_ptr<OSTM>> _customer_vec, TM& _tm, double _amount) {
    std::shared_ptr<TX> tx = _tm._get_tx();
    /* Register the two single account*/
    tx->_register(_from_);
    tx->_register(_from_two_);
    /* Declare required pointers */
    std::shared_ptr<OSTM> _FROM_OSTM_ONE_, _FROM_OSTM_TWO_, _TO_OSTM_;
    std::shared_ptr<BANK> _FROM_, _FROM_TWO_, _TO_;

    bool done = false;
    try {
        while (!done) {
            for (auto&& obj : _customer_vec) {
                /* Register customers accounts from the collection (vector) */
                tx->_register(obj);
                /* From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods  */
                _FROM_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_));
                _FROM_TWO_ = std::dynamic_pointer_cast<BANK> (tx->load(_from_two_));
                _TO_ = std::dynamic_pointer_cast<BANK> (tx->load(obj));
                /* Make changes with the objects */
                _FROM_->SetBalance(_FROM_->GetBalance() - _amount);
                _FROM_TWO_->SetBalance(_FROM_TWO_->GetBalance() - _amount);
                _TO_->SetBalance(_TO_->GetBalance() + (_amount * 2));
                /* From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces */
                _FROM_OSTM_ONE_ = std::dynamic_pointer_cast<OSTM> (_FROM_);
                _FROM_OSTM_TWO_ = std::dynamic_pointer_cast<OSTM> (_FROM_TWO_);
                _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_);
                /* Store changes */
                tx->store(_FROM_OSTM_ONE_);
                tx->store(_FROM_OSTM_TWO_);
                tx->store(_TO_OSTM_);
            }
            /* Commit changes */
            done = tx->commit();
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}


};

#endif /* CLIENT_H */

