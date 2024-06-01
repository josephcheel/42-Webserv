#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <filesystem>
#include <vector>
#include "../inc/colors.h"
#include "../inc/CGI.hpp"

#define MAX_SENT_BYTES 8192
class FileContent
{
private:
	std::string fileName;
	std::vector <std::string> args;
	std::string content;
	std::ifstream file;
	bool isFistFragment;
	bool isFileOpen;
	bool sendComplete;
	bool isCGI;
	std::string CGIFolder;
	struct stat fileStat;
	CGI *cgiModule;

public:
	FileContent();
	FileContent(const std::string &);
	~FileContent();
	int openFile();
	bool setFileName(const std::string &);
	std::string getFileName();
	std::string getContent();
	bool isSendComplete();
	void setFirstFragment(bool);
	bool getFirstFragment();
	std::string getLastModified();
	size_t getContentSize();
	bool isCGIFile();
	void setCGIFile(bool);
	void setCGIFolder(const std::string &);
	std::string getCGIFolder();
};
