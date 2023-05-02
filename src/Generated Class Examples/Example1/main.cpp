#include "myclass.cpp"
#include "vector"
#include "string"
#include <iostream>

MyClass* MyClass::instance = nullptr; //initialize the static pointer

int main()
{
    MyClass::init("test.json");
    MyClass*myClass = MyClass::getInstance();
    std::vector<std::string> path = {"rect", "width"};
    std::cout << myClass->getVar<int>(path) << std::endl;
    myClass->setVar<int>(path, 5);
}
