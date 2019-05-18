#ifndef SAPPHIREED_COMPONENTDEBUG_H
#define SAPPHIREED_COMPONENTDEBUG_H

#include <Component/BaseComponent.h>

namespace Sapphire::Editor::Component
{
  class ComponentDebug : public Sapphire::Editor::Component::BaseComponent
  {
  public:
    ComponentDebug();

    void onRender() override;
    void onReady() override;
  };
}

#endif //SAPPHIREED_COMPONENTDEBUG_H
