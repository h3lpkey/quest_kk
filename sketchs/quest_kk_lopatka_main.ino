/*
752422587 - 40
2863861435 - 40
3585441379 - 00
878907323 - 00
1159628387 - 10
1514737851 - 20
3997568699 - 30
2246149475 - 50
*/
#include <SPI.h>
#include <MFRC522.h> // библиотека "RFID".

#define SS_PIN 10
#define RST_PIN 9

#include <Wire.h> //библиотека i2c
#define SLAVE_ADDRESS 0x07 // ардуино объявлена слейвом

int cardNow = 0;
int correct = 0;
int open = 0;
int support = 0;


MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp ;  // для храниения номера метки в десятичном формате
void setup() {
  Serial.begin(9600);    // Initialize serial communications with the PC
  SPI.begin();  //  инициализация SPI / Init SPI bus.
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
  
  mfrc522.PCD_Init();     // инициализация MFRC522 / Init MFRC522 card.UT);
}
void loop(){
// --== MAGIC MIKHAEL EDITION ==--

  // Поиск новой метки
   if ( mfrc522.PICC_IsNewCardPresent()) {  //Если есть карта - продолжаем
    
  }
  else if ( !mfrc522.PICC_IsNewCardPresent()){ //Если нет - выставляем номер карты и выход 7 в ноль
      uidDec = 0;
      digitalWrite(7, HIGH);
      return;
  }
  // Выбор метки
    if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Выдача серийного номера метки.
  
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uidDecTemp = mfrc522.uid.uidByte[i];
        uidDec = uidDec * 256 + uidDecTemp;
    }
// --== END MAGIC ==--
    // if(digitalRead(8) == HIGH) {
    //     support = 1;
    // } else {
    //     support = 0;
    // }

    
    Serial.println(uidDec);
    if(uidDec == 709309568 and correct == 0 and digitalRead(8) == HIGH) {
        Serial.println("open!");
        correct = 1;
    } else {
        Serial.println("closed!");
        digitalWrite(7, HIGH);
    }
    if( correct == 1) {
        digitalWrite(7, LOW);
    } else {
        digitalWrite(7, HIGH);
    }
    
    if(open == 1) {
        digitalWrite(7, LOW);
        correct = 1;
    }
}


void receiveData(int byteCount)
{
  while(Wire.available()) {
    open = Wire.read();
    Serial.print("read: ");
    Serial.println(open);
    delay(100);
  }
}

void sendData()
{
  Wire.write(correct);
  Serial.print("send: ");
  Serial.println(correct);
  delay(100);
}
