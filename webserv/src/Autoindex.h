#ifndef AUTOINDEX_H_
# define AUTOINDEX_H_

# include <iostream>
# include <vector>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <algorithm>

struct auto_listing {
    std::string name_;
    bool is_dir_;
    std::string date_;
    size_t size_;

    auto_listing() : is_dir_(false) {};
};

class Autoindex {
public:
    Autoindex();
    Autoindex(std::string path);
    ~Autoindex();

    std::string autoIndex(std::string &target);
    static std::string unique_char(std::string str);

private:
    std::string path_;
};

#endif //AUTOINDEX_H_
