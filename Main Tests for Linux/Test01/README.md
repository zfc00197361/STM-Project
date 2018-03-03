threadArraySize = 1 - 300 Nested transaction Test with any number of threads<br>
Function _nesting_ is create a transaction and transfer between two objects<br>
Then create a Transaction inside the transaction, (nested Transaction)<br>
and inside the nested transaction invokes the _two_account_transfer_ transaction, that will be the third level inner transaction.<br>
<br>
TEST details:
Used values :<br>
Tanfer amount used in the transactions :<br>
*transferAmount = 1<br>
Number of threads used in the test application : <br>
*threadArraySize = 1 -10 - 300 specified in every test<br>
<br>
Six OSTM type smart pointer aib_ptr, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, unbl_ptr , these objects are inherites from BANK parent class.<br>
Every thread used two object in the transaction within the _nesting_ function, and creates a nested transaction using the same objects.<br>
Inside the nested transaction makes a function call to the _two_account_transfer_ function, which is creates a transaction and a nested transaction in the nested transaction.<br>
So, every thread used the objects in four level deep transactions.<br>
To make easyer to folow the calculation the transactions are using the objects in the same transfering oder, from-to.<br>
<br>
Test 1: using only 1 Thread with two objetcs aib_ptr, boi_ptr and tranfering 1 unit in every transaction :<br>
thArray[i] = std::thread(_nesting_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);<br>
Start values : Double value : 500 to each.<br>
Nesting level 4.<br>
After transactions : <br>
* To account : aib_ptr - Double value : 504 <br>
* From account : boi_ptr - Double value : 496 <br>
* version number 1. for all object used in transaction<br>
<br>
Test 2: using 10 Thread with two objetcs aib_ptr, boi_ptr and tranfering 1 unit in every transaction :<br>
Start values : Double value : 500 to each.<br>
Nesting level 4.<br>
After transactions : <br>
* To account : aib_ptr - Double value : 540 <br>
* From account : boi_ptr - Double value : 460 <br>
* version number 10. for all object used in transaction<br>
<br>
Test 3: using 300 Thread with six objetcs aib_ptr, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, unbl_ptr and tranfering 1 unit in every transaction :<br>
Every object will be used by 100 threads.<br>
Start values : Double value : 500 to each.<br>
Nesting level 4.<br>
After transactions : <br>
* To account : aib_ptr - Double value : 900 <br>
* From account : boi_ptr - Double value : 100 <br>
* To account : boa_ptr - Double value : 900 <br>
* From account : swplc_ptr - Double value : 100 <br>
* To account : ulster_ptr - Double value : 900 <br>
* From account : unbl_ptr - Double value : 100 <br>
* version number 100. for all object used in transaction<br>




