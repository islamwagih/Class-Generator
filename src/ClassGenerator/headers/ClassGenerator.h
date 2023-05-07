#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "FormattableString.h"
#include "literals.h"
#include "../../GUI/headers/RootConfig.h"
#include "../../GUI/headers/Config.h"

class ClassGenerator
{
protected:
    std::string generateIncludes(const std::string &name, const std::string &extension, const std::string &parserLib);
    std::string generateClassName(const std::string &className);
    std::string generateVisibility(const std::string &visibility);
    std::string generateConstraintsMap();
    std::vector<std::vector<std::string>> getAllLeafs();
    std::string generateOneConstraint(const std::string &path, const std::string &min, const std::string &max);
    std::string generateFilePath(const std::string &filePath);
    std::string generateConcatPath();
    std::string generateStringLiterals();
    std::unordered_set<std::string> getAllNames();
    std::string generateOneStringLiteral(std::string name);
    std::string generateConsturctor(const std::string &className);
    std::string generateInitializeLiterals();
    std::string generateOneInitializeLiteral(std::string name);
    virtual std::string generateGetFromFile() = 0;
    std::string generateIsLeaf();
    virtual std::string generateSetInFile() = 0;
    std::string generateApplyConstraints();
    std::string generateEnd(const std::string &className, const std::string &extension);
    static std::string toUpper(std::string str);

    RootConfig rootConfig;


public:
    ClassGenerator(const RootConfig &root_config);
    virtual std::string generateClass(std::string className) = 0;
};

#endif // CLASSGENERATOR_H