#ifndef LITERALS_H
#define LITERALS_H

#include <string>

std::string INCLUDES = R"(
#ifndef {NAME}_{EXTENSION}
#define {NAME}_{EXTENSION}

#include <map>
#include <vector>
#include <string>
#include "{PARSER_LIB}"
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

std::string CONSTRUCTOR = R"(
    {CLASS_NAME}(std::string filePath)
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
        }

        std::stringstream ss(node.child_value());
        T value;
        ss >> value;
        return value;
    }
)";

std::string IS_LEAF = R"(
    bool isLeaf(std::vector<std::string> path)
    {
        {IMPLEMENTATION}
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
        }
        node.text().set(value);
        return doc.save_file(file_path.c_str());
    }
)";

std::string APPLY_CONSTRAINTS = R"(
    template <typename T>
    bool applyConstraints(std::vector<std::string> path, T value)
    {
        {IMPLEMENTATION}
    }
)";

std::string END = R"(
};

#endif // {NAME}_{EXTENSION}
)";

#endif // LITERALS_H