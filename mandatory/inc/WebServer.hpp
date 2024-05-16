#pragma once
# include <string>
# include <vector>
# include <sstream>
# include <fstream>
# include <iostream>

# include "Server.hpp"
# include "Location.hpp"
# include "ListeningSocket.hpp"

# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/event.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <netdb.h>
# include <arpa/inet.h>

#define BACKLOG 20
#define MAX_EVENTS 300
#define MAX_CLIENTS 100
#define MAX_MSG_SIZE 1024
//  The backlog parameter defines the maximum length for the queue of pending
//      connections.  If a connection request arrives with the queue full, the
//      client may receive an error with an indication of ECONNREFUSED
enum eType {
	READ = 1,
	READHEADER = 2,
	READBODY = 3,
	WRITE = 4,
	OVERWRITE = 5,
	ERROR = 6
};


class WebServer {
	private:
		
		std::ifstream		configFile;
		std::string			configFilename;
		std::string 		fileContent;
		/* Socket Configuration */
		std::map<int, ListeningSocket *>	serverSocket;
		std::map<int, ListeningSocket *>	acceptedSocket;
		
		std::vector<Server *>	servers;
		
		
		int kq;
		int client_events[MAX_CLIENTS];
		void	processConfigFile();

	public:
		WebServer();
		~WebServer();
		WebServer(WebServer const &copy);
		WebServer &operator=(WebServer const &copy);

		void	loadConfigFile(std::string configFile);
		
		
		void	launchServers();
		
		void 	newConnection(int fd);
		void	createSocket();
		void	addEventSet();
		void	eventLoop();
		
		int getConnection(int fd);
		int	addConnection(int fd);
		int	removeConnection(int fd);
		struct sockaddr_in convertHost(std::string hostname, int port);

		void removeFilter(int fd, int type);
		void addFilter(int fd, int type);
};
