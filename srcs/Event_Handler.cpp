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
  std::cout << "strlen : " << strlen(buf) << std::endl;
  if (strlen(buf) == 2)
    return (true);
  origin_message += buf;
  return (false);
}

void Event_Handler::parse_req_msg() {
  parser.run_parsing(request_message, origin_message);
}

// void Event_Handler::process_event(std::string response_message, Request_Message &req_mes, HttpConfig *httpconfig) {
void Event_Handler::process_event(std::string response_message, Request_Message &req_mes, HttpConfig *httpconfig, struct sockadddr_in local_sockaddr_in) {
  // 일단 밖으로 뺏습니다. 아닐 경우 다시 살리세요.
  // 다시 살리면 set_request_message() 에선 clear 를 먼저 해야합니다.
  // 0. client 에게 message 받기
  // set_request_message(buf);

  // 0. config instance 받기, 1번만 setting 하면 되는데, 어찌 처리하는게 좋을까?!
  // if (!config)
  //   set_config(config);

  // 1. message parsing 하기
  // parsing 된 data 는 Request_Message 구조체에 저장합니다.
  // parser.run_parsing(request_message, origin_message);
  // 다 사용한 message 는 지워줍니다.
  origin_message.clear();

  // 2. server side process
    // 0. CGI
    // 1. 그 외 동작

  // 3. response message 생성
  // void gen_res_msg(std::string &res_msg, std::map<std::string, std::vector<std::string> > &header_map, std::string &file_name);
  // generator.gen_res_msg(response_message, req_mes.header_map, req_mes.start_line_map["URL"]);
  LocationConfig *la = httpconfig->getLocationConfig(local_sockaddr_in.);
  generator.set_start_line(response_message);
  generator.set_headers(response_message, req_mes.header_map);
  std::string file_name = "text.txt";
  generator.set_entity_body(response_message, file_name); 

}

Request_Message &Event_Handler::get_req_msg() {
  return (request_message);
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
