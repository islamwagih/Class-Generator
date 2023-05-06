#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "CodeGeneratorINI.h"
#include "fileWriter.h"

void executeBoostExample()
{
	std::string path = "../example.ini";
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(path, pt);

	//Read value
	auto value = pt.get<std::string>("Algorithms.graph_algorithm");
	std::cout<<"OLD: Algorithms.graph_algorithm = "<< value<< std::endl;

	//Write value
	pt.put("Algorithms.graph_algorithm", "breadth_first_search");
	boost::property_tree::ini_parser::write_ini(path, pt);

	//Read value again
	value = pt.get<std::string>("Algorithms.graph_algorithm");
	std::cout<<"NEW: Algorithms.graph_algorithm = "<< value<< std::endl;

	//Revert value to original
	pt.put("Algorithms.graph_algorithm", "depth_first_search");
	boost::property_tree::ini_parser::write_ini(path, pt);

	//Confirm value reversion
	value = pt.get<std::string>("Algorithms.graph_algorithm");
	std::cout<<"LAST: Algorithms.graph_algorithm = "<< value<< std::endl;
}

int main()
{
	//Prepare a fake root config
	std::string fileType = "INI";
	std::vector<Config> configs
	{
		Config("Width",  "int", {"0", "10"}, std::vector<Config>()),
		Config("Height", "int", {"0", "15"}, std::vector<Config>()),
		Config("Length", "int", {"0", "15"}, std::vector<Config>()),
	};
	RootConfig* rootConfig = RootConfig::InitInstance(configs,fileType);

	//Initialise the generator and get output
	CodeGeneratorINI iniGenerator(rootConfig);
	auto parser_h = iniGenerator.generateParserH();
	auto myClass_h = iniGenerator.generateMyClassH();

	//Write output to file
	FileWriter::writeFile("../parser.h", parser_h);
	FileWriter::writeFile("../myClass.h", myClass_h);

	return 0;
}
