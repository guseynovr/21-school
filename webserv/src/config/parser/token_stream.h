/**
 * @file token_stream.h
 * @author Andrei Baidin
 * @brief Token stream breaks passed string into tokens
 * @version 1.0
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TOKEN_STREAM_H_
#define TOKEN_STREAM_H_

#include <cstddef>

enum token_type
{
    ERROR = -1,
    EMPTY,
    REGULAR_TOKEN,
    NAME_TOKEN,
    RESPONSE,  // ASSIGN + NUMBER
    NUMBER,
    ASSIGN,
    LBRACE,
    RBRACE,
    SEMICOLON
};

struct token
{
    const char* str;
    size_t      size;
    token_type  type;
};

class token_stream
{
public:
    /**
     * @brief Construct a new token stream object
     * 
     * @param str a valid pointer to a null-teminated string
     */
    token_stream(const char* str);
    ~token_stream();

    token gettoken();
    bool  puttoken(const token& t);

private:
    token next_token_();
    token expression_();

    token       buf_;
    const char* str_;
    bool        isfull_;

};

#endif  // TOKEN_STREAM_H_
