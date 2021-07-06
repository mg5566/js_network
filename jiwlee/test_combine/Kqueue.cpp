#include "Kqueue.hpp"

Kqueue::Kqueue()
: kq(-1), nchanges(0), nevents(0), change_list(NULL), event_list(NULL)
{
	kqueue_init();
}

Kqueue::~Kqueue()
{
	kqueue_done();
}

int_t	Kqueue::kqueue_init()
{
	kcf.changes = 512;
	kcf.events = 512;
	ts.tv_sec = 5;
	ts.tv_nsec = 0;

	if (kq == -1) {
		kq = kqueue();
		if (kq == -1) {
			logger->log_error(LOG_EMERG, "kqueue() failed");
			return WEBSERV_ERROR;
		}
	}

	change_list = new struct kevent[kcf.changes]();
	if (change_list == NULL) {
		logger->log_error(LOG_EMERG, "malloc(%u) failed", (size_t)kcf.changes);
		return WEBSERV_ERROR;
	}
	event_list = new struct kevent[kcf.events]();
	if (event_list == NULL) {
		logger->log_error(LOG_EMERG, "malloc(%u) failed", (size_t)kcf.events);
		return WEBSERV_ERROR;
	}
	max_changes = kcf.changes;
	nevents = kcf.events;
	return WEBSERV_OK;
}

void	Kqueue::kqueue_done() {
	if (close(kq) == -1) {
		logger->log_error(LOG_ALERT, "kqueue close() failed");
	}
	kq = -1;
	delete[] change_list;
	delete[] event_list;
	max_changes = 0;
	nchanges = 0;
	nevents = 0;
}

// Connection 하나 등록
int		Kqueue::kqueue_add_event(Connection *c, u_short flags, u_int fflag)
{
	EV_SET(&change_list[nchanges], c->get_fd(), flags, fflag, 0, 0, c);	// udata = Connection
	++nchanges;
	return WEBSERV_OK;
}

int		Kqueue::kqueue_del_event(Connection *c, u_short flags, u_int fflag)
{
	EV_SET(&change_list[nchanges], c->get_fd(), flags, fflag, 0, 0, c);
	++nchanges;
	return WEBSERV_OK;
}

int_t	Kqueue::kqueue_process_events(SocketManager *sm)
{
	int				events;
	Event_Handler	event_handler;

	events = kevent(kq, change_list, nchanges, event_list, nevents, &ts);
	nchanges = 0;
	if (events == -1) {
		logger->log_error(LOG_ALERT, "kevent() failed");
		return WEBSERV_ERROR;
	}
	for (int_t i = 0; i < events; ++i) {
		Connection *c = (Connection*)event_list[i].udata;

		if (event_list[i].flags & EV_ERROR) {

			logger->log_error(LOG_ALERT, "%d kevent() error on %d filter:%d", events, (int)event_list[i].ident, (int)event_list[i].filter);
			continue ;
		}
		if (event_list[i].flags & EV_EOF) {
			logger->log_error(LOG_ALERT, "%d kevent() reported about an closed connection %d", events, (int)event_list[i].ident);
			kqueue_del_event(c, EVFILT_READ, EV_DELETE);
			sm->close_connection(c);
		}
		else if (event_list[i].filter == EVFILT_READ) {
			if (c->get_listen()) {
				Connection *conn = c->event_accept(sm);
				kqueue_add_event(conn, EVFILT_READ, EV_ADD);
			}
			else {
				recv(event_list[i].ident, c->buffer, BUF_SIZE, 0);
				event_handler.process_event(c->buffer);
				// c->set_data(parsing된 request message);
				kqueue_add_event(c, EVFILT_WRITE, EV_ADD | EV_ONESHOT);
			}
		}
		else if (event_list[i].filter == EVFILT_WRITE) {
			// make_response_message(c->get_data());
			send(event_list[i].ident, temp.c_str(), temp.size(), 0);
			memset(c->buffer, 0, BUF_SIZE);
			kqueue_add_event(c, EVFILT_READ, EV_ADD);
		}
	}
	return WEBSERV_OK;


	// std::string temp = "world!\n";
	// std::string temp = "HTTP/1.1 200 OK\r\nServer: jsnetwork\r\nContent-Length: 31\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html>\n<html>\n</html>\n";
			
}
