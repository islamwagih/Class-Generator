#include "../headers/INIClassGenerator.h"
#include <iostream>

INIClassGenerator::INIClassGenerator(const RootConfig &root_config) : ClassGenerator(root_config)
{
}

std::string INIClassGenerator::generateClass()
{
    std::string className = this->rootConfig.getClassName();
    std::string name_upperCase = ClassGenerator::toUpper(className);
    std::string classString = "";
    classString += generateIncludes("CPP", "ini.h");
    classString += generateClassName();

    classString += generateVisibility("private");
    classString += generateConstraintsMap();
    classString += generateFilePath("filePath");
    classString += generateConcatPath();

    classString += generateVisibility("public");
    classString += generateStringLiterals();
    classString += generateConsturctor();
    classString += generateGetFromFile();
    classString += generateIsLeaf();
    classString += generateSetInFile();
    classString += generateApplyConstraints();
    classString += generateEnd("CPP");

    return classString;
}

std::string INIClassGenerator::generateGetFromFile()
{
    return ini_literals::GET_FROM_FILE;
}

std::string INIClassGenerator::generateSetInFile()
{
    return ini_literals::SET_IN_FILE;
}
