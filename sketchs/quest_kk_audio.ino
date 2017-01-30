
#include <Wire.h> //библиотека i2c
#define SLAVE_ADDRESS 0x09 // ардуино объявлена слейвом
int trek = 1;
int command = 0;


#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
void setup () {
    Serial.begin (9600);
    pinMode(8, OUTPUT);
    pinMode(10, INPUT);
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    
    mp3_set_serial (Serial);    
    mp3_set_volume (15);
    delay (100);
    mp3_play (1);
    delay (100);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
}
void loop () {        
    if(digitalRead(12) == HIGH) {
        Serial.println("playing game");
        digitalWrite(7, HIGH);
    } else {
        digitalWrite(7, LOW);
        Serial.println("win");
        mp3_play(3); // победа
        trek = 3;
        delay(32000);
    }
    if(trek == 4) {
        mp3_play(trek); // поражение
        Serial.println("loose");
        delay(54000);
    }

    if(trek == 2) {
        Serial.println("5 min");
        mp3_play(trek);
        delay(6000); // предупреждние о 5 минутах
        mp3_play(1);
    }
    mp3_play (1);
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
  Wire.write(trek);
  Serial.print("send: ");
  Serial.println(trek);
  delay(100);
}
