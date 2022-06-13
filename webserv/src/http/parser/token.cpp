/**
 * @file token.cpp
 * @author Andrei Baidin
 * @brief The subroutine for parsing of the token
 * @version 1.0
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*"
 *         / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~"
 *         / DIGIT / ALPHA
 * ALPHA =  %x41-5A / %x61-7A    ; A-Z / a-z
 * DIGIT =  %x30-39              ; 0-9
 */
int is_tchar_(int c)
{
    return std::isalnum(c)
        || c == '!'  || c == '#' || c == '$' || c == '%' || c == '&'
        || c == '\'' || c == '*' || c == '+' || c == '-' || c == '.'
        || c == '^'  || c == '_' || c == '`' || c == '|' || c == '~';
}

/**
 * @details Grammar:
 * token = 1*tchar
 */
int parse_token_(const_uchar *str, size_t& pos, std::string& buf)
{
    size_t cur_pos = pos;

    while (is_tchar_(str[cur_pos])) {
        ++cur_pos;
    }

    if (cur_pos == pos) {
        return (false);
    }

    buf.assign(reinterpret_cast<const char*>(str + pos), cur_pos - pos);
    pos = cur_pos;
    return (true);
}
