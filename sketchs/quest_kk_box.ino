#include <math.h>
#define TERMIST_B 4300 
 
#define VIN 5.0
#define FIRST_LED_PIN 0
#define LED_COUNT 10
#define SMOKE 10
#define AC 11
#define KITCHEN 12
#define ALARM 13

int correct = 0;

void setup()
{
  for (int i = 0; i < LED_COUNT; ++i) {
pinMode(i + FIRST_LED_PIN, OUTPUT);
  }
  Serial.begin(9600);
  pinMode(SMOKE, OUTPUT);
  pinMode(ALARM, OUTPUT);
  pinMode(KITCHEN, OUTPUT);
  pinMode(AC, OUTPUT);
  digitalWrite(AC, 1);
  digitalWrite(SMOKE, 1);
  digitalWrite(ALARM, 1);
  digitalWrite(KITCHEN, 1);
}
 
void loop()
{
  // вычисляем температуру в °С с помощью магической формулы.
  // Используем при этом не целые числа, а вещественные. Их ещё
  // называют числами с плавающей (англ. float) точкой. В
  // выражениях с вещественными числами обязательно нужно явно
  // указывать дробную часть у всех констант. Иначе дробная
  // часть результата будет отброшена
 
   float voltage = analogRead(A0) * VIN / 1023.0;
   float r1 = voltage / (VIN - voltage);
 
 
   float temperature = 1./( 1./(TERMIST_B)*log(r1)+1./(25. + 273.) ) - 273;
 
  for (int i = 0; i < LED_COUNT; ++i) {
    // при 21°С должен гореть один сегмент, при 22°С — два и
    // т.д. Определяем должен ли гореть i-й
    boolean enableSegment = (temperature >= 21+i);
    digitalWrite(i + FIRST_LED_PIN, enableSegment);
    Serial.println(temperature);
    delay(500);                     
    
  }
  Serial.println(millis());
   if(millis() >= 600000) {
      digitalWrite(AC, 0);
  }
    if ( temperature >= 30 and correct == 0){   //Включение реле при температуре 30С
      delay(300);
      digitalWrite(SMOKE, 0);
      delay(4000);
      digitalWrite(SMOKE, 1);
      digitalWrite(ALARM, 0);
      digitalWrite(KITCHEN, 0);
      delay(10000);
      digitalWrite(ALARM, 1);
      digitalWrite(AC, 0);
      correct = 1;
      
    } else {
      digitalWrite(SMOKE, 1);
      digitalWrite(ALARM, 1);
    }
    if(correct == 1) {
        
    }
}