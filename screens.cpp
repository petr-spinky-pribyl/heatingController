#include "screens.h"
#include "conversion.h"

TemperatureScreen::TemperatureScreen(float* _t1, float* _t2) {
  t1 = _t1;
  t2 = _t2;
  oldMinute = minute();
}

void TemperatureScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[16];

  lcd.clear();

  sprintf(buffer, "t1: %2d.%1d   %02d:%02d", (int)*t1, decimalPart(*t1, 10), hour(), minute());
  lcd.setCursor(0,0);
  lcd.print(buffer);

  sprintf(buffer, "t2: %2d.%1d", (int)*t2, decimalPart(*t2, 10));
  lcd.setCursor(0,1);
  lcd.print(buffer);
}

boolean TemperatureScreen::doAction(byte buttonsState, byte* newScreen) {
  boolean redrawRequired = false;
  
  if (oldMinute != minute()) {
    oldMinute = minute();
    redrawRequired = true;
  }
  if (buttonsState == BTPLUS_RELEASED) {
    *newScreen = DELTA_SCREEN;
    redrawRequired = true;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    *newScreen = TOTAL_SCREEN;
    redrawRequired = true;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    *newScreen = SETUP_DELTA_SCREEN;
    redrawRequired = true;
  }
  return redrawRequired;
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
    *newScreen = DAILY_SCREEN;
    return true;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    *newScreen = TEMPERATURE_SCREEN;
    return true;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    *newScreen = SETUP_DELTA_SCREEN;
    return true;
  }
  return false;
}

DailyScreen::DailyScreen(unsigned long* _dailyTotal) {
  dailyTotal = _dailyTotal;
}

void DailyScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[16];

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Dnes spusteno");

  sprintf(buffer, "%d:%d", (int)(*dailyTotal/60), *dailyTotal % 60);
  lcd.setCursor(0,1);
  lcd.print(buffer);
}

boolean DailyScreen::doAction(byte buttonsState, byte* newScreen) {
  if (buttonsState == BTPLUS_RELEASED) {
    *newScreen = TOTAL_SCREEN;
    return true;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    *newScreen = DELTA_SCREEN;
    return true;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    *newScreen = SETUP_DELTA_SCREEN;
    return true;
  }
  return false;
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
    return true;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    *newScreen = DAILY_SCREEN;
    return true;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    *newScreen = SETUP_DELTA_SCREEN;
    return true;
  }
  return false;
}

