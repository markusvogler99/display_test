#include "Display_MCI.h"



Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

double temp_bend =0;
double temp_ax = 0;
int temp_rpm_value = 0; 
int temp_loadcycles = 0;

elapsedMillis time_display;

const int TEXT_SIZE_SMALL = 1;
  const int TEXT_SIZE_LARGE = 2;
  const int ONE_K = 1000;

  const uint16_t INDICATOR_WIDTH = 5;

  const int PHOTODIODE_PIN_2 = 2;

 const uint16_t DIAL_CENTER_X = 320 / 2;
  const uint16_t DIAL_RADIUS = 100;
  const uint16_t DIAL_CENTER_Y = 240 - 1;

  const uint16_t INDICATOR_LENGTH = DIAL_RADIUS - 5;

  const long MAJOR_TICKS[] = { 0, 1000, 2000, 3000,4000, 5000 };
  const int MAJOR_TICK_COUNT = sizeof(MAJOR_TICKS) / sizeof(MAJOR_TICKS[0]);
  const int  MAJOR_TICK_LENGTH = 7;
  const long MINOR_TICKS[] = {500, 1500, 2500, 3500, 4500};
  const int MINOR_TICK_COUNT = sizeof(MINOR_TICKS) / sizeof(MINOR_TICKS[0]);
  const int MINOR_TICK_LENGTH = 3;
  const uint16_t LABEL_RADIUS = DIAL_RADIUS - 18;
  
  const int HALF_CIRCLE_DEGREES = 180;
  const float PI_RADIANS = PI/HALF_CIRCLE_DEGREES;

  const uint16_t DIAL_MAX_RPM = MAJOR_TICKS[MAJOR_TICK_COUNT-1];

  const int DIAL_LABEL_Y_OFFSET = 6;
  const int DIAL_LABEL_X_OFFSET = 4;


  float getPercentMaxRpm(long value) {
	float ret_value = (value * 1.0)/(DIAL_MAX_RPM * 1.0);
	return ret_value;
  };
  float getCircleXWithLengthAndAngle(uint16_t radius, float angle) {
	return DIAL_CENTER_X + radius * cos(angle*PI_RADIANS);
};

float getCircleYWithLengthAndAngle(uint16_t radius, float angle) {
	return DIAL_CENTER_Y + radius * sin(angle*PI_RADIANS);
};



  void drawTicks(const long ticks[], int tick_count, int tick_length) {
  for (int tick_index = 0; tick_index < tick_count; tick_index++) {
		long rpm_tick_value = ticks[tick_index];
		float tick_angle = (HALF_CIRCLE_DEGREES * getPercentMaxRpm(rpm_tick_value)) + HALF_CIRCLE_DEGREES;
		uint16_t dial_x = getCircleXWithLengthAndAngle(DIAL_RADIUS - 1, tick_angle);
		uint16_t dial_y = getCircleYWithLengthAndAngle(DIAL_RADIUS - 1, tick_angle);
		uint16_t tick_x = getCircleXWithLengthAndAngle(DIAL_RADIUS - tick_length, tick_angle);
		uint16_t tick_y = getCircleYWithLengthAndAngle(DIAL_RADIUS - tick_length, tick_angle);
		tft.drawLine(dial_x, dial_y, tick_x, tick_y, ILI9341_WHITE);
	}
}
 
 void drawTickMarks() {
  drawTicks(MAJOR_TICKS, MAJOR_TICK_COUNT, MAJOR_TICK_LENGTH);
  drawTicks(MINOR_TICKS, MINOR_TICK_COUNT, MINOR_TICK_LENGTH);
}

void drawMajorTickLabels() {
	tft.setTextSize(TEXT_SIZE_SMALL);
	for (int label_index = 0; label_index < MAJOR_TICK_COUNT; label_index++) {
		long rpm_tick_value = MAJOR_TICKS[label_index];
		float tick_angle = (HALF_CIRCLE_DEGREES	* getPercentMaxRpm(rpm_tick_value)) + HALF_CIRCLE_DEGREES;
		uint16_t dial_x = getCircleXWithLengthAndAngle(LABEL_RADIUS, tick_angle);
		uint16_t dial_y = getCircleYWithLengthAndAngle(LABEL_RADIUS, tick_angle);
		tft.setCursor(dial_x - DIAL_LABEL_X_OFFSET, dial_y - DIAL_LABEL_Y_OFFSET);
		int label_value = rpm_tick_value / ONE_K;
		tft.print(label_value);
	}
}

void drawIndicatorHand(long rpm_value) {
    float indicator_angle = (HALF_CIRCLE_DEGREES * getPercentMaxRpm(rpm_value)) + HALF_CIRCLE_DEGREES;
    uint16_t indicator_top_x = getCircleXWithLengthAndAngle(INDICATOR_LENGTH, indicator_angle);
    uint16_t indicator_top_y = getCircleYWithLengthAndAngle(INDICATOR_LENGTH, indicator_angle);

	tft.drawTriangle(DIAL_CENTER_X - INDICATOR_WIDTH / PHOTODIODE_PIN_2,
	                     DIAL_CENTER_Y,DIAL_CENTER_X + INDICATOR_WIDTH / PHOTODIODE_PIN_2,
	                     DIAL_CENTER_Y,
	                     indicator_top_x, 
	                     indicator_top_y, 
	                     ILI9341_WHITE);
}

void Display_MCI::init_display()
{
tft.begin();
tft.fillScreen(ILI9341_BLACK);
 tft.setRotation(3);
}

void Display_MCI::draw_display(double reading_bend, double reading_ax, int rpm_value, int test)
 
{

  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 5);
  tft.print("Biegekraft: ");
  
  tft.setCursor(5, 25);
  tft.print("Axialkraft: ");

  tft.setCursor(5, 45);
  tft.print("Drehzahl: ");
  
  tft.setCursor(5, 65);
  tft.print("Lastzyklen: ");
/*
if (time_display > 1000)
  {
   tft.setTextColor(ILI9341_BLACK);
   tft.setCursor(140, 5);
   tft.printf("%3.2f N",temp_bend);

   tft.setCursor(140, 25);
   tft.printf("%3.2f N",temp_ax);

   tft.setCursor(140, 45);
   tft.printf("%d rpm", temp_rpm_value);

   tft.setCursor(140, 65);
   tft.print(temp_loadcycles);

   tft.setTextColor(ILI9341_WHITE);
   tft.setCursor(140, 5);
   tft.printf("%3.2f N",reading_bend);
  
   tft.setCursor(140, 25);
   tft.printf("%3.2f N",reading_ax);

   tft.setCursor(140, 45);
   tft.printf("%d rpm",rpm_value);

  tft.setCursor(140, 65);
   tft.print(test);

   temp_bend =reading_bend;
   temp_ax = reading_ax;
   temp_rpm_value = rpm_value;
   temp_loadcycles = test; 
   time_display = 0;
  }*/
 }
 
     
void Display_MCI::draw_tacho(int rpm)
{
  tft.drawCircle(DIAL_CENTER_X, DIAL_CENTER_Y, DIAL_RADIUS, ILI9341_WHITE);
  drawTickMarks();
  drawMajorTickLabels();
  drawIndicatorHand(rpm);
}

