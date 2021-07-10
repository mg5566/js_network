#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "webserv.hpp"
#include "Time.hpp"

class Logger {
public:
	static void	log_error(int level, const char *fmt, ...) {
		std::stringstream	ss;
		std::ofstream		ofs;

		ofs.open("error.log", std::ofstream::out | std::ios_base::app);
		if (!ofs.is_open())
			std::cerr << "Opening Log file error" << std::endl;

		ss << Time::get_current_time() << " [" << err_levels[level] << "] ";
		va_list ap;

		va_start(ap, fmt);
		while (*fmt) {
			size_t	ui;
			int		d;
			char	*s;

			if (*fmt == '%') {
				++fmt;
				switch(*fmt++) {
				case 'u':
					ui = va_arg(ap, size_t);
					ss << ui;
					break ;
				case 'd':
					d = va_arg(ap, int);
					ss << d;
					break ;
				case 's':
					s = va_arg(ap, char *);
					ss << s;
					break ;
				}
			}
			else
			{
				ss << *fmt;
				++fmt;
			}
		}
		va_end(ap);

		ss << '\n';
		ofs << ss.str();
		ofs.close();
	}

};

#endif
