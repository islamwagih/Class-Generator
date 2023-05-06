//
// Created by khaled on 5/6/23.
//

#ifndef INICLASSGENERATOR_FILEWRITER_H
#define INICLASSGENERATOR_FILEWRITER_H

#include <string>
#include <vector>
#include <iostream>
/**
 * This class is only made for testing before actual
 * integration with the other components
 */
class FileWriter
{
public:
	static void writeFile(const std::string& path, std::vector<std::string>& lines)
	{
		freopen(path.c_str(), "w", stdout);
		for(const auto& line: lines)
			std::cout<<line<<"\n";
	}
};

#endif //INICLASSGENERATOR_FILEWRITER_H
