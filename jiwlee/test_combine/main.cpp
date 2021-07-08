#include "Cycle.hpp"
#include "HttpConfig.hpp"
#include <map>

int main(void)
{
	Cycle cycle;
	try {
		HttpConfig *httpconfig = new HttpConfig();
		cycle.init_cycle(httpconfig);
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	cycle.webserv_cycle();
	return (0);
}
