#include "BaseComponent.h"

using namespace Sapphire::Editor::Component;

BaseComponent::BaseComponent( std::string name ) :
  m_name( std::move( name ) )
{
  m_menuPath = "Tools";
}

BaseComponent::BaseComponent( std::string name, std::string menuPath ) :
  m_name( std::move( name ) ),
  m_menuPath( std::move( menuPath ) )
{
}

const std::string& BaseComponent::getName() const
{
  return m_name;
}

void BaseComponent::setName( const std::string& name )
{
  m_name = name;
}

bool BaseComponent::isEnabled() const
{
  return m_isEnabled;
}

void BaseComponent::setEnabled( bool isEnabled )
{
  m_isEnabled = isEnabled;
}

const std::string& BaseComponent::getMenuPath() const
{
  return m_menuPath;
}

void BaseComponent::setMenuPath( const std::string& menuPath )
{
  m_menuPath = menuPath;
}

void BaseComponent::onShutdown()
{
}