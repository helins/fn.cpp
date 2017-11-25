# Fn

Want to be more functional when coding in C++ ?

Create wrappers for free functions and methods of all sorts and kinds at
**compile time**, unlike std::function which uses dynamic allocation and is a
lot heavier.

<!> This is a bit of a crazy experiment with generics. But it works well.

## Usage

In short :
```cpp
#include "Fn.hpp"


// Any free function.
Fn< int( int ) >::wrap( my_free_function ) ;

// Any method for a given object.
Fn< int( int ) >::wrap< MyClass, &MyClass::my_method >( &my_class_instance ) ;

// Any static method.
Fn< int( int ) >::wrap< Myclass::a_static_method >() ;

// Any object implementing operator().
Fn< void( void ) >( some_object ) ;


// The obvious use case is being able to pass those Fn's to other functions.

// For instance :
void invoke( Fn< int( int, int ) f, int i, int j ) {
    f( i ,
       j ) ;
    }


invoke( Fn< int( int, int )::wrap< AnotherClass, &AnotherClass::add_ints >( &some_instance ) ,
        42 ,
        24 ) ;
```

In long (working example) :
```cpp
#include <iostream>
#include "Fn.hpp"




// The baseline function which will be called by all our examples.
void print_ij( const char *const comment ,
               const int         i       ,
               const int         j       ) {
    
    std::cout << comment
              << "  =  "
              << i + j 
              << std::endl ;
    }




// A simple free function we will test.
void free_fn( const int i ,
              const int j ) {
    
    print_ij( "Free function" ,
              i               ,
              j               ) ;
    }




// A struct with different kinds of methods we will test.
struct StructTest {


    void meth( const int i ,
               const int j ) {
        
        print_ij( "Struct method" ,
                  i               ,
                  j               ) ;
        }




    void meth_const( const int i ,
                     const int j ) const {
        
        print_ij( "Struct const method" ,
                  i                     ,
                  j                     ) ;
        }




    static void meth_static( const int i ,
                             const int j ) {
        
        print_ij( "Struct static method" ,
                  i                      ,
                  j                      ) ;
        }




    void operator()() {

        std::cout << "Struct operator()" << std::endl ;
        }
    } ;




// A function invoking it's Fn argument we'll be using for testing.
void invoke( Fn< void( int, int ) > fn ) {

    std::cout << "Invoking arg Fn... " ;
    fn( 2, 2 ) ;
    }




int main() {
    
    // We will pass our wrapped functions/methods to `invoke` 

    // Free function
    invoke( Fn< void( int, int ) >::wrap< free_fn >() ) ;


    // Struct
    StructTest st ;

    // Struct - Method
    invoke( Fn< void( int, int ) >::wrap< StructTest, &StructTest::meth >( &st )  ) ;

    // Struct - Const method
    invoke( Fn< void( int, int ) >::wrap< StructTest, &StructTest::meth_const >( &st )  ) ;

    // Struct - Static method
    invoke( Fn< void( int, int ) >::wrap< StructTest::meth_static >() ) ;
    
    // Struct - operator()
    Fn< void( void ) > st_op( st ) ;
    st_op() ;



    // Lambdas - Preparing several examples
    auto l1 = []( const int i ,
                  const int j ) {
        
        print_ij( "Lambda non mut" ,
                  i                ,
                  j                ) ;
        } ;

    const auto l2 = []( const int i ,
                        const int j ) {

        print_ij( "Const lambda non mut" ,
                  i                      ,
                  j                      ) ;
        } ;


    auto l3 = []( const int i ,
                  const int j ) mutable {
                  
        print_ij( "Lambda mut" ,
                  i            ,
                  j            ) ;
        } ;


    const auto l4 = []( const int i ,
                        const int j ) mutable {
        
        print_ij( "Const lambda mut" ,
                  i                  ,
                  j                  ) ;
        } ;


    auto l5 = Fn< void( int, int ) >( []( const int i ,
                                          const int j ) {
        
        print_ij( "Lambda in Fn ctor" ,
                  i                   ,
                  j                   ) ;
        } ) ;


    auto l6 = Fn< void( int, int ) >( []( const int i ,
                                          const int j ) mutable {
        
        print_ij( "Lambda mut in Fn ctor" ,
                  i                       ,
                  j                       ) ;
        } ) ;
    

    // Lambdas - Invoking examples
    invoke( l1 ) ;
    invoke( l2 ) ;
    invoke( l3 ) ;
    invoke( l4 ) ;
    invoke( l5 ) ;
    invoke( l6 ) ;


    // Lambdas - Directly in function call
    invoke( []( const int i ,
                const int j ) {
        
        print_ij( "Lambda arg non mut" ,
                  i                    ,
                  j                    ) ;
        } ) ;


    // Lambdas - Directly in function call, mutable
    invoke( []( const int i ,
                const int j ) mutable {
        
        print_ij( "Lambda arg mut" ,
                  i                ,
                  j                ) ;
        } ) ;

    
    return 0 ;
    }
```

## Inspiration

[Member Function Pointers and the Fastest Possible C++
Delegates](https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible)

[The Impossibly Fast C++
Delegates](https://www.codeproject.com/articles/11015/the-impossibly-fast-c-delegates)


## License

The MIT License (MIT)
Copyright © 2017 Adam Helinski

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
