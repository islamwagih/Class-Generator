#ifndef JSONCLASSGENERATOR_H
#define JSONCLASSGENERATOR_H

#include "../../ClassGenerator/headers/ClassGenerator.h"
#include "json_literals.h"

class JSONClassGenerator : public ClassGenerator
{
private:
    std::string genetrateGetJSONValue();

protected:
    std::string generateGetFromFile() override;
    std::string generateSetInFile() override;

public:
    JSONClassGenerator(const RootConfig &rootConfig);
    std::string generateClass() override;
};

#endif // JSONCLASSGENERATOR_H