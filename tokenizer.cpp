#include <cstring>

#include "tokenizer.hpp"

static bool firstIdentifierChar( char c ) {
  if( c == '_' ) return true;
  if( ( c >= 'a' ) && ( c <= 'z' ) ) return true;
  if( ( c >= 'A' ) && ( c <= 'Z' ) ) return true;

  return false;
}

static bool identifierChar( char c ) {
  if( ( c >= '0' ) && ( c <= '9' ) ) return true;
  return firstIdentifierChar( c );
}

static CppToken identifier2( int, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'd':
    if( !strncmp( "do", begin, 2 ) ) return CppToken( l, c, CppToken::Do );
    break;
  
  case 'i':
    if( !strncmp( "if", begin, 2 ) ) return CppToken( l, c, CppToken::If );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 2 );
}

static CppToken identifier3( int, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'f':
    if( !strncmp( "for", begin, 3 ) ) return CppToken( l, c, CppToken::For );
    break;

  case 'i':
    if( !strncmp( "int", begin, 3 ) ) return CppToken( l, c, CppToken::Int );
    break;

  case 'n':
    if( !strncmp( "new", begin, 3 ) ) return CppToken( l, c, CppToken::New );
    break;

  case 't':
    if( !strncmp( "try", begin, 3 ) ) return CppToken( l, c, CppToken::Try );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 3 );
}

static CppToken identifier4( int, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'a':
    if( !strncmp( "auto", begin, 4 ) ) return CppToken( l, c, CppToken::Auto );
    break;

  case 'b':
    if( !strncmp( "bool", begin, 4 ) ) return CppToken( l, c, CppToken::Bool );
    break;

  case 'c':
    if( !strncmp( "case", begin, 4 ) ) return CppToken( l, c, CppToken::Case );
    if( !strncmp( "char", begin, 4 ) ) return CppToken( l, c, CppToken::Char );
    break;

  case 'e':
    if( !strncmp( "else", begin, 4 ) ) return CppToken( l, c, CppToken::Else );
    if( !strncmp( "enum", begin, 4 ) ) return CppToken( l, c, CppToken::Enum );
    break;

  case 'g':
    if( !strncmp( "goto", begin, 4 ) ) return CppToken( l, c, CppToken::Goto );
    break;

  case 'l':
    if( !strncmp( "long", begin, 4 ) ) return CppToken( l, c, CppToken::Long );
    break;

  case 't':
    if( !strncmp( "this", begin, 4 ) ) return CppToken( l, c, CppToken::This );
    if( !strncmp( "true", begin, 4 ) ) return CppToken( l, c, CppToken::True );
    break;

  case 'v':
    if( !strncmp( "void", begin, 4 ) ) return CppToken( l, c, CppToken::Void );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 4 );
}

CppToken identifier5( int, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'b':
    if( !strncmp( "break", begin, 5 ) ) return CppToken( l, c, CppToken::Break );
    break;

  case 'c':
    if( !strncmp( "catch", begin, 5 ) ) return CppToken( l, c, CppToken::Catch );
    if( !strncmp( "class", begin, 5 ) ) return CppToken( l, c, CppToken::Class );
    if( !strncmp( "const", begin, 5 ) ) return CppToken( l, c, CppToken::Const );
    break;

  case 'f':
    if( !strncmp( "false", begin, 5 ) ) return CppToken( l, c, CppToken::False );
    if( !strncmp( "float", begin, 5 ) ) return CppToken( l, c, CppToken::Float );
    break;

  case 's':
    if( !strncmp( "short", begin, 5 ) ) return CppToken( l, c, CppToken::Short );
    break;

  case 't':
    if( !strncmp( "throw", begin, 5 ) ) return CppToken( l, c, CppToken::Throw );
    break;

  case 'u':
    if( !strncmp( "union", begin, 5 ) ) return CppToken( l, c, CppToken::Union );
    if( !strncmp( "using", begin, 5 ) ) return CppToken( l, c, CppToken::Using );
    break;

  case 'w':
    if( !strncmp( "while", begin, 5 ) ) return CppToken( l, c, CppToken::While );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 5 );
}

static CppToken identifier6( int, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'd':
    if( !strncmp( "delete", begin, 6 ) ) return CppToken( l, c, CppToken::Delete );
    if( !strncmp( "double", begin, 6 ) ) return CppToken( l, c, CppToken::Double );
    break;

  case 'e':
    if( !strncmp( "export", begin, 6 ) ) return CppToken( l, c, CppToken::Export );
    if( !strncmp( "extern", begin, 6 ) ) return CppToken( l, c, CppToken::Extern );
    break;

  case 'f':
    if( !strncmp( "friend", begin, 6 ) ) return CppToken( l, c, CppToken::Friend );
    break;

  case 'i':
    if( !strncmp( "inline", begin, 6 ) ) return CppToken( l, c, CppToken::Inline );
    break;

  case 'p':
    if( !strncmp( "public", begin, 6 ) ) return CppToken( l, c, CppToken::Public );
    break;

  case 'r':
    if( !strncmp( "return", begin, 6 ) ) return CppToken( l, c, CppToken::Return );
    break;

  case 's':
    if( !strncmp( "signed", begin, 6 ) ) return CppToken( l, c, CppToken::Signed );
    if( !strncmp( "sizeof", begin, 6 ) ) return CppToken( l, c, CppToken::Sizeof );
    if( !strncmp( "static", begin, 6 ) ) return CppToken( l, c, CppToken::Static );
    if( !strncmp( "struct", begin, 6 ) ) return CppToken( l, c, CppToken::Struct );
    if( !strncmp( "switch", begin, 6 ) ) return CppToken( l, c, CppToken::Switch );
    break;

  case 't':
    if( !strncmp( "typeid", begin, 6 ) ) return CppToken( l, c, CppToken::Typeid );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 6 );
}

static CppToken identifier7( int version, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'a':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "alignas", begin, 7 ) ) ) return CppToken( l, c, CppToken::Alignas );
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "alignof", begin, 7 ) ) ) return CppToken( l, c, CppToken::Alignof );
    break;

  case 'c':
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "char8_t", begin, 7 ) ) ) return CppToken( l, c, CppToken::Char8t );
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "concept", begin, 7 ) ) ) return CppToken( l, c, CppToken::Concept );
    break;

  case 'd':
    if( !strncmp( "default", begin, 7 ) ) return CppToken( l, c, CppToken::Default );
    break;

  case 'm':
    if( !strncmp( "mutable", begin, 7 ) ) return CppToken( l, c, CppToken::Mutable );
    break;

  case 'n':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "nullptr", begin, 7 ) ) ) return CppToken( l, c, CppToken::Nullptr );
    break;

  case 'p':
    if( !strncmp( "private", begin, 7 ) ) return CppToken( l, c, CppToken::Private );
    break;

  case 't':
    if( !strncmp( "typedef", begin, 7 ) ) return CppToken( l, c, CppToken::Typedef );
    break;

  case 'v':
    if( !strncmp( "virtual", begin, 7 ) ) return CppToken( l, c, CppToken::Virtual );
    break;

  case 'w':
    if( !strncmp( "wchar_t", begin, 7 ) ) return CppToken( l, c, CppToken::Wchart );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 7 );
}

static CppToken identifier8( int version, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'c':
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strcmp( "char16_t", begin ) ) ) return CppToken( l, c, CppToken::Char16t );
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strcmp( "char32_t", begin ) ) ) return CppToken( l, c, CppToken::Char32t );
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strcmp( "continue", begin ) ) ) return CppToken( l, c, CppToken::Continue );
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strcmp( "co_await", begin ) ) ) return CppToken( l, c, CppToken::CoAwait );
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strcmp( "co_yield", begin ) ) ) return CppToken( l, c, CppToken::CoYield );
    break;

  case 'd':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strcmp( "decltype", begin ) ) ) return CppToken( l, c, CppToken::Decltype );
    break;

  case 'e':
    if( !strcmp( "explicit", begin ) ) return CppToken( l, c, CppToken::Explicit );
    break;

  case 'n':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "noexcept", begin, 8 ) ) ) return CppToken( l, c, CppToken::Noexcept );
    break;

  case 'o':
    if( !strncmp( "operator", begin, 8 ) ) return CppToken( l, c, CppToken::Operator );
    break;

  case 'r':
    if( !strncmp( "register", begin, 8 ) ) return CppToken( l, c, CppToken::Register );
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "requires", begin, 8 ) ) ) return CppToken( l, c, CppToken::Requires );
    break;

  case 't':
    if( !strncmp( "template", begin, 8 ) ) return CppToken( l, c, CppToken::Template );
    if( !strncmp( "typename", begin, 8 ) ) return CppToken( l, c, CppToken::Typename );
    break;

  case 'u':
    if( !strncmp( "unsigned", begin, 8 ) ) return CppToken( l, c, CppToken::Unsigned );
    break;

  case 'v':
    if( !strncmp( "volatile", begin, 8 ) ) return CppToken( l, c, CppToken::Volatile );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 8 );
}

static CppToken identifier9( int version, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'c':
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "consteval", begin, 9 ) ) ) return CppToken( l, c, CppToken::Consteval );
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "constexpr", begin, 9 ) ) ) return CppToken( l, c, CppToken::Constexpr );
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "co_return", begin, 9 ) ) ) return CppToken( l, c, CppToken::CoReturn );
    break;

  case 'n':
    if( !strncmp( "namespace", begin, 9 ) ) return CppToken( l, c, CppToken::Namespace );
    break;

  case 'p':
    if( !strncmp( "protected", begin, 9 ) ) return CppToken( l, c, CppToken::Protected );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 9 );
}

static CppToken identifier10( int, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'c':
    if( !strncmp( "const_cast", begin, 10 ) ) return CppToken( l, c, CppToken::ConstCast );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 10 );
}

static CppToken identifier11( int, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 's':
    if( !strncmp( "static_cast", begin, 11 ) ) return CppToken( l, c, CppToken::StaticCast );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 11 );
}

static CppToken identifier12( int version, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'd':
    if( !strncmp( "dynamic_cast", begin, 12 ) ) return CppToken( l, c, CppToken::DynamicCast );
    break;

  case 't':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "thread_local", begin, 12 ) ) ) return CppToken( l, c, CppToken::ThreadLocal );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 12 );
}

static CppToken identifier13( int version, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 's':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "static_assert", begin, 13 ) ) ) return CppToken( l, c, CppToken::StaticAssert );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 13 );
}

static CppToken identifier16( int, int l, int c, const char *begin ) {
  switch( *begin ) {
  case 'r':
    if( !strncmp( "reinterpret_cast", begin, 16 ) ) return CppToken( l, c, CppToken::ReinterpretCast );
    break;

  default:
    break;
  }

  return CppToken( l, c, begin, begin + 16 );
}

static CppToken identifier( int version, int l, int c, const char *begin, const char *end ) {
  static CppToken (*functions[])( int, int, int, const char * ) = {
    nullptr,
    nullptr,
    identifier2,
    identifier3,
    identifier4,
    identifier5,
    identifier6,
    identifier7,
    identifier8,
    identifier9,
    identifier10,
    identifier11,
    identifier12,
    identifier13,
    nullptr,
    nullptr,
    identifier16
  };

  auto length = end - begin;

  // Longitud máxima de las palabras reservadas.
  size_t maxLength = sizeof( functions ) / sizeof( functions[0] );

  if( ( static_cast< size_t >( length ) < maxLength ) && functions[length] ) {
    return functions[length]( version, l, c, begin );
  }

  // Si llegamos aquí, no tenemos manejador, luego NO ES una palabra reservada.
  return CppToken( l, c, begin, end );
}

CppToken CppStringTokenizer::next( ) {
  // Ignorar separadores.
  while( ( m_pos.ptr != m_buffer.end ) && ( *m_pos <= ' ' ) ) ++m_pos;

  if( m_pos.ptr == m_buffer.end ) return CppToken( m_pos.line, m_pos.column, CppToken::EndOfBuffer );

  if( firstIdentifierChar( *m_pos ) ) {
    // Es un identificador, o una palabra clave.
    Position origin = m_pos;

    ++m_pos;
    while( ( m_pos.ptr != m_buffer.end ) && ( identifierChar( *m_pos ) ) ) ++m_pos;

    return identifier( m_version, origin.line, origin.column, origin.ptr, m_pos.ptr );
  }

  return CppToken( );
}
