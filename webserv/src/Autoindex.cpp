#include <Autoindex.h>

Autoindex::Autoindex() {}

Autoindex::Autoindex(std::string path) : path_(path) {}

Autoindex::~Autoindex() {}

std::string Autoindex::unique_char(std::string str) {
    std::string::iterator it = str.begin();

    while (it != str.end()) {
        if (*it == '/') {
            it++;
            while (it != str.end() && *it == '/') {
                it = str.erase(it);
            }
        }
        else
            it++;
    }
    return str;
}

std::string set_width(size_t width, const std::string& str) {
    size_t len = str.length();
    std::string w;

    if (len > width)
        width = 0;

    for (size_t i = 0; i < width - len; i++) {
        w += " ";
    }
    w += str;
    return w;
}

bool sort_auto_listing(const auto_listing& i, const auto_listing& j) {
    if (i.is_dir_ && j.is_dir_)
        return (i.name_ < j.name_);
    if (!i.is_dir_ && !j.is_dir_)
        return (i.name_ < j.name_);
    return (i.is_dir_ > j.is_dir_);
}

std::string Autoindex::autoIndex(std::string &target) {
    std::string body;
    struct tm	*tm;
    char buf[32];
    DIR *dir;
    struct stat statbuf;
    struct dirent *ent;

    dir = opendir(path_.c_str());
    body += "<html>\r\n";
    body += "<head><title>Index of " + target + "</title></head>\r\n";
    body += "<body>\r\n";
    body += "<h1>Index of " + target + "</h1><hr><pre>";
    std::vector<auto_listing> listing;

    readdir(dir);
    while ((ent = readdir(dir))) {
        auto_listing li;

        li.name_ = ent->d_name;
        if (li.name_.length() > 50) {
            li.name_.erase(47);
            li.name_ += "..>";
        }
        std::string path(path_ + "/" + ent->d_name);
        stat(path.c_str(), &statbuf);

        if (S_ISDIR(statbuf.st_mode)) {
            li.is_dir_ = true;
            li.name_ += "/";
        }

        tm = gmtime(&statbuf.st_mtime);
        int ret = strftime(buf, 32, "%d-%b-%Y %H:%M", tm);
        li.date_ = std::string(buf, ret);
        li.size_ = statbuf.st_size;
        listing.push_back(li);
    }

    std::sort(listing.begin(), listing.end(), sort_auto_listing);

    for (std::vector<auto_listing>::iterator it = listing.begin(); it != listing.end(); it++) {
        body = body + "<a href=\"" + unique_char(target + + "/" + it->name_) + "\">" + it->name_ + "</a>";
        if (it != listing.begin()) {
            body += set_width(68 - it->name_.length(), it->date_);
            if (it->is_dir_)
                body += set_width(20, "-");
            else
                body += set_width(20, std::to_string(it->size_));
        }
        body += "\r\n";
    }

    body += "</pre><hr></body>\r\n";
    body += "</html>\r\n";
    closedir(dir);
    return body;
}

/* int main()
{
    std::string target = "target";
    std::string body;
    std::string resource_path = ".";
    Autoindex autoindex(resource_path);
    body = autoindex.autoIndex(target);
    std::cout << body << std::endl;
    return 1;
} */
