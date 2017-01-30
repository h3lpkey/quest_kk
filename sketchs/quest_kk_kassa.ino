/*
Если вставлен доллар в кассу
открываем домик мышки
*/

#include <Wire.h> //библиотека i2c
#define SLAVE_ADDRESS 0x04 // ардуино объявлена слейвом

    const int pin_dollar_1       = 2;            // Пины сигналов щелевых датчиков
    const int pin_dollar_2       = 3;
   
    const int pin_mouse          = 5;            // Пин под домик мыши

    bool correctDollar            = false;            // Решили ли задачку с кассой?
    bool mouse = false;
    int dollarHelp = 0;
    

void setup() {
    Serial.begin(9600);
    
    pinMode(pin_mouse,           OUTPUT);        // Пин для открытия домика мышки

    pinMode(pin_dollar_1,        INPUT);         // Переменные для проверки налиия доллора в кассе
    pinMode(pin_dollar_2,        INPUT);
    
    digitalWrite(pin_mouse, 1);                  // Даём +5в на реле, потому что управление идёт с GND
    
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
}

void loop() {
    
    if ( digitalRead(pin_dollar_1)  == HIGH      // Проверка всех датчиков
    and  digitalRead(pin_dollar_2)  == HIGH) {
        Serial.println("DOLLAR");
        correctDollar = true;
    } else {
        correctDollar = false;
    }
}


void receiveData(int byteCount)
{
  while(Wire.available()) {
    mouse = Wire.read();
    Serial.print("mouse door: ");
    Serial.println(mouse);
    if(mouse) {
        digitalWrite(pin_mouse, 0);
    }  else {
        digitalWrite(pin_mouse, 1);
    }
    delay(100);
  }
}

void sendData()
{
  Wire.write(correctDollar);
  Serial.print("Correct dollar: ");
  Serial.println(correctDollar);
  delay(100);

}