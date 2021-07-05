#include <iostream>
#include <string>  // getline

#include "Event_Handler.hpp"

int main(void) {
    Event_Handler event_handler;
    
    std::string input;

    // input 을 여러번 받아서 시도해보겟습니다.
    // 1번째 입력
    // std::cin >> input;
    getline(std::cin, input);
    // event_handler.set_request_message(input.c_str());
    event_handler.process_event(input.c_str());
    event_handler.test_print_origin_message();
    event_handler.test_print_request_message();

    // 2번째 입력
    input.clear();
    //std::cin >> input;
    getline(std::cin, input);
    // event_handler.set_request_message(input.c_str());
    event_handler.process_event(input.c_str());
    event_handler.test_print_origin_message();
    event_handler.test_print_request_message();
    return (0);
}