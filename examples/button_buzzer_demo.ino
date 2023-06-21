#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Fonts/FreeSerifBold12pt7b.h>

#include <SPI.h>

//Define common SPI interfacing pins 
#define _sclk              14
#define _mosi              13 
#define _miso              12

//for Display with ESP32
#define TFT_DC             21
#define TFT_CS             15 
#define TFT_RST            -1   // connected to enable pin of esp32 

#define TFT_BACKLIGHT_PIN   5 

const uint8_t TFT_ORIENTATION = 3;


Adafruit_ILI9341 tft = Adafruit_ILI9341( TFT_CS, TFT_DC, TFT_RST );

const int buzzerPin = 40; //create variable for buzzer pin connected at GPIO40
const int userButton1 = 4; //for programmable button 1 at GPIO4
const int userButton2 = 6; //for programmable button 2 at GPIO6
const int LED = 3;

void beep(int note, int duration){
  tone(buzzerPin, note, duration);
  delay(duration);
}

void setup(void) {
  Serial.begin(115200);
  pinMode(userButton1, INPUT_PULLUP); // programmable buttons need pullup
  pinMode(userButton2, INPUT_PULLUP); // programmable buttons need pullup
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode( TFT_BACKLIGHT_PIN, OUTPUT );     // set backlight pin as OUTPUT
  digitalWrite( TFT_BACKLIGHT_PIN, HIGH );  // activate backlight
  
  SPI.begin( _sclk, _miso, _mosi );
  SPI.setFrequency( 60000000 );

  tft.begin();
  tft.setRotation( TFT_ORIENTATION );
  tft.fillScreen( ILI9341_BLACK );
  tft.setTextColor( ILI9341_WHITE, ILI9341_BLACK );

  tft.setCursor( 12, 20 );
  tft.print( "Hello! Press Button to Test" );
  delay(500);
  beep(1245, 500); // provide frequecy note & duration to sound buzzer
}

void loop() {
  if (digitalRead(userButton1)==0){
    digitalWrite(LED, HIGH);
    tft.fillScreen(ILI9341_BLACK);
    tft.drawRect(0, 0, 320, 240, ILI9341_YELLOW);
    Serial.println("Button 1 Pressed!");
    tft.setCursor( 130, 160 );
    tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);  
    tft.setFont(&FreeSerifBold12pt7b);
    tft.print( "BT1" );
    delay(50);
    beep(1760, 500);
  }

  if (digitalRead(userButton2)==0){
    digitalWrite(LED, HIGH);
    tft.fillScreen(ILI9341_BLACK);
    tft.drawRect(0, 0, 320, 240, ILI9341_YELLOW);
    Serial.println("Button 2 Pressed!");
    tft.setCursor( 130, 160 );
    tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);  
    tft.setFont(&FreeSerifBold12pt7b);
    tft.print( "BT2" );
    delay(50);
    beep(1760, 500);
  }

  digitalWrite(LED, LOW);
  delay(10);
}
