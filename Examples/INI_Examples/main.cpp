#include <iostream>
/*
# Example ini file contents
[Sect]
param1=mew
param2="13"
 */

#include "./TestingINI.cpp"
int main()
{
	Parser* parser = new Parser("./conf.ini");
	auto p1 = parser->getFromFile<std::string>({"sect","param1"});
	std::cout<<"reult:  "<<p1;

	std::vector<std::string> v;
	v = {"Sect22","param1"};
	parser->setInFile(v ,"mew");


	return 0;
}
