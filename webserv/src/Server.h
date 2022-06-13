#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include <sys/event.h>
#include <errno.h>
#include <cstdio>

#include <ClientHandler.h>
#include <Utils.h>
#include <VServerManager.h>

#define DEFAULT_CONF_PATH "configs/default.conf"

class Server
{
enum FD_TYPE {INCOMING, CONNECTED};

public:
    Server();
    ~Server();

    void init(const std::string& config_path);
    void up();
    void down();

private:
    std::map<int, ClientHandler> clients;    //use fd for key
    VServerManager               vs_manager;
    std::vector<struct kevent>   changelist;
    std::vector<struct kevent>   eventlist;
    int                          kq;

    void    init_socket(const struct sockaddr_in& addr);
    void    handle_event(struct kevent);
    void    accept_clients(struct kevent&);
    void    update_event(int fd, int from, int to);
    void    add_event(int fd, bool client);
};

#endif //SERVER_H
