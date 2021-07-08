#include "SocketManager.hpp"

SocketManager::SocketManager()
{}

SocketManager::~SocketManager()
{
	close_listening_sockets();
	delete[] connections;
}

void	SocketManager::init_socket_manager(HttpConfig *&httpconfig)
{
	// listening socket들 할당
	std::multimap<in_port_t, in_addr_t> addrs = httpconfig->getMustListens();
	for(std::multimap<in_port_t, in_addr_t>::iterator it = addrs.begin(); it != addrs.end(); ++it) {
		Listening *ls = new Listening(it->first, it->second);
		listening.push_back(ls);
	}

	//connection socket들 할당
	connection_n = DEFAULT_CONNECTIONS;
	connections = new Connection[connection_n]();
	Connection *c = connections;
	Connection *next = NULL;
	for (int_t i = connection_n - 1; i >= 0; --i) {
		c[i].set_data(next);
		c[i].set_fd(-1);
		c[i].set_httpconfig(httpconfig);
		next = &c[i];
	}
	free_connections = next;
	free_connection_n = connection_n;
}

void	SocketManager::open_listening_sockets(Kqueue* &kq) {
	for (size_t i = 0; i < listening.size(); ++i) {
		try {
			listening[i]->open_listening_socket(this);
			kq->kqueue_set_event(listening[i]->get_listening_connection(), EVFILT_READ, EV_ADD);
		}
		catch(std::exception &e) {
			std::cerr << "SocketManager::open_listening_sockets(fd = " << listening[i]->get_fd() << ")" 
						<< e.what() << std::endl;
		}
	}
}

void	SocketManager::close_listening_sockets() {

	for(size_t i = 0; i < listening.size(); ++i) {
		Listening	*ls = listening[i];
		Connection	*c = ls->get_listening_connection();

		if (c) {
			free_connection(c);
			ls->set_listening_connection(NULL);
		}
		if (close_socket(ls->get_fd()) == -1) {
			Logger::log_error(LOG_EMERG, "close() socket %s failed", ls->get_addr_text().c_str());
			throw closeSocketException();
		}
		delete ls;
	}
}

// free_connections에 있는 connection 하나 return
Connection*		SocketManager::get_connection(socket_t s) {
	Connection *c;

	c = free_connections;
	if (c == NULL) {
		Logger::log_error(LOG_ALERT, "%u worker_connections are not enough", connection_n);
		throw connNotEnoughException();
	}
	free_connections = (Connection*)c->get_data();
	--free_connection_n;
	c->set_fd(s);
	return c;
}

void	SocketManager::free_connection(Connection *c) {
	c->set_data(free_connections);
	free_connections = c;
	++free_connection_n;
}

void	SocketManager::close_connection(Connection *c) {
	socket_t	fd;

	free_connection(c);
	fd = c->get_fd();
	c->set_fd(-1);
	if (close_socket(fd) == -1) {
		Logger::log_error(LOG_ALERT, "close() socket %d failed", fd);
		throw closeSocketException();
	}
}

const std::vector<Listening*>	&SocketManager::get_listening() const {
	return listening;
}

size_t	SocketManager::get_listening_size() const {
	return listening.size();
}

Connection	*SocketManager::get_connections() const {
	return connections;
}