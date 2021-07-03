#include "Logger.hpp"

Logger::Logger() {
	ofs.open("error.log", std::ofstream::out | std::ios_base::app);
	if (!ofs.is_open())
		std::cerr << "Opening Log file error" << std::endl;
	ofs.close();
}

Logger::~Logger() {}

void	Logger::log_error(int level, const char *fmt, ...)
{	
	std::string		errstr;
	ofs.open("error.log", std::ofstream::out | std::ios_base::app);
	if (!ofs.is_open())
		std::cerr << "Opening Log file error" << std::endl;

	t.set_time();
	errstr += t.get_time_data();
	errstr += " [";
	errstr.append(err_levels[level]);
	errstr += "] ";

	va_list ap;

	va_start(ap, fmt);
	while (*fmt) {
		uint_t	ui;
		int		d;
		char	*s;

		if (*fmt == '%') {
			++fmt;
			switch(*fmt++) {
			case 'u':
				ui = va_arg(ap, size_t);
				errstr += ui;
				break ;
			case 'd':
				d = va_arg(ap, int);
				errstr += d;
				break ;
			case 's':
				s = va_arg(ap, char *);
				errstr += s;
				break ;
			}
		}
		else
		{
			errstr += *fmt;
			++fmt;
		}
	}
	va_end(ap);

	linefeed(errstr);
	
	ofs << errstr;
	ofs.close();
}