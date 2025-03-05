#pragma once
#include "vhtml.h"
class vhtml_tag : protected vhtml
{
public:
	vhtml_tag(std::string url_base, std::string string_base = "\0");
	~vhtml_tag();

private:

};

vhtml_tag::vhtml_tag(std::string url_base, std::string string_base) : vhtml(url_base, string_base)
{
	std::cout << 0;
}

vhtml_tag::~vhtml_tag()
{
}


