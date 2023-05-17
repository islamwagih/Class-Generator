#ifndef INICLASSGENERATOR_H
#define INICLASSGENERATOR_H

#include "../../ClassGenerator/headers/ClassGenerator.h"
#include "INI_literals.h"

class INIClassGenerator : public ClassGenerator
{
protected:
    std::string generateGetFromFile() override;
    std::string generateSetInFile() override;

public:
    INIClassGenerator(const RootConfig &root_config);
    std::string generateClass() override;
};

#endif // INICLASSGENERATOR_H
