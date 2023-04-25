#include "..\headers\rootconfig.h"

RootConfig::RootConfig(const std::vector<Config> &configs, const std::string &fileType)
    : configs(configs), fileType(fileType)
{
}

std::vector<Config> RootConfig::getConfigs() const
{
    return this->configs;
}

std::string RootConfig::getFileType() const
{
    return this->fileType;
}