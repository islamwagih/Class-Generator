#ifndef INICLASSGENERATOR_H
#define INICLASSGENERATOR_H

#include "ClassGenerator.h"
#include "INI_literals.h"

class INIClassGenerator :: public ClassGenerator
{
public:
    INIClassGenerator(const std::vector<Config>& configs);
};

#endif // INICLASSGENERATOR_H