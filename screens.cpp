#include "screens.h"
#include "conversion.h"

TemperatureScreen::TemperatureScreen(float* _t1, float* _t2, byte* _hours, byte* _minutes) {
  t1 = _t1;
  t2 = _t2;
  hours = _hours;
  minutes = _minutes;
}

void TemperatureScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[16];

  lcd.clear();

  
  sprintf(buffer, "t1: %2d.%1d   %02d:%02d", (int)*t1, decimalPart(*t1, 10), *hours, *minutes);
  lcd.setCursor(0,0);
  lcd.print(buffer);

  sprintf(buffer, "t2: %2d.%1d", (int)*t2, decimalPart(*t2, 10));
  lcd.setCursor(0,1);
  lcd.print(buffer);
}

