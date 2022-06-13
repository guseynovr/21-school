#include <Server.h>

int main(int argc, char **argv, char **env)
{
    (void) argc;
    (void) argv;
    (void) env;
    std::string path;
    if (argc == 1) {
        path = DEFAULT_CONF_PATH;
    }
    else if (argc == 2) {
        path = argv[1];
    }
    else {
        std::cout << "Usage: ./webserv [path_to_config]";
    }

    Server	server;
    try {
        server.init(path);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    server.up();
}
