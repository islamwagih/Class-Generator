#ifndef ROOTCONFIG_H
#define ROOTCONFIG_H

#include <vector>
#include <string>
#include "Config.h"

class RootConfig
{
public:
    RootConfig(const std::vector<Config> &configs, const std::string &fileType);
    std::vector<Config> getConfigs() const;
    std::string getFileType() const;

private:
    std::vector<Config> configs;
    std::string fileType;
};

#endif // ROOTCONFIG_H
