#ifndef TestingINI_HPP
#define TestingINI_HPP
#include <vector>
#include <string>
#include <stdexcept>
#include "Parser.cpp"

class TestingINI
{
private:
    static TestingINI* instance;
    Parser* parser;
    TestingINI(const std::string &filePath)
    {

        parser = new Parser(filePath);
    }

public:
    void operator=(TestingINI const &) = delete; // delete copy constructor

    static TestingINI *getInstance(const std::string &filePath); // static function definition is outside the class
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

TestingINI *TestingINI::instance = nullptr;


TestingINI *TestingINI::getInstance(const std::string &filePath) {
    if (instance == nullptr)
        instance = new TestingINI(filePath);

    return instance;
}

#endif

