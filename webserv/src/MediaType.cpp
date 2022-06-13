#include <MediaType.h>

MediaType::typesMap_t MediaType::types = init_types();
MediaType::typesMap_t MediaType::extnsns = init_exts();

MediaType::typesMap_t MediaType::init_types()
{
    typesMap_t types_;
    
    types_["xml"] = "application/xml";
    types_["pdf"] = "application/pdf";
    types_["rtf"] = "application/rtf";
    types_["zip"] = "application/zip";
    types_["doc"] = "application/msword";
    types_["epub"] = "application/epub+zip";
    types_["gz"] = "application/gzip";
    types_["php"] = "application/x-httpd-php";
    types_["rar"] = "application/vnd.rar";
    types_["tar"] = "application/x-rar";
    
    types_["gif"] = "image/gif";
    types_["jpeg"] = "image/jpeg";
    types_["jpg"] = "image/jpg";
    types_["png"] = "image/png";

    types_["js"] = "text/javascript";
    types_["txt"] = "text/plain";
    types_["csv"] = "text/csv";
    types_["css"] = "text/css";
    types_["html"] = "text/html";
    types_["htm"] = "text/htm";

    return types_;
}

MediaType::typesMap_t MediaType::init_exts()
{
    typesMap_t exts_;
    
    exts_["application/xml"] = "xml";
    exts_["application/pdf"] = "pdf";
    exts_["application/rtf"] = "rtf";
    exts_["application/zip"] = "zip";
    exts_["application/msword"] = "doc";
    exts_["application/epub+zip"] = "epub";
    exts_["application/gzip"] = "gz";
    exts_["application/x-httpd-php"] = "php";
    exts_["application/vnd.rar"] = "rar";
    exts_["application/x-rar"] = "tar";
    
    exts_["image/gif"] = "gif";
    exts_["image/jpeg"] = "jpeg";
    exts_["image/jpg"] = "jpg";
    exts_["image/png"] = "png";

    exts_["text/javascript"] = "js";
    exts_["text/plain"] = "txt";
    exts_["text/csv"] = "csv";
    exts_["text/css"] = "css";
    exts_["text/html"] = "html";
    exts_["text/htm"] = "htm";

    return exts_;
}

const std::string& MediaType::value(const std::string& ext) 
{
    return types[ext];
}

const std::string& MediaType::extension(const std::string& type)
{
    return extnsns[type];
}
