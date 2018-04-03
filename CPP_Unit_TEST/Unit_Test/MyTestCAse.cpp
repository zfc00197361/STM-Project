

#include "MyTestCAse.h"
#include <iostream>
#include <memory>
#include <condition_variable>
#include <vector>

MyTestCAse::MyTestCAse(const MyTestCAse& orig) {
}

MyTestCAse::~MyTestCAse() {
}
/**
 * 
 * @param _customer_vec
 * @param _tm
 * @param _amount
 */
void MyTestCAse::_collection_bject_(std::vector<std::shared_ptr<OSTM> > _customer_vec, TM& _tm, double _amount, int loop){
    
     std::shared_ptr<TX> tx = _tm._get_tx();

    /*!
     * Declare required pointers 
     */
    std::shared_ptr<OSTM> _TO_OSTM_;
    std::shared_ptr<BANK>  _TO_;

    bool done = false;
    try {
        while (!done) {
            for (int i = 0; i < loop; ++i) {
                for (auto&& obj : _customer_vec) {
                    /*!
                     * Register customers accounts from the collection (vector) 
                     */
                    // auto&& obj = _customer_vec.at(i);
                    tx->_register(obj);
                    /*!
                     * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
                     */
                    _TO_ = std::dynamic_pointer_cast<BANK> (tx->load(obj));
                    /*!
                     * Make changes with the objects
                     */
                    _TO_->SetBalance(_TO_->GetBalance() + (_amount));
                    /*!
                     * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
                     */
                    _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_);
                    /*!
                     * Store changes
                     */
                    tx->store(_TO_OSTM_);
                }
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

/**
 * 
 * @param _to_
 * @param _tm
 * @param _amount
 */
void MyTestCAse::_one_account_transfer_(std::shared_ptr<OSTM> _to_, TM& _tm, double _amount){
     std::shared_ptr<TX> tx = tm._get_tx();
    /*!
     * Register the two single account
     */
    tx->_register(_to_);
    
    std::shared_ptr<OSTM> _TO_OSTM_;
    std::shared_ptr<BANK> _TO_;
    
    try {
        bool done = false;
        while (!done) {
            /*!
             * From std::shared_ptr<OSTM> to std::shared_ptr<BANK> to access the virtual methods
             */
            _TO_ = std::dynamic_pointer_cast<BANK> (tx->load(_to_));
            /*!
             * Make changes with the objects
             */
            _TO_->SetBalance(_TO_->GetBalance() + (_amount ));

            /*!
             * From std::shared_ptr<BANK> to std::shared_ptr<OSTM> to store the memory spaces
             */
            _TO_OSTM_ = std::dynamic_pointer_cast<OSTM> (_TO_);
            /*!
             * Store changes
             */
            tx->store(_TO_OSTM_);

            /*!
             * Commit changes
             */
            done = tx->commit();
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    
    
    
}
/**
 * 
 * @param _from_
 * @param _from_two_
 * @param _customer_vec
 * @param _tm
 * @param _amount
 * This function use two single objects and a collection of objects in the transaction.
 * The two single object transfer 1 - 1 (2) unit to every object in the collection
 */
void MyTestCAse::_complex_transfer_(std::shared_ptr<OSTM> _from_, std::shared_ptr<OSTM> _from_two_, std::vector<std::shared_ptr<OSTM>> _customer_vec, TM& _tm, double _amount) {
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
/**
 * 
 * @param _to_
 * @param _from_one_
 * @param _from_two_
 * @param _from_three_
 * @param _from_four_
 * @param _from_five_
 * @param _tm
 * @param _amount
 */
void MyTestCAse::_six_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_one_, std::shared_ptr<OSTM> _from_two_, std::shared_ptr<OSTM> _from_three_, std::shared_ptr<OSTM> _from_four_, std::shared_ptr<OSTM> _from_five_, TM& _tm, double _amount) {
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
/**
 * 
 * @param _to_
 * @param _from_
 * @param tm
 * @param _amount
 */
 void MyTestCAse::_two_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& tm, double _amount) {

    std::shared_ptr<TX> tx = tm._get_tx();
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
/**
 * 
 * @param _to_
 * @param _from_
 * @param _tm
 * @param _amount
 */
void MyTestCAse::_nesting_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount) {
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

/*
 * TEST DECLARATION FROM HERE *****************************************************
 */


/**
 * Testing the library consistent behavior   
 * LONG RUNNING PROCESS !!!! 1.5 - 2 Minutes !!!
 * This test transfer 1 - 1  unit by 100 threads = 100 * 1 = 100 to every object in the collection (-6000) by single objects
 * After transfer from account has -100 * 600 for both single objects and + 2 unit * 100 to every objects
 */
void MyTestCAse::complex_threaded_functionality_hundred_threads(){
    tm._TX_EXIT();
     std::vector<std::shared_ptr < OSTM>>_customer_vec; 
     for (int i = 0; i < 600; ++i) {
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
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 100; 
    std::thread thArray[threadArraySize];
   
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_complex_transfer_, this, aib_ptr, boi_ptr, std::ref(_customer_vec),  std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
    /* PRINT OUT THE CORRECT VALUES TO THE TWO SINGLE OBJECTS */
    //std::cout << _FROM_BANK_->GetBalance() << std::endl;
    //std::cout << _TO_BANK_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == -59500);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == -59500);
    
}

/**
 * Testing the library consistent behavior 
 * This test transfer 1 - 1  unit by 10 threads = 10 * 1 = 10 to evey object in the collection (-600) by single objects
 * After transfer from account has -10 * 600 for both single objects and + 2 unit * 10 to every objects
 */
void MyTestCAse::complex_threaded_functionality_ten_threads(){
    tm._TX_EXIT();
    std::vector<std::shared_ptr < OSTM>>_customer_vec; 
     for (int i = 0; i < 600; ++i) {
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
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 10; 
    std::thread thArray[threadArraySize];
    // //_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_complex_transfer_, this, aib_ptr, boi_ptr, std::ref(_customer_vec),  std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
    /* PRINT OUT THE CORRECT VALUES TO THE TWO SINGLE OBJECTS */
    //std::cout << _FROM_BANK_->GetBalance() << std::endl;
    //std::cout << _TO_BANK_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == -5500);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == -5500);
    
}


/**
 * Testing the library consistent behavior 
 * This test transfer 1 unit by 100 threads = 100 *1 = 100 
 * After transfer from account has -100, and to account has +100
 */
void MyTestCAse::threaded_functionality_hundred_threads(){
    tm._TX_EXIT();
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 100; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_two_account_transfer_, this, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
    //std::cout << _FROM_BANK_->GetBalance() << std::endl;
    //std::cout << _TO_BANK_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == 400);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 600);
    
}

/**
 * Testing the library consistent behavior 
 * This test transfer 1 unit by 1000 threads = 1000 *1 = 100 
 * After transfer from account has -1000, and to account has +1000
 */
void MyTestCAse::threaded_functionality_thousand_threads(){
    tm._TX_EXIT();
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 1000; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_two_account_transfer_, this, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
    //std::cout << _FROM_BANK_->GetBalance() << std::endl;
    //std::cout << _TO_BANK_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == -500);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 1500);
    
}

/**
 * Testing the library consistent behavior 
 * This test transfer 1 unit by 100 threads from five account to one account 
 * After transfer from account has - 100*1 from the accounts, and to account has +100*5
 */
void MyTestCAse::threaded_functionality_hundred_threads_six_account(){
    tm._TX_EXIT();
    std::shared_ptr<BANK> _FROM_BANK_ONE,_FROM_BANK_TWO,_FROM_BANK_THREE, _FROM_BANK_FOUR, _FROM_BANK_FIVE;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boa_ptr(new BOA(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> ulster_ptr(new ULSTER(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> unbl_ptr(new UNBL(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> swplc_ptr(new SWBPLC(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 100; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_six_account_transfer_, this, aib_ptr, boi_ptr, boa_ptr, ulster_ptr, unbl_ptr, swplc_ptr, std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ONE = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _FROM_BANK_TWO = std::dynamic_pointer_cast<BANK> (boa_ptr);
    _FROM_BANK_THREE = std::dynamic_pointer_cast<BANK> (ulster_ptr);
    _FROM_BANK_FOUR = std::dynamic_pointer_cast<BANK> (unbl_ptr);
    _FROM_BANK_FIVE = std::dynamic_pointer_cast<BANK> (swplc_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
//    std::cout << _FROM_BANK_ONE->GetBalance() << std::endl;
//    std::cout << _FROM_BANK_TWO->GetBalance() << std::endl;
//    std::cout << _FROM_BANK_THREE->GetBalance() << std::endl;
//    std::cout << _FROM_BANK_FOUR->GetBalance() << std::endl;
//    std::cout << _FROM_BANK_FIVE->GetBalance() << std::endl;
//    std::cout << _TO_BANK_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_FROM_BANK_ONE->GetBalance() == 400);
    CPPUNIT_ASSERT(_FROM_BANK_TWO->GetBalance() == 400);
    CPPUNIT_ASSERT(_FROM_BANK_THREE->GetBalance() == 400);
    CPPUNIT_ASSERT(_FROM_BANK_FOUR->GetBalance() == 400);
    CPPUNIT_ASSERT(_FROM_BANK_FIVE->GetBalance() == 400);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 1000);
    
}

/**
 * Testing the library consistent behavior 
 * This test transfer 1 unit by 1000 threads from five account to one account 
 * After transfer from account has - 1000*1 from the accounts, and to account has +1000*5
 */
void MyTestCAse::threaded_functionality_thousand_threads_six_account(){
    tm._TX_EXIT();
    std::shared_ptr<BANK> _FROM_BANK_ONE,_FROM_BANK_TWO,_FROM_BANK_THREE, _FROM_BANK_FOUR, _FROM_BANK_FIVE;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boa_ptr(new BOA(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> ulster_ptr(new ULSTER(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> unbl_ptr(new UNBL(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> swplc_ptr(new SWBPLC(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 1000; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_six_account_transfer_, this, aib_ptr, boi_ptr, boa_ptr, ulster_ptr, unbl_ptr, swplc_ptr, std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ONE = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _FROM_BANK_TWO = std::dynamic_pointer_cast<BANK> (boa_ptr);
    _FROM_BANK_THREE = std::dynamic_pointer_cast<BANK> (ulster_ptr);
    _FROM_BANK_FOUR = std::dynamic_pointer_cast<BANK> (unbl_ptr);
    _FROM_BANK_FIVE = std::dynamic_pointer_cast<BANK> (swplc_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
//    std::cout << _FROM_BANK_ONE->GetBalance() << std::endl;
//    std::cout << _FROM_BANK_TWO->GetBalance() << std::endl;
//    std::cout << _FROM_BANK_THREE->GetBalance() << std::endl;
//    std::cout << _FROM_BANK_FOUR->GetBalance() << std::endl;
//    std::cout << _FROM_BANK_FIVE->GetBalance() << std::endl;
//    std::cout << _TO_BANK_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_FROM_BANK_ONE->GetBalance() == -500);
    CPPUNIT_ASSERT(_FROM_BANK_TWO->GetBalance() == -500);
    CPPUNIT_ASSERT(_FROM_BANK_THREE->GetBalance() == -500);
    CPPUNIT_ASSERT(_FROM_BANK_FOUR->GetBalance() == -500);
    CPPUNIT_ASSERT(_FROM_BANK_FIVE->GetBalance() == -500);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 5500);
    
}

/**
 * Testing the library consistent behavior 
 * Nested threaded function : 3 level of nesting, every thread transfer 3 unit from one object to the another object
 * so, at end of the 100 thransaction the from object transfer 100 * 3 (300) to the another object 
 * 500 - 300 = 200 AND 500 + 300 = 800
 */
void MyTestCAse::nested_hundred_thread_functionality(){
    tm._TX_EXIT();
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 100; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_nesting_, this, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == 200);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 800);
    
}


/**
 * Testing the library consistent behavior 
 * Nested threaded function : 3 level of nesting, every thread transfer 3 unit from one object to the another object
 * so, at end of the 100 thransaction the from object transfer 1000 * 3 (3000) to the another object 
 * 500 - 3000 = -2500 AND 500 + 3000 = 3500
 */
void MyTestCAse::nested_thousand_thread_functionality(){
    tm._TX_EXIT();
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 1000; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_nesting_, this, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == -2500);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 3500);
    
}

/**
 * Testing the library consistent behavior 
 * Transfer between two objects : the from object transfer 20 to the another object
 * 500 - 20 = 480 AND 500 + 20 = 520
 */
void MyTestCAse::two_object_transfer_complete(){
    tm._TX_EXIT();
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    a->_two_account_transfer_(aib_ptr, boi_ptr, tm, 20);
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == 480);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 520);
    
}
/**
 * This function proves the objects states must change from the base values.
 */
void MyTestCAse::two_object_transfer_state_change(){
    tm._TX_EXIT();
    std::shared_ptr<OSTM> boa_ptr(new BOA(300, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> swplc_ptr(new SWBPLC(400, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    a->_two_account_transfer_(swplc_ptr, boa_ptr, tm, 20);
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boa_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (swplc_ptr);

   
    CPPUNIT_ASSERT(!(_FROM_BANK_->GetBalance() == 500));
    CPPUNIT_ASSERT(!(_TO_BANK_->GetBalance() == 500));
    
}
/**
 * Testing the library consistent behavior 
 * This test calls the nested function, where every thread transfer 3 unit in the nested transactions.
 * Because this test in not threaded, the 3 level deep nesting transfer 3*20 = 60 from one 
 * object to the another object.
 * 500 - 60 = 440 AND 500 + 60 = 560
 */
void MyTestCAse::nested_transaction_object_test(){
    tm._TX_EXIT();
    std::shared_ptr<OSTM> ulster_ptr(new ULSTER(500, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> unbl_ptr(new UNBL(600, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    a->_nesting_(ulster_ptr, unbl_ptr, tm, 20);
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (unbl_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (ulster_ptr);
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == 440);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 560);
    
}
/*
 * The library function throws runtime error if the client application tries to 
 * register null pointer in the library. Runtime error should be thrown
 */
void MyTestCAse::register_null_pointer_throw_runtime_error(){
    
    std::shared_ptr<OSTM> null_ptr; 
    std::shared_ptr<TX> tx = tm._get_tx();

    tx->_register(null_ptr);
}

/**
 * The library function throws runtime error if the client application tries to 
 * load a working pointer from the library of a not registered pointer by the client application.
 * Runtime error should be thrown
 */
void MyTestCAse::object_not_registered_throw_runtime_error(){
    
    std::shared_ptr<OSTM> not_registered_object(new BOA(300, 500, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<TX> tx = tm._get_tx();

    tx->load(not_registered_object);
}

/**
 * The test function throws runtime error if the client application tries to 
 * store the changed working pointer as a null pointer.
 * Runtime error should be thrown
 */
void MyTestCAse::store_null_pointer_throw_runtime_error(){
    
    std::shared_ptr<OSTM> null_ptr; 
    std::shared_ptr<TX> tx = tm._get_tx();

    tx->store(null_ptr);
}
/**
 * Testing the nesting increase function. 
 */
void MyTestCAse::increase_nesting(){
    std::shared_ptr<TX> tx = tm._get_tx();
    tx->setTx_nesting_level(0);
    tx->_increase_tx_nesting();
    tx->_increase_tx_nesting();
    tx->_increase_tx_nesting();

    CPPUNIT_ASSERT( tx->getTx_nesting_level() == 3);
}
/**
 * Testing the nesting decrease function. 
 */
void MyTestCAse::decrease_nesting(){
    
    std::shared_ptr<TX> tx = tm._get_tx();
    tx->setTx_nesting_level(10);
    tx->_decrease_tx_nesting();
    tx->_decrease_tx_nesting();
    tx->_decrease_tx_nesting();
    
    CPPUNIT_ASSERT( tx->getTx_nesting_level() == 7);
    tx->_decrease_tx_nesting();
    CPPUNIT_ASSERT( tx->getTx_nesting_level() == 6);
}
/**
 * Testing the nesting increase function to make sure the variable state changing. 
 */
void MyTestCAse::increase_nesting_fail(){
    std::shared_ptr<TX> tx = tm._get_tx();
    tx->setTx_nesting_level(0);
    tx->_increase_tx_nesting();
    tx->_increase_tx_nesting();
    tx->_increase_tx_nesting();

    CPPUNIT_ASSERT( !(tx->getTx_nesting_level() == 0));

}
/**
 * Testing the nesting decrease function to make sure the variable state changing. 
 */
void MyTestCAse::decrease_nesting_fail(){
    
    std::shared_ptr<TX> tx = tm._get_tx();
    tx->setTx_nesting_level(10);
    tx->_decrease_tx_nesting();
    tx->_decrease_tx_nesting();
    tx->_decrease_tx_nesting();
    
    CPPUNIT_ASSERT( !(tx->getTx_nesting_level() == 10));
    tx->_decrease_tx_nesting();
    CPPUNIT_ASSERT( !(tx->getTx_nesting_level() == 12));
}
/**
 * This testing function comparing the Transaction Manager to make sure the application using a Singleton object.
 */
void MyTestCAse::compare_Transaction_Manager_singleton_instance(){
    TM& tm_copy = TM::Instance();
    CPPUNIT_ASSERT( tm == tm_copy );
}
/**
 * This function testing the returned map from the Transaction Manager class. 
 */
void MyTestCAse::TM_get_thread_map(){
    
    std::map< std::thread::id, int > localMap;
    std::map< std::thread::id, int > tmMap = tm.get_thread_Map();
    
    CPPUNIT_ASSERT(localMap == tmMap);
}

/**
 * Design Manual document based tests Implementations
 * 1. Single thread multiple transactional object exchange test
 * 2. Multi-threaded single Object test with 10 threads.
 * 3. Single-threaded multiple object test.
 * 4. Multi-threaded multiple Objects test.
 */

/**
 *  1. Single thread multiple transactional object exchange test
 */
void MyTestCAse::multi_threaded_multiple_object_exchange_test(){
    //ten threads using same objects
    tm._TX_EXIT();
    std::shared_ptr<BANK> _FROM_BANK_;
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 100, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    std::shared_ptr<OSTM> boi_ptr(new BOI(200, 100, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 5;
    int threadArraySize = 10; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_two_account_transfer_, this, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _FROM_BANK_ = std::dynamic_pointer_cast<BANK> (boi_ptr);
    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
//    std::cout << _FROM_BANK_->GetBalance() << std::endl;
//    std::cout << _TO_BANK_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_FROM_BANK_->GetBalance() == 50);
    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 150);
    
}

/**
 * 2. Multi-threaded single Object test with 10 threads.
 */
void MyTestCAse::multi_threaded_single_object_test_with_ten_threads(){
    //one object ten threads
    tm._TX_EXIT();
    std::shared_ptr<BANK> _TO_BANK_;
    
    std::shared_ptr<OSTM> aib_ptr(new AIB(100, 100, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
    
    int transferAmount = 1;
    int threadArraySize = 10; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i] = std::thread(&MyTestCAse::_one_account_transfer_, this, aib_ptr, std::ref(tm), transferAmount);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    

    _TO_BANK_ = std::dynamic_pointer_cast<BANK> (aib_ptr);
    
   // std::cout << _TO_BANK_->GetBalance() << std::endl;

    CPPUNIT_ASSERT(_TO_BANK_->GetBalance() == 110);

}

/**
 * 3. Single-threaded multiple object test.
 */
void MyTestCAse::single_threaded_multiple_object_test(){
    //one transaction multiple objects six object function
    tm._TX_EXIT();
    std::vector<std::shared_ptr < OSTM>>_customer_vec; 
     for (int i = 0; i < 10; ++i) {
        if (i % 6 == 0) {
            std::shared_ptr<OSTM> sharedptr(new AIB(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 5 == 0) {
            std::shared_ptr<OSTM> sharedptr(new BOI(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 4 == 0) {
            std::shared_ptr<OSTM> sharedptr(new BOA(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 3 == 0) {
            std::shared_ptr<OSTM> sharedptr(new SWBPLC(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 2 == 0) {
            std::shared_ptr<OSTM> sharedptr(new ULSTER(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 1 == 0) {
            std::shared_ptr<OSTM> sharedptr(new UNBL(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        }
    }
    std::shared_ptr<BANK> _one_, _two_, _three_, _four_, _five_, _six_;
    int loop = 5;
    int transferAmount = 1;
    int threadArraySize = 1; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) { 
        thArray[i] = std::thread(&MyTestCAse::_collection_bject_, this, std::ref(_customer_vec),  std::ref(tm), transferAmount , loop);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _one_ = std::dynamic_pointer_cast<BANK> (_customer_vec[0]);
    _two_ = std::dynamic_pointer_cast<BANK> (_customer_vec[1]);
    _three_ = std::dynamic_pointer_cast<BANK> (_customer_vec[2]);
    _four_ = std::dynamic_pointer_cast<BANK> (_customer_vec[3]);
    _five_ = std::dynamic_pointer_cast<BANK> (_customer_vec[4]);
    _six_ = std::dynamic_pointer_cast<BANK> (_customer_vec[5]);
 
    
    /* PRINT OUT THE CORRECT VALUES TO THE TWO SINGLE OBJECTS */
//    std::cout << _one_->GetBalance() << std::endl;
//    std::cout << _two_->GetBalance() << std::endl;
//    std::cout << _three_->GetBalance() << std::endl;
//    std::cout << _four_->GetBalance() << std::endl;
//    std::cout << _five_->GetBalance() << std::endl;
//    std::cout << _six_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_one_->GetBalance() == 15);
    CPPUNIT_ASSERT(_two_->GetBalance() == 15);
    CPPUNIT_ASSERT(_three_->GetBalance() == 15);
    CPPUNIT_ASSERT(_four_->GetBalance() == 15);
    CPPUNIT_ASSERT(_five_->GetBalance() == 15);
    CPPUNIT_ASSERT(_six_->GetBalance() == 15);
}

/**
 * 4. Multi-threaded multiple Objects test.
 */
void MyTestCAse::multi_threaded_multiple_objects_test(){
    //three threads all thread use different objects 

    tm._TX_EXIT();
    std::vector<std::shared_ptr < OSTM>>_customer_vec; 
     for (int i = 0; i < 10; ++i) {
        if (i % 6 == 0) {
            std::shared_ptr<OSTM> sharedptr(new AIB(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 5 == 0) {
            std::shared_ptr<OSTM> sharedptr(new BOI(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 4 == 0) {
            std::shared_ptr<OSTM> sharedptr(new BOA(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 3 == 0) {
            std::shared_ptr<OSTM> sharedptr(new SWBPLC(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 2 == 0) {
            std::shared_ptr<OSTM> sharedptr(new ULSTER(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        } else if (i % 1 == 0) {
            std::shared_ptr<OSTM> sharedptr(new UNBL(i, 10, "Joe", "Blog", "High street, Kilkenny, Co.Kilkenny"));
            _customer_vec.push_back(std::move(sharedptr));
        }
    }
    std::shared_ptr<BANK> _one_, _two_, _three_, _four_, _five_, _six_;
    int loop = 1;
    int transferAmount = 1;
    int threadArraySize = 10; 
    std::thread thArray[threadArraySize];

    for (int i = 0; i < threadArraySize; ++i) { 
        thArray[i] = std::thread(&MyTestCAse::_collection_bject_, this, std::ref(_customer_vec),  std::ref(tm), transferAmount , loop);
    }
    
    for (int i = 0; i < threadArraySize; ++i) {
        thArray[i].join();
    }
    
    _one_ = std::dynamic_pointer_cast<BANK> (_customer_vec[0]);
    _two_ = std::dynamic_pointer_cast<BANK> (_customer_vec[1]);
    _three_ = std::dynamic_pointer_cast<BANK> (_customer_vec[2]);
    _four_ = std::dynamic_pointer_cast<BANK> (_customer_vec[3]);
    _five_ = std::dynamic_pointer_cast<BANK> (_customer_vec[4]);
    _six_ = std::dynamic_pointer_cast<BANK> (_customer_vec[5]);
 
    
    /* PRINT OUT THE CORRECT VALUES TO THE TWO SINGLE OBJECTS */
//    std::cout << _one_->GetBalance() << std::endl;
//    std::cout << _two_->GetBalance() << std::endl;
//    std::cout << _three_->GetBalance() << std::endl;
//    std::cout << _four_->GetBalance() << std::endl;
//    std::cout << _five_->GetBalance() << std::endl;
//    std::cout << _six_->GetBalance() << std::endl;
    
    CPPUNIT_ASSERT(_one_->GetBalance() == 20);
    CPPUNIT_ASSERT(_two_->GetBalance() == 20);
    CPPUNIT_ASSERT(_three_->GetBalance() == 20);
    CPPUNIT_ASSERT(_four_->GetBalance() == 20);
    CPPUNIT_ASSERT(_five_->GetBalance() == 20);
    CPPUNIT_ASSERT(_six_->GetBalance() == 20);
}