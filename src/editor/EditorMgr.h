#ifndef SAPPHIREED_EDITORMGR_H
#define SAPPHIREED_EDITORMGR_H

#include <vector>
#include <unordered_map>

#include "Forwards.h"
#include "Component/IComponent.h"

using namespace Sapphire::Editor;

namespace Sapphire::Editor
{
  class EditorMgr
  {
    std::vector< Component::ComponentPtr > m_components;
    std::unordered_map< std::string, std::vector< std::pair< std::string, Component::ComponentPtr > > > m_menuMap;

  public:
    EditorMgr() = default;
    virtual ~EditorMgr() = default;

    void registerComponent( Component::ComponentPtr component );

    bool init();
    void reset();

    void onRender();

  private:

    void renderMenuBar();
  };
}

#endif //SAPPHIREED_EDITORMGR_H
