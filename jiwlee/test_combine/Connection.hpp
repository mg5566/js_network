#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "webserv.hpp"
#include "Listening.hpp"

class Connection {
private:
	bool				listen;

	void				*data;

	socket_t			fd;
	int					type;
	struct sockaddr_in	sockaddr;		// client의 port랑 ip
	socklen_t			socklen;

	Listening			*listening;
	struct sockaddr_in	local_sockaddr;	// local_sockaddr.sin_port == 5000
	socklen_t			local_socklen;

public:
	char				buffer[BUF_SIZE];

	Connection();
	~Connection();

	Connection	*event_accept(SocketManager *sv);

	void	set_listen(bool _listen);
	void	set_data(void *_data);
	void	set_fd(socket_t _fd);
	void	set_type(int _type);
	void	set_listening(Listening *_listening);
	void	set_sockaddr(struct sockaddr_in *sa, socklen_t sl);
	void	set_local_sockaddr(struct sockaddr_in *sa, socklen_t sl);

	bool		get_listen() const;
	void		*get_data() const;
	socket_t	get_fd() const;
	//	get_local_sockaddr() const;
};


#endif
