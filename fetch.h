// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// FETCH.H
// Fetch class is used to download a range of tiles from a tileserver
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef FETCH_H
#define FETCH_H

#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <string>

size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    std::string data((const char*) ptr, (size_t) size * nmemb);
    *((std::stringstream*) stream) << data << std::endl;

    return size * nmemb;
}

class Fetch
{
private:
	void* curl;

	inline bool replace(std::string& str, const std::string& from, const std::string& to);

public:
	Fetch();
	~Fetch();
	inline bool fromUrl(std::string url, int zoom, int x, int y);
};

// CONSTRUCTOR
Fetch::Fetch() {
    curl = curl_easy_init();
}

// DESTRUCTOR
Fetch::~Fetch() {
    curl_easy_cleanup(curl);
}

// REPLACE
// replaces the first occurancy of a string with another string
inline bool Fetch::replace(std::string& str, const std::string& from, const std::string& to) 
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos) 
    {
        return false;
    }

    str.replace(start_pos, from.length(), to);
    return true;
};

// FROM URL
// url would be something like 'http://a.tile.osm.org/{z}/{x}/{y}.png'
inline bool Fetch::fromUrl(std::string url, int zoom, int x, int y)
{
	// replace the zoom, x and y parameters to the url
	this->replace(url, "{z}", std::to_string(zoom));
	this->replace(url, "{x}", std::to_string(x));
	this->replace(url, "{y}", std::to_string(y));

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");

    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(curl);

    /* Check for errors */
    if (res != CURLE_OK) 
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }

    std::string fileContent = out.str();
    std::cout << fileContent << std::endl;
	return true;
};

#endif