/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 07:30:53 by eavedill          #+#    #+#             */
/*   Updated: 2024/04/26 16:23:26 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/SendFile.hpp"

FileName::FileName()
{
	this->filename = "";
	this->setErrCode();
}

FileName::FileName(FileName const &src)
{
	*this = src;
}

FileName &FileName::operator=(FileName const &src)
{
	this->Err_code = src.Err_code;
	this->filename = src.filename;
	return (*this);
}

FileName::FileName(std::string filename)
{
	this->filename = filename;
	this->setErrCode();
}

FileName::~FileName(){}


void FileName::setErrCode()
{
	struct stat *buf;

	int result = stat(this->filename.c_str(), buf);
	if (this->filename == "" || result == -1)
		this->Err_code = 404;
	else
		this->Err_code = 200;
}

int FileName::getErrCode() const
{
	return (this->Err_code);
}

std::string FileName::getErrDesc()
{
	std::map<int, std::string> errorTypes = getHttpErrorTypes();
	return (errorTypes[this->Err_code]);
}

std::string FileName::retFileContent()
{
	std::string content = "";
	std::fstream file2open;

	file2open.open(this->filename.c_str(), std::ios::in);

	while (std::getline(filename, line, '\n'))
		content += line_2;
	return (this->filename);
}