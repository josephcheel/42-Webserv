
#include "../inc/Header.hpp"

Header::Header()
{
	protocol = "HTTP/1.1";
	contentLength = 0;
	contentType = "text/html";
	server = "webserv";
	this->setDate();
}

Header::Header(std::string receiveHeader)
{
	std::istringstream iss(receiveHeader);
	std::string line;

	while (std::getline(iss, line))
	{
		size_t colonPos = line.find(':');
		if (colonPos != std::string::npos)
		{
			std::string key = line.substr(0, colonPos);
			std::string value = line.substr(colonPos + 1);
			key.erase(0, key.find_first_not_of(' '));
			key.erase(key.find_last_not_of(' ') + 1);
			value.erase(0, value.find_first_not_of(' '));
			value.erase(value.find_last_not_of(' '));
			this->attributes[key] = value;
		}
		else
		{
			if (std::count(line.begin(), line.end(), ' ') == 2)
			{
				size_t firstSpace = line.find(' ');
				size_t secondSpace = line.find(' ', firstSpace + 1);
				method = line.substr(0, firstSpace);
				path = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
				protocol = line.substr(secondSpace + 1);
				if (!protocol.empty() && protocol[protocol.size() - 1] == '\r')
					protocol.erase(protocol.size() - 1);

			}
		}
	}
	// std::cout << "HEADER" << std::endl;
	// for (std::map<std::string, std::string>::const_iterator it = attributes.begin(); it != attributes.end(); ++it)
	// {
	// 	std::cout << it->first << " => " << it->second << std::endl;
	// }
}

void Header::setAttribute(std::string key, std::string value)
{
	this->attributes[key] = value;
}

std::map<std::string, std::string> Header::getAttributes()
{
	return attributes;
}

Header::~Header(){}

std::string Header::getMethod()
{
	return method;
}
ExtendedString Header::getPath()
{
	return path;
}

std::string Header::getProtocol()
{
	return protocol;
}

void Header::setPath(std::string path)
{
	this->path = path;
}

std::string Header::generateHeader() const
{
	std::string header;
	
	// std::cout << "Version: $" << Version << "$" << std::endl;
	header = protocol + " " + status + "\r\n"; 
	header += "Server: " + server + "\r\n";
	header += "Date: " + date + "\r\n";
	if (lastModified != "")
		header += "Last-modified: " + lastModified + "\r\n";
	if(contentLength != 0)
		header += "Content-Length: " + toString(contentLength) + "\r\n";
	header += "Content-Type: " + contentType + "\r\n";
	for (std::map<std::string, std::string>::const_iterator it = attributes.begin(); it != attributes.end(); ++it)
		header += it->first + ": " + it->second + "\r\n";
	
	header += "\r\n";
	
	return header;
}

std::string Header::getAttribute(std::string key)
{
	return attributes[key];
}

std::string Header::getContentType() 
{
	return contentType;
}

void Header::setProtocol(std::string protocol)
{
	this->protocol = protocol;
}

void Header::setStatus(std::string status)
{
	this->status = status;
}

void Header::setServer(std::string server)
{
	this->server = server;
}

void Header::setDate()
{
	// Get the current time
	std::time_t currentTime = std::time(NULL);

	// Convert the current time to a string in the desired format
	std::tm* timeInfo = std::gmtime(&currentTime);
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%A, %d-%b-%y %H:%M:%S GMT", timeInfo);

	// Set the date in the header
	this->date = buffer;
}

void Header::setLastModified(std::string lastModified)
{
	this->lastModified = lastModified;
}

void Header::setContentLength(size_t contentLength)
{
	this->contentLength = contentLength;
}

void Header::setContentType(std::string contentType)
{
	size_t point = contentType.find_last_of(".");
	std::string extension = contentType.substr(point + 1, contentType.size());

	/* Create once only */
	std::map<std::string, std::string> Mimetype = create_filetypes();

	if (Mimetype.find(extension) != Mimetype.end())
		this->contentType = Mimetype[extension];
	else
		this->contentType = "text/html";

}

void Header::printReceivedHeader()
{
	std::cout << "Method: " << method << std::endl;
	std::cout << "Path: " << path << std::endl;
	std::cout << "Protocol: " << protocol << std::endl;
	std::cout << "Status: " << status << std::endl;
	std::cout << "Server: " << server << std::endl;
	std::cout << "Date: " << date << std::endl;
	std::cout << "Last-modified: " << lastModified << std::endl;
	std::cout << "Content-Length: " << contentLength << std::endl;
	std::cout << "Content-Type: " << contentType << std::endl;
	for (std::map<std::string, std::string>::const_iterator it = attributes.begin(); it != attributes.end(); ++it)
		std::cout << it->first << ": " << it->second << std::endl;
}
