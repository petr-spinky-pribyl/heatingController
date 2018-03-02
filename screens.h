#ifndef SPI_SCREENS_H
#define SPI_SCREENS_H

#include <Arduino.h>
#include <TimeLib.h>
#include "LiquidCrystal_I2C.h"
#include "buttons.h"

#define TEMPERATURE_SCREEN 0x1
#define DELTA_SCREEN 0x2
#define DAILY_SCREEN 0x3
#define TOTAL_SCREEN 0x4
#define SETUP_DELTA_SCREEN 0x11
#define SETUP_DATE_SCREEN 0x12
#define SETUP_TIME_SCREEN 0x13

/**
 * Obecna trida pro obsluhu obrazovky. Jednotlive podtridy implementuji samotne chovani
 */
class Screen {
public:
   /**
    * Vykresleni stranky.
    */
  virtual void draw(LiquidCrystal_I2C lcd) = 0;
  /**
   * Osetreni stisku klaves
   */
  virtual boolean doAction(byte buttonsState, byte* newScreen) = 0;
};

class TemperatureScreen : public Screen {

public:
  TemperatureScreen(float* _t1, float* _t2);
  void draw(LiquidCrystal_I2C lcd);
  boolean doAction(byte buttonsState, byte* newScreen);

private:
  float*  t1;
  float*  t2;
  int     oldMinute;
};

class DeltaScreen : public Screen {

public:
  DeltaScreen(float* _delta);
  void draw(LiquidCrystal_I2C lcd);
  boolean doAction(byte buttonsState, byte* newScreen);

private:
  float* delta;
};

class DailyScreen : public Screen {

public:
  DailyScreen(unsigned long* _dailyTotal);
  void draw(LiquidCrystal_I2C lcd);
  boolean doAction(byte buttonsState, byte* newScreen);

private:
  unsigned long* dailyTotal;
};

class TotalScreen : public Screen {

public:
  TotalScreen(unsigned long* _total);
  void draw(LiquidCrystal_I2C lcd);
  boolean doAction(byte buttonsState, byte* newScreen);

private:
  unsigned long* total;
};

class SetupDeltaScreen : public Screen {

public:
  SetupDeltaScreen(float* _delta);
  void draw(LiquidCrystal_I2C lcd);
  boolean doAction(byte buttonsState, byte* newScreen);

private:
  float* delta;
};

class SetupDateScreen : public Screen {

public:
  SetupDateScreen();
  void draw(LiquidCrystal_I2C lcd);
  boolean doAction(byte buttonsState, byte* newScreen);

private:
  byte cursorPos;
};

class SetupTimeScreen : public Screen {

public:
  SetupTimeScreen();
  void draw(LiquidCrystal_I2C lcd);
  boolean doAction(byte buttonsState, byte* newScreen);

private:
  byte cursorPos;
};


#endif // SPI_SCREENS_H
