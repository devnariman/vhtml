#pragma once

#include <curl/curl.h>
#include <iostream>
class vhtml
{
public:
	vhtml(std::string url_point, std::string string_point = "\0");
	void html_size();
	friend std::ostream& operator <<(std::ostream& out, const vhtml& html);
	~vhtml();
private:
	// variable : 
	CURL* curl = curl_easy_init();
	CURLcode res;
	std::string readBuffer;
	std::string url;
	short unsigned int size;

	//*******************************
	//*******************************
	//*******************************
	//*******************************


	// function : 
	void vhtml_maping(std::string);
	void getHTML();
	static size_t WriteCallback(void*, size_t, size_t, std::string*);
};

