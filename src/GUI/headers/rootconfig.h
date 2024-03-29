#ifndef ROOTCONFIG_H
#define ROOTCONFIG_H

#include <vector>
#include <string>
#include <stdexcept>
#include "Config.h"

class RootConfig
{
public:
    RootConfig();
    static RootConfig *InitInstance(const std::vector<Config> &configs, const std::string &fileType, const std::string &className);
    static RootConfig *getInstance();

    std::vector<Config> getConfigs() const;
    std::string getFileType() const;
    std::string getClassName() const;

    void setConfigs(const std::vector<Config> &configs);
    void setFileType(const std::string &fileType);
    void setClassName(const std::string &className);

private:
    RootConfig(const std::vector<Config> &configs, const std::string &fileType, const std::string &className);
    static RootConfig *instance;
    std::vector<Config> configs;
    std::string fileType;
    std::string className;
};

#endif // ROOTCONFIG_H
