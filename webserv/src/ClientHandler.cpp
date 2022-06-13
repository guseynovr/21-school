#include <ClientHandler.h>

ClientHandler::ClientHandler()
    : buffer(std::vector<char>(BUFF_SIZE)),
      vs_manager(NULL),
      conf(NULL),
      buff_size(0),
      bytes_sent(0),
      pending(0),
      fd(-1),
      state(RECEIVE),
      buff_state(HEADERS)
{
    init_methods();
}

ClientHandler::ClientHandler(int fd, struct sockaddr_in client_addr,
                             struct sockaddr_in server_addr,
                             VServerManager* vsm)
    : buffer(std::vector<char>(BUFF_SIZE)),
      // request(NULL),
      sockaddr(client_addr),
      serv_addr(server_addr),
      vs_manager(vsm),
      conf(NULL),
      buff_size(0),
      bytes_sent(0),
      pending(0),
      fd(fd),
      state(RECEIVE),
      buff_state(HEADERS)
{
    init_methods();
}

void ClientHandler::init_methods()
{
    methods["GET"] = &ClientHandler::exec_get;
    methods["POST"] = &ClientHandler::exec_post;
    methods["DELETE"] = &ClientHandler::exec_delete;
}

ClientHandler::~ClientHandler()
{
    // delete request;
    close(fd);
}

ClientHandler &ClientHandler::operator=(ClientHandler other)
{
    buffer = other.buffer;
    request = other.request;
    resp = other.resp;
    sockaddr = other.sockaddr;
    serv_addr = other.serv_addr;
    // configs = other.configs;
    conf = other.conf; // no need for deep copy, config is not ClientHandler's responsibility
    buff_size = other.buff_size;
    bytes_sent = other.bytes_sent;
    pending = other.pending;
    fd = other.fd;
    state = other.state;
    buff_state = other.buff_state;
    vs_manager = other.vs_manager;

    other.fd = -1; // TLDR; avoid closing active fds;

    return *this;
}

struct sockaddr_in ClientHandler::getaddr() const { return sockaddr; }

void ClientHandler::clear()
{
    bzero(&buffer[buff_size], buffer.size() - buff_size);
    // bzero(&buffer[0], buffer.size());
    // delete request; request = NULL;
    request.clear();
    resp.clear();
    // buff_size = 0;
    bytes_sent = 0;
    pending = 0;
    state = RECEIVE;
    buff_state = HEADERS;
}

int ClientHandler::process(unsigned long bytes_available)
{
    receive(bytes_available);
    try {
        if (state == RECEIVE && buff_state == HEADERS)
            parse_headers();
        if (state == RECEIVE && buff_state == BODY)
            parse_body();
        if (state == WRITE)
            exec_method();
    }
    catch (StatusCode status_code) {
        state = WRITE;
        resp.prepare(conf, conf->get_location(request.target), status_code);
    }
    catch (std::exception &e) {
        resp.prepare(conf, conf->get_location(request.target), Internal_Server_Error);
        state = WRITE;
    }
    return state;
}

void ClientHandler::parse_headers()
{
    iter_char req_end = extract_request_str();
    if (req_end == buffer.end())
        return;
    size_t parsed = parse_request(buffer.data(), request);
    (void)parsed;
    request.parseQuery();
    // LOG
    std::clog << "Received a request from fd(" << fd << ")" << sockaddr << ":\n"
              << "\t"
              << request.method_name << " "
              << request.target << " "
              << request.http_version
              /* << "\n\thost: " << request.host
              << "\n\tcontent-length: " << request.content_length
              << "\n\ttransfer-encoding: " << request.transfer_encoding  */
              << "\n";
    /* for (webserv::http::HeaderMap::iterator it = request.headers.begin();
            it != request.headers.end(); ++it) {
        std::clog << "\t" << it->first << ":" << it->second << "\n";
    } */
    // END LOG
    if (request.http_version != "HTTP/1.1")
        throw HTTP_Version_Not_Supported;
    move_buffer_to_start(req_end);
    bool has_body = body_expected(request);
    conf = &vs_manager->get_server(serv_addr.sin_addr.s_addr,
                                  serv_addr.sin_port,
                                  request.host);
    if (conf == NULL) {
        throw Not_Found;
    }
    const Location *loc = conf->get_location(request.target);
    if (!loc) {
        throw Not_Found;
    }
    if (request.content_length > static_cast<long>(loc->get_client_max_body_size())) {
        // std::cout << "content_length: " << request.content_length << std::endl;
        // std::cout << "max body size: " << loc->get_client_max_body_size() << std::endl;
        throw Payload_Too_Large;
    }
    if (has_body)
        buff_state = BODY;
    else
        state = WRITE;
}

void ClientHandler::parse_body()
{
    if (buff_size == 0)
        return;
    std::vector<std::string>::const_iterator it;
    it = std::find(request.transfer_encoding.begin(),
                   request.transfer_encoding.end(), "chunked");
    bool chunked = it != request.transfer_encoding.end();
    if (!chunked && buff_size < (unsigned long)request.content_length) {
        return;
    }
    if (!chunked) {
        request.body.resize(request.content_length);
        std::memmove(&request.body[0], buffer.data(), request.content_length);
        std::memmove(&buffer[0], &buffer[request.content_length],
                     buff_size - request.content_length);
        buff_size -= request.content_length;
        state = WRITE;
        return;
    }
    bool eof = false;
    // LOG
    // std::printf("buffer: >>%.*s<<\n", pending, &buffer[buff_size - pending]);
    // std::cout << "pending: " << pending << " buff_size: " << buff_size << "\n";
    // std::cout << "full buffer: " << buffer.data() << "\n";
    // END LOG
    int parsed_bytes = parse_chunked_body(
        &buffer[buff_size - pending],
        pending, request, eof);
    if (parsed_bytes == -1)
        throw Bad_Request;
    const Location* loc = conf->get_location(request.target);
    if (!loc) {
        throw Not_Found;
    }
    if (static_cast<size_t>(request.content_length) > loc->get_client_max_body_size())
        throw Payload_Too_Large;
    pending -= parsed_bytes;
    if (!eof)
        return;
    pending = 0;
    std::clog << "Received body:\n" << request.body << "\n";
    state = WRITE;
}

void ClientHandler::receive(unsigned long bytes_available)
{
    // size - 1 => -1 is for the terminating zero
    if (bytes_available > buffer.size() - 1 - buff_size) {
        if (bytes_available - (buffer.size() - 1 - buff_size) < 4096)
            buffer.resize(buffer.size() + 4096);
        else
            buffer.resize(buffer.size() + bytes_available);
    }
    int ret = recv(fd, &buffer[buff_size], bytes_available, 0);
    if (ret == -1) {
        // TODO: remove errno check
        if (errno == EAGAIN)
        {
            std::cerr << "\033[0;31m"
                      << "recv returned with errno " << errno << " EAGAIN: "
                      << strerror(errno) << "\033[0m\n";
        }
        // std::clog << "Client with error: " << fd << "\n";
        throw std::runtime_error(std::string("recv: ") + strerror(errno));
    }
    // TODO: remove bytes_available check later
    if (static_cast<unsigned long>(ret) != bytes_available) {
        std::cerr << "\033[0;31m"
                  << "recv returned different amount of bytes, that kevent predicted"
                  << "\033[0m\n";
    }
    if (ret == 0) {
        throw std::runtime_error(std::string("Client closed the connection."));
    }
    buff_size += ret;
    if (buff_state == BODY)
        pending += ret;
}

void ClientHandler::move_buffer_to_start(iter_char req_end)
{
    if (req_end != buffer.end()) {
        iter_char result = std::copy(req_end,
                                     buffer.begin() + buff_size,
                                     buffer.begin());
        buff_size = result - buffer.begin();
    }
    else {
        buff_size = 0;
    }
    // std::clog << "buff_size after moving=" << buff_size << std::endl;
}

void ClientHandler::exec_method()
{
    const Location *loc = conf->get_location(request.target);

    const std::vector<std::string>& allowed = loc->get_limit_except();
    if (allowed.size() > 0 && std::find(allowed.begin(), allowed.end(), request.method_name)
            == allowed.end())
    {
        std::string allow_value = allowed[0];
        for (std::vector<std::string>::const_iterator it = allowed.begin() + 1;
             it != allowed.end(); ++it)
        {
            allow_value.append(", " + *it);
        }
        resp.add_header("Allow", allow_value);
        throw Method_Not_Allowed;
    }
    if (!loc->get_redirection().text.empty()) {
        redirect(loc);
    }
    else {
        MethodFunc mf = methods[request.method_name];
        (this->*mf)(loc);
    }
}

bool ClientHandler::exec_cgi(const Location* loc, const std::string& resource_path)
{
    (void) loc;
    std::string cgi_key;
    if (resource_path.find(".py") != std::string::npos)
        cgi_key = ".py";
    else if (resource_path.find(".bla") != std::string::npos)
        cgi_key = ".bla";
    else if (resource_path.find(".php") != std::string::npos)
        cgi_key = ".php";
    else {
        return false;
    }
    cgi_key = cgi_key.substr(1);
    const std::string& cgi_path = loc->get_cgi_path(cgi_key);
    if (cgi_path == "")
        return false;
    CGI cgi = CGI(request, resp, cgi_path, resource_path);
    StatusCode scode = cgi.execute();
    if (scode != OK) {
        throw scode;
    }
    resp.prepare(conf, loc, OK);
    return true;
}

void ClientHandler::exec_delete(const Location *loc)
{
    std::string resource_path = loc->get_root() + request.target;
    std::ifstream f(resource_path.c_str());
    if (!f.good()) {
        throw Not_Found;
    }
    if (system(("rm -f " + resource_path).c_str()) == -1) {
        throw Internal_Server_Error;
    }
    resp.prepare(conf, loc, No_Content);
}

void ClientHandler::redirect(const Location* loc)
{
    Redirection r = loc->get_redirection();
    resp.add_header("Location", r.text);
    resp.prepare(conf, loc, static_cast<StatusCode>(r.code));
}

void ClientHandler::exec_post(const Location* loc)
{
    std::clog << "POST URI: " << request.target << "\n";
    std::string resource_path;// = loc.get_root() + request.target;
    struct stat st;
    // std::string resource_path = loc.get_root() + request.target;
    // std::cout << "resource_path=" << resource_path << "\n";
    try {
        check_file(loc->get_root(), resource_path, st);
        check_directory(st, resource_path, loc);
        if (exec_cgi(loc, resource_path)) {
            return;
        }
    }
    catch (StatusCode e) {
        //cgi invalid, create usual file
    }
    static int id = 1;
    std::stringstream id_str;
    id_str << id++;
    // std::clog << "NO CGI\n";
    std::string ext;
    HeaderMap::iterator it_type = request.headers.find("content-type");
    if (it_type != request.headers.end() && MediaType::extension(it_type->second) != "") {
        ext = "." + MediaType::extension(it_type->second);
    }
    std::string filepath = /* resource_path +  */id_str.str() + ext;
    // FIXME: fix filepath, name extension
    if (system(("mkdir -p " + resource_path).c_str()) == -1) {
        throw Internal_Server_Error;
    }
    // std::clog << "POST mkdir: " << resource_path << "\n";
    resp.add_header("Location", request.target + filepath.substr(filepath.find_last_of("/") + 1));
    std::ofstream file;
    std::clog << "POST file: " << filepath << "\n";
    file.open(resource_path + filepath, std::ofstream::out);
    if (!file) {
        std::clog << "here: " << strerror(errno) << std::endl;
        throw Internal_Server_Error;
    }
    file << request.body;
    file.close();
    if (!file) {
        throw Internal_Server_Error;
    }
    resp.add_body(request.body);
    resp.prepare(conf, loc, Created);
}

/* Location ClientHandler::choose_location(std::string path,
const std::vector<Location> &locations)
{
    typedef std::vector<Location>::const_iterator iter_loc;
    Location result;
    size_t longest = 0;

    for (iter_loc it = locations.begin(); it != locations.end(); ++it) {
        std::string loc_path = (*it).get_path();
        if (path.compare(0, loc_path.size(), loc_path) == 0 && longest < loc_path.size())
        {
            result = *it;
            longest = loc_path.size();
            if (result.is_exact())
            {
                return result;
            }
        }
    }
    if (!longest) {
        throw Forbidden;
    }
    return result;
} */

void ClientHandler::exec_get(const Location* loc)
{
    std::string resource_path;
    struct stat st;
    check_file(loc->get_root(), resource_path, st);
    if (S_ISDIR(st.st_mode) && loc->get_autoindex()) {
        // TODO: setup directory catalog html page, save to body
        Autoindex autoindex(resource_path);
        resp.add_body(autoindex.autoIndex(request.target));
        // std::clog << resp.get_body() << std::endl;
        resp.prepare(conf, loc, OK);
        return;
    }
    check_directory(st, resource_path, loc);
    if (!exec_cgi(loc, resource_path)) {
        get_file(resource_path, resp);
    }
    resp.prepare(conf, loc, OK);
}

void ClientHandler::get_file(const std::string& path, Response &resp)
{
    std::ifstream file(path, std::ifstream::in);
    if (!file) {
        std::clog << "failed to open file " << path;
        throw Internal_Server_Error;
    }
    for (std::string line; std::getline(file, line);) {
        resp.add_body(line + "\n");
    }
    resp.add_header("Content-Type", MediaType::value(getFileExtension(path)));
}

void ClientHandler::check_file(const std::string& root, std::string& resource_path,
struct stat& st)
{
    resource_path = root + request.target;
    if (stat(resource_path.c_str(), &st) < 0) {
        switch (errno)
        {
        case ENOENT:
        case ENOTDIR:
            throw Not_Found;
        case ENAMETOOLONG:
            throw URI_Too_Long;
        case EACCES:
            throw Forbidden;
        default:
            throw Internal_Server_Error;
        }
    }
}

void ClientHandler::check_directory(struct stat &st, std::string &path,
const Location* loc)
{
    if (!S_ISDIR(st.st_mode)) {
        return;
    }
    const std::vector<std::string>& indexes = loc->get_indexes();
    std::string index;
    struct stat idx_st;
    std::string delimiter = path[path.size()-1] == '/' ? "" : "/";

    for (std::vector<std::string>::const_iterator it = indexes.begin();
         it != indexes.end(); ++it)
    {
        index = path + delimiter + (*it);
        if ((stat(index.c_str(), &idx_st) == 0) && S_ISREG(idx_st.st_mode)) {
            path = index;
            return;
        }
    }
    throw Forbidden;
}

ClientHandler::iter_char ClientHandler::extract_request_str()
{
    iter_char it;
    char crlf[] = {'\r', '\n', '\r', '\n'};
    char lflf[] = {'\n', '\n'};
    std::vector<char> &buff = buffer;

    it = std::search(buff.begin(), buff.end(), crlf, crlf + 4);
    if (it != buff.end()) { // "\r\n\r\n" not found
        return it + 4;
    }
    it = std::search(buff.begin(), buff.end(), lflf, lflf + 2);
    if (it != buff.end()) { // "\n\n" not found
        return it + 2;
    }
    return it;
}

bool ClientHandler::body_expected(Request &request)
{
    bool has_cl = request.content_length != -1;
    bool has_te = request.transfer_encoding.size() != 0;
    std::vector<std::string> &te = request.transfer_encoding;

    if (request.method_name == "GET") {
        if (has_cl || has_te) 
            throw Bad_Request;
        return false;
    }
    else if (request.method_name == "POST") {
        if (!has_cl && !has_te && std::find(te.begin(), te.end(), "chunked") == te.end())
            throw Length_Required;
        return true;
    }
    else if (request.method_name == "DELETE") {
        if (has_cl || has_te)
            return true;
        return false;
    }
    else {
        throw Not_Implemented;
    }
}

int ClientHandler::send_response(int flags)
{
    std::string response = resp.serialized();

    int ret = send(fd, &response[bytes_sent],
                   response.size() - bytes_sent, 0);
    if (ret == -1) {
        std::stringstream ss;
        ss << "Failed to send: " << strerror(errno);
        throw std::runtime_error(ss.str());
    }
    bytes_sent += ret;
    std::clog << "Response sent to " << sockaddr << "\n";
    if (bytes_sent == response.size())
        clear(); // reset request-dependent fields before next request
    if (flags & 0x8000 /* EV_EOF */) {
        std::stringstream ss;
        ss << "Client " << sockaddr << " disconnected.\n";
        throw std::runtime_error(ss.str());
    }
    if (resp.get_status_code() >= 400) {
        std::stringstream ss;
        ss << "Response with error info sent to " << sockaddr << " .";
        throw std::runtime_error(ss.str());
    }
    return state;
}
