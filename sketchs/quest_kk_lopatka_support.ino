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
  Serial.begin(9600);    // Initialize serial communications with the PC
  SPI.begin();  //  инициализация SPI / Init SPI bus.
  pinMode(8, OUTPUT);
  mfrc522.PCD_Init();     // инициализация MFRC522 / Init MFRC522 card.UT);
}
void loop(){
// --== MAGIC MIKHAEL EDITION ==--

  // Поиск новой метки
   if ( mfrc522.PICC_IsNewCardPresent()) {  //Если есть карта - продолжаем
    
  }
  else if ( !mfrc522.PICC_IsNewCardPresent()){ //Если нет - выставляем номер карты и выход 7 в ноль
      uidDec = 0;
      digitalWrite(8, LOW);
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

    Serial.println(uidDec);
    if( uidDec == 709309568) {
        digitalWrite(8, HIGH);
        Serial.println("go");
    } else {
        digitalWrite(8, LOW);
    }
   
}