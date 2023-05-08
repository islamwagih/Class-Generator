#include "../headers/ClassGenerator.h"
#include <iostream>

ClassGenerator::ClassGenerator(const RootConfig &root_config)
{
    this->rootConfig = root_config;
}

std::string ClassGenerator::generateIncludes(const std::string &extension, const std::string &parserLib)
{
    return literals::INCLUDES.format({{"{NAME}", this->toUpper(this->rootConfig.getClassName())}, {"{EXTENSION}", extension}, {"{PARSER_LIB}", parserLib}});
}

std::string ClassGenerator::generateClassName()
{
    return literals::CLASS_NAME.format({{"{CLASS_NAME}", this->rootConfig.getClassName()}});
}

std::string ClassGenerator::generateVisibility(const std::string &visibility)
{
    return literals::VISIBILITY.format({{"{VISIBILITY}", visibility}});
}

std::string ClassGenerator::generateConstraintsMap()
{
    std::string constraints = "";
    std::vector<std::vector<std::string>> leafs = getAllLeafs(this->rootConfig.getConfigs());
    for (auto config : leafs)
    {
        constraints += generateOneConstraint(config[0], config[1], config[2]);
    }
    return literals::CONSTRAINTS_MAP.format({{"{CONSTRAINTS}", constraints}});
}

std::vector<std::vector<std::string>> ClassGenerator::getAllLeafs(const std::vector<Config> &configs)
{
    std::vector<std::vector<std::string>> leafs;
    std::vector<Config> configs = this->rootConfig.getConfigs();
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

std::string ClassGenerator::generateConcatPath()
{
    return literals::CONCAT_PATH;
}

std::string ClassGenerator::generateStringLiterals()
{
    std::string stringLiterals = "";
    std::vector<Config> configs = this->rootConfig.getConfigs();
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
    std::vector<Config> configs = this->rootConfig.getConfigs();
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
    return literals::ONE_STRING_LITERAL.format({{"{NAME}", toUpper(name)}});
}

std::string ClassGenerator::generateConsturctor()
{
    std::vector<Config> configs = this->rootConfig.getConfigs();
    return literals::CONSTRUCTOR.format({{"{CLASS_NAME}", this->rootConfig.getClassName()}, {"{INITIALIZE_LITERALS}", generateInitializeLiterals()}});
}

std::string ClassGenerator::generateInitializeLiterals()
{
    std::string initializeLiterals = "";
    std::vector<Config> configs = this->rootConfig.getConfigs();
    std::unordered_set<std::string> names = getAllNames(configs);
    for (auto name : names)
    {
        initializeLiterals += generateOneInitializeLiteral(name);
    }
    return literals::INITIALIZE_LITERALS.format({{"{INITIALIZE_LITERALS}", initializeLiterals}});
}

std::string ClassGenerator::generateOneInitializeLiteral(std::string name)
{
    std::string upper = toUpper(name);
    return literals::ONE_INITIALIZE_LITERAL.format({{"{NAME_UPPER}", upper}, {"{NAME}", name}});
}

std::string ClassGenerator::generateIsLeaf()
{
    return literals::IS_LEAF;
}

std::string ClassGenerator::generateApplyConstraints()
{
    return literals::APPLY_CONSTRAINTS;
}

std::string ClassGenerator::generateEnd(const std::string &extension)
{
    return literals::END.format({{"{CLASS_NAME}", this->rootConfig.getClassName()}, {"{EXTENSION}", extension}});
}

static std::string ClassGenerator::toUpper(std::string str)
{
    std::string upper = "";
    for (int x = 0; x < str.size(); x++)
    {
        upper += toupper(str[x]);
    }
    return upper;
}
