#include "vhtml.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


std::ostream& operator <<(std::ostream& out, const vhtml& html) {
    std::cout << html.readBuffer << std::endl;
    return out;
};


vhtml::vhtml(std::string url_point, std::string string_point)
{
    url = url_point;
    get_constructor_res = getHTML();
    if (get_constructor_res == 0)
    {
        size = 0;
        found_element = "\0";
        domain = "\0";
        IP_numb = "\0";
    }
    else
    {
        size = readBuffer.size();
        getIP();
        classname_maping_First();

        if (string_point != "\0") {
            found_element = vhtml_getElement(string_point);
            std::cout << found_element << std::endl;
        }
    }
}

void vhtml::classname_maping_First() {
    
    int *s = new int;
    *s = 0;
    int* start = new int;
    *start = 0;
    std::string* temp = new std::string;
    int* end = new int;
    std::string* res = new std::string;

    for (size_t i = 0; i < size; i++)
    {
        if (i == 0) {
            *s = readBuffer.find("class=\"");
            *start = readBuffer.find("\"", *s);
            *end = readBuffer.find("\"", *start + 1);
            //std::cout << readBuffer.substr(s , 1 + (end - s))  << std::endl;
            *res = readBuffer.substr(*s, 1 + (*end - *s));
            className_map[*res] = readBuffer.find(*res);
            *temp = readBuffer.substr(*s+6);
        }
        else
        {
            *s = temp->find("class=\"");
            if (*s == -1) { break; }
            *start = temp->find("\"" , *s);
            *end = temp->find("\"", *start + 1);
            *res = temp->substr(*s, 1 + (*end - *s));
            *temp = temp->substr(*s+6);
            className_map[*res] = readBuffer.find(*res);
        }
    }

    delete s;
    delete start;
    delete temp;
    delete end;
    delete res;

    //std::cout << readBuffer[n+6] << std::endl;
    //n = readBuffer.substr(n, 200).find("\"");
    //std::cout << readBuffer.substr(n , 7) << std::endl;
}   

void vhtml::show_all_className() {
    for (const auto& pair : className_map) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}

std::string vhtml::get_element(std::string& string_point) {
    found_element = vhtml_getElement(string_point);
    return found_element;
}

std::string vhtml::vhtml_getElement(std::string& str_point) {


    if (readBuffer.find(str_point) == std::string::npos) {
        std::cout << "It isnt hier !" << std::endl;
        return "\0";
    }
    else
    {
        unsigned short int str_point_index = this->readBuffer.find(str_point);
        int end_tag , start_tag;
        end_tag = Get_endTag(str_point_index);
        start_tag = Get_startTag(str_point_index);
        return readBuffer.substr(start_tag, (end_tag - start_tag)+1);
    }
   
};
int vhtml::Get_endTag(unsigned short int& str_point_index) {

    for (unsigned int i = str_point_index; i < size; i++)
    {
        if (readBuffer[i] == '/' && readBuffer[i - 1] == '<') {
            //e_startIndx == i - 1;
            for (unsigned int j = i - 1; j < size; j++)
            {
                if (readBuffer[j] == '>') {
                    return j;
                }
            }
        }
    }

};
int vhtml::Get_startTag(unsigned short int& str_point_index) {
    for (unsigned int i = str_point_index; i > 0; i--) {
        if (readBuffer[i] == '>') {
            //s_startIndx == i;
            for (unsigned int j = i; j > 0; j--) {
                if (readBuffer[j] == '<') {
                    return j;
                }
            }
        }
    }
};


void vhtml::html_size() {
    std::cout << size;
};

size_t vhtml::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    }
    catch (std::bad_alloc& e) {
        return 0;
    }
    return newLength;
}

int vhtml::getHTML() {
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        

        if (res != CURLE_OK) {
            return 0;
        }
    }
}

std::string IP(const std::string& domain) {
    struct addrinfo hints, * res;
    int err;
    char ipstr[INET6_ADDRSTRLEN];

    // آغاز اتصال به Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return "";
    }

    // تنظیمات برای جستجوی آدرس
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;  // فقط IPv4
    hints.ai_socktype = SOCK_STREAM;

    // جستجوی آدرس دامنه
    if ((err = getaddrinfo(domain.c_str(), NULL, &hints, &res)) != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerror(err) << "\n";
        WSACleanup();
        return "";
    }

    // تبدیل آی‌پی به رشته
    struct sockaddr_in* ipv4 = (struct sockaddr_in*)res->ai_addr;
    inet_ntop(AF_INET, &ipv4->sin_addr, ipstr, sizeof(ipstr));

    freeaddrinfo(res);
    WSACleanup();
    return std::string(ipstr);
}

std::string vhtml::get_domain_ip() {
    return IP_numb;
}


void vhtml::getIP() {
    std::string* temp_ptr = new std::string;
    *temp_ptr = url.substr(url.find('/') + 2, 100);
    int* e = new int;
    *e = temp_ptr->find('/');
    delete temp_ptr;
    int* s = new int;
    *s = url.find('/') + 2;
    domain = url.substr(url.find('/') + 2 , (*e - *s)+*s);
    delete s;
    delete e;
    IP_numb = IP(domain);
}

vhtml::~vhtml()
{
    curl_easy_cleanup(curl);
}