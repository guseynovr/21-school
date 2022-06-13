#include "token_stream.h"
#include "token_utils.h"

token_stream::token_stream(const char* str)
    : buf_((token){ NULL, 0, EMPTY}),
    str_(str),
    isfull_(false)
{
}

token_stream::~token_stream()
{
}

token token_stream::gettoken()
{
    if (isfull_) {
        isfull_ = false;
        return buf_;
    }

    return next_token_();
}

bool token_stream::puttoken(const token& t)
{
    if (isfull_) {
        return false;
    }

    buf_ = t;
    return isfull_ = true;
}

token token_stream::next_token_()
{
    str_ = skip_spaces(str_);
    buf_.str = str_;

    switch (*str_)
    {
    case '{': {
        buf_.type = LBRACE;
        break;
    }
    case '}': {
        buf_.type = RBRACE;
        break;
    }
    case ';': {
        buf_.type = SEMICOLON;
        break;
    }
    case '\0': {
        buf_.type = EMPTY;
        return buf_;
    }
    default: {
        return expression_();
    }
    }

    ++str_;
    buf_.size = 1;
    return buf_;
}

token token_stream::expression_()
{
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(str_);

    if (isnumber(ptr)) {
        buf_.type = NUMBER;
    }
    else if (reinterpret_cast<const char*>(ptr) == str_
        && isname(ptr))
    {
        buf_.type = NAME_TOKEN;
    }
    else if (reinterpret_cast<const char*>(ptr) == str_
        && isresponse(ptr))
    {
        buf_.type = RESPONSE;
    }
    else if (reinterpret_cast<const char*>(ptr) == str_
        && *ptr == '=')
    {
        ++ptr;
        buf_.type = ASSIGN;
    }
    else if (isregular(ptr)) {
        buf_.type = REGULAR_TOKEN;
    }
    else {
        buf_.type = ERROR;
        return buf_;
    }

    buf_.size = reinterpret_cast<const char*>(ptr) - str_;
    str_ = reinterpret_cast<const char*>(ptr);
    return buf_;
}
