#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
int headlights = 6;
int taillights = 7;
int redLed = 9;
int greenLed = 10;
int blueLed = 11;
int key1 = A0;
int key2 = A1;
int key3 = A2;
int key4 = A3;
static String mode = "null";
String myNum = "O44"; // race car number. MUST BE 3-DIGITS!
static int ledState;
static int spkrState;
int speaker = 5 ;
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
static boolean headlightsOn;
static boolean taillightsOn;
void setup() {
  matrix.begin(0x70);  // pass in the address
  pinMode(headlights, OUTPUT);
  pinMode(taillights, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(key1, INPUT);
  pinMode(key2, INPUT);
  pinMode(key3, INPUT);
  pinMode(key4, INPUT);
  ledState = 0;
  int key1s = digitalRead(key1);
  int key2s = digitalRead(key2);
  if (key1s == 1) {
    mode = "Vote";
  } else if (key2s == 1) {
    mode = "Race";
  }
  if (mode == "Vote") {
    digitalWrite(headlights, HIGH);
    headlightsOn = true;  
    digitalWrite(taillights, HIGH);
    taillightsOn = true;
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, HIGH);
  } else {
    digitalWrite(headlights, LOW);
    headlightsOn = false;
    digitalWrite(taillights, LOW);
    taillightsOn = false;
    setColor(255, 255, 0);  // orange  
  }
}
static const uint8_t PROGMEM
  f1_bmp[] =
  { B00001000,
    B00001100,
    B01000101,
    B01010101,
    B11010101,
    B11111111,
    B11111111,
    B11111111 },
  f2_bmp[] =
  { B01001000,
    B00101110,
    B00100010,
    B01101010,
    B11001011,
    B11111111,
    B11111111,
    B11111111 },
  f3_bmp[] =
  { B01000101,
    B01100101,
    B00010011,
    B11011001,
    B01001001,
    B01111001,
    B11111111,
    B11111111 },
  f4_bmp[] =
  { B10001100,
    B11100110,
    B00110010,
    B11010010,
    B01010101,
    B11111111,
    B11111111,
    B11111111 },
  f5_bmp[] =
  { B00110010,
    B01100110,
    B01000100,
    B01010101,
    B11111111,
    B11111111,
    B11111111,
    B11111111 };
static int x = 0;
void loop() {
  if (x == -93) {
    x = 0;
  }
  int key4s = digitalRead(key4);
  if (key4s == 1) {
    if (headlightsOn == 1) {
      digitalWrite(headlights, LOW);
      headlightsOn = false;
      digitalWrite(taillights, LOW);
      taillightsOn = false;
      delay(1000);
    } else {
      digitalWrite(headlights, HIGH);
      headlightsOn = true;
      digitalWrite(taillights, HIGH);
      taillightsOn = true;
      delay(1000);
    }
  }
  
  matrix.setRotation(3);
  if(ledState == 10 && mode != "Vote") {
    setColor(0, 127, 255);
  }
  if (mode == "Vote") {
    matrix.setTextSize(1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Vote for "+myNum+"!");
    matrix.writeDisplay();
    
  } else {
    if (ledState % 5 == 0) {
      matrix.clear();
      matrix.drawBitmap(0, 0, f1_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
    } else if (ledState % 5 == 1) {
      matrix.clear();
      matrix.drawBitmap(0, 0, f2_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
    } else if (ledState % 5 == 2) {
      matrix.clear();
      matrix.drawBitmap(0, 0, f3_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
    } else if (ledState % 5 == 3) {
      matrix.clear();
      matrix.drawBitmap(0, 0, f4_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
    } else if (ledState % 5 == 4) {
      matrix.clear();
      matrix.drawBitmap(0, 0, f5_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
    }
  }
  
   
  x = x - 1;
  ledState = ledState + 1;
  delay(100);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redLed, red);
  analogWrite(greenLed, green);
  analogWrite(blueLed, blue);  
}

