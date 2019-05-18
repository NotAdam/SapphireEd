#include "ImGuiDemo.h"

#include <imgui/imgui.h>

using namespace Sapphire::Editor::Component;

ImGuiDemo::ImGuiDemo() :
  BaseComponent( "ImGui Demo", DEBUG_MENU_CATEGORY )
{
  // hide by default
  m_isEnabled = false;
  m_id = typeid( this ).hash_code();
}

void ImGuiDemo::onRender()
{
  ImGui::ShowDemoWindow( &m_isEnabled );
}