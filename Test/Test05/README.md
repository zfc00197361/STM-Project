Mixed Nested transaction Test with any number of threads<br>
This test use three different functions such as _warehouse_transfer_, _nested_warehouse_transfer_ and _complex_warehouse_transfer_.<br>
The _warehouse_transfer_ takes onlt two objects and create a trnsactions with them.<br>
The _nested_warehouse_transfer_ takes four WAREHOUSE type objects and creates multyple level transactions with mixed objects.<br>
The function _nested_warehouse_transfer_ create nested transaction and invokes the _warehouse_transfer_ function<br>
as a most inner transaction.<br>
The _complex_warehouse_transfer_ takes four WAREHOUSE type of objects and a vector with WAREHOUSE objetcs, and tranfere items between <br>
the collection and the sibngle objetcs.br>
<br>
TEST details:


