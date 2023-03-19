#include <iostream>
#include <curl/curl.h>
#include <list>
#include <string>

using namespace std;

// callback function to handle the HTTP response
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    return size * nmemb;
}

int main()
{
    list<int> status_codes; // create a list to store the status codes

    // initialize cURL
    curl_global_init(CURL_GLOBAL_ALL);

    // create a cURL easy handle for each domain
    CURL* curl_handle = curl_easy_init();
    CURL* curl_handle2 = curl_easy_init();
    CURL* curl_handle3 = curl_easy_init();

    // set the options for each cURL handle
    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.example.com");
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_NOBODY, 1L);

    curl_easy_setopt(curl_handle2, CURLOPT_URL, "http://www.google.com");
    curl_easy_setopt(curl_handle2, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_handle2, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle2, CURLOPT_NOBODY, 1L);

    curl_easy_setopt(curl_handle3, CURLOPT_URL, "http://www.kpn.com");
    curl_easy_setopt(curl_handle3, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_handle3, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle3, CURLOPT_NOBODY, 1L);

    // add the handles to a multi-handle
    CURLM* multi_handle = curl_multi_init();
    curl_multi_add_handle(multi_handle, curl_handle);
    curl_multi_add_handle(multi_handle, curl_handle2);
    curl_multi_add_handle(multi_handle, curl_handle3);

    // perform the requests in parallel
    int still_running;
    do {
        curl_multi_perform(multi_handle, &still_running);
    } while (still_running);

    // get the status codes and add them to the list
    int http_status_code;
    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_status_code);
    status_codes.push_back(http_status_code);

    curl_easy_getinfo(curl_handle2, CURLINFO_RESPONSE_CODE, &http_status_code);
    status_codes.push_back(http_status_code);

    curl_easy_getinfo(curl_handle3, CURLINFO_RESPONSE_CODE, &http_status_code);
    status_codes.push_back(http_status_code);

    // clean up
    curl_multi_remove_handle(multi_handle, curl_handle);
    curl_multi_remove_handle(multi_handle, curl_handle2);
    curl_multi_remove_handle(multi_handle, curl_handle3);
    curl_multi_cleanup(multi_handle);

    curl_easy_cleanup(curl_handle);
    curl_easy_cleanup(curl_handle2);
    curl_easy_cleanup(curl_handle3);

    curl_global_cleanup();

    // print out the status codes
    for (auto it = status_codes.begin(); it != status_codes.end(); ++it) {
        cout << "Status code: " << *it << endl;
    }

    return 0;
}

