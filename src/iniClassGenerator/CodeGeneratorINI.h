//
// Created by khaled on 5/2/23.
//

#ifndef INICLASSGENERATOR_CODEGENERATORINI_H
#define INICLASSGENERATOR_CODEGENERATORINI_H


#include <vector>
#include <string>
#include "../GUI/headers/rootconfig.h"

class CodeGeneratorINI
{
private:
	RootConfig rootConfig;
	int indentationLvl =0;
	std::string indentation;

	std::vector<std::string> classCode;
	std::vector<std::string> directives;
	std::vector<std::string> GetVar;
	std::vector<std::string> SetVar;
	std::vector<std::string> initCode;

	void appendPreprocessors(std::vector<std::string>&);
	std::string getOutputClassName();
	void appendDirectoryMap(std::vector<std::string>&);
	void addLine(const std::string&,std::vector<std::string>&);
	void changeIndentationLvl(int);
	std::vector<std::string> getVariablesNames();
	std::string capitalizeWord(std::string);
	std::string getIniSectionName(std::string file_path);
	std::vector<std::string> generatePreprocessorDirectives();
	std::vector<std::string> generateGetVarFunction();
	std::vector<std::string> generateSetVarFunction();
	std::vector<std::string> generateInitFunction();
	std::string generateTabs(int numTabs);
	std::string iniSetValue();
	std::string iniGetValue();


public:
	CodeGeneratorINI(const RootConfig& c);
    
	std::vector<std::string> generateParserH();
	std::vector<std::string> generateMyClassH();

};


#endif //INICLASSGENERATOR_CODEGENERATORINI_H
