#include "../headers/FormattableString.h"

FormattableString::FormattableString(const std::string &other) : std::string(other) {}

FormattableString::FormattableString(const char *other) : std::string(other) {}

std::string FormattableString::format(std::initializer_list<std::pair<std::string, std::string>> replacements)
{
    std::string formattedString = *this;
    for (auto replacement : replacements)
    {
        // replace all instances of the first string with the second string
        long long unsigned int index = 0; // to avoid compiler warning
        while (true)
        {
            index = formattedString.find(replacement.first, index);
            if (index == std::string::npos)
            {
                break;
            }
            formattedString.replace(index, replacement.first.length(), replacement.second);
            index += replacement.second.length();
        }
    }
    return formattedString;
}

const std::string &FormattableString::operator=(const std::string &other)
{
    std::string::operator=(other);
    return *this;
}

const std::string &FormattableString::operator=(const char *other)
{
    std::string::operator=(other);
    return *this;
}
