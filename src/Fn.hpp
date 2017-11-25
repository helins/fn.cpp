#ifndef SRUTIL_DELEGATE_INCLUDED
#define SRUTIL_DELEGATE_INCLUDED





template < typename TSignature >

class Fn ;




template < typename    TRet  ,
           typename ...TArgs >

class Fn< TRet( TArgs... ) > {


    private:


        void *const _object_ptr  ;

        TRet (* _stub_fn_ptr)( void *const object_ptr, TArgs... ) ;




        Fn( void *const object_ptr                               ,
            TRet (*const stub_ptr)( void *const object_ptr, TArgs... ) )

          : _object_ptr(  object_ptr ) ,
            _stub_fn_ptr( stub_ptr   ) {}




        template < TRet (*const TFn)( TArgs... ) >

        static inline TRet _stub_function( void *const  _       ,
                                           TArgs        ...args ) {

            return TFn( args... ) ;
            }




        template < typename T                     ,
                   TRet (T::*TMethod)( TArgs... ) >

        static inline TRet _stub_method( void *const object_ptr ,
                                         TArgs       ...args    ) {

            return ( static_cast< T* >( object_ptr )->*TMethod )( args... ) ;
            }




        template < typename T                           ,
                   TRet (T::*TMethod)( TArgs... ) const >

        static inline TRet _stub_const_method( void *const object_ptr ,
                                               TArgs       ...args    ) {

            return ( static_cast< T* >( object_ptr )->*TMethod )( args... ) ;
            }




    public:
        

        Fn() : _object_ptr(  nullptr ) ,
               _stub_fn_ptr( nullptr ) {}




        template < typename T                                      ,
                   TRet (T::*TMethod)( TArgs... ) = &T::operator() >

        Fn( T *const object_ptr ) : _object_ptr(  object_ptr               ) ,
                                    _stub_fn_ptr( &_stub_method< T       ,
                                                                 TMethod > ) {}




        template < typename T                                      ,
                   TRet (T::*TMethod)( TArgs... ) = &T::operator() >

        Fn( const T *const object_ptr ) : _object_ptr(  const_cast< T* >( object_ptr )  ) ,
                                          _stub_fn_ptr( &_stub_method< T       ,
                                                                       TMethod >        ) {}




        template < typename T                                      ,
                   TRet (T::*TMethod)( TArgs... ) = &T::operator() >

        Fn( T &object_ptr ) : _object_ptr(  &object_ptr              ) ,
                              _stub_fn_ptr( &_stub_method< T       ,
                                                           TMethod > ) {}




        template < typename T                                      ,
                   TRet (T::*TMethod)( TArgs... ) = &T::operator() >

        Fn( const T &object_ptr ) : _object_ptr(  &const_cast< T& >( object_ptr ) ) ,
                                    _stub_fn_ptr( &_stub_method< T       ,
                                                                 TMethod >        ) {}




        template < typename T                                      ,
                   TRet (T::*TMethod)( TArgs... ) = &T::operator() >
        
        Fn( T &&object_ptr ) : _object_ptr(  &object_ptr              ) ,
                               _stub_fn_ptr( &_stub_method< T       ,
                                                            TMethod > ) {}




        template < typename T                                            ,
                   TRet (T::*TMethod)( TArgs... ) const = &T::operator() >

        Fn( T *const object_ptr ) : _object_ptr(  object_ptr                     ) ,
                                    _stub_fn_ptr( &_stub_const_method< T       ,
                                                                       TMethod > ) {}




        template < typename T                                            ,
                   TRet (T::*TMethod)( TArgs... ) const = &T::operator() >

        Fn( const T *const object_ptr ) : _object_ptr(  const_cast< T* >( object_ptr )  ) ,
                                          _stub_fn_ptr( &_stub_const_method< T       ,
                                                                             TMethod >  ) {}




        template < typename T                                            ,
                   TRet (T::*TMethod)( TArgs... ) const = &T::operator() >

        Fn( T &object_ptr ) : _object_ptr(   &object_ptr                   ) ,
                              _stub_fn_ptr( &_stub_const_method< T       ,
                                                                 TMethod > ) {}




        template < typename T                                            ,
                   TRet (T::*TMethod)( TArgs... ) const = &T::operator() >

        Fn( const T &object_ptr ) : _object_ptr(  &const_cast< T& >( object_ptr ) ) ,
                                    _stub_fn_ptr( &_stub_const_method< T       ,
                                                                       TMethod >    ) {}




        template < TRet (*TFn)( TArgs... ) >

        static inline Fn wrap() {
            
            return Fn( nullptr                ,
                       &_stub_function< TFn > ) ;
            }




        template < typename T                                      ,
                   TRet (T::*TMethod)( TArgs... ) = &T::operator() >

        static inline Fn wrap( T *const object_ptr ) {
        
            return Fn( object_ptr             ,
                       &_stub_method< T       ,
                                      TMethod > ) ;
            }




        template < typename T                                            ,
                   TRet (T::*TMethod)( TArgs... ) const = &T::operator() >

        static inline Fn wrap( T *const object_ptr ) {

            return Fn( object_ptr                   ,
                       &_stub_const_method< T       ,
                                            TMethod > ) ;
            }


        

        inline TRet operator()( TArgs ...args ) const {

            return (*_stub_fn_ptr)( _object_ptr, args... ) ;
            }
    } ;




#endif
