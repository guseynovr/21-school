#ifndef RESPONSE_H
#define RESPONSE_H

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include <HTTPStatusCode.h>
#include <parser.h>
#include <VServer.h>
#include <Utils.h>
#include <MediaType.h>

class Response
{

typedef std::map<std::string, std::string> HeaderMap;
typedef std::map<StatusCode, std::string>  ReasonPhraseMap;

public:
    Response();

    std::string& to_string() const;
    void         set_status_code(StatusCode&);
    StatusCode   get_status_code() const;
    std::string& serialized();

    void        prepare(const VServer *conf, const Location* loc, StatusCode status);
    void        add_body(const std::string&);
    const std::string& get_body() const;
    void        add_header(const std::string&, const std::string&);
    void        clear();

private:
    static ReasonPhraseMap reasons;
    static ReasonPhraseMap init_reasons();

    std::string date_header();
    void        prepare_error_body(const std::string&);
    std::string get_error_path(const Location*);
    void        assemble_response();

    HeaderMap   headers;
    std::string body;
    std::string http_version;
    std::string reason_phrase;
    StatusCode  status_code;
    std::string resp_str;
    void get_file(const std::string& path);
};

#endif //RESPONSE_H
