#ifndef INI_LITERALS_H
#define INI_LITERALS_H

#include "../../ClassGenerator/headers/FormattableString.h"
namespace ini_literals
{
    FormattableString GET_FROM_FILE = R"(template<typename T>
T getFromFile(const std::vector<std::string>& path) {
    mINI::INIFile file(filePath);
    mINI::INIStructure ini;
    file.read(ini);

    std::string section_name = path[0];
    std::string key_name = path[1];

    return ini[section_name][key_name];
})";

    FormattableString SET_IN_FILE = R"(bool setInFile(std::vector<std::string>& path, T value)
{
    mINI::INIFile file(filePath);
    mINI::INIStructure ini;
    file.read(ini);

    std::string section_name = path[0];
    std::string key_name = path[1];
    ini[section_name][key_name] = value;

    if (!file.write(ini)) {
        return false;
    }
    return true;
})";

} // namespace ini_literals

#endif // INI_LITERALS_H