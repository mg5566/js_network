#include "Event_Handler.hpp"

Event_Handler::Event_Handler() {
}

// Event_Handler::Event_Handler(HttpConfig *config) : conf(config){
// }

Event_Handler::~Event_Handler() {}

void Event_Handler::set_request_message(char *buf) {
  origin_message.clear();
  origin_message = buf;
}

void Event_Handler::set_request_message(const char *buf) {
  origin_message.clear();
  origin_message = buf;
}

void Event_Handler::process_event(char *buf) {
  // 0. client 에게 message 받기
  set_request_message(buf);

  // 1. message parsing 하기
  // parsing 된 data 는 Request_Message 구조체에 저장합니다.
  parser.run_parsing(request_message, origin_message);

  // 2. server side process
    // 0. CGI
    // 1. 그 외 동작

  // 3. response message 생성
  // generator.gen_res_msg();
}

void Event_Handler::process_event(const char *buf) {
  set_request_message(buf);

  parser.run_parsing(request_message, origin_message);
}

void Event_Handler::test_print_request_message() {
  std::cout << "test print parsed reuqest message" <<std::endl;
  std::cout << "====start line map====" << std::endl;
  for (std::map<std::string, std::string>::iterator it = request_message.start_line_map.begin();
  it != request_message.start_line_map.end(); ++it) {
    std::cout << it->first << " : " << it->second << std::endl;
  }
  std::cout << "======header map======" << std::endl;
  for (std::map<std::string, std::vector<std::string> >::iterator it = request_message.header_map.begin();
  it != request_message.header_map.end(); ++it) {
    std::cout << it->first << " : ";
    for (std::vector<std::string>::iterator v_it = it->second.begin();
    v_it != it->second.end(); ++v_it) {
      std::cout << *v_it << "|";
    }
    std::cout << std::endl;
  }
  std::cout << "=====entity body======" << std::endl;
  std::cout << request_message.entity_body_str << std::endl;
}

void Event_Handler::test_print_origin_message() {
  std::cout << "test print origin message" << std::endl;
  std::cout << origin_message << std::endl;
}
