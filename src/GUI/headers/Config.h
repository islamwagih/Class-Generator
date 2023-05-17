#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <vector>

class Config
{
private:
    std::string name;
    std::string type;
    std::vector<std::string> constraints;
    std::vector<Config> children;

public:
    Config(const std::string &name, const std::string &type, const std::vector<std::string> &constraints, const std::vector<Config> &children);
    std::string getName() const;
    std::string getType() const;
    std::vector<std::string> getConstraints() const;
    std::vector<Config> getChildren() const;
    ~Config();
};
#endif // CONFIG_H
