#include "Request_Parser.hpp"

Request_Parser::Request_Parser() {
}

Request_Parser::~Request_Parser() {
}

void Request_Parser::run_parsing(Request_Message &rm, std::string origin_message) {
  // std::cout << "===test print origin message===" << std::endl;
  // std::cout << origin_message << std::endl;

  std::vector<std::string> message_vector;

  message_vector = split_message(origin_message);  // start / header / body
  /*
  parse_start_line(message_vector[0]);
  parse_header(message_vector[1]);
  parse_entity(message_vector[2]);
  */
  parse_start_line(rm, message_vector[0]);
  parse_header(rm, message_vector[1]);
  parse_entity(rm, message_vector[2]);
}

std::vector<std::string> Request_Parser::split_message(std::string message) {
  std::vector<std::string> temp;

  // find 후 substr 을 사용하여 request message 를 split 합니다.
  // erase 를 사용하지 않았지만 sequence erase 를 사용하여 지우고 다시 find 하는 방법도 있습니다.
  std::size_t line_end_pos = message.find("\r\n");
  temp.push_back(message.substr(0, line_end_pos));
  // line_end_pos 에 +2 를 해야 \r\n(start line 과 head 의 구분문자열) 을 피할 수 있습니다.
  message.erase(0, line_end_pos + 2);
  std::size_t head_end_pos = message.find("\r\n\r\n");
  temp.push_back(message.substr(0, head_end_pos));
  // std::cout << "test headers" << std::endl;
  // std::cout << message.substr(0 , head_end_pos) << std::endl;
  //std::cout << "entity_end_pos : " << message.length() << std::endl;
  // head_end_pos 에 +4 를 해야 \r\n\r\n(head 와 entity 의 구분문자열) 을 피할 수 있습니다.
  // test entity body
  // std::cout << "test entity body" << std::endl;
  // std::cout << message.substr(head_end_pos + 4, message.length()) << std::endl;
  temp.push_back(message.substr(head_end_pos + 4, message.length()));
  return (temp);
}

/*
split 된 message 를 parsing 합니다.
*/
// GET /index.html HTTP/1.1crlf
void Request_Parser::parse_start_line(Request_Message &rm, std::string message) {
  // parsing 된 data 는 member variable start_line_map 에 key(string), value(string) 형식으로 저장합니다.
  // find 로 space 를 찾고 method 를 저장한다음 method + space 를 지우고 다음을 parsing 합니다.
  std::size_t method_pos = message.find(" ");
  rm.start_line_map["method"] = message.substr(0, method_pos);
  // method position 에 +1 을 해서 space 까지 지워줍니다.
  message.erase(0, method_pos + 1);
  std::size_t uri_pos = message.find(" ");
  rm.start_line_map["URI"] = message.substr(0, uri_pos);
  message.erase(0, uri_pos + 1);
  std::size_t version_pos = message.find("\r\n");
  rm.start_line_map["version"] = message.substr(0, version_pos);
}

// Accept-Charsets: value_1(,) value_2crlf
// Accept-Length: value_1(,) value_2crlf
// crlf
//
void Request_Parser::parse_header(Request_Message &rm, std::string message) {
  std::size_t colon_pos = message.find(":");
  while (colon_pos != message.npos) {
    std::string header = message.substr(0, colon_pos);
    message.erase(0, colon_pos + 2);
    std::size_t end_pos = message.find("\r\n");
    std::vector<std::string> vector = split_value(header, message.substr(0, end_pos));
    message.erase(0, end_pos + 2);
    rm.header_map[header] = vector;
    colon_pos = message.find(":");
  }
  // 위 방식이 잘된다면 colon_pos 가 npos 가 될때까지 loop 를 해보자
}

// entity body 가 포함된 데이터를 보내서 확인해봐야합니다.
void Request_Parser::parse_entity(Request_Message &rm, std::string message) {
  rm.entity_body_str = message;
}

/* header 의 value 를 split 하는 함수
**
** value 는 통일된 format 이 아니라서 ',' or ' ' 을 기준으로 split 할 수 없습니다.
** key 마다 다르게 split 을 진행하겠습니다.
*/
std::vector<std::string> split_value(std::string header, std::string str) {
  // 0. 올바른 header 를 찾습니다.
  // 1. header 에 따라 split 을 다르게 합니다.
  //  - 1개의 value 만 있는 경우
  //  - ',' 을 기준으로 여러 value 가 존재하는 경우가 있고
  // 2. split 결과를 temp vector 에 저장하고, 반환합니다.

  // declare return value
  std::vector<std::string> temp;
  // 0. 올바른 header 찾기
  if (header == "Accept-Charsets")
    temp = split(str, ',');
  else if (header == "Accept-Language")
    temp = split(str, ',');
  else if (header == "Authorization")
    temp = split(str, ' ');
  else if (header == "Host")
    temp.push_back(str);
  else if (header == "User-Agent")
    temp.push_back(str);
  else if (header == "Referer")
    temp.push_back(str);
  else if (header == "Content-Language")
    temp = split(str, ',');
  else if (header == "Content-Length")
    temp.push_back(str);
  else if (header == "Content-Type")
    temp = split(str, ';');
  else if (header == "Data")
    temp.push_back(str);  // data format 이 있긴한데, 언제 사용할지 모르겠습니다. 일단 1개로 간주합니다.
  return (temp);
}

std::vector<std::string> split(std::string str, char limiter) {
  std::vector<std::string> temp;

  std::size_t prev_pos;
  std::size_t pos = str.find(limiter);
  if (pos == str.npos)
    temp.push_back(str.substr(0, str.length()));
  else if (limiter == ' ') {
    while (pos != str.npos) {
      temp.push_back(str.substr(0, pos));
      // " " 을 지나치기 위해서 +1 합니다.
      prev_pos = pos + 1;
      str.erase(0, prev_pos);
      pos = str.find(limiter, prev_pos);
    }
  } else {
    while (pos != str.npos) {
      temp.push_back(str.substr(0, pos));
      // "<limiter> " 을 지나치기 위해서 +2 합니다.
      prev_pos = pos + 2;
      str.erase(0, prev_pos);
      pos = str.find(limiter, prev_pos);
    }
  }
  return (temp);
}
