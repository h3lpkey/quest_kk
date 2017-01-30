/*
Все штурвалы должны быть true
После чего открываем окно
*/

#include <Wire.h> //библиотека i2c
#define SLAVE_ADDRESS 0x15 // ардуино объявлена слейвом

    const int pin_wheel_1        = 9;            // Пины штурвалов
    const int pin_wheel_2        = 10;
    const int pin_wheel_3        = 11;
    const int pin_wheel_4        = 12;
    
    const int pin_window         = 8;            // Пин под реле окна

    int correctWheel            = 0;             // Решели ли задачку штурвалов?
    int help                    = 0;
    

void setup() {
    Serial.begin(9600);
    
    pinMode(pin_window,          OUTPUT);        // Пин для открытия окна

    pinMode(pin_wheel_1,         INPUT);         // Переменные для проверки штурвалов
    pinMode(pin_wheel_2,         INPUT);
    pinMode(pin_wheel_3,         INPUT);
    pinMode(pin_wheel_4,         INPUT);
    
    digitalWrite(pin_window, 1);                 // Даём +5в на реле, потому что управление идёт с GND
    
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
}

void loop() {
    
    if ( correctWheel             == 0           // Решали ли задачку с кассой?
    and  digitalRead(pin_wheel_1) == LOW         // Проверка всех штурвалов
    and  digitalRead(pin_wheel_2) == HIGH        // Этот особенный просто
    and  digitalRead(pin_wheel_3) == LOW
    and  digitalRead(pin_wheel_4) == LOW) {
        digitalWrite(pin_window, 0);             // Включить реле на 220AC под окно
        delay(10000);                            // 10 секунд на открытие
        digitalWrite(pin_window, 1);             // Выключить реле на 220AC под окно
        correctWheel = 1;                        // Запретить еще раз баловаться окном
    }
    if ( help == 1 and correctWheel == 0) {
        digitalWrite(pin_window, 0);             // Включить реле на 220AC под окно
        delay(10000);                            // 10 секунд на открытие
        digitalWrite(pin_window, 1);             // Выключить реле на 220AC под окно
        correctWheel = 1;
    }
    
    Serial.print("correctWheel: ");
    Serial.println(correctWheel);
    Serial.print("help: ");
    Serial.println(help);
    delay(1000);
}


void receiveData(int byteCount)
{
  while(Wire.available()) {
    help = Wire.read();
    Serial.print("read: ");
    Serial.println(help);
    delay(100);
  }
}

void sendData()
{
  Wire.write(correctWheel);
  Serial.print("send: ");
  Serial.println(correctWheel);
  delay(100);
}
