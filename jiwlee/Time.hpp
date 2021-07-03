#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <sstream>
#include <sys/time.h>

class Time {
private:
	struct timeval	tv;
	time_t			sec;

	std::string		data;

public:
	Time();
	~Time();

	void	set_time();
	void	webserv_localtime(time_t s, struct tm *time);

	const std::string	&get_time_data() const;
};

#endif