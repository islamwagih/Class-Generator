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

std::string CodeGeneratorINI::getIniSectionName(std::string file_path)
{
	std::ifstream file(file_path);
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '[' && line[line.length() - 1] == ']') {
			return line.substr(1, line.length() - 2);
		}
	}
}


std::vector<std::string> CodeGeneratorINI::generatePreprocessorDirectives()
{
	std::vector<std::string> Pre;

	Pre.push_back("#ifndef " + capitalizeWord(getOutputClassName()) + "_HPP");
	Pre.push_back("#define " + capitalizeWord(getOutputClassName()) + "_HPP");
	Pre.push_back("#include <vector>");
	Pre.push_back("#include <string>");
	Pre.push_back("#include <stdexcept>");
	Pre.push_back("#include <parser.cpp>");
	Pre.push_back(" ");

	return Pre;
}


std::vector<std::string> CodeGeneratorINI::generateGetVarFunction()
{
	std::vector<std::string> GetVar;
	GetVar.push_back(generateTabs(1) + "template <typename T>");
	GetVar.push_back(generateTabs(1) + "T getVar(std::vector<std::string> path)");
	GetVar.push_back(generateTabs(1) + "{");
	GetVar.push_back(generateTabs(2) + "return parser->getFromFile<T>(path);");
	GetVar.push_back(generateTabs(1) + "}");

	return GetVar;
}


std::vector<std::string> CodeGeneratorINI::generateSetVarFunction()
{
	std::vector<std::string> SetVar;
	SetVar.push_back(generateTabs(1) + "template <typename T>");
	SetVar.push_back(generateTabs(1) + "bool setVar(std::vector<std::string> path, T value)");
	SetVar.push_back(generateTabs(1) + "{");
	SetVar.push_back(generateTabs(2) + "if (parser->applyConstraints<T>(path, value)) return parser->setInFile<T>(path, value);");
	SetVar.push_back(generateTabs(3) + "return false;");
	SetVar.push_back(generateTabs(1) + "}");
	return SetVar;
}


std::vector<std::string> CodeGeneratorINI::generateInitFunction()
{
	std::vector<std::string> init;
	init.push_back(generateTabs(1) + "static void init(std::string filePath)");
	init.push_back(generateTabs(1) + "{");
	init.push_back(generateTabs(2) + "if (instance == nullptr)");
	init.push_back(generateTabs(3) + "instance = new " + getOutputClassName() + "(filePath); ");
	init.push_back(generateTabs(1) + "}");
	return init;
}


std::string CodeGeneratorINI::generateTabs(int numTabs)
{
	std::string tabs = "";
	for (int i = 0; i < numTabs; i++) {
		tabs += "\t";
	}
	return tabs;
}

std::string CodeGeneratorINI::iniSetValue()
{
	std::string iniSetInFile = R"(bool setInFile(std::vector<std::string>& path, T value)
{
    mINI::INIFile file(filePath);
    mINI::INIStructure ini;
    file.read(ini);

    std::string section_name = path[0];
    std::string key_name = path[1];
    ini[section_name][key_name] = value;

    if (!file.write(ini)) {
        return false;
    }
    return true;
})";
	return iniSetInFile;
}

std::string CodeGeneratorINI::iniGetValue()
{
	std::string getVarIni = R"(template<typename T>
T getFromFile(const std::vector<std::string>& path) {
    mINI::INIFile file(filePath);
    mINI::INIStructure ini;
    file.read(ini);

    std::string section_name = path[0];
    std::string key_name = path[1];

    return ini[section_name][key_name];
})";
	return getVarIni;
}


std::vector<std::string> CodeGeneratorINI::generateMyClassH()
{
	directives = generatePreprocessorDirectives();
	classCode.insert(classCode.end(), directives.begin(), directives.end());

	// Class declaration and private members
	classCode.push_back("class " + getOutputClassName());
	classCode.push_back("{");
	classCode.push_back("private:");
	classCode.push_back(generateTabs(1) + "static " + getOutputClassName() + "* instance; ");
	classCode.push_back(generateTabs(1) + "Parser* parser;");
	classCode.push_back(generateTabs(1) + getOutputClassName() + "(std::string filePath)");
	classCode.push_back(generateTabs(1) + "{");
	classCode.push_back(generateTabs(2) + "parser = new Parser(filePath);");
	classCode.push_back(generateTabs(1) + "}");

	// Public members
	classCode.push_back("public:");
	initCode = generateInitFunction();

	classCode.insert(classCode.end(), initCode.begin(), initCode.end());


	classCode.push_back(generateTabs(1) + "static " + getOutputClassName() + "* getInstance()");
	classCode.push_back(generateTabs(1) + "{");
	classCode.push_back(generateTabs(2) + "if (instance == nullptr)");
	classCode.push_back(generateTabs(3) + "throw std::runtime_error(\"MyClass not initialized\");");
	classCode.push_back(generateTabs(2) + "return instance;");
	classCode.push_back(generateTabs(1) + "}");

	GetVar = generateGetVarFunction();
	classCode.insert(classCode.end(), GetVar.begin(), GetVar.end());

	SetVar = generateSetVarFunction();
	classCode.insert(classCode.end(), SetVar.begin(), SetVar.end());

	classCode.push_back("};");
	classCode.push_back("#endif");

	return classCode;
}