#include <Response.h>

Response::ReasonPhraseMap Response::reasons = init_reasons();

Response::Response()
    : status_code(Processing)
{
}

void Response::set_status_code(StatusCode& status)
{
    status_code = status;
}

StatusCode Response::get_status_code() const
{
    return status_code;
}

std::string& Response::serialized()
{
    return resp_str;
}

void Response::clear()
{
    headers.clear();
    body.clear();
    http_version.clear();
    reason_phrase.clear();
    resp_str.clear();
}

void Response::prepare(const VServer* conf, const Location* loc, StatusCode status)
{
    (void) conf;
    http_version = "HTTP/1.1";
    status_code = status;
    reason_phrase = reasons[status];
    if (status_code != Internal_Server_Error) {
        try {
            headers["Date"] = date_header();
        } catch (StatusCode new_status) {
            status_code = new_status;
        }
    }
    if (status_code >= 400) {
        prepare_error_body(get_error_path(loc));
    }
    std::stringstream strstr;
    strstr << body.size() + 2;
    headers["Content-length"] = strstr.str();
    headers["Server"] = "webserv42";
    assemble_response();
}

void Response::assemble_response()
{
    size_t len = http_version.size() + 5 + reason_phrase.size() + 2; //" 200 ".len = 5
    for (HeaderMap::iterator it = headers.begin(); it != headers.end(); ++it) {
        len += it->first.size() + it->second.size() + 4; // '\r\n' + ": "
    }
    len += 2 + body.size() + 2;

    resp_str.reserve(len);
    std::stringstream ss;
    ss << status_code;
    resp_str = http_version + " " + ss.str() + " " + reason_phrase + "\r\n";
    for (HeaderMap::iterator it = headers.begin(); it != headers.end(); ++it) {
        resp_str += it->first + ": " + it->second + "\r\n";
    }
    resp_str += "\r\n" + body + "\r\n";
    // std::clog << "body(" << body.size() << "): " << body << "<<end\n";
}

void Response::add_body(const std::string& str) { body.append(str); }

const std::string& Response::get_body() const { return body; };

std::string Response::get_error_path(const Location* loc)
{
    if (loc == NULL) {
        // std::cout << "NULL\n";
        return std::string();
    }
    std::string error_page = loc->get_error_page(status_code);
    return error_page;
}

void Response::prepare_error_body(const std::string& path)
{
    // std::cout << "path: " << path << std::endl;
    if (path != "") {
        get_file(path);
    }
    // if (path == "") {
    else {
            std::stringstream strs; 
            strs << "<!DOCTYPE html><html><body><center><h1>"
                << status_code << " " << reason_phrase
                << "</h1></center></body></html>";
            body = strs.str();
    }
    headers["Content-type"] = std::string("text/html");
}

void Response::get_file(const std::string& path)
{
    std::ifstream file(path, std::ifstream::in);
    if (!file) {
        std::clog << "failed to open file " << path;
        throw Internal_Server_Error;
    }
    for (std::string line; std::getline(file, line);) {
        add_body(line + "\n");
    }
    add_header("Content-Type", MediaType::value(getFileExtension(path)));
}

void Response::add_header(const std::string& name, const std::string& value)
{
    headers[name] = value;
}

std::string Response::date_header()
{
    time_t      rawtime = time(NULL);
    struct tm*  gmt_time = gmtime(&rawtime);
    const char* fmt = "%a, %d %b %y %T GMT";
    char        out[200];

    if (!gmt_time) {
        std::clog << "gmt_time: " << strerror(errno) << "\n";
        throw Internal_Server_Error;
    }
    if (strftime(out, 200, fmt, gmt_time) == 0) {
        std::clog << "strftime returned 0\n";
        throw Internal_Server_Error;
    }
    return std::string(out);
}

Response::ReasonPhraseMap Response::init_reasons()
{
    ReasonPhraseMap reasons_;

    reasons_[Continue] = "Continue";
    reasons_[Switching_protocols] = "Switching protocols";
    reasons_[Processing] = "Processing";
    reasons_[Early_Hints] = "Early Hints";
    reasons_[OK] = "OK";
    reasons_[Created] = "Created";
    reasons_[Accepted] = "Accepted";
    reasons_[Non_Authoritative_Information] = "Non Authoritative Information";
    reasons_[No_Content] = "No Content";
    reasons_[Reset_Content] = "Reset Content";
    reasons_[Partial_Content] = "Partial Content";
    reasons_[Multi_Status] = "Multi Status";
    reasons_[Already_Reported] = "Already Reported";
    reasons_[IM_Used] = "IM Used";
    reasons_[Multiple_Choices] = "Multiple Choices";
    reasons_[Moved_Permanently] = "Moved Permanently";
    reasons_[Found] = "Found";
    reasons_[See_Other] = "See Other";
    reasons_[Not_Modified] = "Not Modified";
    reasons_[Use_Proxy] = "Use Proxy";
    reasons_[Switch_Proxy] = "Switch Proxy";
    reasons_[Temporary_Redirect] = "Temporary Redirect";
    reasons_[Permanent_Redirect] = "Permanent Redirect";
    reasons_[Bad_Request] = "Bad Request";
    reasons_[Unauthorized] = "Unauthorized";
    reasons_[Payment_Required] = "Payment Required";
    reasons_[Forbidden] = "Forbidden";
    reasons_[Not_Found] = "Not Found";
    reasons_[Method_Not_Allowed] = "Method Not Allowed";
    reasons_[Not_Acceptable] = "Not Acceptable";
    reasons_[Proxy_Authentication_Required] = "Proxy Authentication Required";
    reasons_[Request_Timeout] = "Request Timeout";
    reasons_[Conflict] = "Conflict";
    reasons_[Gone] = "Gone";
    reasons_[Length_Required] = "Length Required";
    reasons_[Precondition_Failed] = "Precondition Failed";
    reasons_[Payload_Too_Large] = "Payload Too Large";
    reasons_[URI_Too_Long] = "URI Too Long";
    reasons_[Unsupported_Media_Type] = "Unsupported Media Type";
    reasons_[Range_Not_Satisfiable] = "Range Not Satisfiable";
    reasons_[Expectation_Failed] = "Expectation Failed";
    reasons_[Im_a_Teapot] = "Im a Teapot";
    reasons_[Misdirected_Request] = "Misdirected_ equest";
    reasons_[Unprocessable_Entity] = "Unprocessable Entity";
    reasons_[Locked] = "Locked";
    reasons_[Failed_Dependency] = "Failed Dependency";
    reasons_[Too_Early] = "Too Early";
    reasons_[Upgrade_Required] = "Upgrade Required";
    reasons_[Precondition_Required] = "Precondition Required";
    reasons_[Too_Many_Requests] = "Too Many Requests";
    reasons_[Request_Header_Fields_Too_Large] = "Request Header Fields Too Large";
    reasons_[Unavailable_or_Legal_Reasons] = "Unavailable or Legal Reasons";
    reasons_[Internal_Server_Error] = "Internal Server Error";
    reasons_[Not_Implemented] = "Not Implemented";
    reasons_[Bad_Gateway] = "Bad Gateway";
    reasons_[Service_Unavailable] = "Service Unavailable";
    reasons_[Gateway_Timeout] = "Gateway Timeout";
    reasons_[HTTP_Version_Not_Supported] = "HTTP Version Not Supported";
    reasons_[Variant_Also_Negotiates] = "Variant Also Negotiates";
    reasons_[Insufficient_Storage] = "Insufficient Storage";
    reasons_[Loop_Detected] = "Loop Detected";
    reasons_[Not_Extended] = "Not Extended";
    reasons_[Network_Authentication_Required] = "Network Authentication Required";

    return reasons_;
}
