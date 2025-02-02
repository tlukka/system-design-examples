## [Majority Element](https://leetcode.com/problems/majority-element/)
- The majority element is the element that appears more than `n / 2` times. You may assume that the majority element always exists in the array.
- Example
```c
Input: nums = [3,2,3]
Output: 3

Example 2:
Input: nums = [2,2,1,1,1,2,2]
Output: 2
```

### Approach-1  //Unordered_map. Time:O(n), Space:O(n)
- **Logic**
  - 1. Iterate thru array create, `unorderd_map<key=element, value=count>`
  - 2. Return key having maximum value 
```c++
class Solution {  
    static bool compare_func(pair<int,int> i, pair<int, int> j){
        return i.second > j.second;    
    }
    
public:
    int majorityElement(vector<int>& nums) {
        if (nums.size() == 1)
            return nums[0];
        
        unordered_map<int,int> um;
        for (auto i:nums)
            um[i]++;

        //Search max value
        unordered_map<int,int>::iterator it;
        it = min_element(um.begin(), um.end(),compare_func);
        return it->first;
    }
};
```

### Approach-2          //[Boyer Moore Voting Algorithm](/DS_Questions/Algorithms). Time:O(n), Space:O(1)
- Problem is solved there, see code there
