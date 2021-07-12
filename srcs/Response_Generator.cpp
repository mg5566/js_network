#include "Response_Generator.hpp"

Response_Generator::Response_Generator() {}

Response_Generator::~Response_Generator() {}

void Response_Generator::set_start_line(std::string &res_msg) {
  res_msg += "HTTP/1.1";
  res_msg += SPACE;
  res_msg += std::to_string(403);
  res_msg += SPACE;
  res_msg += "Forbidden";
  res_msg += CRLF;
}

void Response_Generator::set_headers(std::string &res_msg, std::map<std::string, std::vector<std::string> > &header_map) {
  std::map<std::string, std::vector<std::string> >::iterator map_it = header_map.begin();
  for (; map_it != header_map.end(); ++map_it) {
    res_msg += gen_header(map_it->first, map_it->second);
  }
}

std::string Response_Generator::gen_header(std::string key, std::vector<std::string> values) {
  std::string header;

  header += key;
  header += SPACE;
  header += ":";
  header += SPACE;

  std::vector<std::string>::iterator it = values.begin();
  for (; it != values.end(); ++it)
    header += *it;
  header += CRLF;
  return (header);
}

void Response_Generator::set_entity_body(std::string &res_msg, std::string &file_name) {
  res_msg += CRLF;
  std::fstream read_file(file_name.data());
  if (!read_file.is_open()) {
    std::cout << "occured error : is not opened " << file_name << std::endl;
    return ;
  }
  std::string str;
  while (getline(read_file, str)) {
    res_msg += str;
    res_msg += "\n";
   }
  read_file.close();
}
