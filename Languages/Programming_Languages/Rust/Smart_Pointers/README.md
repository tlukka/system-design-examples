- [Smart Pointers (SP)](#sp)
- **Implementing own Smart pointer**
  - [SP without dereference operator `*`](#wo)
  - [SP with dereference operator `*`](#w)
- [Drop Trait](#dr)
- **Most Common SP**
  - [Box`<T>`](#box)
  - [Rc`<T>` = Reference Counting = Multiple Owners](#rc)
    - [Sharing ownership](#so)

<a name=sp></a>
## Smart Pointers
Same as [C++ Smart,shared pointers](/Languages/Programming_Languages/c++/pointers), allocates memory and deallocates when all references to it goes out of scope. References are also smart pointers but they only point to 1 value. Examples: `vec<T>`, String.
- Smart pointers are implemented using structs.
- To dereference the smart pointer(ie get content of memory pointed by smart pointer), smart pointer class should define deref() function from **[Deref trait](#w)**

## Implementing own Smart pointer
<a name=wo></a>
### SP Without dereference operator
That means memory is allocated, smart pointer points to it but we cannot dereference(ie access contents).
```rs
//struct Test(a);       //This struct can accept type=a, hence not generic.
struct Test<T>(T);      //This is generic, since T can be any type

impl <T> Test<T> {          //This is how to define generic
   fn new(x:T) -> Test<T> { //new() takes generic and returns structure object containing x
       Test(x)
   } 
}

fn main () {
  let mut y = Test::new(5);
  //println("{}",*y);               //Compilation Error
}  
```
<a name=w></a>
### SP with dereference operator / deref trait
- if any structure want to implement a trait, that structure need to provide implementations for the trait’s required methods. 
- For dereference opeartor to become available, deref() function of Deref trait(provided by standard library), need to be implemented.
```rs
use std::ops::Deref;

struct Test<T>(T);

//if we try to place new() inside Deref trait, complier will give error since no function named new() is not declared in 
// Standard library provided Deref trait.

impl<T> Deref for Test<T> {                     //Standard Library's deref trait
    type Target = T;                            //type is associated Type to be used inside Deref trait.
    fn deref(&self) -> &Self::Target {          //Defining deref()
        &self.0                                 //return value from structure which dereference want to get
    }
}

impl<T> Test<T> {
    fn new(x: T) -> Test<T> {                  //impl providing new() function.
        Test(x)
    }
}

fn main() {
    let y = Test::new(5);
    assert_eq!(5, *y);          //Now derefrence smart pointer will work
}

$ cargo run
5
```

<a name=dr></a>
## Drop Triat(Running Code on Cleanup with the Drop Trait) = Destructor
Call drop() function when a value is about to go out of scope. We can provide code to release resources like files or network connections when SP goes out of scope.
### Implementing Drop Triat
The Drop trait requires to implement 1 method `drop()` that takes a mutable reference to self.
```rs
struct mySmartPointer {
    data: String,
}

impl Drop for mySmartPointer {
    fn drop(&mut self) {              
        println!("Dropping mySmartPointer, data: `{}`!", self.data);
    }
}

fn main() {
  {
    let c = mySmartPointer {
        data: String::from("my stuff"),
    };
    let d = mySmartPointer {
        data: String::from("other stuff"),
    };
    println!("mySmartPointer created.");
  } //Drop triat is called, since SP goes out of scope
}
$ cargo run
mySmartPointer created
Dropping mySmartPointer, data: my stuff
Dropping mySmartPointer, data: other stuff
```
### Dropping value inside smart pointer early = Calling Destructor Explicitly
We need to call `std::mem::drop()`, this calls destructor.
```rs
struct mySmartPointer {
    data: String,
}

impl Drop for mySmartPointer {
    fn drop(&mut self) {
        println!("Dropping mySmartPointer `{}`!", self.data);
    }
}

fn main() {
  {
    let c = mySmartPointer {
        data: String::from("some data"),
    };
    println!("mySmartPointer created");
    drop(c);
    println!("mySmartPointer dropped before the end of main.");
  }
}
$ cargo run
mySmartPointer created
Dropping mySmartPointer some data               //Drop triat called early without being waiting to go out of scope.
mySmartPointer dropped before the end of main.
```

## Most Common Smart Pointers
<a name=box></a>
### `Box<T>`
This is smart pointer allocated on heap and variable to store pointer lies on stack.
```rs
fn main() {
    let y = Box::new(5);    //5 is allocated on heap. y points to 5 stored on stack.
    println ("{}", *y);     //5
}   //box deallocated here
```
<a name=rc></a>
### `Rc<T>` = Reference Counting = Multiple Owners
- In most cases ownership is clear, but in some cases there can be multiple owners of data. Examples:
  - _1._ In directed graph, there can be multiple nodes pointing to same node. Same node is owned by mutiple nodes. We cannot free pointed node untill all reference to it are not clean.
  - _2._ We allocated some data on the heap for multiple parts of program to read and we can’t determine at compile time which part will finish using the data last.
- **How `Rc<T>` works?** It keeps track of the number of references to a value. If reference count=0, value can be cleaned up without any references becoming invalid.

<a name=so></a>
#### Sharing ownership using `Rc<T>`
Task: Merge 3 linked lists.
```c
//Input
  | 3 |
  b
          | 5 | -> | 10 | -> |Nil|
          a

  | 4 |
  c  
  
//Output: Create linked list where b and c both should point to head of a
  | 3 |--
  b      |
         |-> | 5 | -> | 10 | -> |Nil|
         |    a
         |
  | 4 |--
  c  
```
- **Code giving compilation error**
```rs
//////////  Problmatic Code   /////////////
use crate::List::{Cons, Nil};
enum List {                                 //Definition of linked list
    Cons(i32, Box<List>),
    Nil,
}
fn main() {
    let a = Cons(5, Box::new(Cons(10, Box::new(Nil))));
    let b = Cons(3, Box::new(a));                       //ownership of a is mvoed to b
    let c = Cons(4, Box::new(a));
}
$ cargo build   
Compilation Error. Why?
The Cons variants own the data they hold, so when we create b list, a is moved into b, then b owns a.
We are not allowed to again move a to c.
```
- **Correct Code**
  - _1. List definition change:_ Inplace of `Box<T>`, now we use `Rc<T>`. 
  - _2._ Create list using Rc::new()
  - _3. Store Reference:_ Instead of ownership being moved to b(ie b taking ownership). Only reference is stored with b. 
    - Rc::clone(&`Rc<list>`):
      - This only increses reference count of of data. Different from clone(), which creates deep copy. Data won't be cleaned up unless there are 0 references to it.
      - Rc::clone() provides immutable references(non-changable).
```rs
enum List {
    Cons(i32, Rc<List>),                                //1
    Nil,
}

use crate::List::{Cons, Nil};
use std::rc::Rc;

fn main() {
    let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));          //2
    let b = Cons(3, Rc::clone(&a));                                     //3. Reference=1
    let c = Cons(4, Rc::clone(&a));                                     //Reference=2
}
```
