#ifndef INICLASSGENERATOR_H
#define INICLASSGENERATOR_H

#include "ClassGenerator.h"
#include "INI_literals.h"

class INIClassGenerator : public ClassGenerator
{
private:
    std::string generateGetFromFile() override;
    std::string generateSetInFile() override;

public:
    INIClassGenerator(const RootConfig &root_config);
    std::string generateClass() override;
};

#endif // INICLASSGENERATOR_H