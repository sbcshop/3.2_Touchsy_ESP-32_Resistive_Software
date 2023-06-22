#include <SPI.h>
#include "Adafruit_GFX.h"      // graphics library
#include "Adafruit_ILI9341.h"  // display driver library
#include <Fonts/FreeMonoBold12pt7b.h> 
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSansOblique12pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>


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

void setup(void) {
  pinMode( TFT_BACKLIGHT_PIN, OUTPUT );     // set backlight pin as OUTPUT
  digitalWrite( TFT_BACKLIGHT_PIN, HIGH );  // Make high to Turn On backlight
  
  SPI.begin( _sclk, _miso, _mosi ); // configure SPI interface
  SPI.setFrequency( 60000000 );

  tft.begin(); // initialize display
  tft.setRotation( TFT_ORIENTATION ); // set orientation of screen
  tft.fillScreen( ILI9341_BLACK );    // Set screen background color
  tft.setTextColor( ILI9341_GREEN, ILI9341_BLACK ); // set text color 
  tft.setCursor( 80, 100 );  // move cursor to co-ordinate (x,y)
  tft.setTextSize(2);
  tft.print( "Hello..." );   // text display with default font
  delay(1000);
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRect(0, 0, 320, 240, ILI9341_CYAN);

  tft.setTextSize(1);
  tft.setCursor( 40, 25 );
  tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK); // set colour
  tft.setFont(&FreeMonoBold12pt7b);  // use different font style for Text, make sure to include particular header file
  tft.print("3.2\" Touchsy ESP32");

  tft.setCursor( 80, 60 );
  tft.setFont(&FreeMono9pt7b);
  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);        
  tft.print("* Resistive *");

  tft.setCursor( 45, 120 );
  tft.setFont(&FreeSansOblique12pt7b);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);       
  tft.print("Thank you for Buying!");

  tft.setCursor( 70, 190 );
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);       
  tft.print("SB Components");
  
  tft.setCursor( 30, 220 );
  tft.setFont(&FreeMono9pt7b);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);       
  tft.print("shop.sb-components.co.uk");
  delay(1000);
  
}

void colorScreen(){
  tft.setRotation( 3 );
  tft.fillScreen(ILI9341_RED);
  tft.drawRect(0, 0, 320, 240, ILI9341_YELLOW);
  delay(1000);
  
  tft.setRotation( 0 );
  tft.fillScreen(ILI9341_GREEN);
  tft.drawRect(0, 0, 240, 320, ILI9341_YELLOW);
  delay(1000);
  
  tft.setRotation( 1 );
  tft.fillScreen(ILI9341_BLUE);
  tft.drawRect(0, 0, 320, 240, ILI9341_YELLOW);
  delay(1000);
  
  tft.setRotation( 2 );
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRect(0, 0, 240, 320, ILI9341_YELLOW);
  delay(1000);
}

void loop() {
  colorScreen();
  delay(10);
}
