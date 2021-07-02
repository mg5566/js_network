#include "Connection.hpp"

Connection::Connection()
: listen(false), fd(-1), type(SOCK_STREAM), listening(NULL)
{
	memset(buffer, 0, BUF_SIZE);
}

Connection::~Connection() {}

// listen == true 일때 호출됨
Connection	*Connection::event_accept(SocketManager *sm) {
	struct sockaddr_in	conn_sockaddr;
	socklen_t			conn_socklen;

	socket_t s = accept(fd, (struct sockaddr *)&conn_sockaddr, &conn_socklen);

	if (s == -1) {
		logger->log_error(LOG_ALERT, "accept() failed");
		return NULL;
	}

	Connection *c = sm->get_connection(s);

	if (c == NULL) {	// free_connection 없음
		if (close_socket(s) == -1) {
			logger->log_error(LOG_ALERT, "close() socket failed");
		}
		return NULL;
	}
	if (nonblocking(s) == -1) {
		logger->log_error(LOG_ALERT, "fcntl(O_NONBLOCK) failed");
		sm->close_connection(c);	// s가 close됨
		return NULL;
	}

	c->listening = listening;
	memcpy(&c->sockaddr, &conn_sockaddr, conn_socklen);
	memcpy(&c->local_sockaddr, &sockaddr, socklen);
	c->local_socklen = socklen;
	return c;
}

/* SETTER */
void	Connection::set_listen(bool _listen)
{ listen = _listen; }
void	Connection::set_data(void *_data)
{ data = _data; }
void	Connection::set_fd(socket_t _fd)
{ fd = _fd; }
void	Connection::set_type(int _type)
{ type = _type; }
void	Connection::set_listening(Listening *_listening)
{ listening = _listening; }
void	Connection::set_sockaddr(struct sockaddr_in *sa, socklen_t sl)
{
	socklen = sl;
	memcpy(&sockaddr, sa, sl);
}
void	Connection::set_local_sockaddr(struct sockaddr_in *sa, socklen_t sl)
{
	local_socklen = sl;
	memcpy(&local_sockaddr, sa, sl);
}

/* GETTER */
bool		Connection::get_listen() const
{ return listen; }
void		*Connection::get_data() const
{ return data; }
socket_t	Connection::get_fd() const
{ return fd; }
