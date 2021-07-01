#include "webserv.hpp"
#include "Cycle.hpp"

int main(void)
{
	std::multimap<in_port_t, in_addr_t>	addrs;
	std::pair<in_port_t, in_addr_t>	addr_80(80, INADDR_ANY);
	std::pair<in_port_t, in_addr_t>	addr_5000(5000, INADDR_ANY);
	std::pair<in_port_t, in_addr_t>	addr_8080(8080, INADDR_ANY);

	addrs.insert(addr_80);
	addrs.insert(addr_5000);
	addrs.insert(addr_8080);

	// config parsing
	Cycle cycle(addrs);
	return (0);
}
