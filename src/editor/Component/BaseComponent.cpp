#include "BaseComponent.h"

using namespace Sapphire::Editor::Component;

BaseComponent::BaseComponent( std::string name ) :
  m_name( std::move( name ) ),
  m_id( typeid( this ).hash_code() ),
  m_isEnabled( false )
{
  m_menuPath = "Tools";
}

BaseComponent::BaseComponent( std::string name, std::string menuPath ) :
  m_name( std::move( name ) ),
  m_menuPath( std::move( menuPath ) ),
  m_id( typeid( this ).hash_code() ),
  m_isEnabled( false )
{
}

bool BaseComponent::init( Sapphire::Editor::EditorMgrPtr editorMgrPtr )
{
  m_editorMgr = std::move( editorMgrPtr );

  return true;
}

const std::string& BaseComponent::getName() const
{
  return m_name;
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

void BaseComponent::onShutdown()
{
}

void BaseComponent::onReady()
{
}

std::size_t BaseComponent::getId() const
{
  return m_id;
}