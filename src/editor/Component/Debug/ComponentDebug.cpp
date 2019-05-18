#include "ComponentDebug.h"

#include <imgui/imgui.h>
#include <Util/Logger.h>
#include "EditorMgr.h"

using namespace Sapphire::Editor::Component;

ComponentDebug::ComponentDebug() :
  BaseComponent( "Components", DEBUG_MENU_CATEGORY )
{
  m_isEnabled = false;
  m_id = typeid( this ).hash_code();
}

void ComponentDebug::onRender()
{
  ImGui::SetNextWindowSize( ImVec2( 600, 450 ), ImGuiCond_FirstUseEver );
  ImGui::Begin( m_name.c_str(), &m_isEnabled );

  ImGui::Text( "Loaded components:" );
  ImGui::Separator();

  ImGui::Columns( 3, "loadedcomponentgrid" );

  ImGui::Text( "ID" ); ImGui::NextColumn();
  ImGui::Text( "Name" ); ImGui::NextColumn();
  ImGui::Text( "Menu" ); ImGui::NextColumn();

  ImGui::Separator();

  // list out components
  for( auto& component : m_editorMgr->getComponents() )
  {
    ImGui::Text( "%llu", component->getId() );
    ImGui::NextColumn();

    ImGui::Text( "%s", component->getName().c_str() );
    ImGui::NextColumn();

    ImGui::Text( "%s", component->getMenuPath().c_str() );
    ImGui::NextColumn();
  }

  ImGui::Columns(1);
  ImGui::Separator();

  ImGui::End();
}

void ComponentDebug::onReady()
{
  Logger::debug( "{} ready", m_name );
}