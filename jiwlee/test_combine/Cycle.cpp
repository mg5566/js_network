#include "Cycle.hpp"

Cycle::Cycle(std::multimap<in_port_t, in_addr_t> &addrs, httpconfig) {
	kq = new Kqueue();
	sm = new SocketManager(addrs, kq, httpconfig);
	logger = new Logger();
}

Cycle::~Cycle() {
	delete kq;
	delete sm;
}

void	Cycle::webserv_cycle(httpconfig) {
	for ( ;; ) {
		if (kq->kqueue_process_events(sm, httpconfig) == WEBSERV_ERROR)
			break ;
	}
}
