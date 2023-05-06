#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "FormattableString.h"
#include "literals.h"
#include "config.h"

class ClassGenerator
{
private:
    std::string generateIncludes(const std::string &name, const std::string &extension, const std::string &parserLib);
    std::string generateClassName(const std::string &className);
    std::string generateVisibility(const std::string &visibility);
    std::string generateConstraintsMap(const std::vector<Config> &configs);
    std::vector<std::vector<std::string>> getAllLeafs(const std::vector<Config> &configs);
    std::string generateOneConstraint(const std::string &path, const std::string &min, const std::string &max);
    std::string generateFilePath(const std::string &filePath);
    std::string generateConcatPath();
    std::string generateStringLiterals(const std::vector<Config> &configs);
    std::unordered_set<std::string> getAllNames(const std::vector<Config> &configs);
    std::string generateOneStringLiteral(std::string name);
    std::string generateConsturctor(const std::vector<Config> &configs, const std::string &className);
    std::string generateInitializeLiterals(const std::vector<Config> &configs);
    std::string generateOneInitializeLiteral(std::string name);
    virtual std::string generateGetFromFile() = 0;
    std::string generateIsLeaf();
    virtual std::string generateSetInFile() = 0;
    std::string generateApplyConstraints();
    std::string generateEnd(const std::string &className, const std::string &extension);
    std::string toUpper(std::string str);

    std::vector<Config> configs;

public:
    ClassGenerator(const std::vector<Config> &configs);
    virtual std::string generateClass(std::string className) = 0;
};

#endif // CLASSGENERATOR_H