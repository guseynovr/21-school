/**
 * @file VServerManager.h
 * @author Andrei Baidin
 * @brief Discribes VServerManager class
 * @version 1.0
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef VSERVER_MANAGER_H_
#define VSERVER_MANAGER_H_

#include "VServer.h"
#include "../../src/config/parser/Config.h"
#include <HTTPStatusCode.h>

#include <string>
#include <map>
#include <list>
#include <stdint.h>

/**
 * @brief Manages several vistual servers and their configurations
 * 
 */
class VServerManager
{
public:
    struct HostMap
    {
        HostMap();

        std::map<std::string, const VServer*> hmap;
        const VServer* default_vs;
        bool is_default;
    };

    typedef std::map<uint16_t, HostMap>   portmap_t;
    typedef std::map<uint32_t, portmap_t> ipmap_t;
    typedef std::list<VServer>            vs_list_t;
    typedef std::list<Config>             conf_list_t;

    VServerManager();
    ~VServerManager();

    /**
     * @brief Parses the passed configuration string
     * 
     * @param str a valid pointer to a null-terminated string
     * @return true on successeful
     * @return false on failure
     */
    bool parse_config(const char* str);
    void clear();

    const VServer&   get_server(uint32_t ip, uint16_t port,
                                const std::string& host);
    const vs_list_t& get_server_list() const;

private:
    VServerManager(const VServerManager&);
    VServerManager& operator=(const VServerManager&);

    ipmap_t     vservers_ptrs_;
    vs_list_t   vservers_;
    conf_list_t configs_;
};

#endif  // VSERVER_MANAGER_H_
