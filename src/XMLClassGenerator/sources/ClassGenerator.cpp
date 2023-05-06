#include "../headers/ClassGenerator.h"
#include <iostream>

ClassGenerator::ClassGenerator(const std::vector<Config> &configs)
{
    this->configs = configs;
}

std::string ClassGenerator::generateClass()
{
    std::string classString = "";
    classString += generateIncludes("PARSER", "CPP", "xml.hpp");
    classString += generateClassName("Parser");

    classString += generateVisibility("private");
    classString += generateConstraintsMap(configs);
    classString += generateFilePath("filePath");
    classString += generateGetXmlDoc();
    classString += generateConcatPath();

    classString += generateVisibility("public");
    classString += generateStringLiterals(configs);
    classString += generateConsturctor(configs, "Parser");
    classString += generateGetFromFile();
    classString += generateIsLeaf();
    classString += generateSetInFile();
    classString += generateApplyConstraints();
    classString += generateEnd("PARSER", "CPP");

    return classString;
}

std::string ClassGenerator::generateIncludes(const std::string &name, const std::string &extension, const std::string &parserLib)
{
    return literals::INCLUDES.format({{"{NAME}", name}, {"{EXTENSION}", extension}, {"{PARSER_LIB}", parserLib}});
}

std::string ClassGenerator::generateClassName(const std::string &className)
{
    return literals::CLASS_NAME.format({{"{CLASS_NAME}", className}});
}

std::string ClassGenerator::generateVisibility(const std::string &visibility)
{
    return literals::VISIBILITY.format({{"{VISIBILITY}", visibility}});
}

std::string ClassGenerator::generateConstraintsMap(const std::vector<Config> &configs)
{
    std::string constraints = "";
    std::vector<std::vector<std::string>> leafs = getAllLeafs(configs);
    for (auto config : leafs)
    {
        constraints += generateOneConstraint(config[0], config[1], config[2]);
    }
    return literals::CONSTRAINTS_MAP.format({{"{CONSTRAINTS}", constraints}});
}

std::vector<std::vector<std::string>> ClassGenerator::getAllLeafs(const std::vector<Config> &configs)
{
    std::vector<std::vector<std::string>> leafs;
    for (auto config : configs)
    {
        if (config.getChildren().size() == 0)
        {
            std::vector<std::string> leaf;
            leaf.push_back(config.getName());
            if (config.getConstraints().size() == 1)
            {
                leaf.push_back(config.getConstraints()[0]);
                leaf.push_back("");
            }
            else
            {
                auto first = config.getConstraints()[0];
                auto second = config.getConstraints()[1];
                if (first.size() != 0 && second.size() != 0 && std::stod(first) > std::stod(second))
                {
                    std::string temp = first;
                    first = second;
                    second = temp;
                }
                leaf.push_back(first);
                leaf.push_back(second);
            }
            leafs.push_back(leaf);
        }
        else
        {
            std::vector<std::vector<std::string>> childrenLeafs = getAllLeafs(config.getChildren());
            leafs.insert(leafs.end(), childrenLeafs.begin(), childrenLeafs.end());
        }
    }
    return leafs;
}

std::string ClassGenerator::generateOneConstraint(const std::string &path, const std::string &min, const std::string &max)
{
    return literals::ONE_CONSTRAINT.format({{"{PATH}", path}, {"{MIN}", min}, {"{MAX}", max}});
}

std::string ClassGenerator::generateFilePath(const std::string &filePath)
{
    return literals::FILE_PATH.format({{"{FILE_PATH}", filePath}});
}

std::string ClassGenerator::generateGetXmlDoc()
{
    return literals::GET_XML_DOC;
}

std::string ClassGenerator::generateConcatPath()
{
    return literals::CONCAT_PATH;
}

std::string ClassGenerator::generateStringLiterals(const std::vector<Config> &configs)
{
    std::string stringLiterals = "";
    std::unordered_set<std::string> names = getAllNames(configs);
    for (auto name : names)
    {
        stringLiterals += generateOneStringLiteral(name);
    }
    return literals::STRING_LITERALS.format({{"{STRING_LITERALS}", stringLiterals}});
}

std::unordered_set<std::string> ClassGenerator::getAllNames(const std::vector<Config> &configs)
{
    std::unordered_set<std::string> names;
    for (auto config : configs)
    {
        if (config.getChildren().size() == 0)
        {
            names.insert(config.getName());
        }
        else
        {
            std::unordered_set<std::string> childrenNames = getAllNames(config.getChildren());
            names.insert(childrenNames.begin(), childrenNames.end());
            names.insert(config.getName());
        }
    }
    return names;
}

std::string ClassGenerator::generateOneStringLiteral(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    return literals::ONE_STRING_LITERAL.format({{"{NAME}", name}});
}

std::string ClassGenerator::generateConsturctor(const std::vector<Config> &configs, const std::string &className)
{
    return literals::CONSTRUCTOR.format({{"{CLASS_NAME}", className}, {"{INITIALIZE_LITERALS}", generateInitializeLiterals(configs)}});
}

std::string ClassGenerator::generateInitializeLiterals(const std::vector<Config> &configs)
{
    std::string initializeLiterals = "";
    std::unordered_set<std::string> names = getAllNames(configs);
    for (auto name : names)
    {
        initializeLiterals += generateOneInitializeLiteral(name);
    }
    return literals::INITIALIZE_LITERALS.format({{"{INITIALIZE_LITERALS}", initializeLiterals}});
}

std::string ClassGenerator::generateOneInitializeLiteral(std::string name)
{
    std::string upper = name;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    return literals::ONE_INITIALIZE_LITERAL.format({{"{NAME_UPPER}", upper}, {"{NAME}", name}});
}

std::string ClassGenerator::generateGetFromFile()
{
    return literals::GET_FROM_FILE;
}

std::string ClassGenerator::generateIsLeaf()
{
    return literals::IS_LEAF;
}

std::string ClassGenerator::generateSetInFile()
{
    return literals::SET_IN_FILE;
}

std::string ClassGenerator::generateApplyConstraints()
{
    return literals::APPLY_CONSTRAINTS;
}

std::string ClassGenerator::generateEnd(const std::string &className, const std::string &extension)
{
    return literals::END.format({{"{CLASS_NAME}", className}, {"{EXTENSION}", extension}});
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