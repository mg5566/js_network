#include "Response_Generator.hpp"

Response_Generator::Response_Generator() {}

Response_Generator::~Response_Generator() {}

void Response_Generator::set_status_map() {
  status_map[100] = "Continue";
  status_map[101] = "Switching Protocol";
  status_map[102] = "Processing";
  status_map[103] = "Early Hints";

  status_map[200] = "OK";
  status_map[201] = "Create";
  status_map[202] = "Accepted";
  status_map[203] = "Non-Authoritative Information";
  status_map[204] = "No Content";
  status_map[205] = "Reset Content";
  status_map[206] = "Partial Content";
  status_map[207] = "Multi-Status";
  status_map[208] = "Multi-Status";
  status_map[226] = "IM Used";

  status_map[300] = "Multiple Choice";
  status_map[301] = "Moved Permanently";
  status_map[302] = "Found";
  status_map[303] = "See Other";
  status_map[304] = "Not Modified";
  status_map[305] = "Use Proxy";
  status_map[306] = "unused";
  status_map[307] = "Temporary Redirect";
  status_map[308] = "Permanent Redirect";

  status_map[400] = "Bad Request";
  status_map[401] = "Unauthorized";
  status_map[402] = "Payment Required";
  status_map[403] = "Forbidden";
  status_map[404] = "Not Found";
  status_map[405] = "Method Not Allowed";
  status_map[406] = "Not Acceptable";
  status_map[407] = "Proxy Authentication Required";
  status_map[408] = "Request Timeout";
  status_map[409] = "Conflict";
  status_map[410] = "Gone";
  status_map[411] = "Length Required";
  status_map[412] = "Precondition Failed";
  status_map[413] = "Payload Too Large";
  status_map[414] = "URI Too Long";
  status_map[415] = "Unsupported Media Type";
  status_map[416] = "Requested Range Not Satisfiable";
  status_map[417] = "Expectation Failed";
  status_map[418] = "I'm a teapot";
  status_map[421] = "Misdirected Request";
  status_map[422] = "Unprocessable Entity";
  status_map[423] = "Locked";
  status_map[424] = "Failed Dependency";
  status_map[426] = "Upgrade Required";
  status_map[428] = "Precondition Required";
  status_map[429] = "Too Many Requests";
  status_map[431] = "Request Header Fields Too Large";
  status_map[451] = "Unavailable For Legal Reasons";

  status_map[500] = "Internal Server Error";
  status_map[501] = "Not Implemented";
  status_map[502] = "Bad Gateway";
  status_map[503] = "Service Unavailable";
  status_map[504] = "Gateway Timeout";
  status_map[505] = "HTTP Version Not Supported";
  status_map[506] = "Variant Also Negotiates";
  status_map[507] = "Insufficient Storage";
  status_map[508] = "Loop Detected";
  status_map[510] = "Not Extended";
  status_map[511] = "Network Authentication Required";
}

void Response_Generator::set_start_line(std::string &res_msg, int status_code) {
  res_msg += "HTTP/1.1";
  res_msg += SPACE;
  res_msg += std::to_string(status_code);
  res_msg += SPACE;
  // res_msg += "Forbidden";
  res_msg += status_map[status_code];
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
