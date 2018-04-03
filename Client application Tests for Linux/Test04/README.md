Nested transaction Test with any number of threads<br>
This test use _nested_warehouse_transfer_, _warehouse_transfer_ functions, and transfer between WAREHOUSE type of objects.<br>
The _warehouse_transfer_ takes two WAREHOUSE type objects and transfer between them.<br>
The _nested_warehouse_transfer_ takes four WAREHOUSE type objects,transfer from w_dist to the first shop, create a nested transaction where transfer to the next shop, and calls the <br>
_warehouse_transfer_ function which will be the next inner level transation and used the third object to transfer to.<br>
<br>
TEST details:<br>
Used values :<br>
Tanfer amount used in the transactions :<br>
*transferAmount = 1<br>
Number of threads used in the test application : <br>
*threadArraySize = 1 - 10 - 300<br>
<br>
Test 1: using only 1 Thread with the _nested_warehouse_transfer_ and transfer from w_dist to c_shop, d_shop, k_shop 1 iPhone, 1 Samsung, 1 Sony and 1 Nokia.<br>
thArray[i] = std::thread(_nested_warehouse_transfer_, c_shop, d_shop, k_shop, w_dist, std::ref(tm), transferAmount);<br>
Start values for w_dist <br>
*No. Iphones : 10000<br>
*No. Samsung : 10000<br>
*No. Sony : 10000<br>
*No. Huawei : 10000<br>
*No. Nokia : 10000<br>
*No. Alcatel : 10000<br>
Start values for all shop objetcs.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
<br>
After transactions : <br>
w_dist <br>
*No. Iphones : 9997<br>
*No. Samsung : 9997<br>
*No. Sony : 9997<br>
*No. Huawei : 10000<br>
*No. Nokia : 9997<br>
*No. Alcatel : 10000<br>
c_shop, d_shop and k_shop<br>
*No. Iphones : 201<br>
*No. Samsung : 201<br>
*No. Sony : 201<br>
*No. Huawei : 200<br>
*No. Nokia : 201<br>
*No. Alcatel : 200<br>
* version number 1. for all object used in transaction<br>
<br>
Test 2: using 10 Thread with the _nested_warehouse_transfer_ and transfer from w_dist to c_shop, d_shop, k_shop 1 iPhone, 1 Samsung, 1 Sony and 1 Nokia.<br>
thArray[i] = std::thread(_nested_warehouse_transfer_, c_shop, d_shop, k_shop, w_dist, std::ref(tm), transferAmount);<br>
Start values for w_dist <br>
*No. Iphones : 10000<br>
*No. Samsung : 10000<br>
*No. Sony : 10000<br>
*No. Huawei : 10000<br>
*No. Nokia : 10000<br>
*No. Alcatel : 10000<br>
Start values for all shop objetcs.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
After transactions : <br>
w_dist <br>
*No. Iphones : 9970<br>
*No. Samsung : 9970<br>
*No. Sony : 9970<br>
*No. Huawei : 10000<br>
*No. Nokia : 9970<br>
*No. Alcatel : 10000<br>
c_shop, d_shop, k_shop<br>
*No. Iphones : 210<br>
*No. Samsung : 210<br>
*No. Sony : 210<br>
*No. Huawei : 200<br>
*No. Nokia : 210<br>
*No. Alcatel : 200<br>
* version number 10. for all object used in transaction<br>
<br>
Test 2: using 300 Thread with the _nested_warehouse_transfer_ and transfer from w_dist to c_shop, d_shop, k_shop 1 iPhone, 1 Samsung, 1 Sony and 1 Nokia.<br>
thArray[i] = std::thread(_nested_warehouse_transfer_, c_shop, d_shop, k_shop, w_dist, std::ref(tm), transferAmount);<br>
Start values for w_dist <br>
*No. Iphones : 10000<br>
*No. Samsung : 10000<br>
*No. Sony : 10000<br>
*No. Huawei : 10000<br>
*No. Nokia : 10000<br>
*No. Alcatel : 10000<br>
Start values for all shop objetcs.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
After transactions : <br>
w_dist <br>
*No. Iphones : 9100<br>
*No. Samsung : 9100<br>
*No. Sony : 9100<br>
*No. Huawei : 10000<br>
*No. Nokia : 9100<br>
*No. Alcatel : 10000<br>
c_shop, k_shop, t_shop and s_shop<br>
*No. Iphones : 400<br>
*No. Samsung : 400<br>
*No. Sony : 400<br>
*No. Huawei : 200<br>
*No. Nokia : 400<br>
*No. Alcatel : 200<br>
d_shop<br>
*No. Iphones : 300<br>
*No. Samsung : 300<br>
*No. Sony : 300<br>
*No. Huawei : 200<br>
*No. Nokia : 300<br>
*No. Alcatel : 200<br>
* version number 300. for all object used in transaction<br>
<br>




