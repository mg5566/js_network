#ifndef CYCLE_HPP
#define CYCLE_HPP

#include "webserv.hpp"
#include "SocketManager.hpp"
#include "Kqueue.hpp"
#include "HttpConfig.hpp"

class Cycle {
private:
	SocketManager	*sm;
	Kqueue			*kq;

public:
	Cycle();
	~Cycle();

	void	init_cycle(HttpConfig *&httpconfig);
	void	webserv_cycle();
};

#endif
