#ifndef PARSER_CPP
#define PARSER_CPP

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "pugixml.hpp"
#include "regex" // for applyConstraints

class Parser
{
private:
    std::map<std::string, std::vector<std::string>> constraints = {
        {"circle.radius", {"1", "50"}},
        {"name", {"[A-Z a-z]+", ""}},
        {"salary", {"8000", "9777.5"}},
        {"militaryState", {"", ""}},
    }; // Auto generated from UI

    std::string filePath;

    pugi::xml_document getXMLDoc(){
        pugi::xml_document doc;
        if(!doc.load_file(filePath.c_str())){
            throw std::runtime_error("XML File not found");
        }
        return doc;
    }

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
    std::string MILITARYSTATE;
    std::string RADIUS;
    std::string CIRCLE;
    std::string SALARY;
    std::string NAME;

    Parser(std::string filePath) : filePath(std::move(filePath))
    {
        MILITARYSTATE = "militaryState";
        RADIUS = "radius";
        CIRCLE = "circle";
        SALARY = "salary";
        NAME = "name";
    }

    template <typename T>
    T getFromFile(std::vector<std::string> &path)
    {
        pugi::xml_document doc = this->getXMLDoc();
        pugi::xml_node node = doc.child("root");
        for (const auto &tag : path)
        {
            node = node.child(tag.c_str());
            if(!node){
                throw std::runtime_error("XML Tag not found");
            }
        }

        auto node_data = static_cast<std::string>(node.child_value());
        if (node_data == "true"){
            node_data = "1";
        }
        else if (node_data == "false"){
            node_data = "0";
        }
        std::stringstream ss(node_data);
        T value;
        ss >> value;
        return value;
    }
    bool isLeaf(std::vector<std::string> path)
    {
        std::string full_path = concatPath(path);
        return constraints.count(full_path) == 1;
    }
    template <typename T>
    bool setInFile(std::vector<std::string> &path, T value)
    {
        pugi::xml_document doc = this->getXMLDoc();
        pugi::xml_node node = doc.child("root");

        for (const auto &tag : path)
        {
            node = node.child(tag.c_str());
            if(!node){
                throw std::runtime_error("XML Tag not found");
            }
        }

        std::stringstream ss;
        ss << value;
        node.text().set(ss.str().c_str());

        return doc.save_file(filePath.c_str());
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
