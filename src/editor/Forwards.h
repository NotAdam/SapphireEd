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

  class EditorMgr;
  using EditorMgrPtr = std::shared_ptr< EditorMgr >;
}

#endif //SAPPHIREED_FORWARDS_H
