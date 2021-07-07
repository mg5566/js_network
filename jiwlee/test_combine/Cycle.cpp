#include "Cycle.hpp"

Cycle::Cycle() {
	logger = new Logger();
	kq = new Kqueue();
	sm = new SocketManager();
}

Cycle::~Cycle() {
	delete logger;
	delete kq;
	delete sm;
}

void	Cycle::init_cycle(HttpConfig *&httpconfig) {
	kq->kqueue_init();
	sm->init_socket_manager(httpconfig);
	sm->open_listening_sockets(kq);
}

void	Cycle::webserv_cycle() {
	for ( ;; ) {
		try {
			kq->kqueue_process_events(sm);
		}
		catch(std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
