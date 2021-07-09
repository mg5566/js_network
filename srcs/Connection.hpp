#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "webserv.hpp"
#include "Listening.hpp"
#include "HttpConfig.hpp"
#include "Request_Message.hpp"

class Connection {
private:
	bool				listen;

	socket_t			fd;
	int					type;
	struct sockaddr_in	sockaddr;		// client의 port랑 ip
	socklen_t			socklen;

	Listening			*listening;
	struct sockaddr_in	local_sockaddr;	// local_sockaddr.sin_port == 5000
	socklen_t			local_socklen;

	HttpConfig			*httpconfig;

	Request_Message		req_msg;
	Connection			*next;

public:
	char				buffer[BUF_SIZE];

	Connection();
	~Connection();

	Connection	*event_accept(SocketManager *sv);

	void	set_listen(bool _listen);
	void	set_next(Connection *_next);
	void	set_fd(socket_t _fd);
	void	set_type(int _type);
	void	set_listening(Listening *_listening);
	void	set_sockaddr(struct sockaddr_in *sa, socklen_t sl);
	void	set_local_sockaddr(struct sockaddr_in *sa, socklen_t sl);
	void	set_httpconfig(HttpConfig *&hc);
	void	set_request_message(Request_Message &req_msg);

	bool				get_listen() const;
	Connection			*get_next() const;
	socket_t			get_fd() const;
	struct sockaddr_in	get_local_sockaddr() const;
	// const HttpConfig	*get_httpconfig() const;
	// const Request_Message		&get_request_message() const;
	HttpConfig	*get_httpconfig();
	Request_Message		&get_request_message();
};


#endif
