Test with 1- 300 number of threads and nested transactions<br>
This test use three different function, _two_account_transfer_, _six_account_transfer_ and _complex_transfer_.<br>
The first function _two_account_transfer_ takes two BANK type of objects and create a transaction with them<br>
The second function  _six_account_transfer_ takes six BANK type of object, create a transaction<br> 
and tranfer items from five account to only one account.<br>
The third function _complex_transfer_, takes two BANK type of object and any size of vector with BANK objetcs,<br>
then creates a transaction and tranfer items from the first two objects to the vector of objects.br>
<br>
TEST details:
Used values :<br>
Tanfer amount used in the transactions :<br>
*transferAmount = 1<br>
Number of threads used in the test application : <br>
*threadArraySize = 1 - 10 - 300<br>
<br>
Test 1: using only 1 Thread with two objetcs and object collection :  aib_ptr, boi_ptr,and 600 OSTM/BANK vector object tranfering 1 unit in every transaction :<br>
thArray[i] = std::thread(_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);<br>
The _complex_transfer_ receiving two single objects aib_ptr, boi_ptr and _customer_vec vector(600 objetcs) and transfering booth single objects 1 - 1 (2 together) units to every single vector objetcs.<br>
Start values : Double value : 500 to each single object.<br>
Start values : Double value : 50 to each vector object.<br>
After transactions : <br>
* To account : aib_ptr - Double value : -100 <br>
* From account : boi_ptr - Double value : -100 <br>
* For all vector object - Double value : 52<br>
* version number 1. for all object used in transaction<br>
<br>
Test 2: using only 10 Thread with two objetcs and object collection : aib_ptr, boi_ptr, 600 OSTM/BANK vector object tranfering 1 unit in every transaction :<br>
thArray[i] = std::thread(_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);<br>
The _complex_transfer_ receiving two single objects aib_ptr, boi_ptr and _customer_vec vector(600 objetcs) and transfering booth single objects 1 - 1 (2 together) units to every single vector objetcs.<br>
Start values : Double value : 500 to each single object.<br>
Start values : Double value : 50 to each vector object.<br>
After transactions : <br>
* To account : aib_ptr - Double value : -5500 <br>
* From account : boi_ptr - Double value : -5500 <br>
* For all vector object - Double value : 70 <br>
* version number 10. for all object used in transaction<br>
<br>
Test 3: using only 300 Thread with six objetcs aib_ptr, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, unbl_ptr, 600 OSTM/BANK vector object tranfering 1 unit in every transaction :<br>
thArray[i] = std::thread(_complex_transfer_, aib_ptr, boi_ptr, std::ref(_customer_vec), std::ref(tm), transferAmount);<br>
The _complex_transfer_ receiving two single objects aib_ptr, boi_ptr and _customer_vec vector(600 objetcs) and transfering booth single objects 1 - 1 (2 together) units to every single vector objetcs.<br>
thArray[i] = std::thread(_six_account_transfer_, boi_ptr, boa_ptr, swplc_ptr, ulster_ptr, aib_ptr, unbl_ptr, std::ref(tm), transferAmount);<br>
The _six_account_transfer_ receiving six single objects and transfering 1 - 1 (5/transaction) to aib_ptr from the other objects.<br>
thArray[i] = std::thread(_two_account_transfer_, aib_ptr, boi_ptr, std::ref(tm), transferAmount);
The _two_account_transfer_ is a nested transaction receiving two single objetcs and transfering 1 unit to aib_ptr from boi_ptr in every transaction/nested transaction.<br>

Start values : Double value : 500 to each single object.<br>
After transactions : <br>
* Account : aib_ptr - Double value : -59400 <br>
* Account : boi_ptr - Double value : -59200 <br>
* Account : boa_ptr - Double value : 400 <br>
* Account : swplc_ptr - Double value : 400 <br>
* Account : ulster_ptr - Double value : 400 <br>
* Account : unbl_ptr - Double value : 400 <br>
* For all vector object - Double value : 250 <br>
* version number 300. for aib_ptr and boi_ptr object used in transaction<br>
* version number 100. for all other object used in transaction<br>
<br>
Test 3: repeat with only 3 thread, 1/per function.<br>
Start values : Double value : 500 to each single object.<br>
After transactions : <br>
* Account : aib_ptr - Double value : -99 <br>
* Account : boi_ptr - Double value : -97 <br>
* Account : boa_ptr - Double value : 499 <br>
* Account : swplc_ptr - Double value : 499 <br>
* Account : ulster_ptr - Double value : 499 <br>
* Account : unbl_ptr - Double value : 499 <br>
* For all vector object - Double value : 52 <br>
* version number 3. for aib_ptr and boi_ptr object used in transaction<br>
* version number 1. for all other object used in transaction<br>





