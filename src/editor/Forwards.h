#ifndef SAPPHIREED_FORWARDS_H
#define SAPPHIREED_FORWARDS_H

#include <memory>

namespace Sapphire::Editor
{
  namespace Component
  {
    class IComponent;
    using ComponentPtr = std::unique_ptr< IComponent >;
  }
}

#endif //SAPPHIREED_FORWARDS_H
