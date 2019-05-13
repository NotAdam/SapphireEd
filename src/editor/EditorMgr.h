#ifndef SAPPHIREED_EDITORMGR_H
#define SAPPHIREED_EDITORMGR_H

#include <vector>

#include "Forwards.h"
#include "Component/IComponent.h"

using namespace Sapphire::Editor;

namespace Sapphire::Editor
{
  class EditorMgr
  {
    std::vector< Component::ComponentPtr > m_components;

  public:
    EditorMgr() = default;
    virtual ~EditorMgr() = default;

    void registerComponent( Component::ComponentPtr component );

    bool init();
    void cleanup();

    void onRender();
  };
}

#endif //SAPPHIREED_EDITORMGR_H
