#include "Logger.hpp"

Logger::Logger() {}

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

// Connection
// ngx_log_error(ngx_socket_errno, "accept() failed");
// ngx_log_error(ngx_socket_errno, "close() socket failed");
// ngx_log_error(ngx_socket_errno, "fcntl(O_NONBLOCK) failed");

// Listening
// ngx_log_error(ngx_socket_errno, "close() socket %V failed", &ls[i].addr_text);
// ngx_log_error(ngx_socket_errno, ngx_nonblocking_n " %V failed", &ls[i].addr_text);
// ngx_log_error(ngx_socket_errno, "close() socket %V failed", &ls[i].addr_text);
// ngx_log_error(err, "bind() to %V failed", &ls[i].addr_text);
// ngx_log_error(ngx_socket_errno, "close() socket %V failed", &ls[i].addr_text);
// ngx_log_error(err, "listen() to %V, backlog %d failed", &ls[i].addr_text, ls[i].backlog);
// ngx_log_error(ngx_socket_errno, "close() socket %V failed", &ls[i].addr_text);


// // Kqueue
// ngx_log_error(ngx_errno, "kqueue() failed");
// ngx_log_error(ngx_errno, "kqueue close() failed");
// ngx_log_error(ngx_errno, "kevent(EVFILT_READ) failed");
// ngx_log_debug1(0, "kevent events: %d", events);
// ngx_log_error(err, "kevent() failed");
// ngx_log_error(event_list[i].data,

// // SocketManager
// ngx_log_debug2(0, "close listening %V #%d ", &ls[i].addr_text, ls[i].fd);
// ngx_log_error(ngx_socket_errno, "close() socket %V failed", &ls[i].addr_text);
// ngx_log_error(0, "%ui worker_connections are not enough", ngx_cycle->connection_n);
// ngx_log_error(err, "close() socket %d failed", fd);