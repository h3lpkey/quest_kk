/*
Сыр должен поскочить через сыроприёмник
там герконов куча, в сыре магнит.
*/

#include <Wire.h> //библиотека i2c
#define SLAVE_ADDRESS 0x06 // ардуино объявлена слейвом

bool KK_cheeze  = false; // наличие сыра
int carmove     = 0; // двигалась ли машинка
int help = 0;

const int pin_cheeze_in         = 2;
const int pin_car               = 4;

void setup() {
    Serial.begin(9600); 
    pinMode(pin_cheeze_in, INPUT);
    pinMode(pin_car, OUTPUT);
    digitalWrite(pin_car, 1); 
    
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
}

void loop() {
   if (digitalRead(pin_cheeze_in) == 0 and carmove == 0) {
    	KK_cheeze = false;
    	Serial.println("NONONONONO");
    } else {
        KK_cheeze = true;
        Serial.println("CHEEEEEEEEZEEEE");
    }
    
    if(KK_cheeze == true and carmove == 0) {
        carmove = 1;
        digitalWrite(pin_car, 0);
        delay(1000);
        digitalWrite(pin_car, 1);
    }
    
    if(help == true and carmove == 0) {
        carmove = 1;
        digitalWrite(pin_car, 0);
        delay(1000);
        digitalWrite(pin_car, 1);
    }
   delay(100);
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
  Wire.write(KK_cheeze);
  Serial.print("send: ");
  Serial.println(KK_cheeze);
  delay(100);
}
