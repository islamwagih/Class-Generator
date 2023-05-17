#include "../headers/literals.h"

namespace literals
{
    FormattableString INCLUDES =
        R"(#ifndef {NAME}_{EXTENSION}
#define {NAME}_{EXTENSION}

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "{PARSER_LIB}"
#include "regex" // for applyConstraints

)";

    FormattableString CLASS_NAME =
        R"(class {CLASS_NAME}
{
)";

    FormattableString VISIBILITY =
        R"({VISIBILITY}:
)";

    FormattableString CONSTRAINTS_MAP =
        R"(    std::map<std::string, std::vector<std::string>> constraints = {
{CONSTRAINTS}    }; // Auto generated from UI

)";

    FormattableString ONE_CONSTRAINT =
        R"(        {"{PATH}", {"{MIN}", "{MAX}"}},
)";

    FormattableString FILE_PATH =
        R"(    std::string filePath;

)";

    // private helper function used by isLeaf , applyConstraints
    FormattableString CONCAT_PATH =
        R"(    std::string concatPath(std::vector<std::string> path){
        std::string full_path = "";
        for (const auto &entry : path)
        {
            full_path += entry + ".";
        }
        // remove last dot
        full_path = full_path.substr(0, full_path.size() - 1);
        return full_path;
    }

)";

    FormattableString STRING_LITERALS =
        R"({STRING_LITERALS}
)";

    FormattableString ONE_STRING_LITERAL =
        R"(    std::string {NAME};
)";

    FormattableString CONSTRUCTOR =
        R"(    {CLASS_NAME}(std::string filePath) : filePath(std::move(filePath))
    {
{INITIALIZE_LITERALS}    }
)";

    FormattableString INITIALIZE_LITERALS =
        R"({INITIALIZE_LITERALS})";

    FormattableString ONE_INITIALIZE_LITERAL =
        R"(        {NAME_UPPER} = "{NAME}";
)";

    FormattableString IS_LEAF = R"(
    bool isLeaf(std::vector<std::string> path)
    {
        std::string full_path = concatPath(path);
        return constraints.count(full_path) == 1;
    })";

    FormattableString APPLY_CONSTRAINTS = R"(
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

    })";

    FormattableString END = R"(
};

#endif // {CLASS_NAME}_{EXTENSION}
)";
} // namespace literals