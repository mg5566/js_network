/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:48:51 by kycho             #+#    #+#             */
/*   Updated: 2021/07/07 19:57:50 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_CONFIG_HPP
# define LOCATION_CONFIG_HPP

# include <vector>
# include <map>
# include <set>
# include <string>

# include "ServerConfig.hpp"
# include "LocationConfig.hpp"

class ServerConfig;

class LocationConfig
{
private:
	std::string					uri;
	
	std::string					root;
	std::vector<std::string>	index;
	bool						autoindex;
	unsigned long				client_max_body_size;
	std::map<int, std::string>	error_page;
	//return
	std::set<std::string>		limit_except;

public:
	LocationConfig(std::vector<std::string> tokens, ServerConfig* server_config);
	~LocationConfig(void);

	bool								checkPrefixMatchUri(std::string request_uri);

	const std::string&					getUri(void) const;
	const std::string&					getRoot(void) const;
	const std::vector<std::string>		getIndex(void) const;
	const bool&							getAutoindex(void) const;
	const unsigned long&				getClientMaxBodySize(void) const;
	const std::map<int, std::string>&	getErrorPage(void) const;

	bool								checkAcceptedMethod(const std::string request_method) const;
	
	// for debug
	void print_status_for_debug(std::string prefix);  // TODO : remove
	const std::set<std::string>&		getLimitExcept(void) const; // TODO : remove
};

#endif
