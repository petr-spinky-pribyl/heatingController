#include "screens.h"
#include "conversion.h"

#define dirty true
#define clean false

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

boolean TemperatureScreen::doAction(byte buttonsState, byte* newScreen) {
  if (buttonsState == BTPLUS_RELEASED) {
    *newScreen = DELTA_SCREEN;
    return dirty;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    *newScreen = TOTAL_SCREEN;
    return dirty;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    *newScreen = SETUP_DELTA_SCREEN;
    return dirty;
  }
  return clean;
}

DeltaScreen::DeltaScreen(float* _delta) {
  delta = _delta;
}

void DeltaScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[16];

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Delta");

  sprintf(buffer, "%2d.%1d", (int)*delta, decimalPart(*delta, 10));
  lcd.setCursor(0,1);
  lcd.print(buffer);
}

boolean DeltaScreen::doAction(byte buttonsState, byte* newScreen) {
  if (buttonsState == BTPLUS_RELEASED) {
    *newScreen = TOTAL_SCREEN;
    return dirty;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    *newScreen = TEMPERATURE_SCREEN;
    return dirty;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    *newScreen = SETUP_DELTA_SCREEN;
    return dirty;
  }
  return clean;
}

TotalScreen::TotalScreen(unsigned long* _total) {
  total = _total;
}

void TotalScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[16];

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Celkem spusteno");

  sprintf(buffer, "%d:%d", (int)(*total/60), *total % 60);
  lcd.setCursor(0,1);
  lcd.print(buffer);
}

boolean TotalScreen::doAction(byte buttonsState, byte* newScreen) {
  if (buttonsState == BTPLUS_RELEASED) {
    *newScreen = TEMPERATURE_SCREEN;
    return dirty;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    *newScreen = DELTA_SCREEN;
    return dirty;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    *newScreen = SETUP_DELTA_SCREEN;
    return dirty;
  }
  return clean;
}

