#include "StringUtils.h"

using namespace Sapphire::Editor::Util;

std::vector< std::string > StringUtils::splitString( const std::string& str, const std::string& delim )
{
  std::vector< std::string > strings;

  std::string::size_type pos = 0;
  std::string::size_type prev = 0;

  while( ( pos = str.find( delim, prev ) ) != std::string::npos )
  {
    strings.emplace_back( str.substr( prev, pos - prev ) );
    prev = pos + 1;
  }

  auto data = str.substr( prev );
  if( !data.empty() )
    strings.emplace_back( data );

  return strings;
}