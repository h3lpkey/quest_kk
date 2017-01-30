// 3319
 #include <EEPROM.h>

#define lock1  18
#define lock2  19
#define reed   14
#define buzzer 16
#define adj    15
#define rdiod  2
#define gdiod  3
#define diod   17

byte matrix[8] = { 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 };
unsigned long timer ;
byte pass[10] ;
byte code[10] ;
byte current = 0 ;
boolean onetime = true ;

void(* resetFunc) (void) = 0; // Reset function

void setup() {////////////////////////////////// SETUP

  Serial.begin(115200);
  //Serial.println(" START");

  for ( int i = 0 ; i < 4 ; i++ )
  {
    pinMode ( matrix[i] , OUTPUT );
    digitalWrite ( matrix[i] , HIGH );
  }

  for ( int i = 0 ; i < 4 ; i++ )
    pinMode ( matrix[i + 4] , INPUT_PULLUP );


  pinMode ( lock1 , OUTPUT );
  pinMode ( lock2 , OUTPUT );
  pinMode ( buzzer , OUTPUT );
  pinMode ( diod , OUTPUT );
  pinMode ( rdiod , OUTPUT );
  pinMode ( gdiod , OUTPUT );
  pinMode ( adj , INPUT_PULLUP);
  pinMode ( reed, INPUT_PULLUP);


  Serial.println(" Current Code");
  for ( int i = 0 ; i < 10 ; i++ )
  {
    pass[i] = EEPROM.read(i);
    Serial.print(" ");
    Serial.print(pass[i]);
  }
  //Serial.println();
   digitalWrite ( lock1 , HIGH );
   digitalWrite ( lock2 , HIGH );


}

void loop() {/////////////////////////////////////// LOOP

  //-----------------------— Кнопка настроки
  while ( digitalRead ( adj ) == 0 )
  {
    if ( millis() - timer < 2000 ) continue ;
    while ( digitalRead ( adj ) == 0 )
    {
      digitalWrite( diod , 1 );
      tone ( buzzer , 300 , 50 );
      delay(100);
    }
    adjust();
  }

  //-------------------------------------— сканирование матрицы кнопок
  for ( int i = 0 ; i < 4 ; i++ )
  {
    digitalWrite ( matrix[i] , 0 );
    for ( int k = 0 ; k < 4 ; k++)
    {
      onetime = true ;
      timer = millis() ;
      while ( digitalRead ( matrix[k + 4] ) == 0 )
      {
        if ( millis() - timer < 50 ) continue;
        if ( onetime )
        {
          onetime = false ;
          btn(i * 4 + k + 1);
          code[current] = i * 4 + k + 1 ;
          current++;
        }
      }
    }
    digitalWrite ( matrix[i] , 1 );
  }


  if ( pass[current] == 0 )
  {
    byte c = 0 ;
    for ( int j = 0 ; j < current ; j++ )
      if ( code[j] == pass[j] ) c++ ;

    if ( c == current )
    {
      for ( int i = 0 ; i < 9 ; i++ )
      {
        tone ( buzzer , random( 100 , 500 ) , random ( 50 , 70 ) );
        delay ( 80 );
      }
      //Serial.println( " Case Opened");

      tone ( buzzer , 400 , 80 );
      delay (100);
      tone ( buzzer , 2500 , 100 );
      digitalWrite( gdiod , HIGH );
      delay ( 100 );
      digitalWrite ( lock1 , LOW );
      delay (2000);
      digitalWrite( gdiod , LOW );
      delay ( 100 );
      digitalWrite ( lock1 , HIGH );
      delay ( 100 );
      //lock_stat = false;
    }
    else
    {
      digitalWrite( rdiod , HIGH );
      tone ( buzzer , 400 , 80 );
      delay (100);
      tone ( buzzer , 2500 , 100 );
      delay ( 300 );
      digitalWrite( rdiod , LOW );
    }
    
    for (int i = 0 ; i < 10 ; i ++ )
      code[i] = 0 ;
    current = 0;
    Serial.println();
  }

      if ( digitalRead (reed) == LOW ) 
      {
       digitalWrite (lock2, HIGH);
      }
      else if ( digitalRead (reed) == HIGH )
      {
       digitalWrite (lock2, LOW);
      } 


}


void adjust ( void )
{
  Serial.println(" New Code");
  for ( int i = 0 ; i < 10 ; i++ )
    EEPROM.write ( i , 0 );

  boolean repeat = true ;
  byte N = 0 ;
  while ( repeat )
  {
    for ( int i = 0 ; i < 4 ; i++ )
    {
      digitalWrite ( matrix[i] , 0 );
      for ( int k = 0 ; k < 4 ; k++)
      {
        onetime = true ;
        timer = millis() ;
        while ( digitalRead ( matrix[k + 4] ) == 0 )
        {
          if ( millis() - timer < 50 ) continue;
          if ( onetime )
          {
            onetime = false ;
            if ( N < 9 ) {
              btn(i * 4 + k + 1);
              EEPROM.write ( N , i * 4 + k + 1 );
              N++;
            }
            else
            {
              tone ( buzzer , 400 , 80 );
              delay(100);
              tone ( buzzer , 250 , 150 );
              delay(200);
            }
          }
        }
      }
      digitalWrite ( matrix[i] , 1 );
    }

    while ( digitalRead ( adj ) == 0 )
    {
      if ( millis() - timer < 1000 ) continue ;
      while ( digitalRead ( adj ) == 0 )
      {
        tone ( buzzer , 300 , 100 );
        delay(200);
      }
      repeat = false ;
    }

  }
 Serial.println();
  digitalWrite ( diod , 0 );
  current = 0 ;

  resetFunc();
}

void btn(byte n)
{
  Serial.print(" ");
  Serial.print(n);
  tone ( buzzer , 500 , 50 );
  digitalWrite( gdiod , 1 );
  delay ( 50 );
  digitalWrite( gdiod , 0 );
  delay ( 30 );
}
