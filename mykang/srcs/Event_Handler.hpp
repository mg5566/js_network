#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <string>

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
  public:
    Event_Handler();
    ~Event_Handler();

    // set req msg
    void set_request_message(char *buf);

    // 발생된 event 를 처리합니다.
    void process_event(char *buf);

    // get response message
    // std::string get_response_message();
};

#endif