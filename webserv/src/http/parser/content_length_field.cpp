/**
 * @file content_length_field.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of the content length field
 * @version 1.0
 * @date 2022-05-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * Content-Length = 1*DIGIT  ; there might be repetitions, they must be equal
 */
int parse_content_length_(Request* data)
{
    HeaderMap::iterator iter = data->headers.find("content-length");
    const char* nptr = NULL;
    char* endptr = NULL;
    long value = 0;
    long tmp = 0;

    if (iter == data->headers.end()) {
        return (true);
    }

    nptr = iter->second.c_str();
    value = std::strtol(nptr, &endptr, 10);
    while (*endptr == ',') {
        nptr = endptr + 1;
        tmp = std::strtol(nptr, &endptr, 10);
        if (tmp != value) {
            return (false);
        }
    }

    data->content_length = value;
    data->headers.erase(iter);
    return (!*endptr);
}
