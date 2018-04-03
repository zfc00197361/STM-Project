Mixed Nested transaction Test with any number of threads<br>
This test use three different functions such as _warehouse_transfer_, _nested_warehouse_transfer_ and _complex_warehouse_transfer_.<br>
The _warehouse_transfer_ takes only two objects and create a trnsactions with them.<br>
The _nested_warehouse_transfer_ takes four WAREHOUSE type objects and creates multyple level transactions with mixed objects.<br>
The function _nested_warehouse_transfer_ create nested transaction and invokes the _warehouse_transfer_ function<br>
as a most inner transaction.<br>
The _complex_warehouse_transfer_ takes four WAREHOUSE type of objects and a vector with WAREHOUSE objetcs, and tranfere items between <br>
the collection and the single objetcs. This function mutilevel nested transactions wher iyt uses the another two functions to nesting.<br>
<br>
TEST details:<br>
Used values :<br>
Tanfer amount used in the transactions :<br>
*transferAmount = 1<br>
Number of threads used in the test application : <br>
*threadArraySize = 1 - 10 - 300<br>
<br>
Test 1: using only 1 Thread with the _complex_warehouse_transfer_ it takes 4 single objects, a vector (600) of WAREHOUSE objects and transfer from w-dist to the other objetcs.<br>
thArray[i] = std::thread(_complex_warehouse_transfer_, d_shop, s_shop, c_shop, std::ref(_warehouse_vec), w_dist, std::ref(tm), transferAmount);<br>
Start values for w_dist <br>
*No. Iphones : 10000<br>
*No. Samsung : 10000<br>
*No. Sony : 10000<br>
*No. Huawei : 10000<br>
*No. Nokia : 10000<br>
*No. Alcatel : 10000<br>
Start values for all shop and vector objetcs.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
<br>
After transactions : <br>
w_dist:<br>
*No. Iphones : 8195<br>
*No. Samsung : 8195<br>
*No. Sony : 8195<br>
*No. Huawei : 10000<br>
*No. Nokia : 8195<br>
*No. Alcatel : 10000<br>
<br>
c_shop.<br>
*No. Iphones : 202<br>
*No. Samsung : 202<br>
*No. Sony : 202<br>
*No. Huawei : 200<br>
*No. Nokia : 202<br>
*No. Alcatel : 200<br>
<br>
k_shop.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
<br>
t_shop.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
<br>
d_shop.<br>
*No. Iphones : 801<br>
*No. Samsung : 801<br>
*No. Sony : 801<br>
*No. Huawei : 200<br>
*No. Nokia : 801<br>
*No. Alcatel : 200<br>
<br>
s_shop.<br>
*No. Iphones : 802<br>
*No. Samsung : 802<br>
*No. Sony : 802<br>
*No. Huawei : 200<br>
*No. Nokia : 802<br>
*No. Alcatel : 200<br>
<br>
vector objetcs<br>
*No. Iphones : 201<br>
*No. Samsung : 201<br>
*No. Sony : 201<br>
*No. Huawei : 200<br>
*No. Nokia : 201<br>
*No. Alcatel : 200<br>
* version number 1. for all object used in transaction<br>
<br>
Test 2: using 10 Thread with the _complex_warehouse_transfer_ it takes 4 single objects, a vector (600) of WAREHOUSE objects and transfer from w-dist to the other objetcs.<br>
thArray[i] = std::thread(_complex_warehouse_transfer_, d_shop, s_shop, c_shop, std::ref(_warehouse_vec), w_dist, std::ref(tm), transferAmount);<br>
Start values for w_dist <br>
*No. Iphones : 10000<br>
*No. Samsung : 10000<br>
*No. Sony : 10000<br>
*No. Huawei : 10000<br>
*No. Nokia : 10000<br>
*No. Alcatel : 10000<br>
Start values for all shop and vector objetcs.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
After transactions : <br>
w_dist:<br>
*No. Iphones : -8050<br>
*No. Samsung : -8050<br>
*No. Sony : -8050<br>
*No. Huawei : 10000<br>
*No. Nokia : 8195<br>
*No. Alcatel : 10000<br>
<br>
c_shop.<br>
*No. Iphones : 220<br>
*No. Samsung : 220<br>
*No. Sony : 220<br>
*No. Huawei : 200<br>
*No. Nokia : 220<br>
*No. Alcatel : 200<br>
<br>
k_shop.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
<br>
t_shop.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
<br>
d_shop.<br>
*No. Iphones : 6210<br>
*No. Samsung : 6210<br>
*No. Sony : 6210<br>
*No. Huawei : 200<br>
*No. Nokia : 6210<br>
*No. Alcatel : 200<br>
s_shop.<br>
*No. Iphones : 6220<br>
*No. Samsung : 6220<br>
*No. Sony : 6220<br>
*No. Huawei : 200<br>
*No. Nokia : 6220<br>
*No. Alcatel : 200<br>

vector objetcs<br>
*No. Iphones : 210<br>
*No. Samsung : 210<br>
*No. Sony : 210<br>
*No. Huawei : 200<br>
*No. Nokia : 210<br>
*No. Alcatel : 200<br>
* version number 10. for all object used in transaction<br>
<br>
<br>
Test 3: using 300 Thread with the _complex_warehouse_transfer_ it takes 4 single objects, a vector (600) of WAREHOUSE objects and transfer from w-dist to the other objetcs.<br>
All the three function used by 100 threads, the calculation is very comlex.<br>
Start values for w_dist <br>
*No. Iphones : 10000<br>
*No. Samsung : 10000<br>
*No. Sony : 10000<br>
*No. Huawei : 10000<br>
*No. Nokia : 10000<br>
*No. Alcatel : 10000<br>
Start values for all shop and vector objetcs.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
After transactions : <br>
<br>
* version number vary for objects used in transaction, depends how many transactions they are used<br>
* w_dist : version :300 <br>
*No. Iphones : -170900<br>
*No. Samsung : -170900<br>
*No. Sony : -170900<br>
*No. Huawei : 200<br>
*No. Nokia : -170900<br>
*No. Alcatel : 200<br> 
<br>
* c_shop version : 100 <br>
*No. Iphones : 500<br>
*No. Samsung : 500<br>
*No. Sony : 500<br>
*No. Huawei : 200<br>
*No. Nokia : 500<br>
*No. Alcatel : 200<br>
<br>
* k_shop version : 200 <br>
*No. Iphones : 300<br>
*No. Samsung : 300<br>
*No. Sony : 300<br>
*No. Huawei : 200<br>
*No. Nokia : 300<br>
*No. Alcatel : 200<br>
<br>
* t_shop version : 100 <br>
*No. Iphones : 300<br>
*No. Samsung : 300<br>
*No. Sony : 300<br>
*No. Huawei : 200<br>
*No. Nokia : 300<br>
*No. Alcatel : 200<br>
<br>
* d_shop version : 100 <br>
*No. Iphones : 60300<br>
*No. Samsung : 60300<br>
*No. Sony : 60300<br>
*No. Huawei : 200<br>
*No. Nokia : 60300<br>
*No. Alcatel : 200<br> 
<br>
* s_shop version : 200 <br>
*No. Iphones : 60500<br>
*No. Samsung : 60500<br>
*No. Sony : 60500<br>
*No. Huawei : 200<br>
*No. Nokia : 60500<br>
*No. Alcatel : 200<br> 
<br>
* all vector objects version : 100 <br>
*No. Iphones : 300<br>
*No. Samsung : 300<br>
*No. Sony : 300<br>
*No. Huawei : 200<br>
*No. Nokia : 300<br>
*No. Alcatel : 200<br>
<br>

