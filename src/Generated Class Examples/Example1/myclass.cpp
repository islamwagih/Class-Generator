#ifndef MYCLASS_HPP
#define MYCLASS_HPP
#include <vector>
#include <string>
#include <stdexcept>
#include <parser.cpp>

class MyClass
{
private:
    static MyClass* instance;
    Parser* parser;
    MyClass(std::string filePath)
    {

        parser = new Parser(filePath);
    }

public:
    // init class. Should be called before any other method
    static void init(std::string filePath)
    {
        if (instance == nullptr)
            instance = new MyClass(filePath);
    }
    static MyClass *getInstance()
    {
        if (instance == nullptr)
            throw std::runtime_error("MyClass not initialized"); // Don't forget to change class name here too
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
