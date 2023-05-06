#include <iostream>
#include "CodeGeneratorINI.h"
#include "fileWriter.h"

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
	auto lines = iniGenerator.generateParserH();

	//Write output to file
	FileWriter::writeFile("../Parser.h",lines);
	return 0;
}
