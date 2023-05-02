//
// Created by khaled on 5/2/23.
//

#include "CodeGeneratorINI.h"

CodeGeneratorINI::CodeGeneratorINI(const Config& config) : config(config)
{}

std::vector<std::string> CodeGeneratorINI::generateParserH()
{
	std::vector<std::string> file;

	//Add preprocessing statements
	appendPreprocessors(file);

	//Add class name





	return file;
}

void CodeGeneratorINI::appendPreprocessors(std::vector<std::string>& file)
{
	file.push_back("#ifndef PARSER_HPP");
	file.push_back("#define PARSER_HPP");
	file.push_back("");
	file.push_back("#include <map>");
	file.push_back("#include <vector>");
	file.push_back("#include <vector>");
//	file.push_back("#include \"parser_lib.hpp\""); //Removed for now
	file.push_back("");
}

std::string CodeGeneratorINI::getOutputClassName()
{
	//TODO Change it to receive from config (field does not exist, yet)
	return "MyClass";
}

void CodeGeneratorINI::appendSingletonSection(std::vector<std::string>& file)
{

}
