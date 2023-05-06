#ifndef LITERALS_H
#define LITERALS_H

#include <string>

std::string INCLUDES = R"(
#ifndef {NAME}_{EXTENSION}
#define {NAME}_{EXTENSION}

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "{PARSER_LIB}"
#include "regex" // for applyConstraints

)";

std::string CLASS_NAME = R"(
    std::string {CLASS_NAME};
)";

std::string VISIBILITY = R"(
{VISIBILITY}:
)";

std::string CONSTRAINTS_MAP = R"(
    std::map<std::string, std::vector<std::string>> constraints = {
        {CONSTRAINTS}
    }; // Auto generated from UI
)";

std::string CONSTRAINTS = R"(
        {"{PATH}", {"{MIN}", "{MAX}"}},
)";

std::string FILE_PATH = R"(
    std::string filePath;
)";

std::string KEYS = R"(
    {KEYS}
)";

std::string KEY = R"(
    std::string {KEY};
)";

// this in private section of XMLParser
std::string privateSection = R"(
    std::string file_path;
    pugi::xml_document getXMLDoc(){

        pugi::xml_document doc;
        if(!doc.load_file(file_path.c_str())){
            throw std::runtime_error("XML File not found");
        }
        return doc;
    }
)";

std::string CONSTRUCTOR = R"(
    {CLASS_NAME}(std::string filePath):file_path(std::move(filePath))
    {
        this->filePath = filePath;
        {KEYS}
    }
)";

std::string GET_FROM_FILE = R"(
    template <typename T>
    T getFromFile(std::vector<std::string>& path)
    {
        pugi::xml_document doc = this->getXMLDoc();
        pugi::xml_node node = doc.child("root");
        for (const auto& tag : path)
        {
            node = node.child(tag.c_str());
            if(!node){
                throw std::runtime_error("XML Tag not found");
            }
        }

        std::stringstream ss(node.child_value());
        T value;
        ss >> value;
        return value;
    }
)";
// private helper function used by isLeaf , applyConstraints
std::string _CONTACT_PATH = R"(

    std::string full_path = "";
    for (const auto &entry : path)
    {
        full_path += entry + ".";
    }
    // remove last dot
    full_path = full_path.substr(0, full_path.size() - 1);
    return full_path;
)";

std::string IS_LEAF = R"(
    bool isLeaf(std::vector<std::string> path)
    {
        std::string full_path = _contactPath(path);
        return constraints.count(full_path) == 1;
    }
)";

std::string SET_IN_FILE = R"(
    template <typename T>
    bool setInFile(std::vector<std::string>& path, T value)
    {
        pugi::xml_document doc = this->getXMLDoc();
        pugi::xml_node node = doc.child("root");

        for (const auto& tag : path)
        {
            node = node.child(tag.c_str());
            if(!node){
                throw std::runtime_error("XML Tag not found");
            }
        }
        node.text().set(value);
        return doc.save_file(file_path.c_str());
    }
)";

std::string APPLY_CONSTRAINTS = R"(
    template <typename T>
    bool applyConstraints(std::vector<std::string> path, T value)
    {
        std::string full_path = _contactPath(path);
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
    return true;
    }
)";

std::string END = R"(
};

#endif // {NAME}_{EXTENSION}
)";

#endif // LITERALS_H