#include <CGI.h>

std::string getContent(int fd_) {
	std::string final;
	char buf[4096 + 1];
	int ret;

	lseek(fd_, 0, SEEK_SET);
	while ((ret = read(fd_, buf, 4096)) != 0) {
		if (ret == -1) {
			return "";
		}
		buf[ret] = '\0';
		final.insert(final.length(), buf, ret);
	}
	return final;
};

CGI::CGI(Request &request, Response &response, const std::string& cgi_path, const std::string &file_path)
    : request_(request),
	  response_(response),
	  cgi_path_(cgi_path),
	  file_path_(file_path) {

    extension_ = getFileExtension(file_path);
	req_body_ = request.body;
	req_headers_ = request.headers;
}


CGI::~CGI() {
  free(argv_[0]);
  free(argv_[1]);
//  if (env_)
//    ft::free_tab(env_);
}

StatusCode CGI::execute() {

  if (!setCGIEnv())
    return Internal_Server_Error;
  if (!(argv_[0] = strdup(cgi_path_.c_str())))
    return Internal_Server_Error;
  if (!(argv_[1] = strdup(file_path_.c_str())))
    return Internal_Server_Error;
  argv_[2] = NULL;

  int pip[2];

  if (pipe(pip) != 0)
    return Internal_Server_Error;

  pid_t pid = fork();

  if (pid == 0) {
    if (dup2(pip[0], 0) == -1)
		return Internal_Server_Error;
	if (dup2(pip[1], 1) == -1)
	  return Internal_Server_Error;
	close(pip[1]);
    close(pip[0]);
    execve(argv_[0], argv_, env_);
    std::cerr << strerror(errno) << std::endl;
    exit(1);
  }
  else if (pid > 0) {
	if (req_body_.length() && write(pip[1], req_body_.c_str(), req_body_.length()) <= 0)
		return Internal_Server_Error;
	close(pip[1]);
    int status;
    if (waitpid(pid, &status, 0) == -1)
      return Internal_Server_Error;
	if (WIFEXITED(status) && WEXITSTATUS(status))
      return Bad_Gateway;
  }
  else {
    return Bad_Gateway;
  }
  body_ = getContent(pip[0]);
  close(pip[0]);
  response_.add_body(body_);

  return OK;
}

//void CGI::parseHeaders(std::map<std::string, std::string> &headers) {
//  size_t end, last;
//  std::string header;
//
//  while ((end = body_.find("\r\n")) != std::string::npos) {
//    if (body_.find("\r\n") == 0) {
//      body_.erase(0, end + 2);
//      break;
//    }
//    if ((last = body_.find(':', 0)) != std::string::npos) {
//      header = body_.substr(0, last);
//      headers[header] = ft::trim_left(body_.substr(last + 1, end - last - 1), ' ');
//    }
//    body_.erase(0, end + 2);
//  }
//  if (headers.count("Content-Length")) {
//    size_t size = ft::stoi(headers["Content-Length"]);
//
//    body_.erase(size);
//  }
//}

bool CGI::setCGIEnv() {
  if (request_.method_name == "POST") {
    cgi_env_["CONTENT_TYPE"] = req_headers_["Content-Type"];
    cgi_env_["CONTENT_LENGTH"] = std::to_string(req_body_.length());
  }
  cgi_env_["GATEWAY_INTERFACE"] = "CGI/1.1";
  cgi_env_["PATH_INFO"] = file_path_;
  cgi_env_["PATH_TRANSLATED"] = file_path_;
  cgi_env_["QUERY_STRING"] = request_.query_str;
  cgi_env_["REMOTE_ADDR"] = request_.host;

  cgi_env_["REQUEST_METHOD"] = request_.method_name;
  cgi_env_["REQUEST_URI"] = file_path_;

  cgi_env_["SCRIPT_NAME"] = cgi_path_;
  cgi_env_["SERVER_NAME"] = request_.host;
  cgi_env_["SERVER_PROTOCOL"] = request_.http_version;
  cgi_env_["SERVER_PORT"] = request_.host;
  cgi_env_["SERVER_SOFTWARE"] = "WEBSERV/1.0";
  cgi_env_["HTTP_HOST"] = request_.host;

  if (extension_ == "php")
    cgi_env_["REDIRECT_STATUS"] = "200";

  for (std::map<std::string, std::string>::iterator it = req_headers_.begin(); it != req_headers_.end(); it++) {
    if (!it->second.empty()) {
      std::string header = "HTTP_" + it->first;
      std::replace(header.begin(), header.end(), '-', '_');
      cgi_env_[header] = it->second;
    }
  }

	if (!(env_ = (char **)malloc(sizeof(char *) * (cgi_env_.size() + 1))))
		return false;

	int i = 0;

	for (std::map<std::string, std::string>::iterator it = cgi_env_.begin(); it != cgi_env_.end(); it++) {
		std::string tmp = it->first + "=" + it->second;
		if (!(env_[i] = strdup(tmp.c_str())))
      return false;
		i++;
	}
	env_[i] = NULL;
  return true;
}
//
//int main()
//{
//    std::string cgi_path = "/home/bulat/school21/ft_webserv/php-cgi_ubuntu";
//    std::string resource_path = "/home/bulat/school21/ft_webserv/www/hills/index.php";
//    // std::string cgi_path = "/usr/bin/php";
//    Response resp;
//    Request request;
//    CGI cgi = CGI(request, resp, cgi_path, resource_path);
//    if (!cgi.execute()) {
//        return false;
//    }
////    resp.prepare(conf, OK);
//    std::cerr << resp.get_body() << std::endl;
//    return 1;
//}
