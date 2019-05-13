#ifndef SAPPHIREED_IMGUIDEMO_H
#define SAPPHIREED_IMGUIDEMO_H

#include <Component/IComponent.h>

namespace Sapphire::Editor::Component
{
class ImGuiDemo : public Sapphire::Editor::Component::IComponent
{
public:
  ImGuiDemo();

  void onRender() override;
};
}

#endif //SAPPHIREED_IMGUIDEMO_H
