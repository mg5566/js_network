#include "Event_Handler.hpp"

Event_Handler::Event_Handler() {}

// Event_Handler::Event_Handler(HttpConfig config) : conf(config){
// }

Event_Handler::~Event_Handler() {}

// 아마도 EVFILT_READ 에서 set request message 를 계속 호출할 것으로 예상합니다.
// void Event_Handler::set_request_message(const char *buf) {
// bool Event_Handler::set_request_message(const char *buf) {
bool Event_Handler::append_buffer_to_request_message(const char *buf) {
  // origin_message.clear();
  // telnet 에서는 1개의 message 가 분할되어 올 수 있습니다. 따라서 계속 이어붙입니다.

  // strlen 으로 조건을 확인하면 안된다.
  // if (strlen(buf) == 2)
  if (strlen(buf) == 0)
    return (true);
  origin_message += buf;
  return (false);
}

void Event_Handler::parse_req_msg() {
  parser.run_parsing(request_message, origin_message);
}

void Event_Handler::process_event(std::string &response_message, Request_Message &req_mes, HttpConfig *httpconfig, struct sockaddr_in local_sockaddr_in) {
  std::cout << "process_event" << std::endl;
  origin_message.clear();

  in_port_t port = local_sockaddr_in.sin_port;
  in_addr_t addr = local_sockaddr_in.sin_addr.s_addr;
  LocationConfig *lc = httpconfig->getLocationConfig(port, addr, req_mes.header_map["Host"][0], "/aaa/aaa");
  if (lc == NULL)
    std::cout << "location config is fail" << std::endl;
  // request message 의 method 에 따라 분기를 나눕니다.
  std::string file_name;
  if (req_mes.start_line_map["method"] == "GET") {
    // GET
    // 0. check if file_name exists
    file_name = lc->getUri() + lc->getRoot() + req_mes.start_line_map["URI"];
    std::cout << "test file name : " << file_name << std::endl;
    // start line
    // generator.set_start_line(response_message);
    std::fstream read_file(file_name, std::fstream::in);
    if (!read_file.is_open()) {
      std::cout << "file cannt open" << std::endl;
      // generator.set_error_page();
      return ;
    }
    generator.set_start_line(response_message, 200);
    // headers
    generator.set_headers(response_message, req_mes.header_map);
    // entity body
    generator.set_entity_body(response_message, file_name);

  } else if (req_mes.start_line_map["method"] == "POST") {

  } else if (req_mes.start_line_map["method"] == "DELETE") {

  } else if (req_mes.start_line_map["method"] == "PUT") {

  } else if (req_mes.start_line_map["method"] == "HEAD") {
    // HEAD
    // start line
    // headers

  } else {
    // return error
    std::string file_name = "error_page.html";
    generator.set_entity_body(response_message, file_name);
  }
  generator.set_start_line(response_message, 403);
  generator.set_headers(response_message, req_mes.header_map);

  // in_port_t port = local_sockaddr_in.sin_port;
  // in_addr_t addr = local_sockaddr_in.sin_addr.s_addr;
  // LocationConfig *la = httpconfig->getLocationConfig(port, addr, "127.0.0.1", "/");
  // LocationConfig *la = httpconfig->getLocationConfig(port, addr, req_mes.header_map["Host"][0], req_mes.start_line_map["URI"]);
  /*
  LocationConfig *lc = httpconfig->getLocationConfig(port, addr, req_mes.header_map["Host"][0], "/aaa/aaa");
  if (lc == NULL)
    std::cout << "location config is fail" << std::endl;
  std::cout << "root : " << lc->getRoot() << std::endl;
  std::cout << "URI  : " << lc->getUri() << std::endl;
  std::cout << "req path : " << req_mes.start_line_map["URI"] << std::endl;
  */
  std::string file_name_temp = "error_page.html";
  generator.set_entity_body(response_message, file_name_temp);
}

Request_Message &Event_Handler::get_req_msg() {
  return (request_message);
}

/*
** process methods
*/

void processHeadMethod() {}

void processGetMethod() {

}

void processPostMethod() {

}

void processPutMethod() {}

void processDeleteMethod() {

}

void Event_Handler::test_print_origin_message() {
  std::cout << "test print origin message" << std::endl;
  std::cout << origin_message << std::endl;
}
