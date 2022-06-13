/**
 * @file chunked_body.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of the chunked body
 * @version 1.0
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * chunk = chunk-size 
 *         [ chunk-ext ] CRLF       ; not implemented
 *         chunk-data CRLF
 * 
 * chunk-size = 1*HEXDIG
 * last-chunk = 1*("0")
 *              [ chunk-ext ] CRLF  ; not implemented
 * chunk-data = 1*OCTET             ; a sequence of chunk-size octets
 */
int parse_chunk_(const char* str, size_t& pos,
                 const size_t size, std::string& buf, bool& eof)
{
    char* endptr = NULL;
    size_t cur_pos = pos;
    const long chunk_size = std::strtol(str + cur_pos, &endptr, 16);
    const size_t bytes = endptr - str - cur_pos;

    if (!bytes) {
        return -1;
    }

    if (!*endptr) {
        return 0;
    }

    cur_pos += bytes;
    if (!parse_eol_(reinterpret_cast<const_uchar*>(str), cur_pos)) {
        return -1;
    }

    if (!chunk_size || cur_pos + chunk_size >= size) {
        eof = !chunk_size;
        return 0;
    }

    pos = cur_pos + chunk_size;
    if (!parse_eol_(reinterpret_cast<const_uchar*>(str), pos)) {
        return -1;
    }

    buf.append(str + cur_pos, chunk_size);
    return chunk_size;
}

/**
 * @details Grammar:
 * chunked-body = *chunk
 *                last-chunk
 *                trailer-part      ; not implemented
 *                CRLF
 */
int parse_chunked_body(const char* str, const size_t size,
                       Request& data, bool& eof)
{
    size_t length = 0;
    size_t pos = 0;
    ssize_t bytes = 0;

    while ((bytes = parse_chunk_(str, pos, size, data.body, eof)) > 0) {
        length += bytes;
    }

    if (!length && bytes == -1) {
        return -1;
    }

    if (eof) {
        data.transfer_encoding.pop_back();
    }
    data.content_length += length;
    return static_cast<int>(pos);
}

int parse_chunked_body(const char* str, Request& data, bool& eof)
{
    return parse_chunked_body(str, std::strlen(str), data, eof);
}
