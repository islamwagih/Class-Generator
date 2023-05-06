#ifndef XML_LITERALS_H
#define XML_LITERALS_H

#include "FormattableString.h"
namespace xml_literals
{

    // this in private section of XMLParser
    FormattableString GET_XML_DOC =
        R"(    pugi::xml_document getXMLDoc(){
        pugi::xml_document doc;
        if(!doc.load_file(filePath.c_str())){
            throw std::runtime_error("XML File not found");
        }
        return doc;
    }

)";

    FormattableString GET_FROM_FILE = R"(
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
        std::stringstream ss(node.child_value());
        T value;
        ss >> value;
        return value;
    })";

    FormattableString SET_IN_FILE = R"(
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
        node.text().set(value);
        return doc.save_file(filePath.c_str());
    })";

} // namespace xml_literals

#endif // XML_LITERALS_H