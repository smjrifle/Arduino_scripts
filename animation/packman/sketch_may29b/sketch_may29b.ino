#include <LiquidCrystal.h>
#include <TimerOne.h>
int zahl = 0;
int zahl1 = 40;
int zahl2 = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


byte pac1[8] = {
  0b00000,
  0b01110,
  0b11011,
  0b11111,
  0b11111,
  0b01110,
  0b00000,
  0b00000
};
byte pac2[8] = {
  0b00000,
  0b01110,
  0b10100,
  0b11000,
  0b11100,
  0b01110,
  0b00000,
  0b00000
};


byte pac2b[8] = { 
  B00000, 
  B11110, 
  B01011, 
  B00111, 
  B01111, 
  B11110, 
  B00000, 
  B00000 };

byte ghost[8] = {  
  B01110, 
  B11111, 
  B10101, 
  B11111, 
  B11111, 
  B10101, 
  B00000, 
  B00000 };

byte punkt[8] = { 
  B00000, 
  B00000, 
  B00000, 
  B01100, 
  B01100, 
  B00000, 
  B00000, 
  B00000};

void setup() {

  lcd.createChar(2, pac1);
  lcd.createChar(3, pac2);
  lcd.createChar(4, punkt);
  lcd.createChar(5, ghost);

  lcd.createChar(7, pac2b);
  
  lcd.begin(16, 2);
  Timer1.initialize(200); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( autoBrightness ); // attach the service routine here
  
}


boolean busy=false;
int part = 0;
int currentReading = 0;
int lastReading = 0;
int count = 0;
void autoBrightness()
{
   
   if(!busy)
   {
   currentReading = analogRead(0); 
   currentReading = 1023-currentReading;
   }
   
   if(count<100)
   {
     part = (currentReading/100)*count;
     count++;
     busy = true;
   }
   else
   {
     busy = false;
     count = 0;
   }
   
   
   
   int value = map(part,0,1023,0,255);
//   Serial.println(value);
   analogWrite(10,value);
  
}

double acc = 0;
 double lastAcc;
int tempCount = 0;
 int count2 = 0;
boolean tempDisplay = true;
void loop() {
  zahl2 = 0;

 lcd.setCursor(1,1); 
 
 if(tempDisplay){
 tempCount++;
  
 float temp = analogRead(1);
 lcd.print("Temp: ");
 acc += temp * 0.48828125;

 if(tempCount >= 5){
   acc /=5;
   lcd.print(acc);
   lastAcc = acc;
   acc = 0;
   tempCount=0; 
 }
 else 
   lcd.print(lastAcc);
   
   lcd.print((char)223);
   lcd.print("C");
   if(count2++ >= 3){
     tempDisplay=false;
   }
 }
 else{
   for(int i=0;i<16;i++)
     lcd.print(" ");
   lcd.setCursor(4,1);
   lcd.print("smjrifle");
   if(count++ >= 6) {
     tempDisplay=true;
    count2 = 0;
   } 
 }
  
    
  lcd.setCursor(zahl, 0);

  while(zahl1 > 0){
    delay(100);
    lcd.write(byte(4));
    zahl1 = zahl1 - 1;

  } 

  lcd.setCursor(zahl, 0); 
  lcd.write(byte(2));
  if(zahl >= 2){
    lcd.setCursor(zahl - 2, 0); 
    lcd.write(byte(5));
  }
  delay(300);
  lcd.setCursor(zahl, 0);
  lcd.write(" ");
  if(zahl >= 2){
    lcd.setCursor(zahl - 2, 0); 
    lcd.write(" ");
  }
  zahl++;

  lcd.setCursor(zahl, 0);
  lcd.write(byte(3));
  if(zahl >= 2){
    lcd.setCursor(zahl - 2, 0); 
    lcd.write(byte(5));
  }
  delay(300);
  lcd.setCursor(zahl, 0);
  lcd.write(" ");
  if(zahl >= 2){
    lcd.setCursor(zahl - 2, 0); 
    lcd.write(" ");
  }
  zahl++;


  if(zahl > 38){
    zahl = zahl - 1;
    while(zahl2 < 39){

      lcd.setCursor(zahl, 0); 
      lcd.write(byte(7));
      if(zahl >= 2){
        lcd.setCursor(zahl - 2, 0); 
        lcd.write(byte(5));
      }
      delay(250);
      lcd.setCursor(zahl, 0);
      lcd.write(" ");
      if(zahl >= 2){
        lcd.setCursor(zahl - 2, 0); 
        lcd.write(" ");
      }
      zahl = zahl - 1;
      lcd.setCursor(zahl, 0);
      lcd.write(byte(2));

      if(zahl >= 2){
        lcd.setCursor(zahl - 2, 0); 
        lcd.write(byte(5));
      }
      delay(250);
      lcd.setCursor(zahl, 0);
      lcd.write(" ");
      if(zahl >= 2){
        lcd.setCursor(zahl - 2, 0); 
        lcd.write(" ");

      }
      zahl2++;

    }
    zahl1 = 40;
    zahl = 0;


  }


}
