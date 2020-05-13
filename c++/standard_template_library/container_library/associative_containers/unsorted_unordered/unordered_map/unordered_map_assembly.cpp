/*      unordered_map_assembly.cpp

******POINTS TO REMEMBER******
1. Stack grows in reverse direction.
  |----stack grows-----|-------------><------heap grows------
 0x450                0x200
 rbp                  rsp       

2. Arguments to function are stored in:  rdi, rsi, rdx, rcx, r8...r15 
*************************************

**********CTR, DTR CALLED***********
unordered_map<datatype1, datatype2> calls
  unordered_map<datatype1, datatype2, hash<datatype1>, equal_to<datatype1>, 
                allocator<pair<datatype1 const, datatype2>>> :: unordered_map(){
                ....
  }

And destructor:
unordered_map<datatype1, datatype2, hash<datatype1>, equal_to<datatype1>, 
              allocator<pair<datatype1 const, datatype2>>> :: ~unordered_map(){
              ........
}
*************************************
        
*/

#include<iostream>
#include<unordered_map>
using namespace std;

int main(){
        unordered_map<int,char> uam;
}

/* ASSEMBLY:
main:
        push    rbp             //1a    
        mov     rbp, rsp        //1b
        sub     rsp, 64         //2. stack of size=64 created
        lea     rax, [rbp-64]   //3
        mov     rdi, rax        //4
        call    unordered_map<int, char, hash<int>, equal_to<int>, allocator<pair<int const, char> > >::unordered_map() [complete object constructor]
        lea     rax, [rbp-64]
        mov     rdi, rax
        call    unordered_map<int, char, hash<int>, equal_to<int>, allocator<pair<int const, char> > >::~unordered_map() [complete object destructor]
        mov     eax, 0
        leave
        ret

STEPS:
1. Function Epilogue.
   a.Push value of rbp0 somewhere on stack
   ------------                        Head     
   rbp0     rsp0                Stack | rbp0=0x450 |

   b.Move rbp to rsp
   --------------------
            rsp10
            rbp1

2. Create stack for main            
   ---------------main-----
            rbp1        rsp1        
            0x364       0x300

3. LEA(Load Effective address)
   ----------------main-----            Registers
            rbp1         rsp1           rax = 0x300
                         /\
                         rax       

4. Store 1st argument for function call in rdi
                                        rdi = rax(1st Argument) <<this pointer

5. Call the template function
*/
