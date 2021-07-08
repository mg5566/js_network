#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

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

class fileOpenException: public std::exception {
	virtual const char *what() const throw() {
		return ("file open error.");
	}
};

#endif