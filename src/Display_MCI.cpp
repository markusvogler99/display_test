#include "Display_MCI.h"



Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

double temp_bend =0;
double temp_ax = 0;
int temp_loadcycles = 0;

elapsedMillis time_display; 


void Display_MCI::init_display()
{
tft.begin();
tft.fillScreen(ILI9341_WHITE);
 tft.setRotation(1);
}

void Display_MCI::draw_display(double reading_bend, double reading_ax, int loadcycles)
 
{

  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(5, 100);
  tft.print("Biegekraft: ");
  
  tft.setCursor(5, 120);
  tft.print("Axialkraft: ");

if (time_display > 1000)
  {


   tft.setTextColor(ILI9341_WHITE);
   tft.setCursor(140, 100);
   tft.printf("%3.2f N",temp_bend);

   tft.setCursor(140, 120);
   tft.printf("%3.2f N",temp_ax);

   tft.setCursor(140, 140);
   tft.print(temp_loadcycles);

   tft.setTextColor(ILI9341_BLACK);
   tft.setCursor(140, 100);
   tft.printf("%3.2f N",reading_bend);
  
   tft.setCursor(140, 120);
   tft.printf("%3.2f N",reading_ax);

   tft.setCursor(140, 140);
   tft.print(loadcycles);

   temp_bend =reading_bend;
   temp_ax = reading_ax;
   temp_loadcycles = loadcycles; 
   time_display = 0;
  }
 }
 
     
     


