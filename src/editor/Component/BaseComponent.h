#ifndef SAPPHIREED_BASECOMPONENT_H
#define SAPPHIREED_BASECOMPONENT_H

#include <string>

namespace Sapphire::Editor::Component
{
  class BaseComponent
  {
  protected:
    std::string m_name;
    std::string m_menuPath;

    bool m_isEnabled;

  public:
    explicit BaseComponent( std::string name );
    BaseComponent( std::string name, std::string menuPath );

    virtual ~BaseComponent() = default;

    virtual void onRender() = 0;
    virtual void onShutdown();

    const std::string& getName() const;
    void setName( const std::string& name );

    bool isEnabled() const;
    void setEnabled( bool isEnabled );

    const std::string& getMenuPath() const;
    void setMenuPath( const std::string& menuPath );
  };
}

#endif //SAPPHIREED_BASECOMPONENT_H
