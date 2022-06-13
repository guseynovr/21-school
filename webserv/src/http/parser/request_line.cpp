/**
 * @file request_line.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of the request line
 * @version 1.0
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * HTTP-version = HTTP-name "/" DIGIT "." DIGIT     ; made [ "." DIGIT ]
 * HTTP-name    = %x48.54.54.50                     ; "HTTP", case-sensitive
 */
int parse_http_version_(const_uchar* str, size_t& pos, std::string& buf)
{
    size_t cur_pos = pos;
    size_t offset = 6;

    if (str[cur_pos] != 'H'
        || str[cur_pos + 1] != 'T'
        || str[cur_pos + 2] != 'T'
        || str[cur_pos + 3] != 'P'
        || str[cur_pos + 4] != '/'
        || !std::isdigit(str[cur_pos + 5]))
    {
        return (false);
    }

    if (str[cur_pos + 6] == '.'
        && std::isdigit(str[cur_pos + 7]))
    {
        offset = 8;
    }

    buf.assign(reinterpret_cast<const char*>(str + cur_pos), offset);
    pos += offset;
    return (true);
}

/**
 * @details Grammar:
 * origin-form = absolute-path [ "?" query ]
 */
int parse_origin_form_(const_uchar *str, size_t& pos)
{
    return (parse_absolute_path_(str, pos)
        && (str[pos] != '?' || (++pos && parse_query_(str, pos))));
}

/**
 * @details Grammar:
 * request-target = origin-form         ; to origin server, not CONNECT or OPTIONS
 *                  / absolute-form     ; to proxy,         not CONNECT or OPTIONS       not implemented
 *                  / authority-form    ; only CONNECT                                   not implemented
 *                  / asterisk-form     ; only OPTIONS                                   not implemented
 */
int parse_target_(const_uchar *str, size_t& pos, std::string& buf)
{
    size_t orig_pos = pos;

    if (!parse_origin_form_(str, pos)) {
        return (false);
    }

    buf.append(reinterpret_cast<const char*>(str + orig_pos), pos - orig_pos);
    return (true);
}

/**
 * @details Grammar:
 * request-line = method SP request-target SP HTTP-version CRLF
 */
int parse_request_line_(const_uchar *str, size_t& pos, Request* data)
{
    return (parse_token_(str, pos, data->method_name)
        && str[pos] == ' ' && ++pos
        && parse_target_(str, pos, data->target)
        && str[pos] == ' ' && ++pos
        && parse_http_version_(str, pos, data->http_version)
        && parse_eol_(str, pos));
}
