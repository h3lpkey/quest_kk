#include <iostream>
#include <fstream>
#include <string>
#include "/var/www/qf2016.pro/json.hpp"
#include <wiringPiI2C.h>
#include <wiringPi.h>
using json = nlohmann::json;
using namespace std;

// адреса
const int ADRKASSA   = 0x04;
const int ADRWHEEL   = 0x15;
const int ADRCHEEZE  = 0x06;
const int ADRLOPATKA = 0x07;
const int ADRKEGI    = 0x08;
const int ADRMUSIC   = 0x09;

// GPIO 7 - нога через которую запитаны вся логика красти
const int FLUSHPIN   = 7;

// стартовое время квеста
const int TIMENOW   = 0;
const int TIMESTART = 0;
const int TIMEPLUS  = 0;
const int TIMEEND   = 3600;

json CONFIG; // настройки квеста, динамичный json файл

// номера треков
const int TREKMAIN  = 1;
const int TREK5MIN  = 2;
const int TREKWIN   = 3;
const int TREKLOOSE = 4;

// путь до конфига
const string PATHJSON = "/var/www/qf2016.pro/config.json";

void checkKassa() {

    int fd = wiringPiI2CSetup(ADRKASSA);
    int sendDataKassa = 0;
    if( CONFIG["dollar"] == 1 and
        CONFIG["order"]  == 1 ) {
        sendDataKassa = 1;
    } else {
        sendDataKassa = 0;
    }
    
    CONFIG["dollar"] = wiringPiI2CRead(fd);
    wiringPiI2CWrite(fd, sendDataKassa);
}

void checkWheel() {

    int fd = wiringPiI2CSetup(ADRWHEEL);
    int sendDataWheel = 0;
    if(CONFIG["wheel"] == 1) {
        sendDataWheel = 1;
        CONFIG["wheel"] = 1;
    } else {
        sendDataWheel = 0;
    }
    CONFIG["wheel"] = wiringPiI2CRead(fd);
    wiringPiI2CWrite(fd, sendDataWheel);
}

void checkCheeze() {

    int fd = wiringPiI2CSetup(ADRCHEEZE);
    int sendData = 0;
    if( CONFIG["cheeze"] == 1) {
        sendData = 1;
    } else {
        sendData = 0;
    }
    CONFIG["cheeze"] = wiringPiI2CRead(fd);
    wiringPiI2CWrite(fd, sendData);
}

void checkLopatka() {

    int fd = wiringPiI2CSetup(ADRLOPATKA);
    CONFIG["lopatka"] = wiringPiI2CRead(fd);
    int sendData = 0;
    if( CONFIG["lopatka"] == 1) {
        sendData = 1;
    } else {
        sendData = 0;
    }
    wiringPiI2CWrite(fd, sendData);
}

void checkKegi() {

    int fd = wiringPiI2CSetup(ADRKEGI);
    int sendDataKegi = 0;
    if( CONFIG["kegi"] == 1) {
        sendDataKegi = 1;
    } else {
        sendDataKegi = 0;
    }
    wiringPiI2CWrite(fd, sendDataKegi);
    CONFIG["kegi"] = wiringPiI2CRead(fd);
}

void checkMusic() {

    int fd = wiringPiI2CSetup(ADRMUSIC);

    CONFIG["trek"] = wiringPiI2CRead(fd);

    if (CONFIG["trek"] == 3) {
        CONFIG["status"] = "end";
    }

    if(CONFIG["now"] == 3300) {
        wiringPiI2CWrite(fd, TREK5MIN);    
    }

    if(CONFIG["now"] < CONFIG["end"]) {
        wiringPiI2CWrite(fd, TREKMAIN);    
    }

    if (CONFIG["now"] > CONFIG["end"]) {
        CONFIG["status"] = "end";
        CONFIG["final"] = 1;
        cout << "time is up! game end." << endl;
        wiringPiI2CWrite(fd, TREKLOOSE);
    }

}

// Перезапуск квеста
void flushGame() {
    CONFIG["status"] = "flushed";
    CONFIG["now"]    = TIMENOW;
    CONFIG["start"]  = TIMESTART;
    CONFIG["plus"]   = TIMEPLUS;
    CONFIG["end"]    = TIMEEND;
    digitalWrite(FLUSHPIN, LOW);
    delay(2000);
    digitalWrite(FLUSHPIN, HIGH);
    cout << "game is " << CONFIG["status"] << endl;
}

// Берёс свежий конфиг игры
void getData () {
    ifstream questConfig (PATHJSON);
    questConfig >> CONFIG;      
}

// Сохроняем изменения в конфиг
void saveData () {
    ofstream newfile(PATHJSON);
    newfile << setw(4) << CONFIG << endl;
}

int main () {

    // https://projects.drogon.net/raspberry-pi/wiringpi/
    wiringPiSetup ();

    pinMode(FLUSHPIN, OUTPUT);        // flush pin
    digitalWrite(FLUSHPIN, HIGH);
    
    // Главный и бесконечный цикл игры
    for(;;) {

        getData();
        
        if (CONFIG["status"] == "starting") { // Запуск игры
            
            CONFIG["now"]   = TIMENOW;
            CONFIG["start"] = TIMESTART;
            CONFIG["plus"]  = TIMEPLUS;
            CONFIG["end"]   = TIMEEND;

            CONFIG["status"] = "playing";

            cout << "game start" << endl;

            do {

                ifstream questConfig (PATHJSON);
                questConfig >> CONFIG; 

                cout << CONFIG << endl; // debug view
                
                // опрос по i2c ардуиок
                checkKassa(); // TODO можно ведь упростить
                checkWheel();
                checkCheeze();
                checkLopatka();
                checkKegi();
                checkMusic();

                // добавляем +1 сек к времени
                int timeGame = CONFIG["now"]; // TODO мб в одну строку?
                    timeGame++;
                    CONFIG["now"] = timeGame;

                // проверки на конец игры
                if (CONFIG["status"] == "flush") {
                    flushGame();
                    saveData();
                    cout << "flushhhh" << endl;
                    break;
                }
                
                if (CONFIG["status"] == "end") {
                    CONFIG["final"] = 1;
                    cout << "game end" << endl;
                    break; // TODO вот тут сделать финал
                }

                // сохроняем изменения
                saveData();
                delay(1000);

            } while (CONFIG["status"] != "playing"); 

            CONFIG["status"] = "end";
            saveData();
        }

        if (CONFIG["status"] == "flush") { // сброс конфига в js, тут только время
            flushGame();
            saveData();
        } else {
            cout << "go?" << endl;
        }

        delay(1000);
    }

    return 0;
}
