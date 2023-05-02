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
	std::string parserClassName = "Parser";
	addLine("class" + parserClassName,file);
	addLine("{",file);
	changeIndentationLvl(1);

	//Add private section
	addLine("Parser* parser;",file);





	return file;
}

void CodeGeneratorINI::appendPreprocessors(std::vector<std::string>& file)
{
	addLine("#ifndef PARSER_HPP",file);
	addLine("#define PARSER_HPP",file);
	addLine("",file);
	addLine("#include <map>",file);
	addLine("#include <vector>",file);
	addLine("#include <vector>",file);
//	file.push_back("#include \"parser_lib.hpp\""); //Removed for now
	addLine("",file);
}

std::string CodeGeneratorINI::getOutputClassName()
{
	//TODO Change it to receive from config (field does not exist, yet)
	return "MyClass";
}

void CodeGeneratorINI::appendSingletonSection(std::vector<std::string>& file)
{

}

void CodeGeneratorINI::changeIndentationLvl(int change)
{
	indentationLvl+= change;
	indentation = "";
	for (int i=0; i<indentationLvl; i++)
	      indentation+=(char)9; //(char)9 is the ascii for the tab character
}

void CodeGeneratorINI::addLine(const std::string& line, std::vector<std::string>& file)
{
	file.push_back(indentation+line);
}
