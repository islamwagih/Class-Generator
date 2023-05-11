#ifndef GeneratedClass_HPP
#define GeneratedClass_HPP
#include <vector>
#include <string>
#include <stdexcept>
#include "parser.cpp"

class GeneratedClass
{
private:
    static GeneratedClass* instance;
    Parser* parser;
    GeneratedClass(const std::string &filePath)
    {

        parser = new Parser(filePath);
    }

public:
    void operator=(GeneratedClass const &) = delete; // delete copy constructor

    static GeneratedClass *getInstance(const std::string &filePath); // static function definition is outside the class
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
        if (parser->applyConstraints<T>(path, value)){
            return parser->setInFile<T>(path, value);
        }
        return false;
    }
};

GeneratedClass *GeneratedClass::instance = nullptr;


GeneratedClass *GeneratedClass::getInstance(const std::string &filePath) {
    if (instance == nullptr)
        instance = new GeneratedClass(filePath);

    return instance;
}

#endif

