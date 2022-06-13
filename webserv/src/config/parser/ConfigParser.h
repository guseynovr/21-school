/**
 * @file ConfigParser.h
 * @author Andrei Baidin
 * @brief Parses config files
 * @version 1.0
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include "../../../inc/config/VServerManager.h"
#include "token_stream.h"

#include "../../../debug.h"

#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <string>

#ifdef DEBUG
# define PRINT_TOKEN(t) \
    std::printf("DEBUG TOKEN: %s: %.*s [type = %d, size=%zu]\n", \
        __FUNCTION__, (int)t.size, t.str, t.type, t.size);
#endif  // DEBUG

#define SERVER                "server"                 // main
#define ROOT                  "root"                   // main, server, location
#define ERROR_PAGE            "error_page"             // main, server, location
#define CLIENT_MAX_BODY_SIZE  "client_max_body_size"   // main, server, location
#define CLIENT_BODY_TEMP_PATH "client_body_temp_path"  // main, server, location
#define AUTOINDEX             "autoindex"              // main, server, location
#define INDEX                 "index"                  // main, server, location
#define SERVER_NAME           "server_name"            // server
#define LISTEN                "listen"                 // server
#define LOCATION              "location"               // server, location
#define RETURN                "return"                 // server, location
#define LIMIT_EXCEPT          "limit_except"           // location
#define CGI_PASS              "cgi_pass"               // location
#define DEFAULT_SERVER        "default_server"         // listen

#define DEFAULT_HOST "0.0.0.0"
#define DEFAULT_PORT 80
#define PORT_LIMIT 65535

class ConfigParser
{
public:
    ConfigParser(VServerManager::ipmap_t& ipmap,
                 VServerManager::vs_list_t& vservers,
                 VServerManager::conf_list_t& configs,
                 const char* str);
    ~ConfigParser();

    bool parse();

private:
    static const char* const http_methods[3];

    void clear_();

    bool http_scope_();
    bool server_scope_(const Config& def_conf);
    bool location_scope_(const Config& def_conf, const Config& serv_conf,
                         VServer& vs);
    bool hsl_directives_(const token& t, Config& conf);

    bool root_(Config& conf);
    bool error_page_(Config& conf);
    bool client_max_body_size_(Config& conf);
    bool client_body_temp_path_(Config& conf);
    bool autoindex_(Config& conf);
    bool index_(Config& conf);

    bool server_name_(VServer& vs);
    bool listen_(VServer& vs);
    bool redirection_(Config& conf);

    bool limit_except_(Config& conf);
    bool cgi_pass_(Config& conf);

    void update_server_conf_(VServer& vs, const Config& def_conf,
                             const Config& serv_conf);
    void update_location_conf_(Location& loc,
                               const Config& def_conf,
                               const Config* serv_conf,
                               const Config* loc_conf);
    bool update_sockaddr_(VServer& vs, const char* ptr,
                          uint16_t port, bool is_default);
    bool insert_vs_(const VServer& vs);
    int is_allowed_http_method(const char* str, size_t size);

    VServerManager::ipmap_t&     ipmap_;
    VServerManager::vs_list_t&   vservers_;
    VServerManager::conf_list_t& configs_;

    token_stream ts_;
};

/**
 * @brief Parse a null-terminating string to http code from 300 to 599
 * @return a code or -1 on error
 */
long strtocode(const char* str);

#endif  // CONFIG_PARSER_H_
