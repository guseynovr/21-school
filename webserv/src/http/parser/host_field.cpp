/**
 * @file host_field.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of the host header field
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * port = *DIGIT
 */
int parse_port_(const_uchar* str, size_t& pos)
{
    size_t cur_pos = pos;

    while (std::isdigit(str[cur_pos])) {
        ++cur_pos;
    }

    pos = cur_pos;
    return true;
}

/**
 * @details Grammar:
 * reg-name = *( unreserved / pct-encoded / sub-delims )
 */
int parse_reg_name_(const_uchar* str, size_t& pos)
{
    size_t cur_pos = pos;

    while ((is_unreserved_(str[cur_pos]) && ++cur_pos)
        || (is_pct_encoded_(str + cur_pos) && (cur_pos += 3))
        || (is_sub_delims_(str[cur_pos]) && ++cur_pos))
    {}

    pos = cur_pos;
    return true;
}

/**
 * @details Grammar:
 * dec-octet = DIGIT                ; 0-9
 *           / %x31-39 DIGIT        ; 10-99
 *           / "1" 2DIGIT           ; 100-199
 *           / "2" %x30-34 DIGIT    ; 200-249
 *           / "25" %x30-35         ; 250-255
 */
int parse_dec_octet_(const_uchar* str, size_t& pos)
{
    const size_t cur_pos = pos;

    if ((str[cur_pos] == '2'
            && ((str[cur_pos + 1] == '5'
                && str[cur_pos + 2] >= '0' && str[cur_pos + 2] <= '5')
            || (str[cur_pos + 1] >= '0' && str[cur_pos + 1] <= '4'
                && str[cur_pos + 2] >= '0' && str[cur_pos + 2] <= '9')))
        || (str[cur_pos] == '1'
            && str[cur_pos + 1] >= '0' && str[cur_pos + 1] <= '9'
            && str[cur_pos + 2] >= '0' && str[cur_pos + 2] <= '9'))
    {
        pos = cur_pos + 3;
        return true;
    }

    if (str[cur_pos] >= '0' && str[cur_pos] <= '9'
        && str[cur_pos + 1] >= '0' && str[cur_pos + 1] <= '9')
    {
        pos = cur_pos + 2;
        return true;
    }

    if (str[cur_pos] >= '0' && str[cur_pos] <= '9')
    {
        pos = cur_pos + 1;
        return true;
    }

    return false;
}

/**
 * @details Grammar:
 * IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet
 */
int parse_ipv4_(const_uchar* str, size_t& pos)
{
    size_t cur_pos = pos;

    if (parse_dec_octet_(str, cur_pos)
        && str[cur_pos] == '.' && ++cur_pos
        && parse_dec_octet_(str, cur_pos)
        && str[cur_pos] == '.' && ++cur_pos
        && parse_dec_octet_(str, cur_pos)
        && str[cur_pos] == '.' && ++cur_pos
        && parse_dec_octet_(str, cur_pos))
    {
        pos = cur_pos;
        return true;
    }
    return false;
}

/**
 * @details Grammar:
 * uri-host = IP-literal / IPv4address / reg-name   ; case-insensitive
 *                                                  ; IP-literal is not implemented
 */
int parse_uri_host_(const_uchar* str, size_t& pos)
{
    return (parse_ipv4_(str, pos)
            || parse_reg_name_(str, pos));
}

/**
 * @details Grammar:
 * Host = uri-host [ ":" port ]
 */
int parse_host_(Request* data)
{
    HeaderMap::iterator iter = data->headers.find("host");

    if (iter == data->headers.end()) {
        return (false);
    }

    const_uchar* str = reinterpret_cast<const_uchar*>(iter->second.c_str());
    size_t pos = 0;

    if (parse_uri_host_(str, pos)
        && (str[pos] != ':'
        || (++pos && parse_port_(str, pos)))
        && str[pos] == '\0')
    {
        data->host = iter->second;
        data->headers.erase(iter);
        return true;
    }

    return false;
}
