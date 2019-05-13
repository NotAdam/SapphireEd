#include "EditorMgr.h"

#include <imgui/imgui.h>

#include <Component/IComponent.h>

#include <Component/Debug/TestComponent/TestComponent.h>
#include <Component/Debug/ImGuiDemo.h>

using namespace Sapphire::Editor;

void EditorMgr::registerComponent( Component::ComponentPtr component )
{
  // setup menus
  auto menuPath = component->getMenuPath();

  // todo: so shit, doesn';t work for multilevel either
  auto pos = menuPath.find_first_of( '/' );
  auto menuCat = menuPath.substr( 0, pos );
  auto menuItem = menuPath.substr( pos + 1, menuPath.length() - 1 );

  m_menuMap[ menuCat ].emplace_back( std::make_pair( menuItem, component ) );

  m_components.emplace_back( std::move( component ) );
}

bool EditorMgr::init()
{
  registerComponent( std::make_shared< Component::TestComponent >() );
  registerComponent( std::make_shared< Component::ImGuiDemo >() );

  return true;
}

void EditorMgr::reset()
{
  m_components.clear();
  m_menuMap.clear();
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
      ImGui::MenuItem( "Exit", NULL, false );
      ImGui::EndMenu();
    }

    for( auto& cat : m_menuMap )
    {
      if( ImGui::BeginMenu( cat.first.c_str() ) )
      {
        for( auto& item : cat.second )
        {
          if( ImGui::MenuItem( item.first.c_str(), NULL, item.second->isEnabled() ) )
            item.second->setEnabled( !item.second->isEnabled() );
        }

        ImGui::EndMenu();
      }
    }

    if( ImGui::BeginMenu( "Help" ) )
    {
      ImGui::MenuItem( "Metrics", NULL, false );
      ImGui::MenuItem( "Style Editor", NULL, false );
      ImGui::MenuItem( "About Dear ImGui", NULL, false );
      ImGui::EndMenu();
    }


    // shitty hack to get right aligned text
    ImGui::SetCursorPosX( ImGui::GetWindowContentRegionMax().x - 75 );
    ImGui::Text( "%.1f FPS", ImGui::GetIO().Framerate );

    ImGui::EndMainMenuBar();
  }
}