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

	//classcode : Vector of strings for the complete class
	std::vector<std::string> classCode;
	//classcode : Vector of strings for preproccessors
	std::vector<std::string> directives;
	//classcode : Vector of strings for the getvar function in the class
	std::vector<std::string> GetVar;
	//classcode : Vector of strings for the setvar function in the class
	std::vector<std::string> SetVar;
	//classcode : Vector of strings for the init function in the class
	std::vector<std::string> initCode;

	void appendPreprocessors(std::vector<std::string>&);
	std::string getOutputClassName();
	void appendDirectoryMap(std::vector<std::string>&);
	void addLine(const std::string&,std::vector<std::string>&);
	void changeIndentationLvl(int);
	std::vector<std::string> getVariablesNames();
	std::vector<std::string> getConstraintsINI();
	std::vector<std::string> generateMapOfConstraints();
	std::string capitalizeWord(std::string);
	std::string getIniSectionName(std::string file_path);
	std::vector<std::string> generatePreprocessorDirectives();
	std::vector<std::string> generateGetVarFunction();
	std::vector<std::string> generateSetVarFunction();
	std::vector<std::string> generateInitFunction();
	std::string generateTabs(int numTabs);

public:
	CodeGeneratorINI(const RootConfig& c);
    
	std::vector<std::string> generateParserH();
	std::vector<std::string> generateMyClassH();

};


#endif //INICLASSGENERATOR_CODEGENERATORINI_H
