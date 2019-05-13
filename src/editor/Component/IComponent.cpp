#include "IComponent.h"

using namespace Sapphire::Editor::Component;

IComponent::IComponent( std::string name ) :
  m_name( std::move( name ) )
{
  m_menuPath = "Tools/" + name;
}

IComponent::IComponent( std::string name, std::string menuPath ) :
  m_name( std::move( name ) ),
  m_menuPath( std::move( menuPath ) )
{
}

const std::string& IComponent::getName() const
{
  return m_name;
}

void IComponent::setName( const std::string& name )
{
  m_name = name;
}

bool IComponent::isEnabled() const
{
  return m_isEnabled;
}

void IComponent::setEnabled( bool isEnabled )
{
  m_isEnabled = isEnabled;
}

const std::string& IComponent::getMenuPath() const
{
  return m_menuPath;
}

void IComponent::setMenuPath( const std::string& menuPath )
{
  m_menuPath = menuPath;
}