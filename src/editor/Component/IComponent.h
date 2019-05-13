#ifndef SAPPHIREED_ICOMPONENT_H
#define SAPPHIREED_ICOMPONENT_H

#include <string>

namespace Sapphire::Editor::Component
{
  class IComponent
  {
  public:
    IComponent() = default;
    virtual ~IComponent() = default;

    virtual void onRender() = 0;
  };
}

#endif //SAPPHIREED_ICOMPONENT_H
