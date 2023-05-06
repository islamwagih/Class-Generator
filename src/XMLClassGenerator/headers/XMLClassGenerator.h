#ifndef XMLCLASSGENERATOR_H
#define XMLCLASSGENERATOR_H

#include "ClassGenerator.h"
#include "xml_literals.h"

class XMLClassGenerator :: public ClassGenerator
{
private:
    std::string generateGetXmlDoc();


public:
    XMLClassGenerator(const std::vector<Config> &configs);
};

#endif // XMLCLASSGENERATOR_H