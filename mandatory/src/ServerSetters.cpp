#include "../inc/Server.hpp"

void Server::setHost(std::string const &host) { this->Host = host; }
void Server::setServerName(std::string const &server_name) { this->serverName = server_name; }
void Server::setErrorPage(std::string const &error_page) {this->errorPage = error_page;}
void Server::setMaxClientBodySizeStr(std::string const &max_client_body_size) { this->maxBodySizeStr = max_client_body_size; }
void Server::setMaxClientBodySize(size_t const &max_client_body_size) { this->maxBodySize = max_client_body_size; }
void Server::setRoot(std::string const &root) { this->root = root; }
void Server::setIndex(std::string const &index) { this->index = index; }
void Server::setCGIFolder(std::string const &str) { this->cgiModule->setCGIFolder(str); }
void Server::addLocation(std::string const &content) { this->locations.push_back(new Location(content)); }

void Server::setHostAddr(in_addr_t Addr) { this->hostAddr = Addr; }

void Server::setCGIExtension(std::string const &str) 
{
	this->cgiModule->setCGIMapExtensions(str);
}

void Server::setIsDefault(std::string const &is_default)
{
	if (is_default == "true")
		this->isDefault = true;
	else if (is_default == "false")
		this->isDefault = false;
	else
	{
		std::cerr << "Error: Valor de is_default no reconocido." << std::endl;
		exit(1);
	}
}

void Server::setPorts(std::string const &portsLine)
{
	std::string aux;
	std::istringstream portStream(portsLine);
	while (std::getline(portStream, aux, ','))
	{
		if (aux.find(":") != std::string::npos)
		{
			std::vector<std::string> ports = splitString(aux, ':');
			if (ports.size() != 2)
			{
				printLog("ERROR", "Port\t\t\t\tWrong range of ports defined.");
				exit(1);
			}
			if (isNumber(ports[0]) == false || isNumber(ports[1]) == false)
			{
				printLog("ERROR", "Port\t\t<" + ports[0] + "> or <" + ports[1] + ">\t\tnot a number.");
				exit(1);
			}
			if (stringToSizeT(ports[0]) > stringToSizeT(ports[1]))
			{
				printLog("ERROR", "Port\t\t<" + ports[0] + ">:<" + ports[1] + ">\tports range must be ascendent");
				exit(1);
			}
			if (stringToSizeT(ports[1]) - stringToSizeT(ports[0]) > 10)
			{
				printLog("ERROR", "Port\t\t<" + ports[0] + ">:<" + ports[1] + ">\tports range can't have more than 10 ports");
				exit(1);
			}
			for (size_t i = stringToSizeT(ports[0]); i <= stringToSizeT(ports[1]); i++)
			{
				this->ports.push_back(toString(i));
			}
			
		}
		else
		{
			if (isNumber(aux) == false)
			{
				printLog("ERROR", "Port\t\t<" + aux + ">\t\tnot a number.");
				exit(1);
			}
			this->ports.push_back(aux);
		}
	}
}

void Server::setAutoindex(std::string const &theAutoIndex)
{
	this->autoIndexStr = theAutoIndex;
}
