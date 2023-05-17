#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <fstream>
#include "../GUI/headers/RootConfig.h"
#include "../ClassGenerator/headers/ClassGenerator.h"
#include "../UserClassGenerator/user_literals.h"
#include "../JSONClassGenerator/headers/JSONClassGenerator.h"
#include "../XMLClassGenerator/headers/XMLClassGenerator.h"
#include "../INIClassGenerator/headers/INIClassGenerator.h"

class Controller
{
public:
    static Controller *getInstance();
    void generateClasses(const RootConfig &rootConfig, const std::string &outPath);
    void generateUserClass(const RootConfig &rootConfig, const std::string &outPath);
    void generateParserclass(const RootConfig &rootConfig, const std::string &outPath);

private:
    static Controller *instance;
    Controller();
    Controller(const Controller &other) = delete;
    Controller &operator=(const Controller &other) = delete;
};

#endif // CONTROLLER_H
