#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "webserv.hpp"
#include "Time.hpp"

class Logger {
private:
	Time			t;
	std::ofstream	ofs;

public:
	Logger();
	~Logger();

	void	log_error(int level, const char *fmt, ...);
};

#endif