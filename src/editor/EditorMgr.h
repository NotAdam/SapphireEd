#ifndef SAPPHIREED_EDITORMGR_H
#define SAPPHIREED_EDITORMGR_H

#include <vector>
#include <unordered_map>

#include "Forwards.h"
#include "Component/BaseComponent.h"

using namespace Sapphire::Editor;

namespace Sapphire::Editor
{
  class EditorMgr
  {
    std::vector< Component::ComponentPtr > m_components;
    std::unordered_map< std::string, std::vector< std::pair< std::string, Component::ComponentPtr > > > m_menuMap;

    bool m_isRunning;

  public:
    EditorMgr();
    virtual ~EditorMgr() = default;

    void registerComponent( Component::ComponentPtr component );

    bool init();
    void shutdown();

    bool isRunning();

    void onRender();

  private:

    void renderMenuBar();
  };
}

#endif //SAPPHIREED_EDITORMGR_H
