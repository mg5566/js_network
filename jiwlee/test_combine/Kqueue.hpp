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

	int_t	kqueue_init();
	void	kqueue_done();
	int		kqueue_add_event(Connection *c, u_short flags, u_int fflag);
	int		kqueue_del_event(Connection *c, u_short flags, u_int fflag);
	int_t	kqueue_process_events(SocketManager *sm);
};

#endif
