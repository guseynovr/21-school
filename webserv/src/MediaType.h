#ifndef MEDIA_TYPE_H
#define MEDIA_TYPE_H

#include <string>
#include <map>

class MediaType
{
    typedef std::map<std::string, std::string> typesMap_t;

public:
    static const std::string& value(const std::string&);
    static const std::string& extension(const std::string&);

private:
    static typesMap_t types;
    static typesMap_t extnsns;
    static typesMap_t init_types();
    static typesMap_t init_exts();

    MediaType();
    ~MediaType();
};

#endif //MEDIA_TYPE_H
