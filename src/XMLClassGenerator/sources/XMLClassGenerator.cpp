#include "../headers/XMLClassGenerator.h"

XMLClassGenerator::XMLClassGenerator(const RootConfig &root_config) : ClassGenerator(root_config)
{
}

std::string XMLClassGenerator::generateClass()
{
    std::string classString = "";
    classString += generateIncludes("CPP", "pugixml.hpp");
    classString += generateClassName();

    classString += generateVisibility("private");
    classString += generateConstraintsMap();
    classString += generateFilePath("filePath");
    classString += generateGetXmlDoc();
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

std::string XMLClassGenerator::generateGetXmlDoc()
{
    return xml_literals::GET_XML_DOC;
}

std::string XMLClassGenerator::generateGetFromFile()
{
    return xml_literals::GET_FROM_FILE;
}

std::string XMLClassGenerator::generateSetInFile()
{
    return xml_literals::SET_IN_FILE;
}
