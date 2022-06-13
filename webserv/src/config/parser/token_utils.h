/**
 * @file token_utils.h
 * @author Andrei Baidin
 * @brief Routines for the token stream
 * @version 1.0
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TOKEN_UTILS_H_
#define TOKEN_UTILS_H_

const char* skip_spaces(const char* str);

int isseparator(int c);
int isnchar(int c);
int ispchar(int c);

bool isnumber(char unsigned const*& str);
bool isname(unsigned char const*& str);
bool isresponse(unsigned char const*& str);
bool isregular(unsigned char const*& str);

#endif  // TOKEN_UTILS_H_
