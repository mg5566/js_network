#include "Time.hpp"

Time::Time() {}
Time::~Time() {}

void	Time::set_time() {
	std::stringstream ss;
	char	buf[20];

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", localtime(&sec));
	ss << buf;
	data = ss.str();
}

const std::string	&Time::get_time_data() const {
	return data;
}