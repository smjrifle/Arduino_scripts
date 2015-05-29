
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte sprite0[8];
byte sprite1[8];
byte sprite2[8];
byte sprite3[8];



void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  lcd.setCursor(0,0);
  lcd.print("tankdemo");
  lcd.setCursor(0,1);
  lcd.print("@@@@@@@@");
  memset(sprite0,7,8);
  memset(sprite1,7,8);
  memset(sprite2,7,8);
  memset(sprite3,7,8);
  lcd.setCursor(0,1);
//  Serial.begin(9600);
}

// Need eight 32-bit quantities that I can use for shifting bits around.
// The original tank image is in these values.

long tankImg[] = {
  ((long)B010000 << 10) | ((long) B000000 << 5) | B000000 // antenna tip
,((long)B010111 << 10) | ((long) B011110 << 5) | B000000 // turret top
,((long)B001111 << 10) | ((long) B011111 << 5) | B011110 // turret mid with barrel
,((long)B000111 << 10) | ((long) B011110 << 5) | B000000 // turret base
,((long)B001111 << 10) | ((long) B011111 << 5) | B010000 // tread top
,((long)B010000 << 10) | ((long) B000000 << 5) | B001000
,((long)B010000 << 10) | ((long) B000000 << 5) | B001000
,((long)B001111 << 10) | ((long) B011111 << 5) | B010000 // tread bottom, 24 pixels total in tread
};

// tankx is the bitwise position across the screen.
// tankcharx is the character-wise position, thus tankx / 5.
// It can be negative.
// At tankx zero, the tank is on the left of the screen
// so tankImg bytes are broken into four custom chars
// the fourth of which being blank bits
// At tankx one, the tank bits shift a bit to the right
// and if I'm clever, the treads are computed so they "rotate"
// And so on
// Because there are five bits horizontally per custom char
// and the tank treads go every other, I can repeat the original
// tank treads starting at even char positions
int tankx = -15;
int tankcharx;
int tankchary = 1;
int treadx = 0;

#define BITS_PER_CHAR 6

void loop() {
  tankcharx = tankx / BITS_PER_CHAR;
//  Serial.print("tankx = ");
//  Serial.print(tankx);
//  Serial.print("  tankcharx = ");
//  Serial.println(tankcharx);
 
  // Initial rendition, no rotation of treads
  if ((tankx % BITS_PER_CHAR) == 0) {
    // Full shift is on, need to draw a blank where the tank last was
    if (tankcharx >= 1) {
      lcd.setCursor(tankcharx-1, tankchary);
      lcd.write(' ');
    }
    if (tankcharx >= 0 && tankcharx <= 7) {
      lcd.setCursor(tankcharx, tankchary);
      lcd.write((byte)0);
    }
    if (tankcharx+1 >= 0 && tankcharx+1 <= 7) {
      lcd.setCursor(tankcharx+1, tankchary);
      lcd.write((byte)1);
    }
    if (tankcharx+2 >= 0 && tankcharx+2 <= 7) {
      lcd.setCursor(tankcharx+2, tankchary);
      lcd.write((byte)2);
    }
    if (tankcharx+3 >= 0 && tankcharx+3 <= 7) {
      lcd.setCursor(tankcharx+3, tankchary);
      lcd.write((byte)3);
    }
  }
  // Compute the bits of the individual custom chars
  int shiftbits = (tankx % BITS_PER_CHAR);
//  Serial.print("shiftbits = ");
//  Serial.println(shiftbits);
  if (shiftbits < 0) { shiftbits += BITS_PER_CHAR; }
  for (int y=0 ; y<8; y++)
  {
    long lval = tankImg[y];
    switch (treadx) {
      case 0:
        switch (y) {
          case 4:
            lval ^= 0x2cb0; break;
          case 7:
            lval ^= 0x2490; break;
        }
        break;
      case 1:
        switch (y) {
          case 4:
//            lval ^= 0x1240; break;
            lval ^= 0x36d0; break;
          case 5:
            lval ^= 0x0008; break;
          case 6:
            lval ^= 0x4000; break;
          case 7:
            lval ^= 0x0920; break;
        }
        break;
      case 2:
        switch (y) {
          case 4:
//            lval ^= 0x0920; break;
            lval ^= 0x1b60; break;
          case 5:
            lval ^= 0x4000; break;
          case 6:
            lval ^= 0x0008; break;
          case 7:
            lval ^= 0x1240; break;
        }
        break;
    }
   
    long lshifted = lval << (BITS_PER_CHAR-shiftbits);
    sprite0[y] = (byte)((lshifted >> (3*BITS_PER_CHAR)) & B011111);
    sprite1[y] = (byte)((lshifted >> (2*BITS_PER_CHAR)) & B011111);
    sprite2[y] = (byte)((lshifted >> (1*BITS_PER_CHAR)) & B011111);
    sprite3[y] = (byte)((lshifted >> (0*BITS_PER_CHAR)) & B011111);
  }
  lcd.createChar(0, sprite0);
  lcd.createChar(1, sprite1);
  lcd.createChar(2, sprite2);
  lcd.createChar(3, sprite3);
  ++tankx;
  if (tankx >= 50) { tankx = -15; }
  ++treadx;
  if (treadx == 3) { treadx = 0; }
  delay(100);
}

