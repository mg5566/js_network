#include "Cycle.hpp"

Cycle::Cycle() {
	std::ofstream ofs;
	ofs.open("error.log", std::ofstream::out | std::ios_base::app);
	if (!ofs.is_open())
		throw fileOpenException();
	ofs.close();
	kq = new Kqueue();
	sm = new SocketManager();
}

Cycle::~Cycle() {
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
