#include "iostream"
#include "GeneratedClass.cpp"
#include <string>

int main()
{
    // make sure to add pugi library to your project
    // required for XML parsing
    auto my_handler = GeneratedClass::getInstance("../xml_file.xml");

    std::cout << my_handler->setVar<std::string>({"name"}, "Elawam") << std::endl;
    std::cout << my_handler->setVar<float>({"salary"}, 8888.5) << std::endl;
    std::cout << my_handler->setVar<int>({"circle", "radius"}, 33) << std::endl;
    std::cout << my_handler->setVar<bool>({"militaryState"}, true) << std::endl;

    std::cout << "-------------------" << std::endl;

    std::cout << my_handler->getVar<std::string>({"name"}) << std::endl;
    std::cout << my_handler->getVar<float>({"salary"}) << std::endl;
    std::cout << my_handler->getVar<int>({"circle", "radius"}) << std::endl;
    std::cout << my_handler->getVar<bool>({"militaryState"}) << std::endl;
}
