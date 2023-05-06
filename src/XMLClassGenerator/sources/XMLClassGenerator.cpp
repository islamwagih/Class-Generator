#include "../headers/ClassGenerator.h"
#include <iostream>

XMLClassGenerator::XMLClassGenerator(const std::vector<Config> &configs) : ClassGenerator(configs)
{
}

std::string XMLClassGenerator::generateClass(std::string className) override
{
    std::string name_upperCase = ClassGenerator::toUpper(className);
    std::string classString = "";
    classString += generateIncludes(name_upperCase, "CPP", "xml.hpp");
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

std::string XMLClassGenerator::generateGetXmlDoc()
{
    return xml_literals::GET_XML_DOC;
}

std::string ClassGenerator::generateGetFromFile() override
{
    return xml_literals::GET_FROM_FILE;
}

std::string ClassGenerator::generateSetInFile() override
{
    return xml_literals::SET_IN_FILE;
}

#include <fstream>
int main()
{
    std::vector<Config> configs;
    Config x("x", "int", {"-3", "3"}, {});
    Config y("y", "bool", {""}, {});
    Config width("width", "string", {"[a-z]+[0-9]+"}, {});
    Config height("height", "int", {"0", "1000"}, {});
    Config rect("rect", "nested", {""}, {x, y, width, height});
    ClassGenerator cg({rect});
    // open file temp.cpp
    std::ofstream file("temp.cpp");
    // write cg.generateClass() to file
    if (file.is_open())
    {
        file << cg.generateClass();
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file";
    }
    // close file
    // std::cout << cg.generateClass({}) << std::endl;
}