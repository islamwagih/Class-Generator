#include "INIClassGenerator.h"
#include <iostream>

INIClassGenerator::INIClassGenerator(const RootConfig &root_config) : ClassGenerator(root_config)
{
}

std::string INIClassGenerator::generateClass()
{
    std::string name_upperCase = ClassGenerator::toUpper(className);
    std::string classString = "";
    classString += generateIncludes(name_upperCase, "CPP", "ini.h");
    classString += generateClassName(className);

    classString += generateVisibility("private");
    classString += generateConstraintsMap(configs);
    classString += generateFilePath("filePath");
    classString += generateGetXmlDoc();
    classString += generateConcatPath();

    classString += generateVisibility("public");
    classString += generateStringLiterals(configs);
    classString += generateConsturctor(configs, className);
    classString += generateGetFromFile();
    classString += generateIsLeaf();
    classString += generateSetInFile();
    classString += generateApplyConstraints();
    classString += generateEnd(name_upperCase, "CPP");

    return classString;
}

std::string INIClassGenerator::generateGetFromFile() override
{
    return ini_literals::GET_FROM_FILE;
}

std::string INIClassGenerator::generateSetInFile() override
{
    return ini_literals::SET_IN_FILE;
}