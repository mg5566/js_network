#ifndef KQUEUE_HPP
#define KQUEUE_HPP

#include "webserv.hpp"
#include "SocketManager.hpp"
#include "Connection.hpp"
#include "Event_Handler.hpp"

typedef struct {
	uint_t		changes;
	uint_t		events;
}		kqueue_conf_t;

class Kqueue {
private:
	int				kq, max_changes, nchanges, nevents;
	struct kevent	*change_list;
	struct kevent	*event_list;
	kqueue_conf_t	kcf;
	struct timespec	ts;

public:
	Kqueue();
	~Kqueue();

	void	kqueue_init();
	void	kqueue_done();
	void	kqueue_set_event(Connection *c, u_short filter, u_int flags);
	void	kqueue_process_events(SocketManager *sm);
};

#endif
