#include "ConfigMgr.h"

#include <filesystem>
#include <Util/Logger.h>

#include <nlohmann/json.hpp>
#include <fstream>

namespace fs = std::filesystem;

using namespace Sapphire::Editor;

ConfigMgr::ConfigMgr( const std::string& basePath )
{
  std::vector< fs::path > filesToLoad;

  std::string defaultSegment = ".default";

  for( auto& file : fs::directory_iterator( basePath ) )
  {
    auto filename = file.path().filename();

    // default file, see if we can copy it
    auto off = filename.string().find( defaultSegment );
    if( off != std::string::npos )
    {
      auto cleanedFilename = filename.string().erase( off, 8 );
      auto newFile = fs::path( basePath + cleanedFilename );

      if( fs::exists( newFile ) )
        continue;

      Logger::info( "Creating default config file from default: {}", filename.string().c_str() );

      fs::copy( file, newFile, fs::copy_options::skip_existing );

      filesToLoad.emplace_back( newFile );
    }
    else
    {
      filesToLoad.emplace_back( file );
    }
  }

  // load groups
  for( fs::path& file : filesToLoad )
  {
    Logger::info( "Loading config file '{}' as group '{}'", file.filename().string(), file.stem().string() );

    try
    {
      m_configs[ file.stem().string() ] = nlohmann::json::parse( std::ifstream( file ) );
    }
    catch( const std::exception& e )
    {
      Logger::warn( "Error loading config file '{}': {}", file.string(), e.what() );
    }
  }
}

nlohmann::json& ConfigMgr::getConfig( const std::string& group )
{
  return m_configs[ group ];
}