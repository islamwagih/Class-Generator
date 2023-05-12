#ifndef PARSER_CPP
#define PARSER_CPP

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "ini.h"
#include "regex" // for applyConstraints

class Parser
{
private:
    std::map<std::string, std::vector<std::string>> constraints = {
        {"param1", {"1", "100"}},
        {"param2", {"10", "20"}},
    }; // Auto generated from UI

    std::string filePath;

    std::string concatPath(std::vector<std::string> path){
        std::string full_path = "";
        for (const auto &entry : path)
        {
            full_path += entry + ".";
        }
        // remove last dot
        full_path = full_path.substr(0, full_path.size() - 1);
        return full_path;
    }

public:
    std::string PARAM2;
    std::string PARAM1;

    Parser(std::string filePath) : filePath(std::move(filePath))
    {
        PARAM2 = "param2";
        PARAM1 = "param1";
    }
template<typename T>
T getFromFile(const std::vector<std::string>& path) {
    mINI::INIFile file(filePath);
    mINI::INIStructure ini;
    file.read(ini);

    std::string section_name = path[0];
    std::string key_name = path[1];

    return ini[section_name][key_name];
}
    bool isLeaf(std::vector<std::string> path)
    {
        std::string full_path = concatPath(path);
        return constraints.count(full_path) == 1;
    }
    template<typename T>
    bool setInFile(std::vector<std::string>& path, T value)
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
    }
    template <typename T>
    bool applyConstraints(std::vector<std::string> path, T value)
    {
        std::string full_path = concatPath(path);
        if (std::is_same < T, int> ::value) {
            std::stringstream ss;
            ss << value;
            int temp_value;
            ss >> temp_value;
            std::string first_constraint = constraints[full_path][0];
            std::string second_constraint = constraints[full_path][1];
            bool valid = true;
            if (!first_constraint.empty()) {
                valid = temp_value >= std::stoi(first_constraint);
            }
            if (!second_constraint.empty() && valid) {
                valid = temp_value <= std::stoi(second_constraint);
            }
            return valid;
        }
        else if(std::is_same < T, bool> ::value){
            return true;
        }
        else if (std::is_same < T, std::string> ::value){
            std::stringstream ss;
            ss << value;
            std::string temp_value = ss.str();
            std::string regex = constraints[full_path][0];
            if(regex.empty()){
                return true;
            }
            return std::regex_match(temp_value, std::regex(regex));
        }
        else{

            std::stringstream ss;
            ss << value;
            double temp_value;
            ss >> temp_value;
            std::string first_constraint = constraints[full_path][0];
            std::string second_constraint = constraints[full_path][1];
            bool valid = true;
            if (!first_constraint.empty()) {
                valid = temp_value >= std::stod(first_constraint);
            }
            if (!second_constraint.empty() && valid) {
                valid = temp_value <= std::stod(second_constraint);
            }
            return valid;
        }

    }
};

#endif // Parser_CPP
