#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <string>
#include <iostream>  // for test print

#include "Request_Message.hpp"
#include "Request_Parser.hpp"

class Event_Handler {
  private:
    std::string         origin_message;
    Request_Message     request_message;
    Request_Parser      parser;
    // 향후 구현 예정입니다.
    // std::string         response_message;
    // Response_Generator  generator;

    // 향후 nginx config 를 받을 변수
    // HttpConfig config;
  public:
    Event_Handler();
    // 향후 nginx config file 을 인자로 받을 수 있도록 합니다.
    // Event_Handler(HttpConfig config);
    ~Event_Handler();

    // set req msg
    void set_request_message(char *buf);
    void set_request_message(const char *buf);

    // set nginx config
    // void set_http_config(HttpConfig &config);

    // 발생된 event 를 처리합니다.
    void process_event(char *buf);
    void process_event(const char *buf);

    /* test
    ** test 와 debug 를 위해서 print 를 하는 함수들을 작성할 예정입니다.
    */
    void test_print_origin_message();
    void test_print_request_message();
};

#endif