#ifndef SAPPHIREED_BASECOMPONENT_H
#define SAPPHIREED_BASECOMPONENT_H

#include <string>
#include "Forwards.h"

namespace Sapphire::Editor::Component
{
  class BaseComponent
  {
  protected:
    std::string m_name;
    std::string m_menuPath;

    std::size_t m_id;

    bool m_isEnabled;

    EditorMgrPtr m_editorMgr;

  public:
    static constexpr auto DEBUG_MENU_CATEGORY = "Debug";
    static constexpr auto TOOLS_MENU_CATEGORY = "Tools";

    explicit BaseComponent( std::string name );
    BaseComponent( std::string name, std::string menuPath );

    virtual ~BaseComponent() = default;

    bool init( EditorMgrPtr editorMgrPtr );

    virtual void onReady();
    virtual void onRender() = 0;
    virtual void onShutdown();

    const std::string& getName() const;
    const std::string& getMenuPath() const;

    bool isEnabled() const;
    void setEnabled( bool isEnabled );


    std::size_t getId() const;
  };
}

#endif //SAPPHIREED_BASECOMPONENT_H
