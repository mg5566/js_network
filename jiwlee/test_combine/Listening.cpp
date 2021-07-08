#include "Listening.hpp"

Listening::Listening(in_port_t port, in_addr_t ipaddr)
: fd(-1), type(SOCK_STREAM), backlog(LISTEN_BACKLOG), connection(NULL)
{
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);
	sockaddr.sin_addr.s_addr = htonl(ipaddr);

	socklen = sizeof(sockaddr);

	// u_char	*p = (u_char *)&sockaddr.sin_addr;
	// addr_text += ntohs(sockaddr.sin_port);
	// setting해야함
	addr_text = "";
}

Listening::~Listening() {}

void	Listening::open_listening_socket(SocketManager *sm) {
	socket_t	s;

	s = socket(sockaddr.sin_family, type, 0);
	if (s < 0) {
		Logger::log_error(LOG_EMERG, "socket() %s failed", addr_text.c_str());
		throw socketException();
	}
	
	fd = s;

	int sock_optval = 1;
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &sock_optval, sizeof(sock_optval)) == -1) {
		Logger::log_error(LOG_EMERG, "setsockopt() to %s failed", addr_text.c_str());
	}

	if (nonblocking(s) == -1) {
		Logger::log_error(LOG_EMERG, "fcntl(O_NONBLOCK) %s failed", addr_text.c_str());
		if (close_socket(s) == -1) {
			Logger::log_error(LOG_EMERG, "close() socket %s failed", addr_text.c_str());
			throw closeSocketException();
		}
		throw nonblockingException();
	}


	if (bind(s, (struct sockaddr *)&sockaddr, socklen) == -1) {
		Logger::log_error(LOG_EMERG, "bind() to %s failed", addr_text.c_str());
		if (close_socket(s) == -1) {
			Logger::log_error(LOG_EMERG, "close() socket %s failed", addr_text.c_str());
			throw closeSocketException();
		}
		throw bindException();
	}

	if (listen(s, backlog) == -1) {
		Logger::log_error(LOG_EMERG, "listen() to %s failed", addr_text.c_str());
		if (close_socket(s) == -1) {
			Logger::log_error(LOG_EMERG, "close() socket %s failed", addr_text.c_str());
			throw closeSocketException();
		}
		throw listenException();
	}

	Connection *c = sm->get_connection(fd);
	c->set_listen(true);
	c->set_type(type);
	c->set_listening(this);
	c->set_sockaddr(&sockaddr, socklen);
	c->set_local_sockaddr(&sockaddr, socklen);
	connection = c;

	///////////지워야함
	std::cout << "listening socket open " << s << std::endl;
}

void		Listening::set_listening_connection(Connection *c) {
	connection = c;
}

Connection	*Listening::get_listening_connection() const {
	return connection;
}

socket_t	Listening::get_fd() const {
	return fd;
}

const std::string		&Listening::get_addr_text() const {
	return addr_text;
}
