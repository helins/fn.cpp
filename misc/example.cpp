#include <iostream>
#include "Fn.hpp"




// This function will be called by all our example.
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
