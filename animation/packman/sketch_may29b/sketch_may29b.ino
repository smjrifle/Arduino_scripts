#include <LiquidCrystal.h>
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
  lcd.begin(20, 4);
}

void loop() {
  zahl2 = 0;
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
