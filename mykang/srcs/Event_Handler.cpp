#include "Event_Handler.hpp"

Event_Handler::Event_Handler() {
}

Event_Handler::~Event_Handler() {}

void Event_Handler::set_request_message(char *buf) {
  origin_message = buf;
}

void Event_Handler::process_event(char *buf) {
  // 0. client 에게 message 받기
  set_request_message(buf);

  // 1. message parsing 하기
  parser.run_parsing(origin_message);

  // 2. server side process
    // 0. CGI
    // 1. 그 외 동작

  // 3. response message 생성
  // generator.gen_res_msg();
}

/*
std::string Event_Handler::get_response_message() {
    return (response_message);
}
*/