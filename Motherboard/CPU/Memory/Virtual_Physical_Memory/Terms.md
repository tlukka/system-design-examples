## Terms
- **Page?** Block of memory on Hard Disk.
- **Paging?** Process of dividing Hard-Disk to equal-sized blocks is called paging.
- **Demand Paging?** Loading the pages into RAM whenever they are required.
- **Pure Demand Paging?** Page fault occurs to bring every page in RAM. Steps: 
    - *1.* Start process without page in RAM.  
    - *2.* Page fault occurs  
    - *3.* Bring page to RAM  
    - *4.* Continue to execute 
    - *5.* Page not found [Go tp step2]
- **Frame?** Block of memory on RAM/Physical Memory.
- **Page Fault?**
  - CPU issues [trap()](/Motherboard/CPU/Memory/Virtual_Physical_Memory/Convert_Virtual_to_Physical_Address/16Bit/) system call. 
  - OS picks a LRU Frame(from Physical Memory/RAM) and moves/writes back to the Hard-Disk/Virtual-Memory. 
  - Then copies Page into RAM. MMU updates mapping.
- **[trap()](/Motherboard/CPU/Memory/Virtual_Physical_Memory/Convert_Virtual_to_Physical_Address/16Bit/)** switches user mode to kernel mode. 
  - Traps are Expensive because of these things done when trap instruction executed? 
    - _1._ rax is copied on stack. rdi, rsi, rcx holds the parameters to passed to trap system call.     //Registers are flushed. CPU caches are flushed. 
    - _2._ Page swap(copies trap system call instructions to RAM). Moves LRU Frame(from RAM) to Hard Disk & trap instruction page to RAM.
    - _3._ MMU mapping updated.
    - _4._ TLB updated, branch prediction tables internal to the CPU updated.
- **Page Eviction:** Movement of pages in/out of RAM is done by SWAPPER.
- **MMU(Memory Management unit)** Takes Virtual address(of Virtual Memory) as Input provides Physical Address(of RAM) as output ie translate virtual to physical address.
