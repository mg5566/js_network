#ifndef REQUEST_MESSAGE_HPP
#define REQUEST_MESSAGE_HPP

#include <map>
#include <string>
#include <vector>

struct Request_Message {
	bool		start_line_complete;
	bool		header_map_complete;
	bool		entity_body_str_complete;

    std::map<std::string, std::string> start_line_map;
    std::map<std::string, std::vector<std::string> > header_map;
    std::string entity_body_str;
};

#endif
