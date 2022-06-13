/**
 * @file uri.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of uri
 * @version 1.0
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * segment = *pchar
 */
int parse_segment_(const_uchar *str, size_t& pos)
{
    while (parse_pchar_(str, pos))
    {}
    return (true);
}

/**
 * @details Grammar:
 * absolute-path = 1*( "/" segment )
 */
int parse_absolute_path_(const_uchar *str, size_t& pos)
{
    size_t cur_pos = pos;

    while (str[cur_pos] == '/') {
        ++cur_pos;
        parse_segment_(str, cur_pos);
    }

    if (cur_pos == pos) {
        return (false);
    }

    pos = cur_pos;
    return (true);
}

/**
 * @details Grammar:
 * query = *( pchar / "/" / "?" )
 */
int parse_query_(const_uchar *str, size_t& pos)
{
    while (parse_pchar_(str, pos)
        || ((str[pos] == '/' || str[pos] == '?') && ++pos))
    {}
    return (true);
}
