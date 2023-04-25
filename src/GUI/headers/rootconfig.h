#ifndef ROOTCONFIG_H
#define ROOTCONFIG_H

#include <vector>
#include <string>
#include "Config.h"

class RootConfig
{
public:
    static RootConfig *InitInstance(const std::vector<Config> &configs, const std::string &fileType);
    static RootConfig *getInstance();

    std::vector<Config> getConfigs() const;
    std::string getFileType() const;

    void setConfigs(const std::vector<Config> &configs);
    void setFileType(const std::string &fileType);

private:
    static RootConfig *instance;
    RootConfig(const std::vector<Config> &configs, const std::string &fileType);
    std::vector<Config> configs;
    std::string fileType;

};

#endif // ROOTCONFIG_H
