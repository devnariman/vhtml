#pragma once
#include <curl/curl.h>
#include <iostream>
#include <map>
#include <vector>


class vhtml
{
public:
	vhtml(std::string url_point, std::string string_point = "\0");
	void html_size();
	void show_all_className();
	std::string get_domain_ip();
	void show_all_className_tagElement();
	std::string get_element(std::string&);
	friend std::string IP(const std::string& domain);
	friend std::ostream& operator <<(std::ostream& out, const vhtml& html);
	~vhtml();
private:
	// variable : 
	CURL* curl = curl_easy_init();
	CURLcode res;
	std::string readBuffer;
	std::string url;
	short unsigned int size;
	std::string domain;
	std::string IP_numb;
	size_t get_constructor_res;
	std::string found_element;
	std::map <std::string, int>::iterator map_iter;
	std::map <std::string , int> className_lineNumber_map;
	std::vector <std::string> all_startelement_whit_class;
	std::vector <std::string>::iterator vector_element_whit_class_iter;
	//*******************************
	//*******************************
	//*******************************
	//*******************************
	// function : 
	
	std::string vhtml_getElement(std::string&);
	int Get_endTag(unsigned short int&);
	int Get_startTag(unsigned short int&);
	int getHTML();
	void getIP();
	void classname_maping_line();
	static size_t WriteCallback(void*, size_t, size_t, std::string*);
};

