/**
 * @file token_utils.cpp
 * @author Andrei Baidin
 * @brief Routines for the token stream
 * @version 1.0
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "token_utils.h"

#include <cctype>

const char* skip_spaces(const char* str)
{
    while (std::isspace(static_cast<unsigned char>(*str))) {
        ++str;
    }

    return str;
}

int isseparator(int c)
{
    return std::isspace(c) || c == ';' || c == '{' || c == '}';
}

int isnchar(int c)
{
    return std::isalnum(c) || c == '_';
}

int ispchar(int c)
{
    return isnchar(c) || c == '.' || c == '-' || c == '/' || c == ':';
}

bool isnumber(char unsigned const*& str)
{
    const unsigned char* ptr = str;

    while (std::isdigit(*ptr)) {
        ++ptr;
    }

    if (ptr == str) {
        return false;
    }

    str = ptr;
    return isseparator(*ptr);
}

bool isname(unsigned char const*& str)
{
    const unsigned char* ptr = str;

    while (isnchar(*ptr)) {
        ++ptr;
    }

    if (ptr == str) {
        return false;
    }

    str = ptr;
    return isseparator(*ptr);
}

bool isresponse(unsigned char const*& str)
{
    const unsigned char* ptr = str;

    if (*ptr++ != '=') {
        return false;
    }

    while (std::isdigit(*ptr)) {
        ++ptr;
    }

    if (ptr - 1 != str && isseparator(*ptr)) {
        str = ptr;
        return true;
    }

    return false;
}

bool isregular(unsigned char const*& str)
{
    const unsigned char* ptr = str;

    while (ispchar(*ptr)) {
        ++ptr;
    }

    if (ptr == str) {
        return false;
    }

    str = ptr;
    return isseparator(*ptr);
}

