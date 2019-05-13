#ifndef SAPPHIREED_ICOMPONENT_H
#define SAPPHIREED_ICOMPONENT_H

#include <string>

namespace Sapphire::Editor::Component
{
  class IComponent
  {
  protected:
    std::string m_name;
    std::string m_menuPath;

    bool m_isEnabled;

  public:
    explicit IComponent( std::string name );
    IComponent( std::string name, std::string menuPath );

    virtual ~IComponent() = default;

    virtual void onRender() = 0;

    const std::string& getName() const;
    void setName( const std::string& name );

    bool isEnabled() const;
    void setEnabled( bool isEnabled );

    const std::string& getMenuPath() const;
    void setMenuPath( const std::string& menuPath );
  };
}

#endif //SAPPHIREED_ICOMPONENT_H
