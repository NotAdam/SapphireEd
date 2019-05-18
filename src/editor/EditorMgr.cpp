#include "EditorMgr.h"

#include <imgui/imgui.h>

#include <Component/BaseComponent.h>

#include <Component/Debug/TestComponent/TestComponent.h>
#include <Component/Debug/ImGuiDemo.h>

#include <Util/Logger.h>

using namespace Sapphire::Editor;

EditorMgr::EditorMgr() :
  m_isRunning( true )
{
  Logger::init( "log/editor" );
}

void EditorMgr::registerComponent( Component::ComponentPtr component )
{
  Logger::debug( "Registering component: {}", component->getName() );

  // setup menus
  m_menuMap[ component->getMenuPath() ].emplace_back( std::make_pair( component->getName(), component ) );

  m_components.emplace_back( std::move( component ) );
}

bool EditorMgr::init()
{
  registerComponent( std::make_shared< Component::TestComponent >() );
  registerComponent( std::make_shared< Component::ImGuiDemo >() );

  return true;
}

void EditorMgr::shutdown()
{
  assert( m_isRunning );

  Logger::info( "Shutting down editor..." );

  for( auto& component : m_components )
  {
    component->onShutdown();
  }

  m_isRunning = false;

  m_components.clear();
  m_menuMap.clear();
}

bool EditorMgr::isRunning()
{
  return m_isRunning;
}

void EditorMgr::onRender()
{
  renderMenuBar();

  for( auto& component : m_components )
  {
    if( component->isEnabled() )
      component->onRender();
  }
}

void EditorMgr::renderMenuBar()
{
  if( ImGui::BeginMainMenuBar() )
  {

    if( ImGui::BeginMenu( "SapphireEd" ) )
    {
      if( ImGui::MenuItem( "Exit", NULL, false ) )
        shutdown();

      ImGui::EndMenu();
    }

    for( auto& cat : m_menuMap )
    {
      if( ImGui::BeginMenu( cat.first.c_str() ) )
      {
        for( auto& item : cat.second )
        {
          bool enabled = item.second->isEnabled();

          if( ImGui::MenuItem( item.first.c_str(), NULL, enabled ) )
            item.second->setEnabled( !enabled );
        }

        ImGui::EndMenu();
      }
    }

    // shitty hack to get right aligned text
    ImGui::SetCursorPosX( ImGui::GetWindowContentRegionMax().x - 75 );
    ImGui::Text( "%.1f FPS", ImGui::GetIO().Framerate );

    ImGui::EndMainMenuBar();
  }
}