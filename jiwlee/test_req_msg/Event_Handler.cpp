#include "Event_Handler.hpp"

Event_Handler::Event_Handler() {}

Event_Handler::~Event_Handler() {}

bool	Event_Handler::parse_req_msg(Connection *c) {
	Request_Parser      parser;

	return parser.run_parsing(c);
}

void Event_Handler::process_event(Connection *c) {
	c->get_request_message().start_line_complete = false;
	c->get_request_message().header_map_complete = false;
	c->get_request_message().entity_body_str_complete = false;

	c->get_request_message().start_line_map.clear();
	c->get_request_message().header_map.clear();
	c->get_request_message().entity_body_str.clear();
}

// void Event_Handler::test_print_request_message(Request_Message &request_message) {
//   std::cout << "test print parsed reuqest message" <<std::endl;
//   std::cout << "====start line map====" << std::endl;
//   for (std::map<std::string, std::string>::iterator it = request_message.start_line_map.begin();
//   it != request_message.start_line_map.end(); ++it) {
//     std::cout << it->first << " : " << it->second << std::endl;
//   }
//   std::cout << "======header map======" << std::endl;
//   for (std::map<std::string, std::vector<std::string> >::iterator it = request_message.header_map.begin();
//   it != request_message.header_map.end(); ++it) {
//     std::cout << it->first << " : ";
//     for (std::vector<std::string>::iterator v_it = it->second.begin();
//     v_it != it->second.end(); ++v_it) {
//       std::cout << *v_it << "|";
//     }
//     std::cout << std::endl;
//   }
//   std::cout << "=====entity body======" << std::endl;
//   std::cout << request_message.entity_body_str << std::endl;
// }
