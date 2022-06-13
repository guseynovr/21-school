#include "Utils.h"

std::ostream& operator << (std::ostream &out, const struct sockaddr_in &c)
{
    out << inet_ntoa(c.sin_addr) << ":" << ntohs(c.sin_port);
    return out;
}

bool operator==(const struct sockaddr_in &one, const struct sockaddr_in &two)
{
/*     std::clog << "sin_addr.saddr 1. "  << one.sin_addr.s_addr
                << " 2. " << two.sin_addr.s_addr
                << "\naddr.sin_family 1. " << one.sin_family
                << " 2. " << two.sin_family
                << "\naddr.sin_len 1." << one.sin_len
                << " 2. " << two.sin_len
                << "\naddr.sin_port 1. " << ntohs(one.sin_port)
                << " 2. " << ntohs(two.sin_port)
                << "\naddr.sin_zero 1. " << one.sin_zero
                << " 2. " << two.sin_zero << "\n"; */
    return one.sin_addr.s_addr == two.sin_addr.s_addr
        && one.sin_port == two.sin_port;
}

std::ostream& operator << (std::ostream &out,
                                  const std::vector<std::string>& strs)
{
    std::vector<std::string>::const_iterator i_str = strs.begin();

    if (i_str != strs.end()) {
        out << *i_str;
        ++i_str;
    }

    for ( ; i_str != strs.end(); ++i_str) {
        out << std::string(" ") << *i_str;
    }

    return out;
}

std::string getFileExtension(const std::string& path)
{
    size_t pos = path.find_last_of(".");

    if (pos == std::string::npos) {
        return std::string();
    }

    return path.substr(pos + 1);
}
