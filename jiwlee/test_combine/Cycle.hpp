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
	Cycle(HttpConfig *&httpconfig);
	~Cycle();

	void	webserv_cycle();
};

#endif
