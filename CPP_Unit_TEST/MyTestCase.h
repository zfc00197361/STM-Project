

#ifndef MYTESTCASE_H
#define MYTESTCASE_H

//Connection between the library and the classes
#include "client.h"
#include "TM.h"
#include <thread>

//#include "TestClient.cpp"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class MyTestCAse : public TestCase{
    CPPUNIT_TEST_SUITE(MyTestCAse);
    /*
     * Complex library tests.
     */
    CPPUNIT_TEST(threaded_functionality_hundred_threads);
    CPPUNIT_TEST(threaded_functionality_thousand_threads);
    CPPUNIT_TEST(threaded_functionality_hundred_threads_six_account);
    CPPUNIT_TEST(threaded_functionality_thousand_threads_six_account);
    CPPUNIT_TEST(nested_hundred_thread_functionality); 
    CPPUNIT_TEST(nested_thousand_thread_functionality);
    CPPUNIT_TEST(complex_threaded_functionality_hundred_threads);
    CPPUNIT_TEST(complex_threaded_functionality_ten_threads);
    CPPUNIT_TEST(two_object_transfer_complete);
    CPPUNIT_TEST(two_object_transfer_state_change);
    CPPUNIT_TEST(nested_transaction_object_test);
    /*
     * Design Manual document based tests
     */
    CPPUNIT_TEST(multi_threaded_multiple_object_exchange_test);
    CPPUNIT_TEST(multi_threaded_single_object_test_with_ten_threads);
    CPPUNIT_TEST(single_threaded_multiple_object_test);
    CPPUNIT_TEST(multi_threaded_multiple_objects_test);
    /*
     * OSTM library-API functions tests, private & public methods
     */
    CPPUNIT_TEST(increase_nesting);
    CPPUNIT_TEST(increase_nesting_fail);
    CPPUNIT_TEST(decrease_nesting);
    CPPUNIT_TEST(decrease_nesting_fail);
    CPPUNIT_TEST(two_object_transfer_state_change);
    CPPUNIT_TEST_EXCEPTION(register_null_pointer_throw_runtime_error, std::runtime_error);
    CPPUNIT_TEST_EXCEPTION(object_not_registered_throw_runtime_error, std::runtime_error);
    CPPUNIT_TEST_EXCEPTION(store_null_pointer_throw_runtime_error, std::runtime_error);
    CPPUNIT_TEST(compare_Transaction_Manager_singleton_instance);
    CPPUNIT_TEST(TM_get_thread_map);
   
    
    
            

    CPPUNIT_TEST_SUITE_END();
public:
    MyTestCAse(){};
    MyTestCAse(const MyTestCAse& orig);
    virtual ~MyTestCAse();

    TM& tm = TM::Instance();
    std::shared_ptr<OSTM> aib_ptr;
    std::shared_ptr<OSTM> boi_ptr;
    std::shared_ptr<OSTM> boa_ptr;
    std::shared_ptr<OSTM> swplc_ptr;
    std::shared_ptr<OSTM> ulster_ptr;
    std::shared_ptr<OSTM> unbl_ptr;
    
    void complex_threaded_functionality_hundred_threads();
    void complex_threaded_functionality_ten_threads();
    void threaded_functionality_hundred_threads();
    void threaded_functionality_thousand_threads();
    void threaded_functionality_hundred_threads_six_account();
    void threaded_functionality_thousand_threads_six_account();
    void nested_hundred_thread_functionality();
    void nested_thousand_thread_functionality();
    void two_object_transfer_complete();
    void two_object_transfer_state_change();
    
    void multi_threaded_multiple_object_exchange_test();
    void multi_threaded_single_object_test_with_ten_threads();
    void single_threaded_multiple_object_test();
    void multi_threaded_multiple_objects_test();
    
    void register_null_pointer_throw_runtime_error();
    void object_not_registered_throw_runtime_error();
    void store_null_pointer_throw_runtime_error();
    void increase_nesting();
    void decrease_nesting();
    void increase_nesting_fail();
    void decrease_nesting_fail();
    void compare_Transaction_Manager_singleton_instance();
    void TM_get_thread_map();
    void nested_transaction_object_test();
    
    
    void _two_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& tm, double _amount);
    void _nesting_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_, TM& _tm, double _amount);
    void _six_account_transfer_(std::shared_ptr<OSTM> _to_, std::shared_ptr<OSTM> _from_one_, std::shared_ptr<OSTM> _from_two_, std::shared_ptr<OSTM> _from_three_, std::shared_ptr<OSTM> _from_four_, std::shared_ptr<OSTM> _from_five_, TM& _tm, double _amount); 
    void _complex_transfer_(std::shared_ptr<OSTM> _from_, std::shared_ptr<OSTM> _from_two_, std::vector<std::shared_ptr<OSTM>> _customer_vec, TM& _tm, double _amount);
    void _one_account_transfer_(std::shared_ptr<OSTM> _to_, TM& _tm, double _amount);
    void _collection_bject_(std::vector<std::shared_ptr<OSTM>> _customer_vec, TM& _tm, double _amount, int loop);
    
  void setUp()
  {
      a = new client(1);
      b = new client(1);
      c = new client(1);

  }

  void tearDown() 
  {
      delete a;
      delete b;
      delete c;
  }

    
private:
    //Private pointer to use in the library
    client *a,*b,*c;
    
};

#endif /* MYTESTCASE_H */

