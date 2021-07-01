#include "Logger.hpp"

void	log_error(int level, const char *fmt)
{
	std::string	err_levels[9] = {
		"", "emerge", "alert", "crit", "error", "warn", "notice", "info", "debug"
	};

	Time 	t;
	
	t.set_time();

	std::string		errstr;

	errstr += t.get_time_data();
	errstr += " [";
	errstr.append(err_levels[level]);
	errstr += "] ";
	errstr.append(fmt);
	std::cout << errstr << std::endl;
}
