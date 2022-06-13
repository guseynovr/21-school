#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <fstream>

#include <unistd.h>
#include <sys/stat.h>

#include <parser.h>
// #include <Config.hpp>
#include <MediaType.h>
#include <Response.h>
#include <Utils.h>
#include <CGI.h>
#include <Autoindex.h>
#include <VServerManager.h>
#include <VServer.h>

#define BUFF_SIZE 8192

class ClientHandler
{
public:
    ClientHandler();
    ~ClientHandler();
    ClientHandler(int fd, struct sockaddr_in client_addr,
                  struct sockaddr_in server_addr,
                  VServerManager* vsm);

    int  process(unsigned long bytes_available);
    int  send_response(int flags);
    // int  getfd() const;
    struct sockaddr_in getaddr() const;

    ClientHandler& operator=(ClientHandler other);

    class CRLFNotFound: public std::runtime_error
    {
    public:
        CRLFNotFound() : runtime_error("CRLF NotFound") {}
    };

private:

    enum State       { RECEIVE = -1, WRITE = -2, };
    enum BufferState { HEADERS =  1, BODY  =  2, };

    typedef std::vector<char>::iterator      iter_char;
    typedef std::vector<Config*>::iterator   iter_conf;
    typedef void (ClientHandler::*MethodFunc)(const Location* loc);
    typedef std::map<std::string, MethodFunc> MethodMap;

    std::vector<char>  buffer;
    MethodMap          methods;
    Request            request;
    Response           resp;
    struct sockaddr_in sockaddr;
    struct sockaddr_in serv_addr;
    // std::vector<Config*>* configs;
    VServerManager*    vs_manager;
    const VServer*     conf;
    size_t             buff_size;
    size_t             bytes_sent;
    int                pending;
    int                fd;
    State              state;
    BufferState        buff_state;

    void init_methods();
    
    void receive(unsigned long bytes_available);
    void parse_headers();
    void parse_body();

    ClientHandler::iter_char extract_request_str();
    Config* choose_config(const std::string& host, struct sockaddr_in addr);
    void move_buffer_to_start(iter_char req_end);
    bool body_expected(Request& request);
    void clear();

    void exec_method();
    void exec_delete(const Location* loc);
    void exec_post(const Location* loc);
    void exec_get(const Location* loc);
    void redirect(const Location* loc);
    bool exec_cgi(const Location* loc, const std::string& resource_path);

    // Location choose_location(std::string path,
    //                         const std::vector<Location>& locations);
    void check_directory(struct stat& st, std::string& path, const Location* loc);
    void check_file(const std::string& root, std::string& resource_path,
                    struct stat& st);
    void get_file(const std::string& path, Response& resp);
};

#endif //CLIENT_HANDLER_H
