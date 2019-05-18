#ifndef SAPPHIREED_FORWARDS_H
#define SAPPHIREED_FORWARDS_H

#include <memory>

namespace Sapphire::Editor
{
  namespace Component
  {
    class BaseComponent;
    using ComponentPtr = std::shared_ptr< BaseComponent >;
  }
}

#endif //SAPPHIREED_FORWARDS_H
