#ifndef SAPPHIREED_EDITORMGR_H
#define SAPPHIREED_EDITORMGR_H

#include <vector>
#include <unordered_map>

#include "Forwards.h"
#include "Component/BaseComponent.h"

using namespace Sapphire::Editor;

namespace Sapphire::Editor
{
  class EditorMgr : public std::enable_shared_from_this< EditorMgr >
  {
    using ComponentList = std::vector< Component::ComponentPtr >;

    ComponentList m_components;
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

    ComponentList getComponents() const;

  private:

    void renderMenuBar();
  };
}

#endif //SAPPHIREED_EDITORMGR_H
