#include "ImGuiDemo.h"

#include <imgui/imgui.h>

using namespace Sapphire::Editor::Component;

ImGuiDemo::ImGuiDemo() :
  IComponent( "ImGui Demo", "Debug/ImGui Demo" )
{
  // hide by default
  m_isEnabled = false;
}

void ImGuiDemo::onRender()
{
  ImGui::ShowDemoWindow( &m_isEnabled );
}