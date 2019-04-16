#include <vector>
#include <iostream>

#include "tokenizer.hpp"

int main( ) {
  CppStringTokenizer tokenizer;
  std::vector< CppToken > parsed;

  tokenizer.setString( "   unsigned     long      reinterpret_cast     unsignedlongint  " );

  while( true ) {
    auto token = tokenizer.next( );
    if( token.error( ) || token.endOfBuffer( ) ) break;
    parsed.push_back( std::move( token ) );
  }

  std::cout << "parsed.size( ): " << parsed.size( ) << '\n';
  for( auto idx : parsed ) std::cout << idx.key << ' ';

  if( ( parsed.size( ) == 4 ) &&
      ( parsed[0].key == CppToken::Unsigned ) &&
      ( parsed[1].key == CppToken::Long ) &&
      ( parsed[2].key == CppToken::ReinterpretCast ) &&
      ( parsed[3].key == CppToken::Identifier ) &&
      ( parsed[3].value == "unsignedlongint" ) ) {
    std::cout << "Superado :-)\n";
  } else {
    std::cout << "Fallido :-(\n";
  }

  return 0;
}
