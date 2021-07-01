#include "Time.hpp"

Time::Time() {}
Time::~Time() {}

void	Time::set_time() {
	// time setting
	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	webserv_localtime(sec, &time);

	std::stringstream ss;

	ss << time.tm_year;
	ss << "/";
	time.tm_mon < 10 ? ss << "0" : NULL;
	ss << time.tm_mon;
	ss << "/";
	time.tm_mday < 10 ? ss << "0" : NULL;
	ss << time.tm_mday;
	ss << " ";
	time.tm_hour < 10 ? ss << "0" : NULL;
	ss << time.tm_hour;
	ss << ":";
	time.tm_min < 10 ? ss << "0" : NULL;
	ss << time.tm_min;
	ss << ":";
	time.tm_sec < 10 ? ss << "0" : NULL;
	ss << time.tm_sec;

	data = ss.str();
}

void	Time::webserv_localtime(time_t s, struct tm *time) {
	struct tm *t;

	t = localtime(&s);
	*time = *t;
	++time->tm_mon;
	time->tm_year += 1900;
}

const std::string	&Time::get_time_data() const {
	return data;
}