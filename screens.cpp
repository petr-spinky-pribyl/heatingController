#include "screens.h"

TemperatureScreen::TemperatureScreen(float* _t1, float* _t2) {
  t1 = _t1;
  t2 = _t2;
  oldMinute = minute();
}

void TemperatureScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[16];
  char tempStr[6];


  lcd.clear();

  dtostrf(*t1, 3, 1, tempStr);
  sprintf(buffer, "t1: %s   %02d:%02d", tempStr, hour(), minute());
  lcd.setCursor(0,0);
  lcd.print(buffer);

  dtostrf(*t2, 3, 1, tempStr);
  sprintf(buffer, "t2: %s", tempStr);
  lcd.setCursor(0,1);
  lcd.print(buffer);
  lcd.noCursor();
  lcd.noBlink();
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
  char deltaStr[6];

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Delta");

  dtostrf(*delta, 3, 1, deltaStr);
  sprintf(buffer, "%s", deltaStr);
  lcd.setCursor(0,1);
  lcd.print(buffer);
  lcd.noCursor();
  lcd.noBlink();
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
  lcd.noCursor();
  lcd.noBlink();
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
  lcd.noCursor();
  lcd.noBlink();
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

SetupDeltaScreen::SetupDeltaScreen(float* _delta) {
  delta = _delta;
}

void SetupDeltaScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[16];
  char deltaStr[6];

  lcd.clear();

  lcd.setCursor(3,0);
  lcd.print("( + / - )");

  dtostrf(*delta, 3, 1, deltaStr);
  sprintf(buffer, "Delta: %s", deltaStr);
  lcd.setCursor(0,1);
  lcd.print(buffer);
  lcd.noCursor();
  lcd.noBlink();
}

boolean SetupDeltaScreen::doAction(byte buttonsState, byte* newScreen) {
  if (buttonsState == BTPLUS_RELEASED) {
    *delta += 0.1f;
    return true;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    *delta -= 0.1f;
    return true;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    *newScreen = SETUP_DATE_SCREEN;
    return true;
  }
  return false;
}

SetupDateScreen::SetupDateScreen() {
  cursorPos = 0;
}

void SetupDateScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[18];

  lcd.clear();

  lcd.setCursor(3,0);
  lcd.print("( + / - )");

  sprintf(buffer, "Datum:%2d.%2d.%4d", day(), month(), year());
  lcd.setCursor(0,1);
  lcd.print(buffer);

  if (cursorPos == 2) {
    lcd.setCursor(15, 1);
  }
  else {
    lcd.setCursor(7 + (cursorPos * 3), 1);
  }
  lcd.cursor();
  lcd.blink();
}

boolean SetupDateScreen::doAction(byte buttonsState, byte* newScreen) {
  if (buttonsState == BTPLUS_RELEASED) {
    if (cursorPos == 0) {
      setTime(hour(), minute(), second(), day() + 1, month(), year());
    }
    if (cursorPos == 1) {
      setTime(hour(), minute(), second(), day(), month() + 1, year());
    }
    if (cursorPos == 2) {
      setTime(hour(), minute(), second(), day(), month(), year() + 1);
    }
    return true;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    if (cursorPos == 0) {
      setTime(hour(), minute(), second(), day() - 1, month(), year());
    }
    if (cursorPos == 1) {
      setTime(hour(), minute(), second(), day(), month() - 1, year());
    }
    if (cursorPos == 2) {
      setTime(hour(), minute(), second(), day(), month(), year() - 1);
    }
    return true;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    cursorPos++;
    if (cursorPos == 3) {
      cursorPos = 0;
      *newScreen = SETUP_TIME_SCREEN;
    }
    return true;
  }
  return false;
}

SetupTimeScreen::SetupTimeScreen() {
  cursorPos = 0;
}

void SetupTimeScreen::draw(LiquidCrystal_I2C lcd) {
  char buffer[16];

  lcd.clear();

  lcd.setCursor(3,0);
  lcd.print("( + / - )");

  sprintf(buffer, "Cas: %2d:%2d", hour(), minute());
  lcd.setCursor(0,1);
  lcd.print(buffer);

  lcd.setCursor(6 + (cursorPos * 3), 1);
  lcd.cursor();
  lcd.blink();
}

boolean SetupTimeScreen::doAction(byte buttonsState, byte* newScreen) {
  if (buttonsState == BTPLUS_RELEASED) {
    if (cursorPos == 0) {
      setTime(hour() + 1, minute(), second(), day(), month(), year());
    }
    if (cursorPos == 1) {
      setTime(hour(), minute() + 1, second(), day(), month(), year());
    }
    return true;
  }
  if (buttonsState == BTMINUS_RELEASED) {
    if (cursorPos == 0) {
      setTime(hour() - 1, minute(), second(), day(), month(), year());
    }
    if (cursorPos == 1) {
      setTime(hour(), minute() - 1, second(), day(), month(), year());
    }
    return true;
  }
  if (buttonsState == BTSETUP_RELEASED) {
    cursorPos++;
    if (cursorPos == 2) {
      cursorPos = 0;
      *newScreen = SETUP_DELTA_SCREEN;
    }
    return true;
  }
  return false;
}

