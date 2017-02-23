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

MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp ;  // для храниения номера метки в десятичном формате
void setup() {
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);    // Initialize serial communications with the PC
  SPI.begin();  //  инициализация SPI / Init SPI bus.
  mfrc522.PCD_Init();     // инициализация MFRC522 / Init MFRC522 card.UT);
}
void loop(){
    
    // --== MAGIC MIKHAEL EDITION ==--

    
  // Поиск новой метки
  
  if ( mfrc522.PICC_IsNewCardPresent()) {
    
  }
  else if ( !mfrc522.PICC_IsNewCardPresent()){ 
      digitalWrite(8, LOW);
      return;
  }
  // Выбор метки
  
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  uidDec = 0;
  // Выдача серийного номера метки.
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
    
  }
  // --== END MAGIC ==--

    if (uidDec == 2863861435 || uidDec == 752422587) {
        Serial.println("40");
        digitalWrite(4, HIGH);
        delay(200);
    } else {
        digitalWrite(4, LOW);
    }
    
    if (uidDec == 1159628387 || uidDec == 1514737851) {
        Serial.println("malo");
        digitalWrite(6, HIGH);
        delay(200);
    } else {
        digitalWrite(6, LOW);
    }
    
    if (uidDec == 2246149475 || uidDec == 3997568699) {
        Serial.println("ryadom");
        digitalWrite(7, HIGH);
        delay(200);
    } else {
        digitalWrite(7, LOW);
    }

  Serial.println(uidDec);
  delay(100);
}