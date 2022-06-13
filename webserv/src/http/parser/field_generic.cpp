/**
 * @file field_generic.cpp
 * @author Andrei Baidin
 * @brief Subroutines for generic parsing of header fields
 * @version 1.0
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * field-vchar = VCHAR / obs-text
 */
int is_field_vchar_(int c)
{
    return is_vchar_(c) || is_obs_text_(c);
}

/**
 * @details Grammar:
 * field-content = field-vchar [ RWS field-vchar ]
 */
int parse_field_content_(const_uchar* str, size_t& pos)
{
    if (is_field_vchar_(str[pos])) {
        size_t cur_pos = ++pos;
        if (parse_rws_(str, cur_pos) && is_field_vchar_(str[cur_pos])) {
            pos = cur_pos;
        }
        return true;
    }
    return false;
}

/**
 * @details Grammar:
 * field-value = *( field-content / obs-fold )
 */
int parse_field_value_(const_uchar* str, size_t& pos,
                        HeaderMap& header_map, const std::string& key)
{
    std::string buf;
    size_t begin_pos = pos;
    size_t cur_pos = begin_pos;

    while (true) {
        if (!parse_field_content_(str, cur_pos)) {
            const size_t size = cur_pos - begin_pos;
            if (parse_obs_fold_(str, cur_pos))
            {
                buf.append(reinterpret_cast<const char*>(str + begin_pos),
                    size).append(1, ' ');
                begin_pos = cur_pos;
            }
            else {
                break;
            }
        }
    }

    std::string& value = header_map[key];
    if (!value.empty()) {
        value.append(",");
    }

    value.append(buf).append(reinterpret_cast<const char*>(str + begin_pos),
        cur_pos - begin_pos);
    pos = cur_pos;
    return (true);
}

/**
 * @details Grammar:
 * field-name = token   ; case-insensitive
 */
int parse_field_name_(const_uchar* str, size_t& pos, std::string& buf)
{
    if (!parse_token_(str, pos, buf)) {
        return (false);
    }

    for (size_t i = 0; i < buf.size(); ++i) {
        buf[i] = std::tolower(buf[i]);
    }

    return (true);
}
