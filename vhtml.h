#pragma once
#include <curl/curl.h>
#include <iostream>
class vhtml
{
public:
	vhtml(std::string url_point, std::string string_point = "\0");
	void html_size();
	std::string get_element(std::string&);
	friend std::ostream& operator <<(std::ostream& out, const vhtml& html);
	~vhtml();
private:
	// variable : 
	CURL* curl = curl_easy_init();
	CURLcode res;
	std::string readBuffer;
	std::string url;
	short unsigned int size;
	size_t get_constructor_res;
	std::string found_element;
	//*******************************
	//*******************************
	//*******************************
	//*******************************
	// function : 
	std::string vhtml_getElement(std::string&);
	int Get_endTag(unsigned short int&);
	int Get_startTag(unsigned short int&);
	int getHTML();
	static size_t WriteCallback(void*, size_t, size_t, std::string*);
};

