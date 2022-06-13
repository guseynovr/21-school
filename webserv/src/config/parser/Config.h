#ifndef CONFIG_H_
#define CONFIG_H_

#include "../../../inc/http/HTTPStatusCode.h"

#include <string>
#include <set>
#include <map>
#include <vector>

enum ConfigFields
{
    E_CGI_PATH,
    E_INDEX,
    E_ERROR_PAGE,
    E_REDIRECTION,
    E_ROOT,
    E_CLIENT_BODY_TEMP_PATH,
    E_CLIENT_MAX_BODY_SIZE,
    E_LIMIT_EXCEPT,
    E_AUTOINDEX
};

struct ErrorPage
{
    std::set<int> codes;
    std::string   uri;
};

/**
 * @brief For 301, 302, 303, 307, and 308 codes text field is url
 * for others it is a response text
 * 
 */
struct Redirection
{
    std::string text;
    int code;
};

struct Config
{
    typedef std::map<std::string, std::string> cgi_path_t;
    typedef std::vector<std::string>           index_t;
    typedef std::vector<std::string>           limit_except_t;
    typedef ErrorPage                          error_page_t;
    typedef Redirection                        redirection_t;
    typedef std::string                        root_t;
    typedef std::string                        client_body_temp_path_t;
    typedef size_t                             client_max_body_size_t;
    typedef bool                               autoindex_t;

    // Location                 location;
    // std::set<std::string>    server_name;
    cgi_path_t              cgi_path;
    index_t                 index;
    limit_except_t          limit_except;
    error_page_t            error_page;
    redirection_t           redirection;
    root_t                  root;
    client_body_temp_path_t client_body_temp_path;
    client_max_body_size_t  client_max_body_size;
    autoindex_t             autoindex;

    int fields_set;
};

int is_field_set(int fields_set, ConfigFields field);
int set_field(int fields_set, ConfigFields field);

#endif  // CONFIG_H_
