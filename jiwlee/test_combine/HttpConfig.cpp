#include "HttpConfig.hpp"

HttpConfig::HttpConfig(void)
{
	must_listens.insert(std::pair<in_port_t, in_addr_t>(80, inet_addr("0.0.0.0")));
	must_listens.insert(std::pair<in_port_t, in_addr_t>(8080, inet_addr("0.0.0.0")));
	must_listens.insert(std::pair<in_port_t, in_addr_t>(9090, inet_addr("172.30.1.34")));

	root = "httptest";
	index.push_back("httptest.html");
	index.push_back("httptest.htm");
	autoindex = true;
	client_max_body_size = 1;

	
	
// 	// make server blocks start
// 	ServerConfig* server1 = new ServerConfig();
// 	server1->root = this->root;
// 	server1->index = this->index;
// 	server1->autoindex = this->autoindex;
// 	server1->error_page = this->error_page;
// 	server1->client_max_body_size = this->client_max_body_size;


// 	ServerConfig* server2 = new ServerConfig();
// 	server2->root = this->root;
// 	server2->index = this->index;
// 	//server2->autoindex = this->autoindex;
// 	server2->autoindex = false;
// 	//server2->error_page = this->error_page;
// 	server2->error_page[404] = "/404.htmp";
// 	server2->error_page[500] = "/50x.htmp";
// 	server2->error_page[502] = "/50x.htmp";
// 	server2->error_page[503] = "/50x.htmp";
// 	server2->error_page[504] = "/50x.htmp";
// 	server2->client_max_body_size = this->client_max_body_size;
// 	server2->server_name.push_back("localhost");


// 	ServerConfig* server3 = new ServerConfig();
// 	server3->root = this->root;
// 	server3->index = this->index;
// 	server3->autoindex = this->autoindex;
// 	server3->error_page = this->error_page;
// 	server3->client_max_body_size = this->client_max_body_size;
// 	server3->server_name.push_back("somename");
// 	server3->server_name.push_back("alias");
// 	server3->server_name.push_back("another.alias");
	
// 	// make server blocks end


// 	// make location blocks start
// 	LocationConfig* location1 = new LocationConfig();
// 	location1->uri_path = "/default";
// 	location1->root = server1->root;
// 	location1->index = server1->index;
// 	location1->autoindex = server1->autoindex;
// 	location1->error_page = server1->error_page;
// 	location1->client_max_body_size = server1->client_max_body_size;

// 	LocationConfig* location2 = new LocationConfig();
// 	location2->uri_path = "/";
// 	location2->root = "html";
// 	location2->index.push_back("index.html");
// 	location2->index.push_back("index.htm");
// 	location2->autoindex = server2->autoindex;
// 	location2->error_page = server2->error_page;
// 	location2->client_max_body_size = server2->client_max_body_size;


// 	LocationConfig* location3 = new LocationConfig();
// 	location3->uri_path = "/test/";
// 	location3->root = server2->root;
// 	location3->index.push_back("test.html");
// 	location3->autoindex = true;
// 	location3->error_page = server2->error_page;
// 	location3->client_max_body_size = server2->client_max_body_size;


// 	LocationConfig* location4 = new LocationConfig();
// 	location4->uri_path = "/50x.html";
// 	location4->root = "html";
// 	location4->index = server2->index;
// 	location4->autoindex = server2->autoindex;
// 	location4->error_page = server2->error_page;
// 	location4->client_max_body_size = server2->client_max_body_size;


// 	LocationConfig* location5 = new LocationConfig();
// 	location5->uri_path = "/";
// 	location5->root = "html";
// 	location5->index.push_back("index.html");
// 	location5->index.push_back("index.htm");
// 	location5->autoindex = server3->autoindex;
// 	location5->error_page = server3->error_page;
// 	location5->client_max_body_size = server3->client_max_body_size;
// 	// make location blocks end


// 	server1->locations.push_back(location1);
// 	server2->locations.push_back(location2);
// 	server2->locations.push_back(location3);
// 	server2->locations.push_back(location4);
// 	server3->locations.push_back(location5);


// 	this->server[80][inet_addr("0.0.0.0")].push_back(server1);
// 	this->server[8080][inet_addr("0.0.0.0")].push_back(server2);
// 	this->server[8080][inet_addr("127.0.0.1")].push_back(server3);
// 	this->server[9090][inet_addr("172.30.1.34")].push_back(server3);
	
}

// HttpConfig::HttpConfig(std::string configFilePath)
// {
// 	// 초기화부분
// 	this->root = "html";
// 	this->index.push_back("index.html");
// 	this->autoindex = false;
// 	this->client_max_body_size = 1000000;
	
// 	// 한번이라도 세팅했었는지 체크하는 변수 
// 	bool check_root_setting = false;
// 	bool check_index_setting = false;
// 	bool check_autoindex_setting = false;
// 	bool check_client_max_body_size = false;

// 	// config파일을 읽어서 content 변수에 담는다.
// 	std::ifstream ifs(configFilePath);
// 	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	
// 	// content를 유의미한 단위로 자른다.(토큰화한다)
// 	ft::Tokenizer tokenizer;
// 	std::vector<std::string> tokens = tokenizer.parse(content);


// 	std::vector<std::vector<std::string> > servers_tokens;  // ServerConfig 객체 생성할떄 사용할 토큰들

// 	std::vector<std::string>::iterator it = tokens.begin();
	
// 	if (*it != "http")
// 		throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"" + (*it) + "\" directive");
// 	if (*(it + 1) != "{")
// 		throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"http\" directive");

// 	it += 2;
// 	while (*it != "}")
// 	{
// 		if ( *it == "root"){

// 			if (*(it + 1) == ";" || *(it + 2) != ";")
// 				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"root\" directive");
// 			if (check_root_setting == true)
// 				throw std::runtime_error("webserv: [emerg] \"root\" directive is duplicate");

// 			this->root = *(it + 1);
// 			check_root_setting = true;
			
// 			it += 3;
			
// 		}else if (*it == "index"){

// 			if (*(it + 1) == ";")
// 				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"index\" directive");

// 			if (check_index_setting == false){
// 				this->index.clear();
// 				check_index_setting = true;
// 			}

// 			it++;
// 			while (*it != ";")
// 			{
// 				this->index.push_back(*it);
// 				it++;
// 			}
// 			it++;

// 		}else if (*it == "autoindex"){

// 			if (*(it + 1) == ";" || *(it + 2) != ";")
// 				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"autoindex\" directive");
// 			if (check_autoindex_setting == true)
// 				throw std::runtime_error("webserv: [emerg] \"autoindex\" directive is duplicate");
// 			if ( (*(it + 1)) != "on" && *(it + 1) != "off")
// 				throw std::runtime_error("webserv: [emerg] invalid value \"" + *(it + 1) + "\" in \"autoindex\" directive, it must be \"on\" or \"off\"");

// 			if (*(it + 1) == "on")
// 				this->autoindex = true;
// 			else
// 				this->autoindex = false;

// 			check_autoindex_setting = true;
// 			it += 3;
			
// 		}else if (*it == "error_page"){
			
// 			// TODO : 예외처리해야함 
			
// 			int count = 2;
// 			while(*(it + count + 1) != ";")
// 				count++;

// 			for(int i = 1; i < count; i++){
// 				int status_code  = atoi((*(it + i)).c_str());

// 				if (this->error_page.find(status_code) == this->error_page.end()){
// 					this->error_page[status_code] = *(it + count);
// 				}
// 			}
// 			it += (count + 2);

// 		}else if (*it == "client_max_body_size"){
			
// 			// TODO : 예외처리해야함
// 			if (check_client_max_body_size == true)
// 				throw std::runtime_error("webserv: [emerg] \"client_max_body_size\" directive is duplicate");
			
			
// 			std::string size_str = *(it + 1);

// 			this->client_max_body_size = atoi(size_str.c_str());

// 			char last_char = size_str[size_str.length() - 1];
// 			if ( last_char == 'k'){
// 				client_max_body_size *= 1000;
// 			}else if (last_char == 'm'){
// 				client_max_body_size *= 1000000;	
// 			}else if (last_char == 'g'){
// 				client_max_body_size *= 1000000000;	
// 			}
			
// 			check_client_max_body_size = true;
// 			it += 3;

// 		}else if (*it == "server"){
			
// 			// TODO : 예외처리해야함

// 			std::vector<std::string> server_tokens;

// 			server_tokens.push_back(*it);
// 			it++;
// 			server_tokens.push_back(*it);
// 			it++;

// 			int cnt = 1;
// 			while (cnt != 0){
// 				if (*it == "{") cnt++;
// 				else if (*it == "}") cnt--;
// 				server_tokens.push_back(*it);
// 				it++;
// 			}
// 			servers_tokens.push_back(server_tokens);
			
// 		}else {
// 			throw std::runtime_error("webserv: [emerg] unknown directive \"" + (*it) + "\"");
// 		}
// 	}

// 	std::vector<std::vector<std::string> >::iterator server_it = servers_tokens.begin();
// 	for (; server_it != servers_tokens.end(); server_it++){
// 		ServerConfig *new_server = new ServerConfig(*server_it, this);

// 		for (std::vector<std::string>::iterator i = new_server->listens.begin(); i != new_server->listens.end(); i++)
// 		{
// 			std::size_t pos = (*i).find(':');
// 			std::string ip_addr_str = (*i).substr(0, pos);
// 			std::string port_str = (*i).substr(pos + 1);

// 			in_addr_t ip_addr = inet_addr(ip_addr_str.c_str());
// 			in_port_t port = htons(atoi(port_str.c_str()));
	
// 			server[port][ip_addr].push_back(new_server);

// 			if (must_listens.find(port) == must_listens.end() || must_listens.find(port)->second != inet_addr("0.0.0.0")){
// 				if (ip_addr == inet_addr("0.0.0.0")){
// 					must_listens.erase(port);
// 				}
// 				must_listens.insert(std::pair<in_port_t, in_addr_t>(port, ip_addr));
// 			}		
// 		}
// 	}
// }

HttpConfig::~HttpConfig()
{
	std::cout << "~HttpConfig() 호출~~~" << std::endl;
}

std::multimap<in_port_t, in_addr_t>	HttpConfig::getMustListens(void)
{
	return must_listens;
}

// ServerConfig* HttpConfig::getServerConfig(in_port_t port, in_addr_t ip_addr, std::string server_name)
// {
// 	if (server.find(port) == server.end())
// 		return NULL;

// 	std::vector<ServerConfig*> *server_list = NULL;

// 	if (server[port].find(ip_addr) != server[port].end())
// 	{
// 		server_list = &server[port][ip_addr];
// 	}
// 	else if (server[port].find(inet_addr("0.0.0.0"))!= server[port].end())
// 	{
// 		server_list = &server[port][inet_addr("0.0.0.0")];
// 	}

// 	if (server_list == NULL)
// 	{
// 		return NULL;
// 	}

// 	ServerConfig* server_ptr = (*server_list)[0];

// 	for(std::vector<ServerConfig*>::iterator it = server_list->begin(); it != server_list->end(); it++)
// 	{
// 		if ((*it)->isMatchServerName(server_name))
// 		{
// 			server_ptr = *it;
// 		}
// 	}

// 	return server_ptr;
// }

// LocationConfig* HttpConfig::getLocationConfig(in_port_t port, in_addr_t ip_addr, std::string server_name, std::string request_uri)
// {
// 	ServerConfig* server_config = this->getServerConfig(port, ip_addr, server_name);
// 	LocationConfig* location_config = server_config->getLocationConfig(request_uri);
// 	return location_config;
// }


// // ############## for debug ###################
// void HttpConfig::print_all_server_location_for_debug(void)  // TODO : remove
// {
// 	this->print_status_for_debug("");
	
// 	for (std::map<in_port_t, std::map<in_addr_t, std::vector<ServerConfig*> > >::iterator it = server.begin(); it != server.end(); it++)
// 	{
// 		in_port_t port = it->first;
// 		std::map<in_addr_t, std::vector<ServerConfig*> > addr_server_map = it->second;
		
// 		std::cout << "port : " <<  ntohs(port) << std::endl;
		
// 		for (std::map<in_addr_t, std::vector<ServerConfig*> >::iterator it2 = addr_server_map.begin(); it2 != addr_server_map.end(); it2++){
// 			in_addr_t ip_addr = it2->first;
// 			std::vector<ServerConfig*> server_list = it2->second;

// 			struct in_addr addr1;
// 			addr1.s_addr = ip_addr;
// 			std::cout << "\tip_addr : " << inet_ntoa(addr1) << std::endl;

// 			for (std::vector<ServerConfig*>::iterator it3 = server_list.begin(); it3 != server_list.end(); it3++){
// 				(*it3)->print_status_for_debug("\t\t");		

// 				std::vector<LocationConfig*>	locations = (*it3)->locations;
// 				for (std::vector<LocationConfig*>::iterator it4 = locations.begin(); it4 != locations.end(); it4++){
// 					(*it4)->print_status_for_debug("\t\t\t");
// 				}

// 			}
// 		}
// 	}
// }

// void HttpConfig::print_status_for_debug(std::string prefix){  // TODO : remove
// 	std::cout << prefix;
// 	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HttpConfig ~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	
	
// 	std::cout << prefix;
// 	std::cout << "root : " << this->root << std::endl;
	
// 	std::cout << prefix;
// 	std::cout << "index : ";
// 	for (std::vector<std::string>::iterator i = this->index.begin(); i != this->index.end(); i++){
// 		std::cout << *i << " ";
// 	}
// 	std::cout << std::endl;
	
// 	std::cout << prefix;
// 	std::cout << "autoindex : " << this->autoindex << std::endl;

// 	std::cout << prefix;
// 	std::cout << "client_max_body_size : " << this->client_max_body_size << std::endl;

// 	std::cout << prefix;
// 	std::cout << "error_page : " ;
// 	for (std::map<int, std::string>::iterator i = this->error_page.begin(); i != this->error_page.end(); i++){
// 		std::cout << i->first << ":" << i->second << "  ";
// 	}
// 	std::cout << std::endl;
// 	std::cout << prefix;
// 	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	
// }