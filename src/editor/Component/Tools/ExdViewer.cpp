#include "ExdViewer.h"

#include "EditorMgr.h"
#include "Util/Logger.h"

#include <Sapphire/deps/datReader/GameData.h>
#include <Sapphire/deps/datReader/File.h>
#include <Sapphire/deps/datReader/Exd.h>
#include <Sapphire/deps/datReader/Exh.h>
#include <Sapphire/deps/datReader/ExdCat.h>
#include <Sapphire/deps/datReader/ExdData.h>

#include <string>
#include <string_view>

#include "Util/StringUtils.h"

#include "imgui/imgui.h"

using namespace Sapphire::Editor::Component;

ExdViewer::ExdViewer() :
  BaseComponent( "EXD Viewer", TOOLS_MENU_CATEGORY ),
  m_openSheet( -1 ),
  m_fieldCount( 0 )
{
  m_id = typeid( this ).hash_code();
}

void ExdViewer::onReady()
{
  // load root.exl
  auto rootExl = m_editorMgr->getGameData()->getFile( ROOT_EXL_PATH );
  if( !rootExl )
  {
    Logger::error( "Unable to load root.exl from {}", ROOT_EXL_PATH );
    return;
  }

  auto rawData = rootExl->get_data_sections().at( 0 );
  auto data = std::string( rawData.data(), rawData.size() );

  uint16_t id = 0;

  auto rows = Util::StringUtils::splitString( data, "\n" );

  m_exds.reserve( rows.size() );

  // todo: this is so aids holy shit
  for( const auto& row : rows )
  {
    // garbage
    if( row.find( EXLT_MAGIC ) != std::string::npos )
      continue;

    auto rowData = Util::StringUtils::splitString( row, "," );

    m_exds[ id++ ] = std::make_pair( std::atoi( rowData.at( 1 ).c_str() ), rowData.at( 0 ) );
  }
}

void ExdViewer::onRender()
{
  ImGui::SetNextWindowSize( ImVec2( 800, 600 ), ImGuiCond_FirstUseEver );

  static ImGuiTextFilter exdSheetFilter;

  auto initialY = ImGui::GetCursorPosY();

  ImGui::Begin( m_name.c_str(), &m_isEnabled );
  {
    exdSheetFilter.Draw( "", SIDEBAR_WIDTH );

    ImGui::BeginChild( "EXDs", ImVec2( SIDEBAR_WIDTH, 0 ), true );
    {
      for( const auto& row : m_exds )
      {
        if( !exdSheetFilter.PassFilter( row.second.second.c_str() ) )
          continue;

        if( ImGui::Selectable( row.second.second.c_str(), row.first == m_openSheet ) )
          selectSheet( row.first );
      }
    }
    ImGui::EndChild();

    ImGui::SameLine();

    // reset cursor pos to hide space that the invisible filter takes up
    ImGui::SetCursorPosY( initialY );

    // todo: move this out to own func
    if( m_openSheet != -1 )
    {
      ImGui::BeginGroup();

      ImGui::BeginChild( "scrolling", ImVec2( 0, 0 ), true,
                         ImGuiWindowFlags_HorizontalScrollbar );

      renderCurrentSheet();

      ImGui::EndChild();

      ImGui::EndGroup();
    }
  }

  ImGui::End();
}

void ExdViewer::renderCurrentSheet()
{
  ImGui::Columns( m_fieldCount );

  ImGui::Text( "Key" );
  ImGui::NextColumn();

  // todo: output headings

  for( int i = 0; i < m_fieldCount - 1; ++i )
  {
    ImGui::Text( "{%d}", i );
    ImGui::NextColumn();
  }

  ImGuiListClipper clipper( m_rows.size() );

  while( clipper.Step() )
  {
    for( int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++ )
    {
      auto& row = m_rows[ i ];

      ImGui::SetNextItemWidth( 20 );
      ImGui::Text( "%d", i );
      ImGui::NextColumn();

      int index = 0;
      for( const auto& col : row )
      {
        auto type = m_renderTypes[ index++ ];

        switch( type )
        {
          case xiv::exd::DataType::boolean:
            ImGui::Text( "%s", std::get< bool >( col ) ? "true" : "false" );
            break;

          case xiv::exd::DataType::float32:
            ImGui::Text( "%f", std::get< float >( col ) );
            break;

          case xiv::exd::DataType::string:
            ImGui::Text( "%s", std::get< std::string >( col ).c_str() );
            break;

          case xiv::exd::DataType::int8:
            ImGui::Text( "%d", std::get< int8_t >( col ) );
            break;
          case xiv::exd::DataType::int16:
            ImGui::Text( "%d", std::get< int16_t >( col ) );
            break;
          case xiv::exd::DataType::int32:
            ImGui::Text( "%d", std::get< int32_t >( col ) );
            break;

          case xiv::exd::DataType::uint8:
            ImGui::Text( "%d", std::get< uint8_t >( col ) );
            break;
          case xiv::exd::DataType::uint16:
            ImGui::Text( "%d", std::get< uint16_t >( col ) );
            break;
          case xiv::exd::DataType::uint32:
            ImGui::Text( "%d", std::get< uint32_t >( col ) );
            break;
          case xiv::exd::DataType::uint64:
            ImGui::Text( "%llu", std::get< uint64_t >( col ) );
            break;

          default:
            ImGui::Text( "{unknown type}");
            break;
        }

        ImGui::NextColumn();
      }
      ImGui::Separator();
    }
  }

  ImGui::Columns( 1 );
}

void ExdViewer::selectSheet( uint16_t id )
{
//  Logger::debug( "Selected sheet: {}", id );
  m_openSheet = id;

  try
  {
    auto& cat = m_editorMgr->getExdData()->get_category( m_exds[ id ].second );

    auto& header = cat.get_header();
    // add 1 for key column
    m_fieldCount = header.get_header().field_count + 1;

    auto language = xiv::exd::Language::en;

    bool foundLang = false;
    for( const auto& lang : header.get_languages() )
    {
      if( lang == language )
        foundLang = true;
    }

    if( !foundLang )
      language = xiv::exd::Language::none;

    // setup fields
    int index = 0;
    for( const auto& field : header.get_exh_members() )
    {
      m_renderTypes[ index++ ] = field.type;
    }

    // load sheet
    m_currentSheet = cat.get_data_ln( language );

    m_rows = m_currentSheet.get_rows();
  }
  catch( const std::exception& e )
  {
    Logger::error( "Caught exception loading exd data: {}", e.what() );
    m_openSheet = -1;
  }
}