#include "Cycle.hpp"

Cycle::Cycle(std::multimap<in_port_t, in_addr_t> &addrs) {
	kq = new Kqueue();
	sm = new SocketManager(addrs, kq);
	webserv_cycle();
}

Cycle::~Cycle() {
	delete kq;
	delete sm;
}

void	Cycle::webserv_cycle() {
	for ( ;; ) {
		if (kq->kqueue_process_events(sm) == WEBSERV_ERROR)
			break ;
	}
}
