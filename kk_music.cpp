#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <unistd.h>


#include "/home/pi/json.hpp"
using json = nlohmann::json;
using namespace std;

const string PATHJSON = "/home/pi/config.json";

int lastTrek = 0;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
  for(;;) {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.105/config.json");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    auto CONFIG = json::parse(readBuffer);

    int trek = CONFIG["trek"];

    if(trek != lastTrek && CONFIG["status"] == "playing") { // замена трека
        system("killall omxplayer.bin");
        lastTrek = trek;

        switch (trek) {
            case 1 :
                cout << "trek 1" << endl;
                system("omxplayer -o local --vol 600 KK_main.mp3 &");
                break;
            case 2 :
                cout << "trek 2" << endl;
                system("omxplayer -o local --vol 800 KK_5min.mp3 &");
                break;
            case 3 :
                cout << "trek 3" << endl;
                system("omxplayer -o local KK_win.mp3 &");
                break;
            case 4 :
                cout << "trek 4" << endl;
                system("omxplayer -o local --vol 800 KK_loose.mp3 &");
                break;
            case 8 :
                cout << "trek 8" << endl;
                system("omxplayer -o local --vol 750 KK_legend.wav &");
                break;
        } 
    }



    sleep(5); // 1 секунда

  }
  


  }
  return 0;
}