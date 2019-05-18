#include "EditorMgr.h"

#include <imgui/imgui.h>

#include <Component/BaseComponent.h>

#include <Component/Debug/ComponentDebug.h>
#include <Component/Debug/ImGuiDemo.h>
#include <Component/Exd/ExdViewer.h>

#include <Util/Logger.h>

#include <Sapphire/deps/datReader/GameData.h>
#include <Sapphire/deps/datReader/ExdData.h>

using namespace Sapphire::Editor;

EditorMgr::EditorMgr() :
  m_isRunning( true )
{
  Logger::init( "log/editor" );
}

void EditorMgr::registerComponent( Component::ComponentPtr component )
{
  Logger::debug( "Registering component: {} ({})", component->getName(), component->getId() );

  // setup menus
  m_menuMap[ component->getMenuPath() ].emplace_back( std::make_pair( component->getName(), component ) );

  m_componentIdToPtrMap[ component->getId() ] = component;
  m_components.emplace_back( component );
}

bool EditorMgr::init()
{
  // init gamedata
  m_gameData = std::make_shared< xiv::dat::GameData >( "C:/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );
  m_exdData = std::make_shared< xiv::exd::ExdData >( *m_gameData );

  // regular components
  registerComponent( std::make_shared< Component::ExdViewer >() );

  // debug components
  registerComponent( std::make_shared< Component::ComponentDebug >() );
  registerComponent( std::make_shared< Component::ImGuiDemo >() );

  // inject this class and wake up components that init successfully
  for( auto& component : m_components )
  {
    if( !component->init( shared_from_this() ) )
    {
      Logger::warn( "Failed to init component: {}", component->getName() );

      continue;
    }

    component->onReady();
  }

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
  m_componentIdToPtrMap.clear();
  m_menuMap.clear();
}

bool EditorMgr::isRunning()
{
  return m_isRunning;
}

void EditorMgr::onRender()
{
  ImGui::NewFrame();

  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
  // because it would be confusing to have two docking targets within each others.
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos( viewport->Pos );
  ImGui::SetNextWindowSize( viewport->Size );
  ImGui::SetNextWindowViewport( viewport->ID );
  ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
  ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
  if( dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode )
    window_flags |= ImGuiWindowFlags_NoBackground;

  ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );
  ImGui::Begin( "DockSpace", NULL, window_flags );
  ImGui::PopStyleVar();
  ImGui::PopStyleVar( 2 );

  // DockSpace
  ImGuiIO& io = ImGui::GetIO();
  if( io.ConfigFlags & ImGuiConfigFlags_DockingEnable )
  {
    ImGuiID dockspace_id = ImGui::GetID( "DockSpace" );
    ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );
  }

  ImGui::End();

  renderMenuBar();

  for( auto& component : m_components )
  {
    if( component->isEnabled() )
      component->onRender();
  }

  // Rendering
  ImGui::Render();
}

void EditorMgr::renderMenuBar()
{
  if( ImGui::BeginMainMenuBar() )
  {

    if( ImGui::BeginMenu( "SapphireEd" ) )
    {
      ImGui::MenuItem( "Settings", NULL, false );

      ImGui::Separator();

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

EditorMgr::ComponentList& EditorMgr::getComponents()
{
  return m_components;
}

Component::ComponentPtr EditorMgr::getComponentById( std::size_t id )
{
  auto component = m_componentIdToPtrMap.find( id );
  if( component == m_componentIdToPtrMap.end() )
    return nullptr;

  return component->second;
}

xiv::dat::GameDataPtr EditorMgr::getGameData() const
{
  return m_gameData;
}

xiv::exd::ExdDataPtr EditorMgr::getExdData() const
{
  return m_exdData;
}