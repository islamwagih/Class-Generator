//
// Created by khaled on 5/2/23.
//

#ifndef INICLASSGENERATOR_CODEGENERATORINI_H
#define INICLASSGENERATOR_CODEGENERATORINI_H


#include <vector>
#include <string>
#include "../GUI/headers/Config.h"

class CodeGeneratorINI
{
private:
	Config config;
	int indentationLvl =0;
	std::string indentation;
	void appendPreprocessors(std::vector<std::string>&);
	std::string getOutputClassName();
	void appendSingletonSection(std::vector<std::string>&);
	void changeIndentationLvl(int);
	void addLine(const std::string&,std::vector<std::string>&);
public:
	CodeGeneratorINI(const Config& c);
	std::vector<std::string> generateParserH();
	std::vector<std::string> generateMyClassH();
};


#endif //INICLASSGENERATOR_CODEGENERATORINI_H
