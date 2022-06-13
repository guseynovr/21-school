/**
 * @file obs.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of obs characters
 * @version 1.0
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * obs-text = %x80-FF
 */
int is_obs_text_(int c)
{
    return c >= 0x80 && c <= 0xff;
}

/**
 * @details Grammar:
 * obs-fold = CRLF RWS  ; obsolete line folding
 */
int parse_obs_fold_(const_uchar* str, size_t& pos)
{
    size_t cur_pos = pos;
    if (parse_eol_(str, cur_pos)) {
        if (parse_rws_(str, cur_pos)) {
            pos = cur_pos;
            return true;
        }
    }
    return false;
}
