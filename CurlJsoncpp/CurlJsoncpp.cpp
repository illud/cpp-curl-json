#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Post() {
    CURL* curl;
    CURLcode res;
    struct curl_slist* header;
    std::string readBuffer;
    std::string jsonstr = "{ title: 'curl',body : 'curl',userId : 1980}";

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* post a curl handle */
    curl = curl_easy_init();
    if (curl) {

        header = NULL;
        header = curl_slist_append(header, "Content-Type: application/json");
        header = curl_slist_append(header, "Accept: */*");
        //header = curl_slist_append(header, "Origin: https://jsonplaceholder.typicode.com");
       // header = curl_slist_append(header, "Referer: https://jsonplaceholder.typicode.com");
        header = curl_slist_append(header, "User-Agent: Mozilla/4.0 (Windows 7 6.1) Java/1.7.0_51");

        /* First set the URL that is about to receive our POST. This URL can
       just as well be an https:// URL if that is what should receive the
       data. */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts");

        /* Now specify the POST data */
       //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonstr.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonstr.length());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res == CURLE_OK){
            std::cout << "Posted" << std::endl;
        }
        else{
            std::cout << curl_easy_strerror((CURLcode)res) << std::endl;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void Get() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts?userId=1");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        //std::cout << readBuffer.c_str() << std::endl;

        // json reader
        Json::Reader reader;
        // this will contain complete JSON data
        Json::Value completeJsonData;
        // reader reads the data and stores it in completeJsonData
        reader.parse(readBuffer, completeJsonData);
        // complete JSON data
        //std::cout << "Complete JSON data : " << std::endl << completeJsonData << std::endl;

        for (int i = 0; i < completeJsonData.size(); i++)
        {
            // get the title associated with name key
            std::cout << "Title: " << completeJsonData[i]["title"] << std::endl;
        }
    }
}

void Put() {
    CURL* curl;
    CURLcode res;
    struct curl_slist* header;
    std::string readBuffer;
    std::string jsonstr = "{id: 1,title : 'foo',body : 'bar',userId : 1}";

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* put a curl handle */
    curl = curl_easy_init();
    if (curl) {

        header = NULL;
        header = curl_slist_append(header, "Content-Type: application/json");
        header = curl_slist_append(header, "Accept: */*");
        header = curl_slist_append(header, "User-Agent: Mozilla/4.0 (Windows 7 6.1) Java/1.7.0_51");

        /* First set the URL that is about to receive our POST. This URL can
       just as well be an https:// URL if that is what should receive the
       data. */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts/1");

        /* Now specify the POST data */
       //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonstr.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonstr.length());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res == CURLE_OK) {
            std::cout << "Updated" << std::endl;
        }
        else {
            std::cout << curl_easy_strerror((CURLcode)res) << std::endl;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void Delete() {
    CURL* curl;
    CURLcode res;
    struct curl_slist* header;
    std::string readBuffer;
    std::string jsonstr = "{id: 1,title : 'foo',body : 'bar',userId : 1}";

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* put a curl handle */
    curl = curl_easy_init();
    if (curl) {

        header = NULL;
        header = curl_slist_append(header, "Content-Type: application/json");
        header = curl_slist_append(header, "Accept: */*");
        header = curl_slist_append(header, "User-Agent: Mozilla/4.0 (Windows 7 6.1) Java/1.7.0_51");

        /* First set the URL that is about to receive our POST. This URL can
       just as well be an https:// URL if that is what should receive the
       data. */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts/1");

        /* Now specify the POST data */
       //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonstr.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonstr.length());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res == CURLE_OK) {
            std::cout << "Deleted" << std::endl;
        }
        else {
            std::cout << curl_easy_strerror((CURLcode)res) << std::endl;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main()
{
    Post();
    Get();
    Put();
    Delete();

    system("pause");
    return 0;
}