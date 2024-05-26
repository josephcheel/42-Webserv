/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:49:08 by eavedill          #+#    #+#             */
/*   Updated: 2024/05/26 15:25:25 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Client.hpp"

Client::Client(){}

Client::Client(Server *srv)
{
	this->server = srv;
	this->fileContent.setCGIFolder(srv->getCGIFolder());
}

Client::Client(std::string const &str, Server *srv)
{
	this->server = srv;
	this->fileContent.setCGIFolder(srv->getCGIFolder());
	this->loadCompleteClient(str);
}

Client &Client::operator=(Client const &rsh)
{
	std::map<std::string, std::string>::const_iterator itb = rsh.Request.begin();
	std::map<std::string, std::string>::const_iterator ite = rsh.Request.end();
	while(itb != ite)
	{
		this->Request[itb->first] = itb->second;
		itb++;
	}
	return (*this);
}

Client::~Client()
{
}

void Client::addKeyReq(std::string const &key, std::string const &value)
{
	this->Request[key] = value;
}

void Client::addKeyType(std::string const &value)
{
	this->Request[REQ_TYPE] = value;
}

void Client::addKeyFile(std::string const &value)
{
	this->Request[REQ_FILE] = this->server->getRoot() + value;
	if (value == "/")
		this->Request[REQ_FILE] += this->server->getIndex();
	replaceString(this->Request[REQ_FILE], "%20", " ");
	std::cout << "File: " << this->Request[REQ_FILE] << std::endl;
}

void Client::addKeyVers(std::string const &value)
{
	this->Request[REQ_VER] = value;
}

std::map<std::string, std::string>::iterator Client::findClient(std::string const &key)
{
	return (this->Request.find(key));
}

std::map<std::string, std::string>::iterator Client::getBeginClient()
{
	return (this->Request.begin());
}

std::map<std::string, std::string>::iterator Client::getEndClient()
{
	return (this->Request.end());
}

void Client::clearClient()
{
	this->Request.clear();
}

void Client::deleteClient(std::string const &key)
{
	this->Request.erase(key);
}

void Client::updateClient(std::string const &key, std::string const &value)
{
	this->Request[key] = value;
}

void Client::loadCompleteClient( std::string const &str)
{
	std::vector<std::string> lines = splitString(str, '\n');
	std::vector<std::string> parts = splitString(lines[0], ' ');
	if (parts.size() == 3)
	{
		std::cout << "Parts: " << parts[0] << " " << parts[1] << " " << parts[2] << std::endl;
		this->addKeyType(parts[0]);
		this->addKeyFile(parts[1]);
		this->addKeyVers(parts[2]);
	}
	std::cout << "Lines: " << str << std::endl;
	for (size_t i = 1; i < lines.size(); i++)
			this->addKeyReq(lines[i].substr(0, lines[i].find(":")), lines[i].substr(lines[i].find(":") + 1, lines.size()));
	this->loadDataHeader();
}




// std::string getExtension(std::string filePath)
// {
// 	size_t point = filePath.find_last_of(".");
// 	std::string extension = filePath.substr(point + 1, filePath.size());

// 	std::map<std::string, std::string> Mimetype = create_filetypes();

// 	if (Mimetype.find(extension) != Mimetype.end())
// 	{
// 		std::cout << CHR_BLUE << "found extension " << extension << ": " << Mimetype[extension] << RESET << std::endl;
// 		return(Mimetype[extension]);
// 	}
// 	else
// 	{
// 		std::cout << CHR_MGENTA << "NOT found extension " << extension << RESET << std::endl;
// 		return("text/html"); 
// 	}
// }


/*
Normalize the path, removes .., adds ./ at teh beggining if necessary, removes / at the end, removes duplicate /.
*/
std::string	Client::normalizePath(std::string path)
{
	while (path.find("..") != std::string::npos)
		path.erase(path.find(".."), 2);

	std::vector<std::string> parts = splitString(path, '/');
	std::string normalizePath;
	for (size_t i = 0; i < parts.size(); i++)
	{
		if (i == 0)
		{
			if (parts[i] == ".")
				normalizePath = parts[i] + "/";
			else if (i == (parts.size() - 1))
				normalizePath = "/" + parts[i];
			else
				normalizePath = "/" + parts[i] + "/";
		}
		else if (i == (parts.size() - 1))
			normalizePath += parts[i];
		else
			normalizePath += parts[i] + "/";
	}
	return (normalizePath);
}

std::string Client::getFilePath()
{
	std::cout << "Normalizing Path: " << normalizePath(server->getRoot()) << std::endl;
	std::string filePath = normalizePath(server->getRoot()) +  this->Request[REQ_FILE];
	if (filePath.at(filePath.size() - 1) == '/')
		filePath += server->getIndex();
	filePath = filePath.substr(0, filePath.find("?"));
	std::cout << "MY File Path: " << filePath << std::endl;

	return (filePath);
}

std::string Client::getFileContent()
{
	std::string content;
		content = this->fileContent.getContent();
	return (content);
}

// std::string Client::getAnswerToSend()
// {	
// 	std::string answer;
// 	std::string filePath = getFilePath();
// 	std::string file_content = getFileContent(filePath);
// 	if (file_content.find("HTTP/1.1 404 Not Found\r\n\r\n") != std::string::npos)
// 		return ("HTTP/1.1 404 Not Found\r\n\r\n");
// 	answer += "HTTP/1.1 200 OK\r\nContent-Type: " + getExtension(filePath) + "\r\nContent-Lenght: " + std::to_string(file_content.size())  + "\r\n\r\n";
// 	std::cout << getExtension(filePath) << std::endl;
	
// 	std::cout << "File Path: " << filePath << "$" << std::endl;
// 	// std::ifstream file;
// 	std::cout << "File Path: " << filePath << std::endl;
// 	answer += file_content;
// 	return (answer);
// }
std::string Client::getAnswerToSend()
{	
	std::string answer;
	std::string filePath = this->fileContent.getFileName();
	std::cout << "File Path: " << filePath << std::endl;
	std::string file_content = getFileContent();
	if (this->fileContent.getFirstFragment())
	{
		std::cout << "Header :" << header.generateHeader() << std::endl;
		answer += header.generateHeader() + file_content;
		this->fileContent.setFirstFragment(false);
	}
	else
		answer += file_content;
	return (answer);
}

bool Client::isSendComplete()
{
	return this->fileContent.isSendComplete();
}

void Client::loadDataHeader()
{
	std::cout << "File1: " << this->Request[REQ_FILE] << std::endl;
	if (fileContent.setFileName(this->Request[REQ_FILE]))
	{
		header.setContentType(this->Request[REQ_FILE]);
		std::cout << "confirm opened" << std::endl;
		header.setLastModified(fileContent.getLastModified());
		header.setContentLength(fileContent.getContentSize());
		header.setStatus("200 OK");
		header.setServer(server->getServerName());
	}
	else
		header.setStatus("404 Not Found");
}
