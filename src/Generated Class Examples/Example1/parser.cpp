#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>
#include <vector>
#include <string>
#include "parser_lib.hpp"

class Parser
{
private:
    std::map<std::string, std::vector<std::string>> constraints = {
        {"rect1.width", {"0", "10"}},
        {"rect1.height", {"0", "10"}},
        {"rect2.width", {"", ""}},
        {"rect2.height", {"", ""}},
        {"dimension1.dimension2.dimension3", {"", ""}}}; // Auto generated from UI
    std::string filePath;

public:
    std::string RECT1;
    std::string RECT2;
    std::string WIDTH;
    std::string HEIGHT;
    std::string DIMENSION1;
    std::string DIMENSION2;
    std::string DIMENSION3;

    Parser(std::string filePath)
    {
        this->filePath = filePath;
        RECT1 = "rect1";
        RECT2 = "rect2";
        WIDTH = "width";
        HEIGHT = "height";
        DIMENSION1 = "dimension1";
        DIMENSION2 = "dimension2";
        DIMENSION3 = "dimension3";
    }

    template <typename T>
    T getFromFile(std::vector<std::string> path)
    {
    }

    bool isLeaf(std::vector<std::string> path)
    {
        return true;
    }

    template <typename T>
    bool setInFile(std::vector<std::string> path, T value)
    {
    }

    template <typename T>
    bool applyConstraints(std::vector<std::string> path, T value)
    {
    }
};

#endif
