#ifndef JSON_LITERALS_H
#define JSON_LITERALS_H

#include "../../ClassGenerator/headers/FormattableString.h"

namespace json_literals
{
    // this in private section of JSONParser
    extern FormattableString GET_JSON_OBJ;
    extern FormattableString GET_JSON_VALUE;
    extern FormattableString GET_FROM_FILE;
    extern FormattableString SET_IN_FILE;
} // namespace json_literals

#endif // JSON_LITERALS_H