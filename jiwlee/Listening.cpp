#include "Listening.hpp"

Listening::Listening(in_port_t port, in_addr_t ipaddr)
: fd(-1), type(SOCK_STREAM), backlog(LISTEN_BACKLOG), connection(NULL)
{
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);
	sockaddr.sin_addr.s_addr = htonl(ipaddr);

	socklen = sizeof(sockaddr);
}

Listening::~Listening() {}

int_t	Listening::open_listening_socket(SocketManager *sm) {
	socket_t s;

	s = socket(sockaddr.sin_family, type, 0);
	if (s < 0) {
		log_error(LOG_EMERG, "socket() failed");
		// std::cerr << "fail to connect..." << std::endl;
		return WEBSERV_ERROR;
	}
	if (nonblocking(s) == -1) {
		log_error(LOG_EMERG, "nonblocking() failed");
		if (close_socket(s) == -1) {
			log_error(LOG_EMERG, "close_socket() failed");
		}
		return WEBSERV_ERROR;
	}


	if (bind(s, (struct sockaddr *)&sockaddr, socklen) == -1) {
		log_error(LOG_EMERG, "bind() failed");
		if (close_socket(s) == -1) {
			log_error(LOG_EMERG, "close_socket() failed");
		}
		return WEBSERV_CONTINUE;
	}

	if (listen(s, backlog) == -1) {
		log_error(LOG_EMERG, "listen() failed");
		if (close_socket(s) == -1) {
			log_error(LOG_EMERG, "close_socket() failed");
		}
		return WEBSERV_CONTINUE;
	}

	fd = s;

	Connection *c = sm->get_connection(fd);	// listening socket을 Connection에 넣음
	c->set_listen(true);
	c->set_type(type);
	c->set_listening(this);
	c->set_sockaddr(&sockaddr, socklen);
	c->set_local_sockaddr(&sockaddr, socklen);
	connection = c;
	return WEBSERV_OK;
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
