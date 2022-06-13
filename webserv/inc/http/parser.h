/**
 * @file parser.h
 * @author Andrei Baidin
 * @brief Structures and methods for parsing http messages.
 * @version 1.0
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef HTTP_PARSER
#define HTTP_PARSER

#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <HTTPStatusCode.h>
#include <Request.h>

typedef std::map<std::string, std::string> HeaderMap;
typedef std::vector<std::string>           StrVector;

class http_parse_error : public std::runtime_error
{
public:
    http_parse_error();
};

/* struct RequestData
{
    HeaderMap   headers;
    std::string method_name;
    std::string target;
    std::string http_version;
    std::string host;
    std::string body;
    StrVector   transfer_encoding;
    long        content_length;

    RequestData();
    void clear();
}; */

/**
 * @brief Parses the chunked body of http request message.
 * The Transfer-encoding field of the data structure
 * must have "chunked" value in the end, otherwise
 * it may lead to undefined behavior.
 * 
 * @param str a valid pointer to a null-terminating string
 * @param size a number of characters in the string
 * @param data structure to save parsed data.
 * @param eof a value to indicate end of the chunked body
 * @return a number of bytes parsed or -1 on error
 * 
 * @exception std::bad_alloc
 * @exception std::length_error
 */
int parse_chunked_body(const char* str, const size_t size,
                       Request& data, bool& eof);

/**
 * @brief Parses the chunked body of http request message.
 * The Transfer-encoding field of the data structure
 * must have "chunked" value in the end, otherwise
 * it may lead to undefined behavior.
 * 
 * @param str a valid pointer to a null-terminating string
 * @param data structure to save parsed data.
 * @param eof a value to indicate end of the chunked body
 * @return a number of bytes parsed or -1 on error
 * 
 * @exception std::bad_alloc
 * @exception std::length_error
 */
int parse_chunked_body(const char* str, Request& data, bool& eof);

/**
 * @brief Parses http request message
 * 
 * @param str a valid poiter to a null-terminating string
 * @return pointer to the parsed structure
 * 
 * @exception std::bad_alloc
 * @exception std::length_error
 * @exception webserv::http::http_parse_error
 */
Request* parse_request(const char* str);

/**
 * @brief Parses http request message
 * 
 * @param str a valid poiter to a null-terminating string
 * @param data structure to save parsed data
 * @return a number of bytes parsed
 * 
 * @exception std::bad_alloc
 * @exception std::length_error
 * @exception webserv::http::http_parse_error
 */
size_t parse_request(const char* str, Request& data);

#endif /* HTTP_PARSER */
