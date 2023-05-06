#ifndef JSONCLASSGENERATOR_H
#define JSONCLASSGENERATOR_H

#include "ClassGenerator.h"
#include "json_literals.h"

class JSONClassGenerator :: public ClassGenerator
{
private:
    std::string generateGetJSONValue();
    std::string generateGETJSONObj();


public:
    JSONClassGenerator(const RootConfig &rootConfig);
};

#endif // JSONCLASSGENERATOR_H