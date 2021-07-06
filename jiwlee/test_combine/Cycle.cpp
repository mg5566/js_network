#include "Cycle.hpp"

Cycle::Cycle(HttpConfig *&httpconfig) {
	logger = new Logger();
	kq = new Kqueue();
	sm = new SocketManager(httpconfig, kq);
}

Cycle::~Cycle() {
	delete logger;
	delete kq;
	delete sm;
}

void	Cycle::webserv_cycle() {
	for ( ;; ) {
		if (kq->kqueue_process_events(sm) == WEBSERV_ERROR)
			break ;
	}
}
