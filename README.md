# BarcodeHash

![alt text](https://raw.githubusercontent.com/anthonyhseo/BarcodeHash/master/ArrayBSTHash.jpg)
The graph above shows the data for the array, BST and HashTable. As you can see, as n gets large the timing for the array grows linearly. The graph below shows the data without the array timing.

![alt text](https://raw.githubusercontent.com/anthonyhseo/BarcodeHash/master/BSTHash.jpg)
The timing for the BST is O(logN). For the HashTable, you can see that the earlier elements have higher timing than the later elements. This makes sense because the later elements are towards the front of the linked list while the earlier ones are towards the back of the list. 