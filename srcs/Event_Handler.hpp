#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <string>
#include <iostream>  // for test print
#include <sys/socket.h>  // struct sockaddr_in

#include "Request_Message.hpp"
#include "Request_Parser.hpp"
#include "Response_Generator.hpp"
#include "HttpConfig.hpp"

class Event_Handler {
  private:
    std::string         origin_message;
    Request_Message     request_message;
    Request_Parser      parser;
    // 향후 구현 예정입니다.
    std::string         response_message;
    Response_Generator  generator;

    // 향후 nginx config 를 받을 변수
    // HttpConfig config;
  public:
    Event_Handler();
    // 향후 nginx config file 을 인자로 받을 수 있도록 합니다.
    // Event_Handler(HttpConfig config);
    ~Event_Handler();

    // set req msg
    // void set_request_message(char *buf);
    // bool set_request_message(const char *buf);
    bool append_buffer_to_request_message(const char *buf);

    // set nginx config
    // void set_http_config(HttpConfig &config);

    // request_message 를 parsing 합니다.
    void parse_req_msg();

    // get 혹은 post 를 위한 file open

    // 발생된 event 를 처리합니다.
    // void process_event();
    void process_event(std::string response_message, Request_Message &req_mes, HttpConfig *httpconfig, struct sockadddr_in local_sockaddr_in);

    Request_Message &get_req_msg();

    /* test
    ** test 와 debug 를 위해서 print 를 하는 함수들을 작성할 예정입니다.
    */
    void test_print_origin_message();
    void test_print_request_message();
};

#endif
