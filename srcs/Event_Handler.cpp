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
  if (strlen(buf) == 2)
    return (true);
  origin_message += buf;
  return (false);
}

void Event_Handler::parse_req_msg() {
  parser.run_parsing(request_message, origin_message);
}

void Event_Handler::process_event(std::string &response_message, Request_Message &req_mes, HttpConfig *httpconfig, struct sockaddr_in local_sockaddr_in) {
  origin_message.clear();

  generator.set_start_line(response_message);
  generator.set_headers(response_message, req_mes.header_map);
  /*
  LocationConfig* location2 = config->getLocationConfig(port2, ip_addr2, server_name2, request_uri2);

  if (location2 == NULL){
		std::cout << "location2 is null" << std::endl;
	}
	else{
		location2->print_status_for_debug("\t");
		std::cout << "\t" << location2->checkAcceptedMethod("PUT") << std::endl;
	}
  */
  in_port_t port = local_sockaddr_in.sin_port;
  in_addr_t addr = local_sockaddr_in.sin_addr.s_addr;
  // LocationConfig *la = httpconfig->getLocationConfig(port, addr, "localhost", req_mes.start_line_map["URI"]);
  // LocationConfig *la = httpconfig->getLocationConfig(port, addr, "localhost", "/");
  LocationConfig *la = httpconfig->getLocationConfig(port, addr, "127.0.0.1", "/");
  if (la == NULL) {
    std::cout << "location config is fail" << std::endl;
  }
  std::string file_name = "error_page.html";
  // std::cout << "port is " << port << std::endl;
  // std::cout << "port is " << htons(port) << std::endl;
  // std::cout << "addr is " << addr << std::endl;
  generator.set_entity_body(response_message, file_name);
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
