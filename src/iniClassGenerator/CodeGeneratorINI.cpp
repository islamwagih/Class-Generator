//
// Created by khaled on 5/2/23.
//

#include "CodeGeneratorINI.h"

CodeGeneratorINI::CodeGeneratorINI(RootConfig* rootConfig) : rootConfig(*rootConfig)
{}

std::vector<std::string> CodeGeneratorINI::generateParserH()
{
	file.clear();
	//Add preprocessing statements
	appendPreprocessors(file);

	//Add class name
	std::string parserClassName = "Parser";
	addLine("class " + parserClassName);
	addLine("{");

	//Add private section
	addLine("private:");
	changeIndentationLvl(1);
	appendDirectoryMap(file);
	addLine("std::string filePath;");
	changeIndentationLvl(-1);

	//Add public section
	addLine("private:");
	changeIndentationLvl(1);
	auto variables =  getVariablesNames();

	//Add public variables section
	for(const auto& variableName: variables)
	{
		addLine("std::string " + capitalizeWord(variableName) + ";");
	}

	//Add constructor
	addLine(parserClassName +" (std::string filePath)");
	addLine("{");
	changeIndentationLvl(1);
	addLine("this->filePath = filePath;");
	//init class variables
	for(const auto& variableName: variables)
	{
		addLine(capitalizeWord(variableName) + " = \"" + variableName+"\";");
	}
	changeIndentationLvl(-1);
	addLine("}");
	addLine("");

	//Write the function: getFromFile()
	//TODO change path to be vector of enum values
	addLine("template <typename T>");
	addLine("T getFromFile(std::vector<std::string> path)");
	addLine("{");
	changeIndentationLvl(1);
	addLine("boost::property_tree::ptree pt;");
	addLine("boost::property_tree::ini_parser::read_ini(filePath, pt);");
	addLine("T value = pt.get<T>(path);");
	addLine("return value;");
	changeIndentationLvl(-1);
	addLine("}");


	//Write the function: setInFile()
	//TODO change path to be vector of enum values
	addLine("template <typename T>");
	addLine("bool setInFile(std::vector<std::string> path, T value)");
	addLine("{");
	changeIndentationLvl(1);
	addLine("if(applyConstrains(path, value) == false)  return false;");
	addLine("boost::property_tree::ptree pt;");
	addLine("boost::property_tree::ini_parser::read_ini(filePath, pt);");
	addLine("pt.put(path, value);");
	addLine("return (getFromFile<T>(path) == value);");  //Validate be re-reading the value
	changeIndentationLvl(-1);
	addLine("}");


	//Write the function: applyConstraints()
	addLine("template <typename T>");
	addLine("bool applyConstraints(std::vector<std::string> path, T value)");
	addLine("{");
	changeIndentationLvl(1);
	//TODO add the implementation for applyConstraints
	addLine("return true;");
	changeIndentationLvl(-1);
	addLine("}");


	//Close the class
	changeIndentationLvl(-1);
	addLine("};");
	addLine("");
	addLine("#endif");
	return file;
}

void CodeGeneratorINI::appendPreprocessors(std::vector<std::string>& file)
{
	addLine("#ifndef PARSER_HPP");
	addLine("#define PARSER_HPP");
	addLine("");
	addLine("#include <map>");
	addLine("#include <vector>");
	addLine("#include <vector>");
	//boost library headers
	addLine("#include <boost/property_tree/ptree.hpp>");
	addLine("#include <boost/property_tree/ini_parser.hpp>");
//	file.push_back("#include \"parser_lib.hpp\""); //Removed for now
	addLine("");
}

std::string CodeGeneratorINI::getOutputClassName()
{
	//TODO Change it to receive from config (field does not exist, yet)
	return "MyClass";
}

//This function changes how many indentation levels should the next line have
void CodeGeneratorINI::changeIndentationLvl(int change)
{
	indentationLvl+= change;
	indentation = "";
	int newLevel = std::max(indentationLvl, 0);
	for (int i=0; i < newLevel; i++)
	      indentation+=(char)9; //(char)9 is the ascii for the tab character
}

void CodeGeneratorINI::addLine(const std::string& line)
{
	file.push_back(indentation+line);
}

void CodeGeneratorINI::appendDirectoryMap(std::vector<std::string>& file)
{
	//TODO create the directory map
}

std::vector<std::string> CodeGeneratorINI::getVariablesNames()
{
	//No nesting as ini is only one level
	std::vector<std::string> variables;
	for(const auto& var: rootConfig.getConfigs())
		variables.push_back(var.getName());
	return variables;
}

std::string CodeGeneratorINI::capitalizeWord(std::string word)
{
	for (char & i : word)
		if (isalpha(i))
			i = toupper(i);
	return word;
}
