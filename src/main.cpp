#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "SPI.h"
#include "HX711.h"
#include "SD.h"


// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

const int BENDING_FORCE_DOUT_PIN = 2;
const int BENDING_FORCE_SCK_PIN = 3;

const int AXIAL_FORCE_DOUT_PIN = 6;
const int AXIAL_FORCE_SCK_PIN = 20;


const int BUTTON = 5;
int BUTTONstate = 0;
int count_value =0;
int prestate =0;
int counter = 0; 
int column = 0;
double reading_bend = 0;
double reading_ax = 0;

File myFile;
 

HX711 bending_force;
HX711 axial_force;

elapsedMillis em;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);


unsigned long testText() {
 // unsigned long start = micros();
  tft.setCursor(5, 100);
  tft.setTextColor(ILI9341_RED);  
  tft.setTextSize(3);
  tft.println("Hello World!");
}




void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
  tft.begin();
  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
   tft.fillScreen(ILI9341_WHITE);
  
   pinMode(BUTTON, INPUT);

   bending_force.begin(BENDING_FORCE_DOUT_PIN, BENDING_FORCE_SCK_PIN);
   axial_force.begin(AXIAL_FORCE_DOUT_PIN, AXIAL_FORCE_SCK_PIN);

}


void loop(void) {
  tft.setRotation(3);
    //testText();

   BUTTONstate = digitalRead(BUTTON);

  if(em > 5000){
    em = 0;
    Serial.println("Test");
    
  }

 if (BUTTONstate == HIGH && prestate == 0) {
     count_value++;
     prestate = 1;
     tft.fillScreen(ILI9341_WHITE);
   } else if(BUTTONstate == LOW) {
     prestate = 0;
   }
 
  tft.setCursor(5, 5);
   tft.setTextColor(ILI9341_BLACK);  
   tft.setTextSize(2);
   tft.print("Lastzyklen: ");
   tft.print(count_value);


  // set the stroke color to white#
   tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(5, 100);
  tft.print("Biegekraft: ");
   tft.setCursor(140, 100);

  if (bending_force.is_ready()) {
     reading_bend = bending_force.read()*0.000111688 + 1.05;
    if (reading_bend < 0)
    {
      reading_bend = reading_bend * (-1);
    }
    tft.setTextColor(ILI9341_BLACK);
    tft.printf("%3.2f N",reading_bend); 
  } else {
    tft.println("HX711 not found.");
  }

   tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(5, 120);
  tft.print("Axialkraft: ");
   tft.setCursor(140, 120);

  if (axial_force.is_ready()) {
     reading_ax = axial_force.read()*0.000111688 + 1.05;
    if (reading_ax < 0)
    {
      reading_ax = reading_ax * (-1);
    }
    tft.setTextColor(ILI9341_BLACK);
    tft.printf("%3.2f N",reading_ax); 
  } else {
    tft.println("HX711 not found");
  }

  
  delay(500);
  tft.setTextColor(ILI9341_WHITE);
   tft.setCursor(140, 100);
   tft.printf("%3.2f N",reading_bend);
   tft.setTextColor(ILI9341_WHITE);
   tft.setCursor(140, 120);
   tft.printf("%3.2f N",reading_ax);
  
 



}

