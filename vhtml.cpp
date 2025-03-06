#include "vhtml.h"

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
    }
    else
    {
        size = readBuffer.size();
        if (string_point != "\0") {
            found_element = vhtml_getElement(string_point);
        }
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
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            return 0;
        }
    }
}

vhtml::~vhtml()
{
    // std::cout << "\nits good by" << std::endl;
}