#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

int main()
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
	return 0;
}
