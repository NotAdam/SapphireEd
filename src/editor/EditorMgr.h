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
    using ComponentIdToPtrMap = std::unordered_map< std::size_t, Component::ComponentPtr >;

    ComponentList m_components;
    ComponentIdToPtrMap m_componentIdToPtrMap;
    std::unordered_map< std::string, std::vector< std::pair< std::string, Component::ComponentPtr > > > m_menuMap;

    bool m_isRunning;

    xiv::dat::GameDataPtr m_gameData;
    xiv::exd::ExdDataPtr m_exdData;

    bool m_isSettingsUIOpen;

    ConfigMgrPtr m_configMgr;

  public:
    EditorMgr();
    virtual ~EditorMgr() = default;

    void registerComponent( Component::ComponentPtr component );

    bool init();
    void shutdown( bool exitEditor = true );

    bool isRunning();

    void onRender();

    ComponentList& getComponents();
    Component::ComponentPtr getComponentById( std::size_t id );

    xiv::dat::GameDataPtr getGameData() const;
    xiv::exd::ExdDataPtr getExdData() const;
  private:

    void renderMenuBar();
    void renderSettingsUI();
  };
}

#endif //SAPPHIREED_EDITORMGR_H
