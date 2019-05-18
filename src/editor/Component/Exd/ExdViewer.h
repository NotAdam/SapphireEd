#ifndef SAPPHIREED_EXDVIEWER_H
#define SAPPHIREED_EXDVIEWER_H

#include <Component/BaseComponent.h>

#include <vector>
#include <unordered_map>

#include <Sapphire/deps/datReader/Exd.h>
#include <Sapphire/deps/datReader/Exh.h>

namespace Sapphire::Editor::Component
{
  class ExdViewer : public Sapphire::Editor::Component::BaseComponent
  {
    static constexpr auto ROOT_EXL_PATH = "exd/root.exl";
    static constexpr auto EXLT_MAGIC = "EXLT";
    static constexpr auto SIDEBAR_WIDTH = 300;

    enum RenderType
    {
      String,
      Integer,
      Boolean
    };

    std::size_t m_openSheet;
    uint16_t m_fieldCount;
    xiv::exd::Exd m_currentSheet;
    std::map<uint32_t, std::vector<xiv::exd::Field>> m_rows;

    using ExdIndexNamePair = std::pair< int16_t, std::string >;

    std::unordered_map< uint16_t, ExdIndexNamePair > m_exds;
    std::unordered_map< uint16_t, xiv::exd::DataType > m_renderTypes;

    void renderCurrentSheet();

    void selectSheet( uint16_t id );


  public:
    ExdViewer();

    void onRender() override;
    void onReady() override;
  };
}




#endif //SAPPHIREED_EXDVIEWER_H
