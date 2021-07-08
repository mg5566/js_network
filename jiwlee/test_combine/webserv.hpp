#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <map>
#include <vector>
#include <fstream>

typedef	int					socket_t;
typedef intptr_t			int_t;
typedef uintptr_t			uint_t;
typedef u_short				in_port_t;

#define DEFAULT_CONNECTIONS	512
#define LISTEN_BACKLOG		511
#define BUF_SIZE			30000
#define nonblocking(s)		fcntl(s, F_SETFL, O_NONBLOCK)
#define close_socket		close

#define WEBSERV_CONTINUE	1
#define WEBSERV_OK			0
#define WEBSERV_ERROR		-1

#define LOG_STDERR			0
#define LOG_EMERG			1
#define LOG_ALERT			2
#define LOG_CRIT			3
#define LOG_ERR				4
#define LOG_WARN			5
#define LOG_NOTICE			6
#define LOG_INFO			7
#define LOG_DEBUG			8

class Kqueue;
class SocketManager;
class Listening;
class Connection;
class Logger;

extern Logger	*logger;

const std::string	err_levels[9] = { "", "emerge", "alert", "crit", "error", "warn", "notice", "info", "debug" };

class webservCycleException: public std::exception {
	virtual const char *what() const throw() {
		return ("Webserv cycle error happen.");
	}
};

class kqueueException: public std::exception {
	virtual const char *what() const throw() {
		return ("kqueue() error.");
	}
};

class keventException: public std::exception {
	virtual const char *what() const throw() {
		return ("kqueue() error.");
	}
};

class socketException: public std::exception {
	virtual const char *what() const throw() {
		return ("socket() error.");
	}
};

class bindException: public std::exception {
	virtual const char *what() const throw() {
		return ("bind() error.");
	}
};

class listenException: public std::exception {
	virtual const char *what() const throw() {
		return ("listen() error.");
	}
};

class nonblockingException: public std::exception {
	virtual const char *what() const throw() {
		return ("nonblocking() error.");
	}
};

class acceptExcception: public std::exception {
	virtual const char *what() const throw() {
		return ("accept() error.");
	}
};

class connNotEnoughException: public std::exception {
	virtual const char *what() const throw() {
		return ("connection not enough error.");
	}
};

class closeSocketException: public std::exception {
	virtual const char *what() const throw() {
		return ("connection not enough error.");
	}
};

#endif
