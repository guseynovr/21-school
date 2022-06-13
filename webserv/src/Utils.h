#ifndef UTILS_H
#define UTILS_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::ostream& operator << (std::ostream &out, const struct sockaddr_in &c);
bool operator==(const struct sockaddr_in &one, const struct sockaddr_in &two);
std::ostream& operator << (std::ostream &out,
                           const std::vector<std::string>& strs);
std::string getFileExtension(const std::string& path);

#endif //UTILS_H
