#include <Server.h>

Server::Server()
    : eventlist(std::vector<struct kevent>(1024)) //TODO: use number of workers for size???
{
    //TODO: get number of cores
}

Server::~Server() {

}

void Server::init(const std::string& config_path)
{
    //TODO: parse config file into configs
    // std::cout << "config_path: " << config_path << "\n";
    FILE *file = std::fopen(config_path.c_str(), "rb");
    if (!file) {
        throw std::runtime_error((std::string("File not opened: ") + strerror(errno)).c_str());
    }
    off_t size = lseek(fileno(file), 0, SEEK_END);
    // off_t size = lseek(fileno(file), 0, SEEK_CUR);
    lseek(fileno(file), 0, SEEK_SET);
    std::string file_data(size+1, 0);
    // errno = 0;
    // std::cout << "eerno = " << errno << ": " << strerror(errno) << "\n";
    int ret = std::fread(&file_data[0], 1, size, file);
    // std::clog << file_data <<"\n";
    if (ret != size) {
        std::clog << "ret = " << ret << " size = " << size << std::endl;
        throw std::runtime_error((std::string("read error: ") + strerror(errno)).c_str());
    }
    // exit(EXIT_FAILURE);
    if (!vs_manager.parse_config(file_data.data())) {
        throw std::runtime_error("Config parse error");
    }
    std::fclose(file);

    const VServerManager::vs_list_t& serv_list = vs_manager.get_server_list();
    for (VServerManager::vs_list_t::const_iterator it = serv_list.begin();
        it != serv_list.end(); ++it) {
        const VServer::sock_map_t& listens = it->get_listens();
        for (VServer::sock_map_t::const_iterator it2 = listens.begin(); it2 != listens.end(); ++it2) {
            init_socket(it2->first);
        }
    }

    kq = kqueue();
    if (kq == -1) {
        throw std::runtime_error(std::string(
            "Failed to create new kernel event queue") + strerror(errno));
    }
}

void Server::init_socket(const struct sockaddr_in& addr)
{
    // std::cout << "addr: " << addr << std::endl;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error(std::string("socket: ") + strerror(errno));
    }
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::runtime_error(std::string("setsockopt: ") + strerror(errno));
    }
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(sockaddr)) < 0) {
        throw std::runtime_error(std::string("bind: ") + strerror(errno));
    }
    if (listen(sockfd, 512) < 0) { //default backlog: linux 4096, nginx 512
        throw std::runtime_error(std::string("listen: ") + strerror(errno));
    }
    add_event(sockfd, false);
}

void Server::up()
{
    std::clog << "webserv starting\n";
    // for (iter_conf it = configs.begin(); it < configs.end(); ++it) {
    //     std::clog << "\t" << (*it)->get_server_names()
    //         << " at " << (*it)->get_listen() << "\n";
    // }
    // const VServerManager::vs_list_t& serv_list = vs_manager.get_server_list();
    // for (VServerManager::vs_list_t::const_iterator it = serv_list.begin();
    //     it != serv_list.end(); ++it) {
    //     const VServer::sock_map_t& listens = it->get_listens();
    //     for (VServer::sock_map_t::const_iterator it2 = listens.begin(); it2 != listens.end(); ++it2) {
    //         std::clog << "\t" << (*it)->get_server_names()
    //             << " at " << (*it)->get_listen() << "\n";
    //     }
    // }

    int nev;
    for/* ever */(;;) {
        //TODO: set timeout ??
        nev = kevent(kq, changelist.data(), changelist.size(),
                     eventlist.data(), eventlist.size(), NULL);
        changelist.clear();
        if (nev == 0) {
            //TODO: handle timeout error ??
            std::clog << "No events received\n";
            continue;
        }
        else if (nev < 0) {
            std::cerr << "kevent returned error, errno " << errno << ": "
                << strerror(errno) << std::endl;
            //TODO: handle error: free memory, fds...
            continue;
        }
        for (int i = 0; i < nev; ++i) {
            handle_event(eventlist[i]);
        }
    }
}

void Server::handle_event(struct kevent event)
{
    if (event.udata) {
        accept_clients(event);
        return;
    }

    ClientHandler& cl = clients[event.ident];
    int            next = 0;

    try {
        if (event.filter == EVFILT_READ)
            next = cl.process(static_cast<unsigned long>(event.data));
        else if (event.filter == EVFILT_WRITE)
            next = cl.send_response(event.flags);
        update_event(event.ident, event.filter, next);
    } 
    catch (std::exception& e) {
        std::clog << e.what() << " Removing client " << cl.getaddr() << "\n";
        clients.erase(event.ident);
    }
}

void    Server::accept_clients(struct kevent& event)
{
    int                fd;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    socklen_t          addrlen = sizeof(struct sockaddr_in);

    //data contains the size of the listen backlog
    for (int i = 0; i < event.data; ++i) {
        fd = accept(event.ident, (struct sockaddr *)&client_addr, &addrlen);
        if (fd < 0) {
            //TODO: handle errors
            std::clog << "Accept: " << strerror(errno) << "\n";
            continue;
        }
        std::clog << "Client accepted from " << client_addr << "\n";
        if (getsockname(event.ident, (struct sockaddr*)&server_addr, &addrlen)
                == -1) {
            std::clog << "getsockname: " << strerror(errno) << "\n";
            continue;
        }
        add_event(fd, true);
        clients[fd] = ClientHandler(fd, client_addr, server_addr, &vs_manager);
    }
}

void    Server::add_event(int fd, bool client)
{
    struct kevent kev;

    EV_SET(&kev, fd, EVFILT_READ, EV_ADD, 0, 0,
            reinterpret_cast<void*>(client ? 0 : 1));
    changelist.push_back(kev);
    if (client) {
        EV_SET(&kev, fd, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, 0);
        changelist.push_back(kev);
    }
}

void    Server::update_event(int fd, int from, int to)
{
    struct kevent kev;

    EV_SET(&kev, fd, from, EV_DISABLE, 0, 0, 0);
    changelist.push_back(kev);
    EV_SET(&kev, fd, to, EV_ENABLE, 0, 0, 0);
    changelist.push_back(kev);
}
