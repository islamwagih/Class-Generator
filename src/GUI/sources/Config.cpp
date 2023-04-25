#include "headers/Config.h"

Config::Config(const std::string &name, const std::string &type, const std::vector<std::string> &constraints, const std::vector<Config> &children)
    : name(name), type(type), constraints(constraints), children(children)
{
}

std::string Config::getName() const
{
    return this->name;
}

std::string Config::getType() const
{
    return this->type;
}

std::vector<std::string> Config::getConstraints() const
{
    return this->constraints;
}

std::vector<Config> Config::getChildren() const
{
    return this->children;
}

Config::~Config()
{
}

QDebug operator<<(QDebug debug, const Config &config)
{
    debug << "Config(" << config.getName().c_str() << ", " << config.getType().c_str() << ", Constrains(";
    for(auto str : config.getConstraints()){
        debug << str.c_str() << ',';
    }

    debug<< "), Children(" << config.getChildren() << ") )";
    return debug;
}
