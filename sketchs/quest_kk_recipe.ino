
#include <Wire.h> //библиотека i2c
#define SLAVE_ADDRESS 0x09 // ардуино объявлена слейвом
int final = 0;
int trek = 0;

#include <SoftwareSerial.h>
void setup () {
    Serial.begin (9600);
    
    pinMode(4, INPUT);
    pinMode(8, OUTPUT);
    pinMode(3, OUTPUT);
    
    digitalWrite(3, HIGH);
    digitalWrite(8, HIGH);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
}
void loop () {
    
    
    if (digitalRead(4) == LOW) { // WIN
        Serial.println("win game");
        digitalWrite(10, HIGH);
        final = 1;
        digitalWrite(3, LOW); // открыть финальную дверь
    } else {
        Serial.println("playing game");
        final = 0;
    }

    
    
    delay(1000);
}

void receiveData(int byteCount)
{
  while(Wire.available()) {
    trek = Wire.read();
    Serial.print("read: ");
    Serial.println(trek);
    delay(100);
  }
}

void sendData()
{
  Wire.write(final);
  Serial.print("send: ");
  Serial.println(final);
  delay(100);
}
