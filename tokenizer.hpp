#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <iostream>

class CppToken {
public:
  enum {
    ReadError = -1,
    Invalid = -2,
    EndOfFile = 0,
    EndOfBuffer,
    Identifier,
    Alignas, // alignas 7
    Alignof, // alignof 7
    Auto, // auto 4
    Bool, // bool 4
    Break, // break 5
    Case, // case 4
    Catch, // catch 5
    Char, // char 4
    Char8t, // char8_t 7
    Char16t, // char16_t 8
    Char32t, // char32_t 8
    Class, // class 5
    Concept, // concept 7
    Const, // const 5
    Consteval, // consteval 9
    Constexpr, // constexpr 9
    ConstCast, // const_cast 10
    Continue, // continue 8
    CoAwait, // co_await 8
    CoReturn, // co_return 9
    CoYield, // co_yield 8
    Decltype, // decltype 8
    Default, // default 7
    Delete, // delete 6
    Do, // do 2
    Double, // double 6
    DynamicCast, // dynamic_cast 12
    Else, // else 4
    Enum, // enum 4
    Explicit, // explicit 8
    Export, // export 6
    Extern, // extern 6
    False, // false 5
    Float, // float 5
    For, // for 3
    Friend, // friend 6
    Goto, // goto 4
    If, // if 2
    Inline, // inline 6
    Int, // int 3
    Long, // long 4
    Mutable, // mutable 7
    Namespace, // namespace 9
    New, // new 3
    Noexcept, // noexcept 8
    Nullptr, // nullptr 7
    Operator, // operator 8
    Private, // private 7
    Protected, // protected 9
    Public, // public 6
    Register, // register 8
    ReinterpretCast, // reinterpret_cast 16
    Requires, // requires 8
    Return, // return 6
    Short, // short 5
    Signed, // signed 6
    Sizeof, // sizeof 6
    Static, // static 6
    StaticAssert, // static_assert 13
    StaticCast, // static_cast 11
    Struct, // struct 6
    Switch, // switch 6
    Template, // template 8
    This, // this 4
    ThreadLocal, // thread_local 12
    Throw, // throw 5
    True, // true 4
    Try, // try 3
    Typedef, // typedef 7
    Typeid, // typeid 6
    Typename, // typename 8
    Union, // union 5
    Unsigned, // unsigned 8
    Using, // using 5
    Virtual, // virtual 7
    Void, // void 4
    Volatile, // volatile 8
    Wchart, // wchar_t 7
    While // while 5
  };

  int line;
  int column;
  int key;
  std::string value;

  CppToken( ) : line( 0 ), column( 0 ), key( Invalid ) { }
  CppToken( int lin, int col, int k = CppToken::Invalid ) : line( lin ), column( col ), key( k ) { }
  CppToken( const CppToken & ) = default;
  CppToken( CppToken && ) = default;
  CppToken &operator=( const CppToken & ) = default;
  CppToken &operator=( CppToken && ) = default;

  CppToken( int l, int c ) : line( l ), column( c ), key( Invalid ) { }

  void set( const char *begin, const char *end ) {
    value.assign( begin, end );
    key = Identifier;
  }
  void set( int k ) {
    value.clear( );
    key = k;
  }

  // Si TRUE, no se puede continuar, ni rellenando el buffer.
  bool error( ) const { return key < 0; }
  // TRUE si se puede continuar.
  bool endOfBuffer( ) const { return key == CppToken::EndOfBuffer; }
};

class CppStringTokenizer {
  struct Buffer {
    const char *begin = nullptr;
    const char *end = nullptr;

    Buffer( ) = default;
    explicit Buffer( const std::string &buf ) { set( buf ); }
    Buffer( const char *b, size_t len = 0 ) { set( b, len ); }
    Buffer( const char *b, const char *e ) { set( b, e ); }

    Buffer( const Buffer & ) = default;
    Buffer( Buffer &&o ) {
      new (this)Buffer( o );
      o.reset( );
    }
    Buffer &operator=( const Buffer & ) = default;
    Buffer &operator=( Buffer &&o ) {
      new (this)Buffer( o );
      o.reset( );
      return *this;
    }

    void set( const std::string &str ) {
      begin = &str.front( );
      end = &str.back( ) + 1;
    }
    void set( const char *b, size_t len = 0 ) {
      if( !len ) len = std::char_traits< char >::length( b );

      begin = b;
      end = b + len;
    }
    void set( const char *b, const char *e ) {
      begin = b;
      end = e;
    }

    void reset( ) {
      begin = nullptr;
      end = nullptr;
    }
  };

  struct Position {
    int line = 0;
    int column = 0;
    const char *ptr = nullptr;

    Position( ) = default;
    Position( const Position & ) = default;
    Position( Position &&o ) {
      new (this) Position( o );
      o.reset( );
    }
    Position &operator=( const Position & ) = default;
    Position &operator=( Position &&o ) {
      new (this) Position( o );
      o.reset( );
      return *this;
    }

    void reset( ) {
      line = 0;
      column = 0;
      ptr = nullptr;
    }

    void nextLine( const char *p ) {
      ++line;
      column = 0;
      ptr = p;
    }

    char operator*( ) const { return *ptr; }

    bool operator==( const char c ) const { return *ptr == c; }
    bool operator!=( const char c ) const { return *ptr != c; }

    Position operator++( ) {
      ++column;
      ++ptr;
      return *this;
    }
    Position operator++( int ) {
      Position tmp( *this );

      ++column;
      ++ptr;

      return tmp;
    }
    Position &operator+=( size_t l ) {
      line += static_cast< int >( l );
      ptr += l;
      return *this;
    }
  };

  int m_version;
  Buffer m_buffer;
  Position m_pos;

public:
  static constexpr int CPP11 = 199711;
  static constexpr int CPP14 = 201402;
  static constexpr int CPP17 = 201703;

  explicit CppStringTokenizer( int version = 1 ) : m_version( version ) { }
  CppStringTokenizer( const CppStringTokenizer & ) = default;
  CppStringTokenizer( CppStringTokenizer &&o ) {
    new (this) CppStringTokenizer( o );
    o.reset( );
  }
  CppStringTokenizer &operator=( const CppStringTokenizer & ) = default;
  CppStringTokenizer &operator=( CppStringTokenizer &&o ) {
    new (this) CppStringTokenizer( o );
    o.reset( );
    return *this;
  }

  void reset( ) {
    m_buffer.reset( );
    m_pos.reset( );
  }

  void setString( const std::string &str ) {
    m_buffer.set( str );
    m_pos.nextLine( m_buffer.begin );
  }
  void setString( const char *b, size_t len = 0 ) {
    m_buffer.set( b, len );
    m_pos.nextLine( m_buffer.begin );
  }
  template< typename BEG, typename END > void setString( BEG b, END e ) {
    m_buffer.set( &( *b ), &( *e ) );
    m_pos.nextLine( m_buffer.begin );
  }

  CppToken next( );
};

#endif
