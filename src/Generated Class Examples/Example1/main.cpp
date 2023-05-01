#include "myclass.hpp"
#include "parser.hpp"
#include "vector"
#include "string"
#include <iostream>
int main()
{
    MyClass::init("test.json");
    MyClass *myClass = MyClass::getInstance();
    std::vector<std::string> path = {Parser::RECT1, Parser::WIDTH};
    std::cout << myClass->getVar<int>(path) << std::endl;
    myClass->setVar<int>(path, 5);
}