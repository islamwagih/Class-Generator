#ifndef XMLCLASSGENERATOR_H
#define XMLCLASSGENERATOR_H

#include "../../ClassGenerator/headers/ClassGenerator.h"
#include "xml_literals.h"

class XMLClassGenerator : public ClassGenerator
{
private:
    std::string generateGetXmlDoc();

protected:
    std::string generateGetFromFile() override;
    std::string generateSetInFile() override;

public:
    XMLClassGenerator(const RootConfig &root_config);
    std::string generateClass() override;
};

#endif // XMLCLASSGENERATOR_H