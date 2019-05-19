#ifndef SAPPHIREED_CONFIGMGR_H
#define SAPPHIREED_CONFIGMGR_H

#include <string>
#include <unordered_map>

#include "Forwards.h"
#include <nlohmann/json_fwd.hpp>

namespace Sapphire::Editor
{
  class ConfigMgr
  {
    std::unordered_map< std::string, nlohmann::json > m_configs;

  public:
    static constexpr auto EDITOR_CONFIG_GROUP = "editor";

    explicit ConfigMgr( const std::string& basePath = "./data/config/" );

    nlohmann::json& getConfig( const std::string& group );

    void saveGroup( const std::string& group );
    void saveAll();
  };
}




#endif //SAPPHIREED_CONFIGMGR_H
