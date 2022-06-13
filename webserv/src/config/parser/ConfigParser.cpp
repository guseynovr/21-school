/**
 * @file ConfigParser.cpp
 * @author Andrei Baidin
 * @brief Parses config files
 * @version 1.0
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ConfigParser.h"

int is_field_set(int fields_set, ConfigFields field)
{
    return fields_set & (1 << field);
}

int set_field(int fields_set, ConfigFields field)
{
    return fields_set | (1 << field);
}

long strtocode(const char* str)
{
    long code = std::strtol(str, NULL, 10);

    if (errno == ERANGE || code < 300 || code > 599) {
        return -1;
    }

    return code;
}

ConfigParser::ConfigParser(VServerManager::ipmap_t& ipmap,
                           VServerManager::vs_list_t& vservers,
                           VServerManager::conf_list_t& configs,
                           const char* str)
    : ipmap_(ipmap),
    vservers_(vservers),
    configs_(configs),
    ts_(str)
{
}

ConfigParser::~ConfigParser()
{
}

bool ConfigParser::parse()
{
    Config default_conf = {
        Config::cgi_path_t(),
        Config::index_t(1, "index.html"),
        Config::limit_except_t(),
        Config::error_page_t(),
        Config::redirection_t(),
        Config::root_t("html"),
        Config::client_body_temp_path_t("client_body_temp"),
        Config::client_max_body_size_t(1024 * 1024),
        Config::autoindex_t(false),
        0
    };

    configs_.push_back(default_conf);

    if (http_scope_()) {
        return (true);
    }

    clear_();
    return (false);
}

void ConfigParser::clear_()
{
    ipmap_.clear();
    vservers_.clear();
    configs_.clear();
}

bool ConfigParser::http_scope_()
{
    Config& def_conf = configs_.front();
    token t = ts_.gettoken();
    bool result = true;

    while (result && t.type == NAME_TOKEN) {
        if (!std::strncmp(t.str, SERVER, t.size)) {
            result = server_scope_(def_conf);
        }
        else {
            result = hsl_directives_(t, def_conf);
        }

        t = ts_.gettoken();
    }

    return (result && t.type == EMPTY);
}

void ConfigParser::update_location_conf_(Location& loc,
                                         const Config& def_conf,
                                         const Config* serv_conf,
                                         const Config* loc_conf)
{
    if (loc_conf && is_field_set(loc_conf->fields_set, E_CGI_PATH)) {
        loc.cgi_path_ = &loc_conf->cgi_path;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_CGI_PATH)) {
        loc.cgi_path_ = &serv_conf->cgi_path;
    }
    else {
        loc.cgi_path_ = &def_conf.cgi_path;
    }

    if (loc_conf && is_field_set(loc_conf->fields_set, E_INDEX)) {
        loc.index_ = &loc_conf->index;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_INDEX)) {
        loc.index_ = &serv_conf->index;
    }
    else {
        loc.index_ = &def_conf.index;
    }

    if (loc_conf && is_field_set(loc_conf->fields_set, E_ERROR_PAGE)) {
        loc.error_page_ = &loc_conf->error_page;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_ERROR_PAGE)) {
        loc.error_page_ = &serv_conf->error_page;
    }
    else {
        loc.error_page_ = &def_conf.error_page;
    }

    if (loc_conf && is_field_set(loc_conf->fields_set, E_REDIRECTION)) {
        loc.redirection_ = &loc_conf->redirection;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_REDIRECTION)) {
        loc.redirection_ = &serv_conf->redirection;
    }
    else {
        loc.redirection_ = &def_conf.redirection;
    }

    if (loc_conf && is_field_set(loc_conf->fields_set, E_ROOT)) {
        loc.root_ = &loc_conf->root;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_ROOT)) {
        loc.root_ = &serv_conf->root;
    }
    else {
        loc.root_ = &def_conf.root;
    }

    if (loc_conf && is_field_set(loc_conf->fields_set, E_CLIENT_BODY_TEMP_PATH)) {
        loc.client_body_temp_path_ = &loc_conf->client_body_temp_path;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_CLIENT_BODY_TEMP_PATH)) {
        loc.client_body_temp_path_ = &serv_conf->client_body_temp_path;
    }
    else {
        loc.client_body_temp_path_ = &def_conf.client_body_temp_path;
    }

    if (loc_conf && is_field_set(loc_conf->fields_set, E_CLIENT_MAX_BODY_SIZE)) {
        loc.client_max_body_size_ = &loc_conf->client_max_body_size;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_CLIENT_MAX_BODY_SIZE)) {
        loc.client_max_body_size_ = &serv_conf->client_max_body_size;
    }
    else {
        loc.client_max_body_size_ = &def_conf.client_max_body_size;
    }

    if (loc_conf && is_field_set(loc_conf->fields_set, E_LIMIT_EXCEPT)) {
        loc.limit_except_ = &loc_conf->limit_except;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_LIMIT_EXCEPT)) {
        loc.limit_except_ = &serv_conf->limit_except;
    }
    else {
        loc.limit_except_ = &def_conf.limit_except;
    }

    if (loc_conf && is_field_set(loc_conf->fields_set, E_AUTOINDEX)) {
        loc.autoindex_ = &loc_conf->autoindex;
    }
    else if (serv_conf && is_field_set(serv_conf->fields_set, E_AUTOINDEX)) {
        loc.autoindex_ = &serv_conf->autoindex;
    }
    else {
        loc.autoindex_ = &def_conf.autoindex;
    }
}

