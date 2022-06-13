/**
 * @file parse_routines.h
 * @author Andrei Baidin
 * @brief Subroutines for parsing of http message
 * @details
 * This file contains methods that is used by http parser.
 * Do not include it directly to your project. Use 'http_parse.h' instead.
 * @version 1.0
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PARSE_ROUTINES_H
#define PARSE_ROUTINES_H

#include "../../../inc/http/parser.h"
#include <Request.h>

#include <cctype>
#include <cstdlib>
#include <cstring>

#include "../../../debug.h"

#define TC_CHUNKED "chunked"
#define TC_COMPRESS "compress"
#define TC_DEFLATE "deflate"
#define TC_GZIP "gzip"
#define TC_XCOMPRESS "x-compress"
#define TC_XGZIP "x-gzip"

typedef const unsigned char const_uchar;


/* request line */

int parse_request_line_(const_uchar *str, size_t& pos, Request* data);
int parse_target_(const_uchar *str, size_t& pos, std::string& buf);
int parse_origin_form_(const_uchar *str, size_t& pos);
int parse_http_version_(const_uchar* str, size_t& pos, std::string& buf);


/* uri */

int parse_query_(const_uchar *str, size_t& pos);
int parse_absolute_path_(const_uchar *str, size_t& pos);
int parse_segment_(const_uchar *str, size_t& pos);


/* header fields */

int parse_header_fields_generic_(const_uchar* str, size_t& pos, Request* data);
int parse_header_field_(const_uchar* str, size_t& pos, HeaderMap& header_map);


/* field generic */

int parse_field_name_(const_uchar* str, size_t& pos, std::string& buf);
int parse_field_value_(const_uchar* str, size_t& pos,
                        HeaderMap& header_map, const std::string& key);
int parse_field_content_(const_uchar* str, size_t& pos);
int is_field_vchar_(int c);


/* registered header fields */

int parse_reg_header_fields_(Request* data);


/* host field */

int parse_host_(Request* data);
int parse_uri_host_(const_uchar* str, size_t& pos);
int parse_ipv4_(const_uchar* str, size_t& pos);
int parse_reg_name_(const_uchar* str, size_t& pos);
int parse_port_(const_uchar* str, size_t& pos);
int parse_dec_octet_(const_uchar* str, size_t& pos);


/* content_length */

int parse_content_length_(Request* data);


/* transfer encoding */

int parse_transfer_coding_(const_uchar* str, size_t& pos, std::string& buf);
int parse_transfer_encoding_(Request* data);


/* obs */

int parse_obs_fold_(const_uchar* str, size_t& pos);
int is_obs_text_(int c);


/* pchar */

int parse_pchar_(const_uchar *str, size_t& pos);
int is_pct_encoded_(const_uchar *str);
int is_sub_delims_(int c);
int is_unreserved_(int c);


/* Augmented Backus-Naur Form (ABNF) */

int parse_eol_(const_uchar* str, size_t& pos);
int parse_rws_(const_uchar* str, size_t& pos);
int parse_ows_(const_uchar* str, size_t& pos);
int is_eol_(const_uchar* str, size_t pos);
int is_hexdig_(int c);
int is_vchar_(int c);
int is_wsp_(int c);


/* token */

int parse_token_(const_uchar *str, size_t& pos, std::string& buf);
int is_tchar_(int c);

#endif  /* PARSE_ROUTINES_H */
