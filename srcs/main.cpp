#include "Cycle.hpp"
#include "HttpConfig.hpp"
#include <map>

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	Cycle cycle;
	try {
		HttpConfig *httpconfig = new HttpConfig(argv[1]);
		cycle.init_cycle(httpconfig);
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	cycle.webserv_cycle();
	return (0);
}
