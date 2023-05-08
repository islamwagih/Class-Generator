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

void Controller::generateClass(const RootConfig &rootConfig, const std::string &outPath)
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
    std::ofstream out(outPath + "/" + rootConfig.getClassName() + ".cpp");
    out << generatedClass;
    out.close();
}
