#ifndef JSON_LITERALS_H
#define JSON_LITERALS_H

#include "../../ClassGenerator/headers/FormattableString.h"
namespace json_literals
{

    // this in private section of XMLParser
    FormattableString GET_JSON_OBJ =
        R"(    nlohmann::json json_object;
)";


} // namespace json_literals

#endif // JSON_LITERALS_H