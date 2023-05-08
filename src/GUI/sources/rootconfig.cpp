#include "headers\rootconfig.h"

RootConfig *RootConfig::instance = nullptr;

RootConfig::RootConfig()
{
}

RootConfig::RootConfig(const std::vector<Config> &configs, const std::string &fileType, const std::string &className)
    : configs(configs), fileType(fileType), className(className)
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

std::string RootConfig::getClassName() const
{
    return this->className;
}

void RootConfig::setConfigs(const std::vector<Config> &configs)
{
    this->configs = configs;
}

void RootConfig::setFileType(const std::string &fileType)
{
    this->fileType = fileType;
}

void RootConfig::setClassName(const std::string &className)
{
    this->className = className;
}

RootConfig *RootConfig::InitInstance(const std::vector<Config> &configs, const std::string &fileType, const std::string &className)
{
    if (instance == nullptr)
    {
        instance = new RootConfig(configs, fileType, className);
    }
    else
    {
        instance->setConfigs(configs);
        instance->setFileType(fileType);
        instance->setClassName(className);
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
