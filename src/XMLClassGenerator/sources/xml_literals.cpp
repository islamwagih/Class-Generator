#include "../headers/xml_literals.h"

namespace xml_literals
{

    // this in private section of XMLParser
    FormattableString GET_XML_DOC =
        R"(    pugi::xml_document getXMLDoc(){
        pugi::xml_document doc;
        if(!doc.load_file(filePath.c_str())){
            throw std::runtime_error("XML File not found, make sure the file path is correct");
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
                throw std::runtime_error("XML Tag not found, make sure the path is correct");
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
                throw std::runtime_error("XML Tag not found, make sure the path is correct");
            }
        }

        std::stringstream ss;
        ss << value;
        node.text().set(ss.str().c_str());

        return doc.save_file(filePath.c_str());
    })";

} // namespace xml_literals