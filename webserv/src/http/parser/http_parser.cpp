/**
 * @file http_parser.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of http messages
 * @version 1.0
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

http_parse_error::http_parse_error()
    : std::runtime_error("")
{}

/**
 * @details Grammar:
 * HTTP-message = start-line
 *                *( header-field CRLF )
 *                CRLF
 *                [ message-body ]      ; not implemented
 */
Request* parse_request(const char* str)
{
    Request* data = NULL;
    const_uchar* ustr = reinterpret_cast<const_uchar*>(str);

    try {
        size_t pos = 0;
        data = new Request();

        if (!parse_request_line_(ustr, pos, data)
            || !parse_header_fields_generic_(ustr, pos, data)
            || !parse_eol_(ustr, pos)
            || !parse_reg_header_fields_(data))
        {
            throw Bad_Request;
        }

        return data;
    }
    catch (...) {
        delete data;
        throw;
    }
}

size_t parse_request(const char* str, Request& data)
{
    const_uchar* ustr = reinterpret_cast<const_uchar*>(str);
    size_t pos = 0;

    if (!parse_request_line_(ustr, pos, &data)
        || !parse_header_fields_generic_(ustr, pos, &data)
        || !parse_eol_(ustr, pos)
        || !parse_reg_header_fields_(&data))
    {
        data.clear();
        throw Bad_Request;
    }

    return pos;
}
