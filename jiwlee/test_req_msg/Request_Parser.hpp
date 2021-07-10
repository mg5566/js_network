#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include "Request_Message.hpp"
#include "Connection.hpp"

#include <iostream>  // test print

class Request_Parser {
  public:
    // Request_Parser(Request_Message &rm, std::string buf);
    Request_Parser();
    ~Request_Parser();

    bool run_parsing(Connection *c);
    std::vector<std::string> split_message(std::string message);

    void parse_start_line(Request_Message &rm, std::string message);
    void parse_header(Request_Message &rm, std::string message);
    void parse_entity(Request_Message &rm, std::string message);
};

std::vector<std::string> split(std::string str, char limiter);
std::vector<std::string> split_value(std::string header, std::string str);

#endif
