#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h> 
#include <SPI.h>


//Define common SPI interfacing pins 
#define _sclk              14
#define _mosi              13 
#define _miso              12

//for Display with ESP32
#define TFT_DC             21
#define TFT_CS             15 
#define TFT_RST            -1   // connected to enable pin of esp32 

//for Touch controller with ESP32
#define TOUCH_CS_PIN       47
#define TOUCH_IRQ_PIN      0

#define TFT_BACKLIGHT_PIN   5 

//This is to configure touch co-ordinates
#define TFT_NORMAL          1
#define TFT_UPSIDEDOWN      3

const uint8_t TFT_ORIENTATION = 3;

Adafruit_ILI9341 tft = Adafruit_ILI9341( TFT_CS, TFT_DC, TFT_RST );

XPT2046_Touchscreen touch( TOUCH_CS_PIN, TOUCH_IRQ_PIN );

void setup(void) {
  pinMode( TFT_BACKLIGHT_PIN, OUTPUT );     // set backlight pin as OUTPUT
  digitalWrite( TFT_BACKLIGHT_PIN, HIGH );  // activate backlight

  SPI.begin( _sclk, _miso, _mosi );
  SPI.setFrequency( 60000000 );

  tft.begin();
  tft.setRotation( TFT_ORIENTATION );

  tft.fillScreen( ILI9341_BLACK );
  tft.setTextColor( ILI9341_GREEN, ILI9341_BLACK );

  touch.begin();
  touch.setRotation(1);
  tft.setTextSize(2);
  tft.println( "Touch Screen Demo...Ready!" );
  tft.setTextColor( ILI9341_YELLOW, ILI9341_BLACK );
  tft.print("Hold Down pen and move");
}

TS_Point rawLocation;
void loop() {
  if ( touch.touched() ){
    tft.fillScreen(ILI9341_BLACK);
    tft.drawRect(0, 0, 320, 240, ILI9341_PURPLE);
  }

  while (touch.touched())
      {
          rawLocation = touch.getPoint();
          int   a = map(rawLocation.x, 240, 3790, 0, tft.height());
          int   b = map(rawLocation.y, 145, 3870, 0, tft.width()); 
          if ( TFT_ORIENTATION == TFT_UPSIDEDOWN )
          {
            tft.fillCircle( mapFloat( rawLocation.x, 340, 3790, 320, 0 ),mapFloat( rawLocation.y, 200, 3870, 0, 240 ),2,ILI9341_YELLOW );
          }
      }

  delay(10);
}

static inline __attribute__((always_inline)) float mapFloat( float x, const float in_min, const float in_max, const float out_min, const float out_max)
{
  return ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min;
}
