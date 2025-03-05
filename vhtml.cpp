#include "vhtml.h"
vhtml::vhtml(std::string url_point, std::string string_point)
{
    url = url_point;
    getHTML();
    size = readBuffer.size();

    if (string_point != "\0") {
        vhtml_maping(string_point);
    }

}
void vhtml::vhtml_maping(std::string str_point) {
    if (readBuffer.find(str_point) == std::string::npos) {
        std::cout << "It isnt hier !" << std::endl;
    }
    else
    {
        size_t str_point_start = readBuffer.find(str_point), str_point_end = str_point_start + std::size(str_point);

        for (size_t i = str_point_start; i < str_point_end; i++)
        {
            std::cout << readBuffer.at(i) << std::endl;
        }
             

        //std::cout << "index of str point : " << str_point_start << std::endl;
        //std::cout << "char in this index number : " << readBuffer.at(str_point_start) << std::endl;
        //std::cout << "size : " << size << std::endl;
    }
   
};



std::ostream& operator <<(std::ostream& out, const vhtml& html) {
    std::cout << html.readBuffer << std::endl;
    return out;
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

void vhtml::getHTML() {
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        }
    }
}

vhtml::~vhtml()
{
    // std::cout << "\nits good by" << std::endl;
}