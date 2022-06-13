#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
// #include <parser.h>


class Request
{
public:
    typedef std::map<std::string, std::string> HeaderMap;
    typedef std::vector<std::string>           StrVector;

// private:
    HeaderMap   headers;
    std::string method_name;
    std::string target;
    std::string http_version;
    std::string query_str;
    std::string host;
    std::string body;
    StrVector   transfer_encoding;
    long        content_length;

    Request();

    void clear();
    void parseQuery();

};

#endif //REQUEST_H
