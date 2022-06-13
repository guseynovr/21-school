#ifndef CGI_H_
# define CGI_H_

# include <iostream>
# include <map>

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include <Request.h>
# include <Response.h>
# include <Utils.h>

// class Request;

class CGI {
 public:

  CGI(Request &request, Response &response, const std::string& cgi_path, const std::string &file_path);
  ~CGI();

  StatusCode execute();
  bool setCGIEnv();
//  void parseHeaders(std::map<std::string, std::string> &headers);
  std::string &getBody();

 private:
  Request &request_;
  Response &response_;
  std::map<std::string, std::string> req_headers_;
  std::string cgi_path_;
  std::string cgi_exe_;
  std::string extension_;
  std::string cwd_;
  std::string file_path_;
  std::string body_;
  std::string req_body_;
  std::map<std::string, std::string> cgi_env_;
  char **env_;
  char *argv_[3];
};

#endif
