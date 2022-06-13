#ifndef VSERVER_H_
#define VSERVER_H_

#include "Location.h"

#include <map>
#include <set>
#include <string>

#include <netinet/ip.h>

enum CompareType
{
    PART,
    WHOLE
};

template <typename sockaddr>
struct sockaddr_less
{
    bool operator()(const sockaddr& lhs, const sockaddr& rhs) const
    {
        return lhs.sin_addr.s_addr < rhs.sin_addr.s_addr ||
            (lhs.sin_addr.s_addr == rhs.sin_addr.s_addr &&
            lhs.sin_port < rhs.sin_port);
    }
};

class VServer
{
public:
    friend class ConfigParser;

    typedef std::map<std::string, Location,
        std::greater<std::string> >             locs_map_t;
    typedef std::set<std::string>               name_set_t;
    typedef std::map<struct sockaddr_in, bool,
        sockaddr_less<struct sockaddr_in> >     sock_map_t;
    typedef locs_map_t::const_iterator          loc_it;

    VServer();
    VServer(VServer const &other);
    ~VServer();

    VServer& operator = (VServer const &other);

    const Location*   get_location(const std::string& uri) const;
    const name_set_t& get_names() const;
    const sock_map_t& get_sockaddrs() const;
    const sock_map_t& get_listens() const;

private:
    locs_map_t locations_;
    locs_map_t locations_exact_;
    name_set_t server_names_;
    sock_map_t listens_;
};

#endif  // VSERVER_H_
