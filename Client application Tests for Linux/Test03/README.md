Test with any number of threads<br>
This test use _warehouse_transfer_ function, and transfer between WAREHOUSE type of objects.br>
All the objects contains fileds such as iPhone, Samsung, Sony, Nokia and more similar phone make representative fields.<br>
The main object is the CARPHONE_WAREHOUSE is the distribution center representative object.<br>
The tests transafers phones from the CARPHONE_WAREHOUSE distribution object to the other shop representativ objetcs, or between the shops.<br>
The CARPHONE_WAREHOUSE has 10000 for stock to all fieldS by default, and the shops has 200 to all fileds by default.<br> 
<br>
TEST details:<br>
Used values :<br>
Tanfer amount used in the transactions :<br>
*transferAmount = 1<br>
Number of threads used in the test application : <br>
*threadArraySize = 1 - 10 - 300<br>
<br>
Test 1: using only 1 Thread with the _warehouse_transfer_ and transfer from w_dist to c_shop 1 iPhone, 1 Samsung, 1 Sony and 1 Nokia only to the c_shop object.<br>
thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);<br>
Start values for w_dist Object<br>
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
**After transactions :** <br>
w_dist Object<br>
*No. Iphones : 9999<br>
*No. Samsung : 9999<br>
*No. Sony : 9999<br>
*No. Huawei : 10000<br>
*No. Nokia : 9999<br>
*No. Alcatel : 10000<br>
c_shop Object<br>
*No. Iphones : 201<br>
*No. Samsung : 201<br>
*No. Sony : 201<br>
*No. Huawei : 200<br>
*No. Nokia : 201<br>
*No. Alcatel : 200<br>
* version number 1. for all object used in transaction<br>
<br>
Test 2: using 10 Thread with the _warehouse_transfer_ and transfer from w_dist to c_shop 1 iPhone, 1 Samsung, 1 Sony and 1 Nokia.<br>
thArray[i] = std::thread(_warehouse_transfer_, c_shop, w_dist, std::ref(tm), transferAmount);<br>
Start values for w_dist <br>
*No. Iphones : 10000<br>
*No. Samsung : 10000<br>
*No. Sony : 10000<br>
*No. Huawei : 10000<br>
*No. Nokia : 10000<br>
*No. Alcatel : 10000<br>
<br>
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
*No. Iphones : 9990<br>
*No. Samsung : 9990<br>
*No. Sony : 9990<br>
*No. Huawei : 10000<br>
*No. Nokia : 9990<br>
*No. Alcatel : 10000<br>
c_shop<br>
*No. Iphones : 210<br>
*No. Samsung : 210<br>
*No. Sony : 210<br>
*No. Huawei : 200<br>
*No. Nokia : 210<br>
*No. Alcatel : 200<br>
* version number 10. for all object used in transaction<br>
<br>
Test 3 : using 300 Thread with the _warehouse_transfer_ and transfer from w_dist to c_shop 1 iPhone, 1 Samsung, 1 Sony and 1 Nokia.<br>
All the objects receive phones from the warehouse objetcs, in a way that all objects used by 100 threads.<br>
Start values for w_dist <br>
*No. Iphones : 10000<br>
*No. Samsung : 10000<br>
*No. Sony : 10000<br>
*No. Huawei : 10000<br>
*No. Nokia : 10000<br>
*No. Alcatel : 10000<br>
Start values for all shop objetcs used by transactions.<br>
*No. Iphones : 200<br>
*No. Samsung : 200<br>
*No. Sony : 200<br>
*No. Huawei : 200<br>
*No. Nokia : 200<br>
*No. Alcatel : 200<br>
After transactions : <br>
w_dist <br>
*No. Iphones : 9700<br>
*No. Samsung : 9700<br>
*No. Sony : 9700<br>
*No. Huawei : 10000<br>
*No. Nokia : 9700<br>
*No. Alcatel : 10000<br>
All shop objects should be same<br>
*No. Iphones : 300<br>
*No. Samsung : 300<br>
*No. Sony : 300<br>
*No. Huawei : 200<br>
*No. Nokia : 300<br>
*No. Alcatel : 200<br>
* version number 300. for warehous w_dist object<br>
* version number 100. for all object used in transaction<br>
















