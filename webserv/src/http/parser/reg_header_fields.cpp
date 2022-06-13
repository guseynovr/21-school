/**
 * @file reg_header_fields.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of registered header fields of http messages
 * @version 1.0
 * @date 2022-05-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

int parse_reg_header_fields_(Request* data)
{
    return parse_host_(data)
        && parse_content_length_(data)
        && parse_transfer_encoding_(data);
}
