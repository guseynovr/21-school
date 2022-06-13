/**
 * @file abnf.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of characters according to ABNF notation
 * @version 1.0
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * eol = [ CR ] LF
 */
int parse_eol_(const_uchar* str, size_t& pos)
{
    size_t offset = 0;
    if (str[pos] == '\r') {
        offset = 1;
    }
    return (str[pos + offset] == '\n' && (pos += offset + 1));
}

/**
 * @details Grammar:
 * RWS = 1*WSP  ; optional whitespace
 */
int parse_rws_(const_uchar* str, size_t& pos)
{
    size_t cur_pos = pos;

    while (is_wsp_(str[cur_pos])) {
        ++cur_pos;
    }

    if (cur_pos == pos) {
        return false;
    }

    pos = cur_pos;
    return true;
}

/**
 * @details Grammar:
 * OWS = *WSP   ; optional whitespace
 */
int parse_ows_(const_uchar* str, size_t& pos)
{
    size_t cur_pos = pos;

    while (is_wsp_(str[cur_pos])) {
        ++cur_pos;
    }

    pos = cur_pos;
    return (true);
}

int is_eol_(const_uchar* str, size_t pos)
{
    return str[pos] == '\n'
        || (str[pos] == '\r' && str[pos + 1] == '\n');
}

/**
 * @details Grammar:
 * HEXDIG =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
 */
int is_hexdig_(int c)
{
    return std::isdigit(c) || (c >= 'A' && c <= 'F');
}

/**
 * @details Grammar:
 * WSP = SP / HTAB  ; white space
 */
int is_wsp_(int c)
{
    return c == ' ' || c == '\t';
}

/**
 * @details Grammar:
 * VCHAR = %x21-7E      ; visible (printing) characters
 */
int is_vchar_(int c)
{
    return c >= 0x21 && c <= 0x7e;
}
