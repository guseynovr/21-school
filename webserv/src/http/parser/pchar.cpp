/**
 * @file pchar.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of pchar characters
 * @version 1.0
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

#ifdef DEBUG
# undef return
#endif /* DEBUG */

/**
 * @details Grammar:
 * sub-delims = "!" / "$" / "&" / "'" / "(" / ")"
 *            / "*" / "+" / "," / ";" / "="
 */
int is_sub_delims_(int c)
{
    return c == '!' || c == '$' || c == '&' || c == '\'' || c == '('
        || c == ')' || c == '*' || c == '+' || c == ','  || c == ';'
        || c == '=';
}

/**
 * @details Grammar:
 * pct-encoded = "%" HEXDIG HEXDIG
 */
int is_pct_encoded_(const_uchar *str)
{
    return str[0] == '%'
        && is_hexdig_(str[1])
        && is_hexdig_(str[2]);
}

/**
 * @details Grammar:
 * unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
 */
int is_unreserved_(int c)
{
    return std::isalnum(c)
        || c == '-' || c == '.'
        || c == '_' || c == '~';
}

/**
 * @details Grammar:
 * pchar = unreserved / pct-encoded / sub-delims / ":" / "@"
 */
int parse_pchar_(const_uchar *str, size_t& pos)
{
    return ((is_unreserved_(str[pos]) && ++pos)
        || (is_pct_encoded_(str + pos) && (pos += 3))
        || (is_sub_delims_(str[pos]) && ++pos)
        || ((str[pos] == ':'
        || str[pos] == '@') && ++pos));
}
