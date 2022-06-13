/**
 * @file transfer_encoding_field.cpp
 * @author Andrei Baidin
 * @brief Subroutines for parsing of the transfer encoding field
 * @version 1.0
 * @date 2022-05-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "parse_routines.h"

/**
 * @details Grammar:
 * transfer-parameter = token BWS "=" BWS ( token / quoted-string )
 */
// int parse_transfer_parameter_(const_uchar* str, size_t& pos)
// {
//     //
// }

/**
 * @details Grammar:
 * transfer-extension = token *( OWS ";" OWS transfer-parameter )
 */
// int parse_transfer_extension_(const_uchar* str, size_t& pos, std::string& buf)
// {
//     size_t cur_pos = pos;

//     if (!parse_token_(str, cur_pos, buf)) {
//         return (false);
//     }
// }

int is_valid_transfer_encoding_(Request* data)
{
    const StrVector& v = data->transfer_encoding;
    const size_t size = v.size();
    size_t count = 0;

    for (size_t i = 0; i < size; ++i) {
        if (!std::strcmp(v[i].c_str(), TC_CHUNKED) &&
            (i != size - 1 || ++count != 1))
        {
            return false;
        }
    }

    if (count) {
        data->content_length = 0;
    }
    return true;
}

/**
 * @details Grammar:
 * transfer-coding = "chunked"
 *                 / "compress"
 *                 / "deflate"
 *                 / "gzip"
 *                 / "x-compress"           ; Deprecated (alias for compress)
 *                 / "x-gzip"               ; Deprecated (alias for gzip)
 *                 / transfer-extension     ; not implemented
 */
int parse_transfer_coding_(const_uchar* str, size_t& pos, std::string& buf)
{
    static const char* codings[] = {
        TC_CHUNKED, TC_COMPRESS, TC_DEFLATE, TC_GZIP, TC_XCOMPRESS, TC_XGZIP
    };
    static const size_t sizes[] = {
        sizeof(TC_CHUNKED) - 1, sizeof(TC_COMPRESS) - 1, sizeof(TC_DEFLATE) - 1,
        sizeof(TC_GZIP) - 1, sizeof(TC_XCOMPRESS) - 1, sizeof(TC_XGZIP) - 1
    };
    static const size_t count = sizeof(codings) / sizeof(char*);

    const char* ptr = reinterpret_cast<const char*>(str + pos);

    for (size_t i = 0; i < count; ++i) {
        if (!std::strncmp(ptr, codings[i], sizes[i])) {
            if (i > 3) {
                const size_t size = sizeof("x-") - 1;
                buf.assign(ptr + size, sizes[i] - size);
            }
            else {
                buf.assign(ptr, sizes[i]);
            }
            pos += sizes[i];
            return (true);
        }
    }

    return (false);  // parse_transfer_extension_(str, pos, buf));
}

/**
 * @details Grammar:
 * Transfer-Encoding = 1#transfer-coding
 * 
 * list rule:
 * #element => [ ( "," / element ) *( OWS "," [ OWS element ] ) ]
 * 1#element => *( "," OWS ) element *( OWS "," [ OWS element ] )
 */
int parse_transfer_encoding_(Request* data)
{
    HeaderMap::iterator iter = data->headers.find("transfer-encoding");
    std::string buf;

    if (iter == data->headers.end()) {
        return (true);
    }

    const_uchar* str = reinterpret_cast<const_uchar*>(iter->second.c_str());
    size_t pos = 0;

    while (str[pos] == ',') {
        ++pos;
        parse_ows_(str, pos);
    }

    if (!parse_transfer_coding_(str, pos, buf)) {
        return (false);
    }

    data->transfer_encoding.push_back(buf);

    while (parse_ows_(str, pos) && (str[pos] == ',' && ++pos)) {
        size_t tmp = pos;
        if (parse_ows_(str, tmp) &&
            parse_transfer_coding_(str, tmp, buf))
        {
            data->transfer_encoding.push_back(buf);
            pos = tmp;
        }
    }

    if (str[pos] != '\0' ||
        !is_valid_transfer_encoding_(data)) {
        return (false);
    }

    data->headers.erase(iter);
    return (true);
}
