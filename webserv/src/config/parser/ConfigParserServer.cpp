/**
 * @file ConfigParserServer.cpp
 * @author Andrei Baidin
 * @brief Routines for parsing configuration directives in server scope
 * @version 1.0
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ConfigParser.h"

const char* const ConfigParser::http_methods[] = { "GET", "POST", "DELETE" };

bool ConfigParser::server_scope_(const Config& def_conf)
{
    token t = ts_.gettoken();

    if (t.type != LBRACE) {
        return (false);
    }

    vservers_.push_back(VServer());
    configs_.push_back(Config());

    VServer& vs = vservers_.back();
    Config& serv_conf = configs_.back();
    serv_conf.fields_set = 0;

    bool result = true;
    t = ts_.gettoken();

    while (result && t.type == NAME_TOKEN) {
        if (!std::strncmp(t.str, SERVER_NAME, t.size)) {
            result = server_name_(vs);
        }
        else if (!std::strncmp(t.str, LISTEN, t.size)) {
            result = listen_(vs);
        }
        else if (!std::strncmp(t.str, LOCATION, t.size)) {
            result = location_scope_(def_conf, serv_conf, vs);
        }
        else if (!std::strncmp(t.str, RETURN, t.size)) {
            result = redirection_(serv_conf);
        }
        else {
            result = hsl_directives_(t, serv_conf);
        }

        t = ts_.gettoken();
    }

    update_server_conf_(vs, def_conf, serv_conf);

    return (result && insert_vs_(vs) && t.type == RBRACE);
}

bool ConfigParser::location_scope_(const Config& def_conf,
                                   const Config& serv_conf,
                                   VServer& vs)
{
    bool exact = false;

    token t = ts_.gettoken();

    if (t.type == ASSIGN) {
        exact = true;
        t = ts_.gettoken();
    }

    if ((t.type != REGULAR_TOKEN && t.type != NAME_TOKEN && t.type != NUMBER) ||
        ts_.gettoken().type != LBRACE)
    {
        return (false);
    }

    typedef std::pair<VServer::locs_map_t::iterator, bool> loc_pair;

    std::string uri(t.str, t.size);
    loc_pair pr;

    if (exact) {
        pr = vs.locations_exact_.insert(std::make_pair(uri, Location(uri)));
    }
    else {
        pr = vs.locations_.insert(std::make_pair(uri, Location(uri)));
    }

    if (!pr.second) {
        return (false);
    }

    configs_.push_back(Config());

    Location& loc = pr.first->second;
    Config& loc_conf = configs_.back();
    loc_conf.fields_set = 0;

    bool result = true;
    t = ts_.gettoken();

    while (result && t.type == NAME_TOKEN) {
        if (!std::strncmp(t.str, LIMIT_EXCEPT, t.size)) {
            result = limit_except_(loc_conf);
        }
        else if (!std::strncmp(t.str, CGI_PASS, t.size)) {
            result = cgi_pass_(loc_conf);
        }
        else {
            result = hsl_directives_(t, loc_conf);
        }

        t = ts_.gettoken();
    }

    update_location_conf_(loc, def_conf, &serv_conf, &loc_conf);

    return (result && t.type == RBRACE);
}

int ConfigParser::is_allowed_http_method(const char* str, size_t size)
{
    for (size_t i = 0; i < sizeof(http_methods); ++i) {
        if (!std::strncmp(str, http_methods[i], size)) {
            return i;
        }
    }

    return -1;
}

bool ConfigParser::limit_except_(Config& conf)
{
    token t = ts_.gettoken();

    if (is_field_set(conf.fields_set, E_LIMIT_EXCEPT)) {
        return (false);
    }

    int method_num;
    while (t.type == NAME_TOKEN &&
           (method_num = is_allowed_http_method(t.str, t.size)) != -1)
    {
        conf.limit_except.push_back(http_methods[method_num]);
        t = ts_.gettoken();
    }

    conf.fields_set = set_field(conf.fields_set, E_LIMIT_EXCEPT);
    return (t.type == SEMICOLON);
}

bool ConfigParser::cgi_pass_(Config& conf)
{
    token t = ts_.gettoken();

    if (is_field_set(conf.fields_set, E_CGI_PATH) ||
        t.type != NAME_TOKEN)
    {
        return (false);
    }

    std::string& path = conf.cgi_path[std::string(t.str, t.size)];

    if (!path.empty() ||
        (t = ts_.gettoken()).type != REGULAR_TOKEN)
    {
        return (false);
    }

    path.assign(t.str, t.size);
    conf.fields_set = set_field(conf.fields_set, E_CGI_PATH);
    return (ts_.gettoken().type == SEMICOLON);
}

bool ConfigParser::redirection_(Config& conf)
{
    if (is_field_set(conf.fields_set, E_REDIRECTION)) {
        return (false);
    }

    token t = ts_.gettoken();

    if (t.type == NUMBER) {
        if ((conf.redirection.code = strtocode(t.str)) == -1) {
            return (false);
        }

        t = ts_.gettoken();
    }

    if (t.type != REGULAR_TOKEN && t.type != NAME_TOKEN) {
        return (false);
    }

    conf.redirection.text.assign(t.str, t.size);
    conf.fields_set = set_field(conf.fields_set, E_REDIRECTION);
    return (ts_.gettoken().type == SEMICOLON);
}

bool ConfigParser::server_name_(VServer& vs)
{
    token t = ts_.gettoken();

    if (t.type != REGULAR_TOKEN &&
        t.type != NAME_TOKEN &&
        t.type != NUMBER) {
        return (false);
    }

    do {
        vs.server_names_.insert(std::string(t.str, t.size));
        t = ts_.gettoken();
    } while (t.type == REGULAR_TOKEN ||
             t.type == NAME_TOKEN ||
             t.type == NUMBER);

    return (t.type == SEMICOLON);
}

bool ConfigParser::listen_(VServer& vs)
{
    token t = ts_.gettoken();

    if (t.type == ERROR || t.type == EMPTY) {
        return (false);
    }

    std::string str(t.str, t.size);
    size_t pos = str.find(':');

    const char* ptr = str.c_str();
    long port = DEFAULT_PORT;
    bool is_default = false;

    if (pos != std::string::npos) {
        str[pos] = '\0';
        port = htons(std::strtol(ptr + pos + 1, NULL, 10));
        if (errno == ERANGE) {
            return (false);
        }
    }
    else if (t.type == NUMBER) {
        port = std::strtol(ptr, NULL, 10);
        if (errno == ERANGE) {
            return (false);
        }

        ptr = DEFAULT_HOST;
    }

    if ((t = ts_.gettoken()).type == NAME_TOKEN &&
        !std::strncmp(t.str, DEFAULT_SERVER, t.size))
    {
        is_default = true;
        t = ts_.gettoken();
    }

    if (!port || port > PORT_LIMIT ||
        !update_sockaddr_(vs, ptr, static_cast<uint16_t>(port), is_default))
    {
        return (false);
    }

    return (t.type == SEMICOLON);
}

void ConfigParser::update_server_conf_(VServer& vs, const Config& def_conf,
                                       const Config& serv_conf)
{
    if (vs.server_names_.empty()) {
        vs.server_names_.insert("");
    }

    if (vs.listens_.empty()) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = DEFAULT_PORT;
        vs.listens_.insert(std::make_pair(addr, true));
    }

    if (vs.locations_.empty() && vs.locations_exact_.empty()) {
        Location& loc = vs.locations_.insert(
            std::make_pair("/", Location("/"))).first->second;
        update_location_conf_(loc, def_conf, &serv_conf, NULL);
    }
}

bool ConfigParser::update_sockaddr_(VServer& vs, const char* ptr,
                                    uint16_t port, bool is_default)
{
    struct hostent* hent = gethostbyname(ptr);

    if (!hent) {
        return (false);
    }

    struct in_addr** list = reinterpret_cast<struct in_addr**>(hent->h_addr_list);

    for (size_t i = 0; list[i]; ++i) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr = *list[i];
        addr.sin_port = port;
        if (!vs.listens_.insert(std::make_pair(addr, is_default)).second) {
            return (false);
        }
    }

    return (true);
}

bool ConfigParser::insert_vs_(const VServer& vs)
{
    typedef VServer::sock_map_t::const_iterator csock_iter;
    typedef VServer::name_set_t::const_iterator cname_iter;

    csock_iter end = vs.listens_.end();

    for (csock_iter iter = vs.listens_.begin(); iter != end; ++iter) {
        const struct sockaddr_in& addr = iter->first;
        VServerManager::HostMap& host_map =
            ipmap_[addr.sin_addr.s_addr][addr.sin_port];

        // second -> bool is_default;
        if (iter->second || !host_map.default_vs) {
            if (host_map.is_default) {
                return (false);
            }

            host_map.default_vs = &vs;
            host_map.is_default = iter->second;
        }

        cname_iter nend = vs.server_names_.end();
        for (cname_iter niter = vs.server_names_.begin(); niter != nend; ++niter) {
            host_map.hmap.insert(std::make_pair(*niter, &vs));
        }
    }

    return (true);
}

