//
// Created by khaled on 5/2/23.
//

#include "CodeGeneratorINI.h"

CodeGeneratorINI::CodeGeneratorINI(const RootConfig& rootConfig) : rootConfig(rootConfig)
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

	//Add private section
	addLine("private:",file);
	changeIndentationLvl(1);
	appendDirectoryMap(file);
	addLine("std::string filePath;",file);
	changeIndentationLvl(-1);

	//Add public section
	addLine("private:",file);
	changeIndentationLvl(1);
	auto variables =  getVariablesNames();

	//Add public variables section
	for(const auto& variableName: variables)
	{
		addLine("std::string " + capitalizeWord(variableName) + ";",file);
	}

	//Add constructor
	addLine(parserClassName +" (std::string filePath)",file);
	addLine("{",file);
	changeIndentationLvl(1);
	addLine("this->filePath = filePath;",file);
	//init class variables
	for(const auto& variableName: variables)
	{
		addLine(capitalizeWord(variableName) + " = " + variableName+";",file);
	}
	changeIndentationLvl(-1);
	addLine("}",file);
	addLine("",file);

	//Write the function: getFromFile()
	addLine("template <typename T>",file);
	addLine("T getFromFile(std::vector<std::string> path)",file);
	addLine("{",file);
	changeIndentationLvl(1);
	//TODO add the implementation for getFromFile
	changeIndentationLvl(-1);
	addLine("}",file);


	//Write the function: setInFile()
	addLine("template <typename T>",file);
	addLine("bool setInFile(std::vector<std::string> path, T value)",file);
	addLine("{",file);
	changeIndentationLvl(1);
	//TODO add the implementation for setInFile
	changeIndentationLvl(-1);
	addLine("}",file);


	//Write the function: applyConstraints()
	addLine("template <typename T>",file);
	addLine("bool applyConstraints(std::vector<std::string> path, T value)",file);
	addLine("{",file);
	changeIndentationLvl(1);
	//TODO add the implementation for applyConstraints
	changeIndentationLvl(-1);
	addLine("}",file);


	//Close the class
	changeIndentationLvl(-1);
	addLine("};",file);
	addLine("",file);
	addLine("#endif",file);
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

//This function changes how many indentation levels should the next line have
void CodeGeneratorINI::changeIndentationLvl(int change)
{
	indentationLvl+= change;
	indentation = "";
	int newLevel = std::max(indentationLvl, 0);
	for (int i=0; i < newLevel; i++)
	      indentation+=(char)9; //(char)9 is the ascii for the tab character
}

void CodeGeneratorINI::addLine(const std::string& line, std::vector<std::string>& file)
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
