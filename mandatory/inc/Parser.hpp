#pragma once
# include <iostream>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include "utils.hpp"
# include "Location.hpp"
# include <iostream>
# include <cstring> // Required for memset
# define DEFAULT_MAX_BOD_SIZE 1024

class Location;

class Parser
{
	private:
	public:
		static bool checkPorts(std::vector<std::string> const &ports);
		static bool checkPort(std::string port);
		static bool checkHost(std::string host);
		static bool checkServerName(std::string serverName);
		static bool checkErrorPage(std::string errorPage);
		static bool checkRoot(std::string root);
		static bool checkPath(std::string root, std::string attributeName);
		static bool checkIndex(std::string index, std::string root);
		static in_addr_t	isValidHost(std::string hostname);
		static long long checkClientBodySize(std::string maxClientBodySize);

		static bool checkAutoIndex(std::string autoindex);
		static int checkLocationName(std::string name);
		static int checkRootAliasReturn(std::string root, std::string alias, std::string return_);
		static bool checkReturnIgnore(std::string allowMethods, std::string autoindex, std::string index);
		static bool checkCgiString(std::string cgiPath, std::string cgiExtension);
		static bool checkCgi(std::vector<std::string> paths, std::vector<std::string> extensions);
		static bool checkAllowedMethods(std::string allowMethods);
};