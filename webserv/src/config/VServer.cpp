#include "../../inc/config/VServer.h"

#include <vector>

VServer::VServer()
{
}

VServer::VServer(const VServer& other)
    : locations_(other.locations_),
    server_names_(other.server_names_),
    listens_(other.listens_)
{
}

VServer::~VServer()
{
}

VServer& VServer::operator=(const VServer& other)
{
    if (this != &other) {
        locations_ = other.locations_;
        server_names_ = other.server_names_;
        listens_ = other.listens_;
    }

    return *this;
}

const Location* VServer::get_location(const std::string& uri) const
{
    for (loc_it it = locations_exact_.begin(); it != locations_exact_.end(); ++it) {
        if (!strncmp(it->first.c_str(), uri.c_str(), it->first.size())) {
            return &it->second;
        }
    }
    for (loc_it it = locations_.begin(); it != locations_.end(); ++it) {
        if (!strncmp(it->first.c_str(), uri.c_str(), it->first.size())) {
            return &it->second;
        }
    }
    return NULL;
}

const VServer::sock_map_t& VServer::get_listens() const
{
    return listens_;
}
