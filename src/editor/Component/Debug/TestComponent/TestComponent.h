#ifndef SAPPHIREED_TESTCOMPONENT_H
#define SAPPHIREED_TESTCOMPONENT_H

#include <Component/BaseComponent.h>

namespace Sapphire::Editor::Component
{
  class TestComponent : public Sapphire::Editor::Component::BaseComponent
  {
  public:
    TestComponent();

    void onRender() override;
  };
}

#endif //SAPPHIREED_TESTCOMPONENT_H
