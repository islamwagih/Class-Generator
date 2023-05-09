#include "user_literals.h"

namespace user_literals
{
    FormattableString USER_CLASS = 
R"(#ifndef {CLASS_NAME}_HPP
#define {CLASS_NAME}_HPP
#include <vector>
#include <string>
#include <stdexcept>
#include <parser.cpp>

class {CLASS_NAME}
{
private:
    static {CLASS_NAME}* instance;
    Parser* parser;
    {CLASS_NAME}(std::string filePath)
    {

        parser = new Parser(filePath);
    }

public:
    // init class. Should be called before any other method
    static void init(std::string filePath)
    {
        if (instance == nullptr)
            instance = new {CLASS_NAME}(filePath);
    }
    static {CLASS_NAME} *getInstance()
    {
        if (instance == nullptr)
            throw std::runtime_error("{CLASS_NAME} not initialized");
        return instance;
    }
    template <typename T>
    T getVar(std::vector<std::string> path)
    {
        if (!parser->isLeaf(path))
        {
            throw std::runtime_error("Path is not a leaf");
        }
        return parser->getFromFile<T>(path);
    }
    template <typename T>
    bool setVar(std::vector<std::string> path, T value)
    {
        if (!parser->isLeaf(path))
        {
            throw std::runtime_error("Path is not a leaf");
        }
        if (parser->applyConstraints<T>(path, value)) return parser->setInFile<T>(path, value);
        return false;
    }
};



#endif
)";
}