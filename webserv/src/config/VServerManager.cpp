/**
 * @file VServerManager.cpp
 * @author Andrei Baidin
 * @brief Implementation of VServerManager class
 * @version 1.0
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../../inc/config/VServerManager.h"
#include "parser/ConfigParser.h"

VServerManager::HostMap::HostMap()
    : default_vs(NULL),
    is_default(false)
{
}

VServerManager::VServerManager()
{
}

VServerManager::~VServerManager()
{
}

bool VServerManager::parse_config(const char* str)
{
    ConfigParser parser(vservers_ptrs_, vservers_, configs_, str);
    return parser.parse();
}

void VServerManager::clear()
{
    vservers_ptrs_.clear();
    vservers_.clear();
    configs_.clear();
}

const VServer&   VServerManager::get_server(uint32_t ip, uint16_t port,
const std::string& host)
{
    ipmap_t::const_iterator ip_it = vservers_ptrs_.find(ip);
    if (ip_it == vservers_ptrs_.end()) {
        throw Not_Found;
    }

    portmap_t::const_iterator port_it = ip_it->second.find(port);
    if (port_it == ip_it->second.end()) {
        throw Not_Found;
    }

    std::map<std::string, const VServer*>::const_iterator host_it;
    host_it = port_it->second.hmap.find(host);
    if (host_it == port_it->second.hmap.end()) {
        return *port_it->second.default_vs;
    }
    return *host_it->second;
}

const VServerManager::vs_list_t& VServerManager::get_server_list() const
{
    return vservers_;
}

