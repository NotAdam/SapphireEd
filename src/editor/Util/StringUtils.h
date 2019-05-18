#ifndef SAPPHIREED_STRINGUTILS_H
#define SAPPHIREED_STRINGUTILS_H

#include <string>
#include <vector>

namespace Sapphire::Editor::Util
{
  class StringUtils
  {
  public:
    static std::vector< std::string > splitString( const std::string& str, const std::string& delim );
  };
}




#endif //SAPPHIREED_STRINGUTILS_H
