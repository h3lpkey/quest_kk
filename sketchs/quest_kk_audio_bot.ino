#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

void setup () {
    Serial.begin (9600);
    mp3_set_serial (Serial);    
    mp3_set_volume (15);
    delay (100);
    mp3_play (1);
    delay (100);
}
void loop () { 
    if (digitalRead(10) == HIGH) {
        Serial.println("win");
        mp3_play(3); // победа
        delay(32000);
        mp3_play(1);
    } else {
        Serial.println("win ---");
    }
    
    if (digitalRead(11) == HIGH) {
        Serial.println("legend");
        mp3_set_volume (25);
        delay (100);
        mp3_play(8); // legend
        delay(41000);
        mp3_set_volume (15);
        delay(100);
        mp3_play(1);
    } else {
        Serial.println("legend ---");
    }
    
    if (digitalRead(12) == HIGH) {
        Serial.println("loose");
        mp3_play(4); // loose
        delay(54000);
        mp3_play(1);
    } else {
        Serial.println("loose ---");
    }
}
