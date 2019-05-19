#ifndef SAPPHIREED_LEVELINSPECTOR_H
#define SAPPHIREED_LEVELINSPECTOR_H

#include <Component/BaseComponent.h>

namespace Sapphire::Editor::Component
{
  class LevelInspector : public Sapphire::Editor::Component::BaseComponent
  {
  public:
    LevelInspector();

    void onRender() override;
    void onReady() override;
  };
}

#endif //SAPPHIREED_LEVELINSPECTOR_H
