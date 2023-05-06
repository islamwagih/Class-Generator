#include "JSONClassGenerator.h"

JSONClassGenerator::JSONClassGenerator(const RootConfig &rootConfig) : ClassGenerator(rootConfig)
{
}

std::string XMLClassGenerator::generateClass(std::string className) override
{
    std::string name_upperCase = ClassGenerator::toUpper(className);
    std::vector<Config> configs = this->rootConfig.getConfigs();
    std::string classString = "";
    classString += generateIncludes(name_upperCase, "CPP", "json.hpp");
    classString += generateClassName(className);

    classString += generateVisibility("private");
    classString += generateConstraintsMap(configs);
    classString += generateGETJSONObj();
    classString += generateFilePath("filePath");
    classString += generateConcatPath();

    classString += generateVisibility("public");
    classString += generateStringLiterals(configs);
    classString += generateConsturctor(configs, className);
    classString += generateGetFromFile();
    classString += generateIsLeaf();
    classString += genetrateGetJSONValue();
    classString += generateSetInFile();
    classString += generateApplyConstraints();
    classString += generateEnd(name_upperCase, "CPP");

    return classString;
}

std::string JSONClassGenerator::generateGetXmlDoc()
{
    return json_literals::GET_JSON_VALUE;
}

std::string JSONClassGenerator::generateGetFromFile() override
{
    return json_literals::GET_FROM_FILE;
}

std::string JSONClassGenerator::generateSetInFile() override
{
    return json_literals::SET_IN_FILE;
}

std::string generateGETJSONObj(){
    return json_literals::GET_JSON_OBJ;
}

