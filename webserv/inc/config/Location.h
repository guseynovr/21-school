#ifndef LOCATION_H_
#define LOCATION_H_

#include "../../src/config/parser/Config.h"

#include <string>

class Location
{
public:
    friend class ConfigParser;

    Location(const std::string& uri);
    Location(const Location &other);
    ~Location();

    Location& operator = (const Location &other);

    const std::string&                     get_cgi_path(const std::string& extension) const;
    const Config::index_t&                 get_indexes() const;
    const Config::limit_except_t&          get_limit_except() const;
    const std::string&                     get_error_page(int code) const;
    const Config::redirection_t&           get_redirection() const;
    const Config::root_t&                  get_root() const;
    const Config::client_body_temp_path_t& get_client_body_temp_path() const;

    Config::client_max_body_size_t get_client_max_body_size() const;
    Config::autoindex_t            get_autoindex() const;

private:
    const Config::cgi_path_t              *cgi_path_;
    const Config::index_t                 *index_;
    const Config::error_page_t            *error_page_;
    const Config::redirection_t           *redirection_;
    const Config::root_t                  *root_;
    const Config::client_body_temp_path_t *client_body_temp_path_;
    const Config::client_max_body_size_t  *client_max_body_size_;
    const Config::limit_except_t          *limit_except_;
    const Config::autoindex_t             *autoindex_;

    static const std::string empty_str_;
    std::string uri_;
};

#endif  // LOCATION_H_
