/*      sort_array_of_0_1_2.cpp

Situation/Task: Given a array with integers 0, 1, 2 to represent the color red, white & blue.
You need to sort the array INPLACE and in one go O(n).
Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Logic-1 (not do this)
- Traverse the array, count no of 0s,1s,2s. //3*8=24 bytes extra
- Again Traverse the array, replaced elements with count of 0s,1s,2s
- complexity:
  Time: 2O(n). Since twice traversal of array is needed
  Space: 3 element extra array needed to be taken

**********Logic-2(Dutch National Flag Problem)*********
http://users.monash.edu/~lloyd/tildeAlgDS/Sort/Flag/
- Point here is we keep all 1's in middle, keep all 0's on left
  and keep all 2's on right.
- Take 3 pointers:
        lo, mid, high
-Do these things on encountering different elements:
        if(ele==1) do nothing, just increment mid
        if(ele==0) swap mid with lo. increment lo and mid
        if(ele==2) swap mid with hi. decrement hi.

Complexity:
Time: O(n)
Space: O(1). No extra space required
*****************************************************
*/
#include<iostream>
#include<vector>
using namespace std;

class A {
public:
        void sort012(vector<int>& nums);
        void disp(vector<int>& nums){
                for (int i = 0; i < nums.size(); i++)
                cout << nums[i] << " ";
        }
};

void A::sort012(vector<int> &a){
        int lo = 0;
        int hi = a.size() - 1;
        int mid = 0;

        while(mid <= hi){
                if(a[mid]==0){
                        swap(a[lo], a[mid]);
                        lo++; mid++;
                }else if(a[mid]==1){
                                mid++;
                }else if(a[mid]==2){
                        swap(a[mid],a[hi]);
                        hi--;
                }
        }
}

int main(){
        vector<int> v={2,0,2,1,1,0};
        A a;
        a.sort012(v);
        a.disp(v);
}
/*
Output:
# ./a.out
0 0 1 1 2 2
*/
