#include "LevelInspector.h"

using namespace Sapphire::Editor::Component;

LevelInspector::LevelInspector() :
  BaseComponent( "Level Inspector", TOOLS_MENU_CATEGORY )
{
  m_id = typeid( this ).hash_code();
}

void LevelInspector::onReady()
{

}

void LevelInspector::onRender()
{

}
