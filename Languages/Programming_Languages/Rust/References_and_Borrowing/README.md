- [Reference = Borrowing](#bow)
- [Dangling Reference](#danglingref)
- [Mutable Reference](#mutref)
  - [1. Mutable & immutable References in same scope not allowed](#MutImmutable)
  - [2. Two Mutable references are not allowed in same scope](#MutMut)
  - [3. Mutable References are allowed in seperate scope](#MutSep)
- [Borrow Checker](#bc)
  - [1. Generic / Named Lifetimes](#genericlt)
    - [1.1 Function will return smaller of both lifetimes](#smaller)
- [Lifetime Elision](#lifee)
  - [1. How compiler determines Lifetime](#how)
- [Lifetime for structs](#struct)
- [Static lifetime](#static)


<a name="bow"></a> 
## Borrowing = Reference (&var)
- **What?** Means passing the reference of a variable. Borrowing means that needed to be returned(we cannot change).
```rust
fn print( a : &Vec<i32>) {
  println!("{}"a.len());            //1
  //a.push(2);                      //Compilation error. We cannot change borrowed. Changing immutable
}
fn main() {
  let mut v = Vec::new();
  v.push(1);
  print(&v);                         //Borrowed not moved
  println!("{}", v[0]);              //1
}
```

<a name="danglingref"></a>
## Dangling Reference
- **Dangling pointer?** Pointer points to memory, memory is freed and pointer is used.
- **Dangling reference?** Similar to Dangling pointer, when reference to a value is used, value is freed and reference is used after that.
- **C++ Problem:** Since b is local variable and is freed as fun() goes out of scope.
```c++
int& fun() {    //Function returning reference
  int b = 10;
  return b;
}

int main() {
  int &a = fun();       //a is reference variable pointing to b, which does not exist
  cout << a;            
}
# g++ test.cpp        //No compile error
# ./a.out
  Segmentation Fault
```
- **Rust:** Complier does not allow DR.
```rust
fn fun() -> &i32 {
  let b = 10;
  &b                        //Reference is returned
}
fn main() {
  let a = fun();
}
# rustc test.rs
Compilation error

Solution: Return by value = Transfer ownership
fn fun() -> i32 {
  let b = 10;
  b                        
}
```

<a name="mutref"></a>
## Mutable Reference
- We know a borrowed item cannot be changed, but mutable reference can be changed.
```rust
fn print( a : &mut Vec<i32>) {        //3. Accept mutable reference using `some_string: &mut String`
  a.push(2);
}
fn main() {
  let mut v = Vec::new();             //1. Declare mutable variable
  v.push (1);
  print (&mut v);                     //2.Create mutable Reference using `&mut`
  println! ("{}", v[0]);
}
# rustc test.rs
# test.exe
```

<a name="MutImmutable"></a>
### 1. Mutable & immutable References in same scope not allowed
```rust
    let mut v = vec![1, 2, 3, 4, 5];
    let first = &v[0];
    v.push(6);                                    //Compilation Error
    println!("first:{}", first);
```
*Compilation Error Why?*
  - The code might look like should work. 
  - This error is due to the way vectors work. adding a new element onto the end of the vector might require allocating new memory and copying the old elements to the new space. 
  - if there isn’t enough room to put all the elements next to each other where the vector currently is. In that case, the reference to the first element would be pointing to deallocated memory. 
  - The borrowing rules prevent programs from ending up in that situation.

<a name="MutMut"></a>
### 2. Two Mutable references are not allowed in same scope
- *Why?* To avoid data race conditions. Race condition occurs when any of 3 behaviours happen:
    - Two or more pointers access the same data at the same time.
    - At least one of the pointers is being used to write to the data.
    - There’s no mechanism being used to synchronize access to the data.
```rust
  let mut s = String::from("hello");
  let r1 = &mut s;
  let r2 = &mut s;                            //Compilation Error
  println!("{}, {}", r1, r2);
```
<a name="MutSep"></a>
### 3. Mutable References are allowed in seperate scope
```rustc
  let mut s = String::from("hello");
  {
    let r1 = &mut s;
  } // r1 goes out of scope here, so we can make a new reference with no problems.
  let r2 = &mut s;
```

<a name=bc></a>
## Borrow Checker
- Rust compiler has a borrow checker that compares scopes to determine whether all borrows are valid.
- _Lifetimes_
  - a is main()'s block
  - b is Block-1
```rs
fn main() {
  let a = 10;
  {                   //Block-1
    let mut b = &a;
  }
  println!("{}",b);   //Compile Error, Borrow=Reference of variable goes out of scope and used.
}
```
<a name=genericlt></a>
### 1. Generic / Named Lifetimes
- **Compliation Error. Why?** rustc cannot ascertain Return value (&str) is reference of a or reference of b.
```rs
fn largest(x:&str, y:&str) -> &str{
    if x.len() > y.len() {
        x
    } else {
        y
    }
}
fn main() {
    println!("{}", largest(String::from("abcd"), String::from("xyz")));
}
$ cargo run                 //Compilation error
   Compiling 
error[E0106]: missing lifetime specifier
 --> src/test.rs:9:33
  |
9 | fn largest(x: &str, y: &str) -> &str {
  |               ----     ----     ^ expected named lifetime parameterr
```
- **Solution: Generic lifetime parameter `'a`** 
  - Prefix every parameter with `'a`. Apostrophe a (`'a`) denotes reference has generic lifetime. This is also called _Lifetime Annotation Syntax_.
  - Lifetime of references still does not change. 
  - Lifetime annotations only need to be declared in function parameters, it does not goes inside body of function.
  - Examples
```rs
&i32        // a reference
&'a i32     // a reference with an explicit lifetime
&'a mut i32 // a mutable reference with an explicit lifetime
```
- Fixed code
```rs
fn largest<'a>(x:&'a str, y:&'a str) -> &'a str{           //Need to declare generic lifetime parameters inside <> before parameter list.
    if x.len() > y.len() {
        x
    } else {
        y
    }
}
fn main() {
    println!("{}", largest(&String::from("abcd"), &String::from("xyz")));
}
$ cargo run
$ test.exe
abcd
```

<a name=smaller></a>
#### 1.1 Function will return smaller of both lifetimes
```rs
fn main() {                           //Block-1
    let x = String::from("abcd");
    let result;
    {                                 //Block-2
        let y = String::from("xyz");
        result = largest(x, y);
    }
    println!("{}", result);           //Printing string which is out of scope
}
```
Compliation Error Why?
- largest() will return smaller lifetime from x and y. y has smaller lifetime(ie Block-2).
- largest() will return y, which goes out of scope and we try printing string which is out of scope

<a name=lifee></a>
## Lifetime Elision
- The patterns programmed into Rust complier which applies lifetime rules in desired situtation.
- **Input lifetimes:** Lifetimes on function or method parameters.
- **Output Lifetimes:** lifetimes on return values.
<a name=how></a>
### 1. How compiler determines Lifetime
- Compiler uses 3 rules to figure out what lifetimes references have when there aren’t explicit annotations. If the compiler gets to the end of the three rules and there are still references for which it can’t figure out lifetimes, the compiler will stop with an error.
- _Rule-1:_ Each parameter that is a reference gets its own lifetime parameter. 
```rs
fn longest<'a, 'b>(x: &'a str, y: &'b str) -> &str {
```
- _Rule-2:_ if there is exactly one input lifetime parameter, that lifetime is assigned to all output lifetime parameters.
```rs
fn foo<'a>(x: &'a i32) -> &'a i32.
```
- _Rule-3:_ If there are multiple input lifetime parameters, but one of them is `&self` or `&mut self`, the lifetime of self is assigned to all output lifetime parameters.

<a name=struct></a>
## Lifetime variables for structs
```rs
struct test<'a> {                       //struct having 1 member having lifetime
    part: &'a str,
}
impl<'a> test<'a> {                     //impl need to be declared with lifetime var,
    fn fun(&self) -> i32 {
        3
    }
}
```
<a name=static></a>
## Static lifetime
- This reference can live for the entire duration of the program. All string literals have the 'static lifetime. 
- The text of this string is stored directly in the program’s binary, which is always available
```rs
let s: &'static str = "test";
```
