/**
 * @file header_fields.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of header fields of http messages
 * @version 1.0
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * header-field = field-name ":" OWS field-value OWS
 */
int parse_header_field_(const_uchar* str, size_t& pos, HeaderMap& header_map)
{
    std::string buf;

    return (parse_field_name_(str, pos, buf)
        && (str[pos] == ':' && ++pos)
        && parse_ows_(str, pos)
        && parse_field_value_(str, pos, header_map, buf)
        && parse_ows_(str, pos));
}

/**
 * @details Grammar:
 * headers = *( header-field CRLF )
 */
int parse_header_fields_generic_(const_uchar* str, size_t& pos, Request* data)
{
    HeaderMap& header_map = data->headers;

    while (str[pos] && !is_eol_(str, pos)) {
        if (!parse_header_field_(str, pos, header_map)
            || !parse_eol_(str, pos))
        {
            return (false);
        }
    }

    return (true);
}
