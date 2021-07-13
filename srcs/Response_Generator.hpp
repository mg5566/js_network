#ifndef RESPONSE_GENERATOR_HPP
#define RESPONSE_GENERATOR_HPP

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#define SPACE " "
#define CRLF "\r\n"

class Response_Generator {
  private:
    std::map<int, std::string> status_map;

  public:
    Response_Generator();
    ~Response_Generator();

    void set_status_map();

    // void gen_res_msg(std::string &res_msg, std::map<std::string, std::vector<std::string> > &header_map, std::string &file_name);

    void set_start_line(std::string &res_msg,int status_code);
    void set_headers(std::string &res_msg, std::map<std::string, std::vector<std::string> > &header_map);
    void set_entity_body(std::string &res_msg, std::string &file_name);

    // std::string get_res_msg(void);
    std::string gen_header(std::string key, std::vector<std::string> values);
};

#endif
