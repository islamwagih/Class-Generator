#include "Controller.h"

Controller *Controller::instance = nullptr;

Controller::Controller()
{
}

Controller *Controller::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Controller();
    }
    return instance;
}

void Controller::generateClasses(const RootConfig &rootConfig, const std::string &outPath)
{
    generateUserClass(rootConfig, outPath);
    generateParserclass(rootConfig, outPath);
}

void Controller::generateUserClass(const RootConfig &rootConfig, const std::string &outPath)
{
    std::ofstream out(outPath + "/" + rootConfig.getClassName() + ".cpp");
    out << user_literals::USER_CLASS.format({{"{CLASS_NAME}", rootConfig.getClassName()}});
    out.close();
}

void Controller::generateParserclass(const RootConfig &rootConfig, const std::string &outPath)
{
    auto type = rootConfig.getFileType();
    ClassGenerator *generator;
    if (type == "JSON")
    {
        generator = new JSONClassGenerator(rootConfig);
    }
    else if (type == "XML")
    {
        generator = new XMLClassGenerator(rootConfig);
    }
    else if (type == "INI")
    {
        generator = new INIClassGenerator(rootConfig);
    }
    std::string generatedClass = generator->generateClass();
    std::ofstream out(outPath + "/Parser.cpp");
    out << generatedClass;
    out.close();
}
