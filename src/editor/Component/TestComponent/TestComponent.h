#ifndef SAPPHIREED_TESTCOMPONENT_H
#define SAPPHIREED_TESTCOMPONENT_H

#include <Component/IComponent.h>

namespace Sapphire::Editor::Component
{
  class TestComponent : public Sapphire::Editor::Component::IComponent
  {
  public:
    TestComponent();

    void onRender() override;
  };
}

#endif //SAPPHIREED_TESTCOMPONENT_H
