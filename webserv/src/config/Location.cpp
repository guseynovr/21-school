#include "../../inc/config/Location.h"

const std::string Location::empty_str_ = "";

Location::Location(const std::string& uri)
    : cgi_path_(NULL),
    index_(NULL),
    error_page_(NULL),
    redirection_(NULL),
    root_(NULL),
    client_body_temp_path_(NULL),
    client_max_body_size_(NULL),
    limit_except_(NULL),
    autoindex_(NULL),
    uri_(uri)
{
}

Location::Location(const Location &other)
    : cgi_path_(other.cgi_path_),
    index_(other.index_),
    error_page_(other.error_page_),
    redirection_(other.redirection_),
    root_(other.root_),
    client_body_temp_path_(other.client_body_temp_path_),
    client_max_body_size_(other.client_max_body_size_),
    limit_except_(other.limit_except_),
    autoindex_(other.autoindex_),
    uri_(other.uri_)
{
}

Location::~Location()
{
}

Location &Location::operator=(const Location &other)
{
    if (this != &other) {
        cgi_path_ = other.cgi_path_;
        index_ = other.index_;
        error_page_ = other.error_page_;
        redirection_ = other.redirection_;
        root_ = other.root_;
        client_body_temp_path_ = other.client_body_temp_path_;
        client_max_body_size_ = other.client_max_body_size_;
        limit_except_ = other.limit_except_;
        autoindex_ = other.autoindex_;
        uri_ = other.uri_;
    }

    return *this;
}


const std::string& Location::get_cgi_path(const std::string& extension) const
{
    typedef Config::cgi_path_t::const_iterator iter;

    iter res = cgi_path_->find(extension);

    return (res == cgi_path_->end()) ? empty_str_ : res->second;
}

const Config::index_t& Location::get_indexes() const
{
    return *index_;
}

const Config::limit_except_t& Location::get_limit_except() const
{
    return *limit_except_;
}

const std::string& Location::get_error_page(int code) const
{
    return (error_page_->codes.find(code) == error_page_->codes.end()) ? empty_str_ : error_page_->uri;
}

const Config::redirection_t& Location::get_redirection() const
{
    return *redirection_;
}

const Config::root_t& Location::get_root() const
{
    return *root_;
}

const Config::client_body_temp_path_t& Location::get_client_body_temp_path() const
{
    return *client_body_temp_path_;
}

Config::client_max_body_size_t Location::get_client_max_body_size() const
{
    return *client_max_body_size_;
}

Config::autoindex_t Location::get_autoindex() const
{
    return *autoindex_;
}
