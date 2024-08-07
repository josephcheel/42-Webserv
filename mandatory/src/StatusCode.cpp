/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:51:07 by eavedill          #+#    #+#             */
/*   Updated: 2024/07/04 07:37:03 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/StatusCode.hpp"

StatusCode::StatusCode()
{
	this->createDefaultErrorCodes();
	this->setFileContentForStatusCode(0, DEFAULT_ERROR_FILE);
}

StatusCode::~StatusCode()
{
}

int StatusCode::getCode()
{
	return this->currentCode;
}

void StatusCode::createDefaultErrorCodes()
{
	this->mapCodes[0] = "000 Template";
	this->mapCodes[100] = "100 Continue";
	this->mapCodes[101] = "101 Switching Protocols";
	this->mapCodes[200] = "200 OK";
	this->mapCodes[201] = "201 Created";
	this->mapCodes[202] = "202 Accepted";
	this->mapCodes[203] = "203 Non - Authoritative Information";
	this->mapCodes[204] = "204 No Content";
	this->mapCodes[205] = "205 Reset Content";
	this->mapCodes[206] = "206 Partial Content";
	this->mapCodes[300] = "300 Multiple Choices";
	this->mapCodes[301] = "301 Moved Permanently";
	this->mapCodes[302] = "302 Found";
	this->mapCodes[303] = "303 See Other";
	this->mapCodes[304] = "304 Not Modified";
	this->mapCodes[305] = "305 Use Proxy";
	this->mapCodes[307] = "307 Temporary Redirect";
	this->mapCodes[400] = "400 Bad Request";
	this->mapCodes[401] = "401 Unauthorized";
	this->mapCodes[402] = "402 Payment Required";
	this->mapCodes[403] = "403 Forbidden";
	this->mapCodes[404] = "404 Not Found";
	this->mapCodes[405] = "405 Method Not Allowed";
	this->mapCodes[406] = "406 Not Acceptable";
	this->mapCodes[407] = "407 Proxy Authentication Required";
	this->mapCodes[408] = "408 Request Time - out";
	this->mapCodes[409] = "409 Conflict";
	this->mapCodes[410] = "410 Gone";
	this->mapCodes[411] = "411 Length Required";
	this->mapCodes[412] = "412 Precondition Failed";
	this->mapCodes[413] = "413 Request Entity Too Large";
	this->mapCodes[414] = "414 Request - URI Too Large";
	this->mapCodes[415] = "415 Unsupported Media Type";
	this->mapCodes[416] = "416 Requested range not satisfiable";
	this->mapCodes[417] = "417 Expectation Failed";
	this->mapCodes[500] = "500 Internal Server Error";
	this->mapCodes[501] = "501 Not Implemented";
	this->mapCodes[502] = "502 Bad Gateway";
	this->mapCodes[503] = "503 Service Unavailable";
	this->mapCodes[504] = "504 Gateway Time - out";
	this->mapCodes[505] = "505 HTTP Version not supported";
}

void StatusCode::setFileContentForStatusCode(int CodeNumber, const std::string &CodeFileContent)
{
	ExtendedString content("");
	std::ifstream fileStream;
	fileStream.open(CodeFileContent.c_str(), std::ios::out | std::ios::binary); //| std::ios::app | std::ios::ate
	if(fileStream.is_open())
	{
		char buffer[MAX_SENT_BYTES];
		while (fileStream.read(buffer, MAX_SENT_BYTES))
			content.append(buffer, fileStream.gcount());
		content.append(buffer, fileStream.gcount());
	}
	else
	{
		content = this->getInternContent();
		printLog("WARNING", CodeFileContent + " File does not exist.\t Set error page to default " CHR_GREEN "GET" RESET " value");
	}
	mapCodesFileContent[CodeNumber] = content;
}

std::string StatusCode::getCodeContent(int errorCode)
{
	this->setCurrentCode(errorCode);
	return mapCodes[errorCode];
}

ExtendedString StatusCode::getFileContentForStatusCode(int errorCode)
{
	this->setCurrentCode(errorCode);
	ExtendedString content;
	if (mapCodesFileContent.find(errorCode) == mapCodesFileContent.end())
	{
		content = mapCodesFileContent[0];
		content.replaceString("{{ErrorCode}}", mapCodes[errorCode]);
		return content;
	}
	return mapCodesFileContent[errorCode];
}

void StatusCode::setCurrentCode(int code)
{
	this->currentCode = code;
}

int StatusCode::getCurrentCode()
{
	return this->currentCode;
}

void StatusCode::loadErrorPageFromDir(const ExtendedString &dir)
{
	struct dirent *dirp;
	DIR *dp;
	if ((dp = opendir(dir.c_str())) == NULL)
	{
		return;
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_type == DT_REG)
		{
			std::string fileName = dir + "/" + dirp->d_name;
			std::string code = dirp->d_name;
			code = code.substr(0, code.find("."));
			setFileContentForStatusCode(atoi(code.c_str()), fileName);
		}
	}
	closedir(dp);
}

ExtendedString StatusCode::getInternContent()
{
	ExtendedString content;
	content = "<html>\n";
	content += "<head>\n";
	content += "<title> {{ErrorCode}}</title>\n";
	content += "</head>\n";
	content += "<body>\n";
	content += "<table border = \"0\" cellspacing = \"2\">\n";
	content += "<tr><td><h2>This is an internal text defined.</h2></td></tr>\n";
	content += "<tr><td><h4>{{ErrorCode}}.<h4></td></tr>\n";
	content += "<tr><td><h5>Please generate the file ./templates/error_template.html or define it on statusCodesDefinition.hpp</h5></td></tr>\n";
	content += "</table>\n";
	content += "</body>\n";
	content += "</html>\n";
	return content;
}