#include "TestComponent.h"

#include <imgui/imgui.h>

using namespace Sapphire::Editor::Component;

TestComponent::TestComponent() :
  IComponent( "TestComponent", "Debug/TestComponent" )
{
}

void TestComponent::onRender()
{
  static float f = 0.0f;
  static int counter = 0;

  ImGui::Begin( m_name.c_str(), &m_isEnabled );


  ImGui::SliderFloat( "float", &f, 0.0f, 1.0f );  // Edit 1 float using a slider from 0.0f to 1.0f

  if( ImGui::Button("Button" ) )  // Buttons return true when clicked (most widgets return true when edited/activated)
    counter++;

  ImGui::SameLine();
  ImGui::Text( "counter = %d", counter );

  ImGui::Text( "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
               ImGui::GetIO().Framerate );
  ImGui::End();
}