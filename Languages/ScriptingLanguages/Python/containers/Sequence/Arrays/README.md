**Arrays**


### Arrays (homogeneous data)
- Arrays in python can only contain elements of same data types i.e., data type of array should be homogeneous. 
- This consumes far less memory than lists.
- Lists can contain elements of different data types i.e., data type of lists can be heterogeneous. It has the disadvantage of consuming large memory
```py
import array
a = array.array('i', [1, 2, 3])
for i in a:
    print(i, end=' ')    #OUTPUT: 1 2 3

a = array.array('i', [1, 2, 'string'])    #OUTPUT: TypeError: an integer is required (got type str)

a = [1, 2, 'string']
for i in a:
   print(i, end=' ')    #OUTPUT: 1 2 string
```
