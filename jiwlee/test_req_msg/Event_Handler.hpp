#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <string>
#include <iostream>  // for test print

#include "webserv.hpp"
#include "Request_Parser.hpp"

class Event_Handler {
  private:
    std::string         origin_message;

  public:
    Event_Handler();
    ~Event_Handler();

    bool parse_req_msg(Connection *c);

    void process_event(Connection *c);

    /* test
    ** test 와 debug 를 위해서 print 를 하는 함수들을 작성할 예정입니다.
    */
    void test_print_origin_message();
	void test_print_request_message(Request_Message &request_message);
};

#endif
