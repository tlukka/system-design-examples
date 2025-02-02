**[Duplicate elements in unsorted array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)**
- [Approach-1, Store count, O(n), O(n)](#a1)
- [Approach-2, Hash Table, O(n), O(n)](#a2)
- [Approach-3, O(n), O(1)](#a3)
  - [Logic](#l)

## Duplicate elements in unsorted array
- Find duplicates in array in O(n) time & constant extra space.
-  where all the integers of nums are in the range `[1, n]`
- Example
```c
Input: [4, 3, 2, 7, 8, 2, 3, 1]
Output: [2, 3]
```

<a name=a1></a>
### Approach-1    //Store count   `Time:O(n) Space:O(n)`
- Traverse array store count in seperate array
```c
Input:        4   3   2   7   8   2   3   1

Count Arr:    1   2   2   1   0   0   1   1   0  
index         0   1   2   3   4   5   6   7   8
-> index=0 store freq of number 1
-> index=1 store freq of number 2
```

<a name=a2></a>
### Approach-2    //Hash Table     `Time:O(n), Space:O(n)`
- Take a hash table.
- Insert into HashTable: if element is not present earlier in hashMap.
  - if element exists in hashtable(it means its duplicate). -> insert in vector
- Complexity:
  - Space: O(n)
  - Time: O(1)
```c
    vector<int> findDuplicates(vector<int>& nums) {
      unordered_set<int> us;
      vector<int> v;

      for(auto i:nums){
        if(us.find(i) != us.end())
          v.push_back(i);
        else
          us.insert(i);
      }
      return v;
    }
```

<a name=a3></a>
### Approach-3    //Time:O(n), Space:O(1)
- We will extend Approach-1. In approach-1 we are storing count of occurences in Seperate array, Now we will store count of occurences of elements in input array only. {Since we donot have extra Space}
<a name=l></a>
#### Logic
- Store count of occurences of elements in Original Array. Increment element by sizeofArray.
  - *Why increment by sizeofArray* Because we need to retrieve original element also. This is Preserving original Element.
- Traverse array again
  - if `arr[i] > 2*sizeOfArray` it means This element(ie index) occured 2 times.
  - if `arr[i] > 3*sizeOfArray` it means This element(ie index) occured 3 times.
```c
Array:    4   3   2   7   8   2   3   1
Index:    0   1   2   3   4   5   6   7

a[0]=4. a[4] += 2*a[0]    //Increment 8 at index 4`

Array:    4   3   2   7   8*2=16    2   3   1
Index:    0   1   2   3     4       5   6   7

*`i = 1, a[1]=3, Increment 8 at index 3`*
`a[3] = a[3]+8`
a[1]=3.   a[3] += 2*a[1]

Array:    4   3   2   7  16   2   3   1
Index:    0   1   2   3   4   5   6   7
```

| elements-> | 4 | 3 | 2 | 7+8=15 | 16 | 2 | 3 | 1 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Indexes-> | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

*`i = 2, a[2]=2, Increment 8 at index 2`*
`a[3] = a[3]+8`

| elements-> | 4 | 3 | 2+8=10 | 15 | 16 | 2 | 3 | 1 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Indexes-> | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

*`i = 3, a[3]=15, Since we are adding 8 to Original Elements, We need to retrieve Original element to increment its occurance count. original_element=a[i]%8. We might have added 8 and this might be incremented value, which is the present case. original_element=a[4]%8=7. Increment 8 at index 7`*
`a[7] = a[7]+8`

| elements-> | 4 | 3 | 10 | 15 | 16 | 2 | 3 | 1+8=9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Indexes-> | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

*`i = 4, a[4]=16, original_element=a[4]%8=0. Increment 8 at index 0`*
`a[0] = a[0]+8`

| elements-> | 4+8=12 | 3 | 10 | 15 | 16 | 2 | 3 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Indexes-> | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

*`i = 5, a[5]=2, original_element=a[2]%8=2. Increment 8 at index 2`*
`a[2] = a[2]+8`

| elements-> | 12 | 3 | 10+8=18 | 15 | 16 | 2 | 3 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Indexes-> | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

*`i = 6, a[6]=3, original_element=a[6]%8=3. Increment 8 at index 3`*
`a[3] = a[3]+8`

| elements-> | 12 | 3 | 18 | 15+8=23 | 16 | 2 | 3 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Indexes-> | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

*`i = 7, a[7]=9, original_element=a[7]%8=1. Increment 8 at index 1`*
`a[1] = a[1]+8`

| elements-> | 12 | 3+8=11 | 18 | 23 | 16 | 2 | 3 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Indexes-> | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

**Duplicate elements=index-of-array whose value > 16?**
- Remember, this is not input array, this is a hashMap where elements are indexes and occurence count is value at index.
```
vector<int> findDuplicates(vector<int>& a) {
    int size = a.size();
    vector<int> v;
    for (int i = 0; i < size; i++)
    {
      original_element = a[i]%size;
      a[original_element %s] = a[original_element % s] + s;
    }
    for (int i = 0; i < s; i++){
        if (a[i] > s*2)
        {
            if(!i)                                    //Index 0 will store count of max element not 0
              v.push_back(size);
            else
              v.push_back(i);
        }
    }
    return v;
}

int main(){
  vector<int> a = {4,3,2,7,8,2,3,1};
  vector<int> b = findDuplicates(a);
  for(auto i:b)
    cout<<i<<" ";
}  
```
