- **const Rules**
  - **const Member variables**
    - [1. Initialized only once](#c1)
  - **const Member Function**
    - [1. can only change mutable members](#c2)
  - **const function arguments**
    - [1. cannot be modified](#c3)
  - **const object**
    - [1. Member variables present in const object cannot be changed](#c4)
    - [2. const object can only call const function](#c5)
- **explicit**
  - [implicit conversion / Conversion constructor](#im)
- **[extern](#ext)**
  - [extern C](#extc)
- [final keyword](#final)
- **[new](new)**
- **scope Resolution**
  - [1. class members can be accessed using sr](#sr1)
- **static**
  - **static member variables**
    - [1. Initialized outside class](#s1)
  - **static class member function**
    - [1. Called without class object](#s2)
    - [2. Don't have access to this pointer or super](#s3)
  - [3. static class](#sc)
- [this](#this)
- [volatile variable](#vo)


## const
### const Member Variables
<a name=c1></a>
#### 1. const member variables can be initialized only once
java does not have const keyword, rather it has final.
```cpp
        const int a = 2;
        a=4;                 //Compilation Error
```
### const Member Function
<a name=c2></a>
#### 1. Can only change mutable variables 
int const fun(), const int fun()//Both are same function returning constant Integer
```cpp
        int a;    mutable int c;
        void fun() const{
            a = 5;        //Compilation Error
            c = 2;        //OK
        }
```
### const Function Arguments
<a name=c3></a>
#### 1. Cannot be modified
```cpp
        int fun(const int a){
            a=10;    //Compilation Error
        } 
```
### const Objects
<a name=c4></a>
#### 1. Member variables present in cosnt object cannot be changed
```cpp
        const obj s(1,2);
        obj.a=100;    //Compilation Error
```
<a name=c5></a>
#### 2. const object can only call const function
```cpp
class A {
public:
	void fun() { cout << "fun"; }
};

int main() {
	const A obj;
	obj.fun();
}
$ ./a.out
Compilation Error				//Can be resolved either by making fun() const. or making obj non-const.
```

## explicit
<a name=im></a>
#### Implicit conversion / Conversion Constructor
- Compiler converts data-type to class object which is wrong. This is allowed for contructor taking 1 argument.
- Example-1: fun() takes object as argument but we passed int and compiler did conversion internally. This is done using default constructor(1).
```cpp
class A {
  int a;
public:
    A(int b) : a(b) {}             //Conversion ctr
    int get() {
      return a;
    }
};

int main() {
  A obj1 (3);
  cout << obj1.get();			//3
  obj1 = 4;				//Implicit Conversion
  cout << obj1.get();			//4
}
```
**Explicit** Explicit can only come in front of 1 argument constructor. Prefixing the explicit keyword before constructor prevents the compiler for using that constructor for implicit conversions. Above code will give error, we need.
```c++
class A {
  ...
  public:
     explicit A(int b) : a(b) {}             //CONSTRUCTOR PREFIXED with EXPLICIT stops implicit conversion
  ...
};
```

<a name=ext></a>
## extern
<a name=extc></a>
### extern C
**What?**
- With extern C we tell C++ Compiler not to [mangle name](/Languages/Programming_Languages/c++/#nm) of functions/symbols.
- "extern C" is used to call C functions from C++ code.

**Problem: Compile C code with g++ compiler**
- fun() is present in C code. fun() will be used by C++ code by shared library(`*.so`) which will be dynamically linked.
- C++ Compiler will [mangle function name](/Languages/Programming_Languages/c++/#nm) from fun() to f12asfn() at time of object code creation.
- At time of Linking, C++ code calls f12asfn() but shared-library will call the function by actual name, and actual name is mangled by compiler it will generate a linker error.
```c
int printf(const char *format,...);
int main(){
    int a = 1;
    printf("%d",a);
}
$ g++ test.cpp
$ ./a.out
undefined reference to `printf(char const*, ...)'
```

**Solution:** Ask compiler not to mangle function name if its coming from C.
```cpp
#ifdef __cplusplus
extern "C" {                //Do not mangle name of foo().
#endif
  int printf(const char *format,...);
#ifdef __cplusplus
}
#endif

int main(){
    int a = 1;
    printf("%d",a);
}
$ ./a.out
1
```

<a name=new></a>
## new keyword
Used for Allocating Objects.
```cpp
ptr = new data_type;

double *ptr = new double; 
char *ptr = new char[20];	     
char *ptr = new char[20](); 	//Initializing Array with 0 values
int* ptr = new int(5);		//Allocates int, Initializes to 5
```

## scope resolution
<a name=sr1></a>
#### 1. class members can be accessed using sr
```cpp
class A {
public:
    void set(int x) {A::a = x;}		//“A::a = x” is same as “this->a = x”
    int get() { return a; }	//Bright Computing(Netherland)
private:
    int a;
};

int main() {
    A obj;
    obj.set(4);
    cout << obj.get();
    return 0;
}
```

## static
It has different meaning in different contexts.
### Static member variables
<a name=s1></a>
#### 1. static variable are initialized outside the class
- static variables are shared among all Objects of class. Only 1 copy of variables is created.
- Since we cannot have multiple copies of static variable hence cannot be initialized inside constructor.
- _Initialization:_ at compile-time.
- _Calling:_ Without creation of class object, ie shared among objects.
- Java does not support Static Local variables
```cpp
class A{
  static int var;
public:
  A(){}
  void disp(){
     cout<<var;
  }
};
int A::var=10;  //Rule: Initialize static variable. THIS IS REQUIRED, else Compiler will give undefined reference Error for var
int main(){
	A obj1, obj2;
	obj1.disp();    //10
	obj2.disp();    //10
} 
```

### Static member Functions
<a name=s2></a>
#### 1. Called without class object
SMF can access: Static Data Members, Static Member Function, non-static functions from outside class.
```c++
class A{
public:
  static void fun(){
    cout<<"fun";
  }
};
int main(){
  A::fun();         //fun
}
```

<a name=s3></a>
#### 2. static member functions don't have access to this pointer or super
```cpp
class A {
    static int a;
public:
    static A& fun();
};
int A::a = 0;
A& A::fun() {
    A::a++;
    return *this;
}
int main() {
    A obj;
    obj.fun();
}
$ ./a.out
‘this’ is unavailable for static member functions
```

<a name=sc></a>
#### 3. static class
Only present in Java. Way of grouping classes in Java. Only Inner(Nested classes) can be created static. But its not necessary that all nested classes needs to be static. 
```java
public class test{
    public static class InnerStatic{
        public InnerStatic(){    System.out.println("InnerTest");    }
    };
    public test(){    System.out.println("test");    }    
};
```

<a name=final></a>
## final

|Final|Java|C++|
|---|---|---|
|Class variable|<ul><li>Should be initialized at time of declaration</li></ul><ul><li>Value cannot be changed</li></ul>|same as const|
|Class Method|<ul><li>if final function is defined in base class, it cannot be overridden in derv class(Compilation error)</li></ul><ul><li>Final methods gets inherited</li></ul>|final|
|final class|Cannnot be extended/inherited||


<a name=this></a>
## this pointer
- This pointer holds address of current active object
- this pointer is stored on stack, heap, DS(based on implementation)
- We know only every object has seperate data members, But All objects have same member functions in Code segment. So How a function knows which object is calling it to set/get the variables => Using this pointer.
- `(*this):` returns address of current object.
 ```c++
class A{
  int a;
public:
  void fun(int x){        //Implemented as void fun(const test *this, int x)
    a = x;                //this->a=x
   }
};

int main(){
    A obj
    obj.fun(10);                //obj.fun(&obj, 10);
}
```

<a name=vo></a>
### Volatile
- Request to complier to not place variable on Register(ie donot Optimize the variable).
  - _Optimization:_ 
    - _1._ Compiler moves some variables from memory to register to perform fast & deliver speed.
    - _2._ Programmer Optimization: Less time,space complexity of written code
```c
int main (){
   int val;   val++;		//val would be copied from Memory to CPU register, then operation is performed.
}
int main (){
   volatile int value;  val++;	//val not copied from Memory to CPU register.
}
```
- **Why volatile?**
  - _1._ volatile variable is not placed on register, making sure variable is not changed outside current scope.
- **Use Case:** 2 Threads are talking on global variable. This variable should not be optimized(ie should be volatile)
  - Let Thread-1 does var++, Compiler optimizes the variable & places on Register. Since threads can execute asynchronously, Thread-2 comes in & tries to read. 
  - Since on variable some CPU operations are going on, its final value is yet no calculated. Thread-2 reads wrong value.
