#include "..\headers\rootconfig.h"

RootConfig *RootConfig::instance = nullptr;

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

void RootConfig::setConfigs(const std::vector<Config> &configs)
{
    this->configs = configs;
}

void RootConfig::setFileType(const std::string &fileType)
{
    this->fileType = fileType;
}

RootConfig *RootConfig::InitInstance(const std::vector<Config> &configs, const std::string &fileType)
{
    if (instance == nullptr)
    {
        instance = new RootConfig(configs, fileType);
    }
    else
    {
        instance->setConfigs(configs);
        instance->setFileType(fileType);
    }
    return instance;
}

RootConfig *RootConfig::getInstance()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("RootConfig instance not initialized");
    }
    return instance;
}