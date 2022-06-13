#include <Request.h>

Request::Request()
    : content_length(-1)
{
    //
}

void Request::clear()
{
    this->headers.clear();
    this->http_version.clear();
    this->method_name.clear();
    this->target.clear();
}

void Request::parseQuery()
{
    size_t query_start = target.find_first_of("?");
    if (query_start == std::string::npos)
        return;
    query_str = target.substr(query_start + 1);
    target = target.substr(0, query_start);
}
