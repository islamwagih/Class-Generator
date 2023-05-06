#ifndef FORMATTABLESTRING_H
#define FORMATTABLESTRING_H

#include <string>

class FormattableString : public std::string
{
public:
    FormattableString(const std::string &other);
    FormattableString(const char *other);
    std::string format(std::initializer_list<std::pair<std::string, std::string>> replacements);
    const std::string &operator=(const std::string &other);
    const std::string &operator=(const char *other);
};

#endif // FORMATTABLESTRING_H