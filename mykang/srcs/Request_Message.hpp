#ifndef REQUEST_MESSAGE_HPP
#define REQUEST_MESSAGE_HPP

#include <map>
#include <string>
#include <vector>

struct Request_Message {
    std::map<std::string, std::string> start_line_map;
    std::map<std::string, std::vector<std::string> > header_map;
    std::string entity_body_str;
};

#endif