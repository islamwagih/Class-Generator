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
	void addPreprocessors(std::vector<std::string>&);
public:
	CodeGeneratorINI(const Config& c);
	std::vector<std::string> generateParserH();
	std::vector<std::string> generateMyClassH();
};


#endif //INICLASSGENERATOR_CODEGENERATORINI_H
