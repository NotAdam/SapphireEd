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

  class ConfigMgr;
  using ConfigMgrPtr = std::shared_ptr< ConfigMgr >;
}

namespace xiv
{
  namespace dat
  {
    class GameData;
    using GameDataPtr = std::shared_ptr< GameData >;
  }

  namespace exd
  {
    class ExdData;
    using ExdDataPtr = std::shared_ptr< ExdData >;
  }
}

#endif //SAPPHIREED_FORWARDS_H
