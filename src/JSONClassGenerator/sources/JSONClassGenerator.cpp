#include "../headers/JSONClassGenerator.h"

JSONClassGenerator::JSONClassGenerator(const RootConfig &rootConfig) : ClassGenerator(rootConfig)
{
}

std::string JSONClassGenerator::generateClass(std::string className)
{
    std::string name_upperCase = toUpper(className);
    std::string classString = "";
    classString += generateIncludes(name_upperCase, "CPP", "json.hpp");
    classString += generateClassName(className);

    classString += generateVisibility("private");
    classString += generateConstraintsMap();
    classString += generateFilePath("filePath");
    classString += generateConcatPath();

    classString += generateVisibility("public");
    classString += generateStringLiterals();
    classString += generateConsturctor(className);
    classString += generateGetFromFile();
    classString += generateIsLeaf();
    classString += genetrateGetJSONValue();
    classString += generateSetInFile();
    classString += generateApplyConstraints();
    classString += generateEnd(name_upperCase, "CPP");

    return classString;
}

std::string JSONClassGenerator::genetrateGetJSONValue()
{
    return json_literals::GET_JSON_VALUE;
}

std::string JSONClassGenerator::generateGetFromFile()
{
    return json_literals::GET_FROM_FILE;
}

std::string JSONClassGenerator::generateSetInFile()
{
    return json_literals::SET_IN_FILE;
}

std::string generateGETJSONObj()
{
    return json_literals::GET_JSON_OBJ;
}

