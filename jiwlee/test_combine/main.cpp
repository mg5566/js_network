#include "Cycle.hpp"
#include "HttpConfig.hpp"
#include <map>

Logger		*logger;

int main(void)
{
	HttpConfig *httpconfig = new HttpConfig();
	
	Cycle cycle(httpconfig);

	cycle.webserv_cycle();

	delete httpconfig;
	return (0);
}
