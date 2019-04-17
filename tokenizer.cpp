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

static void identifier2( CppToken &token, int, const char *begin ) {
  switch( *begin ) {
  case 'd':
    if( !strncmp( "do", begin, 2 ) ) {
      token.set( CppToken::Do );
      return;
    }
    break;
  
  case 'i':
    if( !strncmp( "if", begin, 2 ) ) {
      token.set( CppToken::If );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 2 );
}

static void identifier3( CppToken &token, int, const char *begin ) {
  switch( *begin ) {
  case 'f':
    if( !strncmp( "for", begin, 3 ) ) {
      token.set( CppToken::For );
      return;
    }
    break;

  case 'i':
    if( !strncmp( "int", begin, 3 ) ) {
      token.set( CppToken::Int );
      return;
    }
    break;

  case 'n':
    if( !strncmp( "new", begin, 3 ) ) {
      token.set( CppToken::New );
      return;
    }
    break;

  case 't':
    if( !strncmp( "try", begin, 3 ) ) {
      token.set( CppToken::Try );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 3 );
}

static void identifier4( CppToken &token, int, const char *begin ) {
  switch( *begin ) {
  case 'a':
    if( !strncmp( "auto", begin, 4 ) ) {
      token.set( CppToken::Auto );
      return;
    }
    break;

  case 'b':
    if( !strncmp( "bool", begin, 4 ) ) {
      token.set( CppToken::Bool );
      return;
    }
    break;

  case 'c':
    if( !strncmp( "case", begin, 4 ) ) {
      token.set( CppToken::Case );
      return;
    }
    if( !strncmp( "char", begin, 4 ) ) {
      token.set( CppToken::Char );
      return;
    }
    break;

  case 'e':
    if( !strncmp( "else", begin, 4 ) ) {
      token.set( CppToken::Else );
      return;
    }
    if( !strncmp( "enum", begin, 4 ) ) {
      token.set( CppToken::Enum );
      return;
    }
    break;

  case 'g':
    if( !strncmp( "goto", begin, 4 ) ) {
      token.set( CppToken::Goto );
      return;
    }
    break;

  case 'l':
    if( !strncmp( "long", begin, 4 ) ) {
      token.set( CppToken::Long );
      return;
    }
    break;

  case 't':
    if( !strncmp( "this", begin, 4 ) ) {
      token.set( CppToken::This );
      return;
    }
    if( !strncmp( "true", begin, 4 ) ) {
      token.set( CppToken::True );
      return;
    }
    break;

  case 'v':
    if( !strncmp( "void", begin, 4 ) ) {
      token.set(  CppToken::Void );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 4 );
}

static void identifier5( CppToken &token, int, const char *begin ) {
  switch( *begin ) {
  case 'b':
    if( !strncmp( "break", begin, 5 ) ) {
      token.set( CppToken::Break );
      return;
    }
    break;

  case 'c':
    if( !strncmp( "catch", begin, 5 ) ) {
      token.set( CppToken::Catch );
      return;
    }
    if( !strncmp( "class", begin, 5 ) ) {
      token.set( CppToken::Class );
      return;
    }
    if( !strncmp( "const", begin, 5 ) ) {
      token.set( CppToken::Const );
      return;
    }
    break;

  case 'f':
    if( !strncmp( "false", begin, 5 ) ) {
      token.set( CppToken::False );
      return;
    }
    if( !strncmp( "float", begin, 5 ) ) {
      token.set( CppToken::Float );
      return;
    }
    break;

  case 's':
    if( !strncmp( "short", begin, 5 ) ) {
      token.set( CppToken::Short );
      return;
    }
    break;

  case 't':
    if( !strncmp( "throw", begin, 5 ) ) {
      token.set( CppToken::Throw );
      return;
    }
    break;

  case 'u':
    if( !strncmp( "union", begin, 5 ) ) {
      token.set( CppToken::Union );
      return;
    }
    if( !strncmp( "using", begin, 5 ) ) {
      token.set( CppToken::Using );
      return;
    }
    break;

  case 'w':
    if( !strncmp( "while", begin, 5 ) ) {
      token.set( CppToken::While );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 5 );
}

static void identifier6( CppToken &token, int, const char *begin ) {
  switch( *begin ) {
  case 'd':
    if( !strncmp( "delete", begin, 6 ) ) {
      token.set( CppToken::Delete );
      return;
    }
    if( !strncmp( "double", begin, 6 ) ) {
      token.set( CppToken::Double );
      return;
    }
    break;

  case 'e':
    if( !strncmp( "export", begin, 6 ) ) {
      token.set( CppToken::Export );
      return;
    }
    if( !strncmp( "extern", begin, 6 ) ) {
      token.set( CppToken::Extern );
      return;
    }
    break;

  case 'f':
    if( !strncmp( "friend", begin, 6 ) ) {
      token.set( CppToken::Friend );
      return;
    }
    break;

  case 'i':
    if( !strncmp( "inline", begin, 6 ) ) {
      token.set( CppToken::Inline );
      return;
    }
    break;

  case 'p':
    if( !strncmp( "public", begin, 6 ) ) {
      token.set( CppToken::Public );
      return;
    }
    break;

  case 'r':
    if( !strncmp( "return", begin, 6 ) ) {
      token.set( CppToken::Return );
      return;
    }
    break;

  case 's':
    if( !strncmp( "signed", begin, 6 ) ) {
      token.set( CppToken::Signed );
      return;
    }
    if( !strncmp( "sizeof", begin, 6 ) ) {
      token.set( CppToken::Sizeof );
      return;
    }
    if( !strncmp( "static", begin, 6 ) ) {
      token.set( CppToken::Static );
      return;
    }
    if( !strncmp( "struct", begin, 6 ) ) {
      token.set( CppToken::Struct );
      return;
    }
    if( !strncmp( "switch", begin, 6 ) ) {
      token.set( CppToken::Switch );
      return;
    }
    break;

  case 't':
    if( !strncmp( "typeid", begin, 6 ) ) {
      token.set( CppToken::Typeid );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 6 );
}

static void identifier7( CppToken &token, int version, const char *begin ) {
  switch( *begin ) {
  case 'a':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "alignas", begin, 7 ) ) ) {
      token.set( CppToken::Alignas );
      return;
    }
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "alignof", begin, 7 ) ) ) {
      token.set( CppToken::Alignof );
      return;
    }
    break;

  case 'c':
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "char8_t", begin, 7 ) ) ) {
      token.set( CppToken::Char8t );
      return;
    }
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "concept", begin, 7 ) ) ) {
      token.set( CppToken::Concept );
      return;
    }
    break;

  case 'd':
    if( !strncmp( "default", begin, 7 ) ) {
      token.set( CppToken::Default );
      return;
    }
    break;

  case 'm':
    if( !strncmp( "mutable", begin, 7 ) ) {
      token.set( CppToken::Mutable );
      return;
    }
    break;

  case 'n':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "nullptr", begin, 7 ) ) ) {
      token.set( CppToken::Nullptr );
      return;
    }
    break;

  case 'p':
    if( !strncmp( "private", begin, 7 ) ) {
      token.set( CppToken::Private );
      return;
    }
    break;

  case 't':
    if( !strncmp( "typedef", begin, 7 ) ) {
      token.set( CppToken::Typedef );
      return;
    }
    break;

  case 'v':
    if( !strncmp( "virtual", begin, 7 ) ) {
      token.set( CppToken::Virtual );
      return;
    }
    break;

  case 'w':
    if( !strncmp( "wchar_t", begin, 7 ) ) {
      token.set( CppToken::Wchart );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 7 );
}

static void identifier8( CppToken &token, int version, const char *begin ) {
  switch( *begin ) {
  case 'c':
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "char16_t", begin, 8 ) ) ) {
      token.set( CppToken::Char16t );
      return;
    }
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "char32_t", begin, 8 ) ) ) {
      token.set( CppToken::Char32t );
      return;
    }
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "co_await", begin, 8 ) ) ) {
      token.set( CppToken::CoAwait );
      return;
    }
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "co_yield", begin, 8 ) ) ) {
      token.set( CppToken::CoYield );
      return;
    }
    break;
    if( !strncmp( "continue", begin, 8 ) ) {
      token.set( CppToken::Continue );
      return;
    }
    break;

  case 'd':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "decltype", begin, 8 ) ) ){
      token.set( CppToken::Decltype );
      return;
    }
    break;

  case 'e':
    if( !strncmp( "explicit", begin, 8 ) ) {
      token.set( CppToken::Explicit );
      return;
    }
    break;

  case 'n':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "noexcept", begin, 8 ) ) ) {
      token.set( CppToken::Noexcept );
      return;
    }
    break;

  case 'o':
    if( !strncmp( "operator", begin, 8 ) ) {
      token.set( CppToken::Operator );
      return;
    }
    break;

  case 'r':
    if( !strncmp( "register", begin, 8 ) ) {
      token.set( CppToken::Register );
      return;
    }
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "requires", begin, 8 ) ) ) {
      token.set( CppToken::Requires );
      return;
    }
    break;

  case 't':
    if( !strncmp( "template", begin, 8 ) ) {
      token.set( CppToken::Template );
      return;
    }
    if( !strncmp( "typename", begin, 8 ) ) {
      token.set( CppToken::Typename );
      return;
    }
    break;

  case 'u':
    if( !strncmp( "unsigned", begin, 8 ) ) {
      token.set( CppToken::Unsigned );
      return;
    }
    break;

  case 'v':
    if( !strncmp( "volatile", begin, 8 ) ) {
      token.set( CppToken::Volatile );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 8 );
}

static void identifier9( CppToken &token, int version, const char *begin ) {
  switch( *begin ) {
  case 'c':
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "consteval", begin, 9 ) ) ) {
      token.set( CppToken::Consteval );
      return;
    }
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "constexpr", begin, 9 ) ) ) {
      token.set( CppToken::Constexpr );
      return;
    }
    if( ( version > CppStringTokenizer::CPP17 ) && ( !strncmp( "co_return", begin, 9 ) ) ) {
      token.set( CppToken::CoReturn );
      return;
    }
    break;

  case 'n':
    if( !strncmp( "namespace", begin, 9 ) ) {
      token.set( CppToken::Namespace );
      return;
    }
    break;

  case 'p':
    if( !strncmp( "protected", begin, 9 ) ) {
      token.set( CppToken::Protected );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 9 );
}

static void identifier10( CppToken &token, int, const char *begin ) {
  switch( *begin ) {
  case 'c':
    if( !strncmp( "const_cast", begin, 10 ) ) {
      token.set( CppToken::ConstCast );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 10 );
}

static void identifier11( CppToken &token, int, const char *begin ) {
  switch( *begin ) {
  case 's':
    if( !strncmp( "static_cast", begin, 11 ) ) {
      token.set( CppToken::StaticCast );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 11 );
}

static void identifier12( CppToken &token, int version, const char *begin ) {
  switch( *begin ) {
  case 'd':
    if( !strncmp( "dynamic_cast", begin, 12 ) ) {
      token.set( CppToken::DynamicCast );
      return;
    }
    break;

  case 't':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "thread_local", begin, 12 ) ) ) {
      token.set( CppToken::ThreadLocal );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 12 );
}

static void identifier13( CppToken &token, int version, const char *begin ) {
  switch( *begin ) {
  case 's':
    if( ( version >= CppStringTokenizer::CPP11 ) && ( !strncmp( "static_assert", begin, 13 ) ) ) {
      token.set( CppToken::StaticAssert );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 13 );
}

static void identifier16( CppToken &token, int, const char *begin ) {
  switch( *begin ) {
  case 'r':
    if( !strncmp( "reinterpret_cast", begin, 16 ) ) {
      token.set( CppToken::ReinterpretCast );
      return;
    }
    break;

  default:
    break;
  }

  token.set( begin, begin + 16 );
}

/*
  version: versión del estándar.
  l, c: línea y columna iniciales.
  begin: puntero al primer caracter.
  end: puntero al final del buffer.
*/
static size_t identifier( CppToken &token, int version, const char *begin, const char *end ) {
  static void (*functions[])( CppToken &, int, const char * ) = {
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

  // Buscamos la longitud del identificador.
  size_t length = 1;
  const char *curr = begin + 1;

  while( ( curr != end ) && identifierChar( *curr ) ) {
    ++curr;
    ++length;
  }

  if( length < ( sizeof( functions ) / sizeof( functions[0] ) ) && functions[length] ) {
    functions[length]( token, version, begin );
    return length;
  }

  // Si llegamos aquí, no tenemos manejador, luego NO ES una palabra reservada.
  token.set( begin, curr );
  return length;
}

CppToken CppStringTokenizer::next( ) {
  // Ignorar separadores.
  while( ( m_pos.ptr != m_buffer.end ) && ( *m_pos <= ' ' ) ) ++m_pos;

  if( m_pos.ptr == m_buffer.end ) return CppToken( m_pos.line, m_pos.column, CppToken::EndOfBuffer );

  CppToken ret;

  if( firstIdentifierChar( *m_pos ) ) {
    // Esto no falla. Por fuerza, es un identificador o una palabra reservada.
    m_pos += identifier( ret, m_version, m_pos.ptr, m_buffer.end );
  }

  return ret;
}
