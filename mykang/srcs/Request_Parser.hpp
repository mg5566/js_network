#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include "Request_Message.hpp"

#include <iostream>  // test print

class Request_Parser {
  private:
    std::string origin_message;

    std::map<std::string, std::string> start_line_map;
    std::map<std::string, std::vector<std::string> > header_map;
    std::string entity_str;

  public:
    // Request_Parser(Request_Message &rm, std::string buf);
    Request_Parser();
    ~Request_Parser();

    void run_parsing(std::string origin_message);
    std::vector<std::string> split_message(std::string message);
    void parse_start_line(std::string message);
    void parse_header(std::string message);
    void parse_entity(std::string message);

};

std::vector<std::string> split(std::string str, char limiter);
std::vector<std::string> split_value(std::string header, std::string str);

void print_parsed_data(std::map<std::string, std::string> sl, std::map<std::string, std::vector<std::string> > h, std::string e);

#endif