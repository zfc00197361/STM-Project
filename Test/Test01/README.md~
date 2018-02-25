threadArraySize = 300Nested transaction Test with any number of threads<br>
Function _nesting_ is create a transaction and transfer between two objects<br>
Then create a Transaction inside the transaction, (nested Transaction)<br>
and inside the nested transaction invokes the _two_account_transfer_ transaction, that will be the third level inner transaction.<br>
<br>
TEST details:
Used values :<br>
Tanfer amount used in the transactions :<br>
*transferAmount = 1<br>
Number of threads used in the test application : <br>
*threadArraySize = 300<br>
<br>
Six OSTM type smart pointer aib_ptr, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, unbl_ptr , these objects are inherites from BANK parent class.<br>
Every thread used two object in the transaction within the _nesting_ function, and creates a nested transaction using the same objects.<br>
Inside the nested transaction makes a function call to the _two_account_transfer_ function, which is creates a transaction and a nested transaction in the nested transaction.<br>
So, every thread used the objects in four level deep transactions.<br>
To make easyer to folow the calculation the transactions are using the objects in the same transfering oder, from-to.<br>
<br>
Test 1: using only 1 Thread with two objetcs aib_ptr, boi_ptr and tranfering 1 unit in every transaction :<br>
Start values : Double value : 500 to each.<br>
After transactions : <br>
* To account : aib_ptr - Double value : 504 <br>
* From account : boi_ptr - Double value : 496 <br>

