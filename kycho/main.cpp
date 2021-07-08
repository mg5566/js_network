/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 03:33:46 by kycho             #+#    #+#             */
/*   Updated: 2021/07/07 20:07:40 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HttpConfig.hpp"

int main(void)
{
	HttpConfig* config;
	try
	{
		config = new HttpConfig("./sample.conf");	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (0);
	}


	std::cout << "\n\n\n<<< must_listens 출력 시작>>>" << std::endl;
	std::multimap<in_port_t, in_addr_t> must_listens = config->getMustListens();
	for (std::multimap<in_port_t, in_addr_t>::iterator it = must_listens.begin(); it != must_listens.end(); it++)
	{
		in_addr_t ip_addr = it->second;
		in_port_t port = it->first;
		struct in_addr addr;
		addr.s_addr = ip_addr;
		std::cout << "ip_addr:port   => " << inet_ntoa(addr) << ":" << ntohs(port) << std::endl; 
	}
	std::cout << "<<< must_listens 출력 끝>>>\n\n\n" << std::endl;

	// 전체상태 출력해보는 함수
	//config->print_all_server_location_for_debug();

	// 요청 포트, 주소, uri, server_name 설정 
	in_port_t port2 = htons(8080);
	in_addr_t ip_addr2 = inet_addr("123.123.123.123");
	std::string server_name2 = "ccc";
	std::string request_uri2 = "/";

	std::cout << "----- getServerConfig() test -----" << std::endl;
	ServerConfig* server = config->getServerConfig(port2, ip_addr2, server_name2);
	if (server == NULL){
		std::cout << "server is null" << std::endl;
	}else {
		const std::vector<LocationConfig*> &locations = server->getLocationConfigs();
		//server->getLocationConfigs()
		
		for(std::vector<LocationConfig*>::const_iterator it = locations.begin(); it != locations.end(); it++){
			std::cout << "uri_path : " << (*it)->getUri() << std::endl;
		}

		LocationConfig* location = server->getLocationConfig(request_uri2);
		if (location == NULL){
			std::cout << "location is null" << std::endl;
		}
		else{
			location->print_status_for_debug("\t");
		}
	}

	std::cout << "----- getLocationConfig() test -----" << std::endl;
	LocationConfig* location2 = config->getLocationConfig(port2, ip_addr2, server_name2, request_uri2);
	if (location2 == NULL){
		std::cout << "location2 is null" << std::endl;
	}
	else{
		location2->print_status_for_debug("\t");
		std::cout << "\t" << location2->checkAcceptedMethod("PUT") << std::endl;
	}
	
	std::cout << "main 끝~~~" << std::endl;
	return (0);
}
