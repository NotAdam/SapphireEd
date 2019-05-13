#include "EditorMgr.h"

#include <Component/IComponent.h>
#include <Component/TestComponent/TestComponent.h>

using namespace Sapphire::Editor;

void EditorMgr::registerComponent( Component::ComponentPtr component )
{
  m_components.emplace_back( std::move( component ) );
}

bool EditorMgr::init()
{
  registerComponent( std::make_unique< Component::TestComponent >() );

  return true;
}

void EditorMgr::cleanup()
{
  m_components.clear();
}

void EditorMgr::onRender()
{
  for( auto& component : m_components )
  {
    component->onRender();
  }
}