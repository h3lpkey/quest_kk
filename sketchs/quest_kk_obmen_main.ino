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
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h> // библиотека "RFID".

#define SS_PIN 53
#define RST_PIN 5

#include <Servo.h> //используем библиотеку для работы с сервоприводом

Servo servo; //объявляем переменную servo типа Servo

LiquidCrystal lcd(32, 30, 28, 26, 24, 22);

int cardNow = 0; // приложенная 
int coins = 0; // счёт монет
int correct = 0; // выполнена ли задача
int full = 6; // сколько монет надо
int right = 0; // от ложных срабатываний
int ryadom = 0;
int malo = 0;


MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp ;  // для храниения номера метки в десятичном формате
void setup() {
  Serial.begin(9600);    // Initialize serial communications with the PC
  SPI.begin();  //  инициализация SPI / Init SPI bus.
  mfrc522.PCD_Init();     // инициализация MFRC522 / Init MFRC522 card.UT);
  servo.attach(10); //привязываем привод к порту 10
  // Спасибо амперке за урок
  // устанавливаем размер (количество столбцов и строк) экрана
    lcd.begin(16, 2);
    // печатаем первую строку
    lcd.print("\x42\xC3\xB2\x65\x70\xB8\xBF\x65 \xBA\x79\x70\x63");
    // устанавливаем курсор в колонку 0, строку 1. То есть на
    // самом деле это вторая строка, т.к. нумерация начинается с нуля
    lcd.setCursor(5, 1);
    // печатаем вторую строку
    lcd.print("\x4D\x6F\xBD\x65\xBF: 0");
    servo.write(0); //ставим вал под 0
    pinMode(7, INPUT);
}
void loop(){
    

    if(digitalRead(12) == HIGH) {
        coins++;
        Serial.print("coins: ");
        Serial.println(coins);
        lcd.setCursor(12, 1);
        // печатаем вторую строку
        lcd.print(coins);
        delay(200);
    }
    
    Serial.println(uidDec);
    if(digitalRead(8) == HIGH) {
        right++;
        Serial.println("right: ");
        Serial.println(right);
    } else {
        right = 0;
    }
    if(digitalRead(7) == HIGH) {
        ryadom++;
        Serial.println("ryadom: ");
        Serial.println(ryadom);
    } else {
        ryadom = 0;
    }
    if(digitalRead(6) == HIGH) {
        malo++;
        Serial.println("malo: ");
        Serial.println(malo);
    } else {
        malo = 0;
    }
    
// --== MAGIC MIKHAEL EDITION ==--

  // Поиск новой метки
   if ( mfrc522.PICC_IsNewCardPresent()) {  //Если есть карта - продолжаем
    
  }
  else if ( !mfrc522.PICC_IsNewCardPresent()){ //Если нет - выставляем номер карты и выход 7 в ноль
      uidDec = 0;
      digitalWrite(7, LOW);
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

    if (malo >= 10) { // 10 20
        lcd.setCursor(0, 0);
        lcd.print("\x48\x65 \xB4\x61\xE3\x61\xB9       "); // ne gadai
    }
    if (ryadom >= 10) { // 10 20
        lcd.setCursor(0, 0);
        lcd.print("\x54\xC3 \x79\xB3\x65\x70\x65\xBD \x3F  "); // ti yveren &
    }

    if (uidDec == 3585441379 or uidDec == 878907323) { // 40 + 00
        if (right >= 10 and correct == 0) {  
        lcd.setCursor(0, 0);
        lcd.print("\x42\x65\x70\xBD\xC3\xB9 \xBA\x79\x70\x63  "); // vernii kurs
        }
    }
    
    if (uidDec == 3585441379 or uidDec == 878907323) {
        
        
        if (right >= 10 and correct == 0 and coins >= 6) {  
        correct = 1;
        lcd.setCursor(0, 0);
        lcd.print("    \x42\x6F\xB7\xC4\xBC\xB8\xBF\x65             "); // vozmite
        lcd.setCursor(0, 1);
        lcd.print("     \x4B\x79\xBE\xC6\x70\x79             "); // kypury
        Serial.println("activated");                            
        digitalWrite(7, HIGH);
        // Возмите купюру
        servo.write(100);
        delay(500);
        servo.write(0); //ставим вал под 0
        delay(500);
        servo.write(100);
        delay(500);
        servo.write(0); //ставим вал под 0

        delay(5000);
        }
    }
}