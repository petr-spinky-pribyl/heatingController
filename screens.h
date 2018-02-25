#ifndef SPI_SCREENS_H
#define SPI_SCREENS_H

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "buttons.h"

#define TEMPERATURE_SCREEN 0x1
#define DELTA_SCREEN 0x2
#define DAILY_SCREEN 0x3
#define TOTAL_SCREEN 0x4
#define SETUP_DELTA_SCREEN 0x11
#define SETUP_DATE_SCREEN 0x12
#define SETUP_TIME_SCREEN 0x13
#define SETUP_SCREEN 0x10

#define isSetup(s) (s & SETUP_SCREEN)

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
  virtual Screen* manageButtons(ButtonController* buttons) = 0;
  /**
   * Factory pro ziskani instnce obrazovky podle kodu
   */
  static Screen* getScreen(byte screenCode);
};

class TemperatureScreen : public Screen {

public:
  TemperatureScreen(float* _t1, float* _t2, byte* _hours, byte* minutes);
  void draw(LiquidCrystal_I2C lcd);
  Screen* manageButtons(ButtonController* buttons);

private:
  float* t1;
  float* t2;
  byte* hours;
  byte* minutes;
};

#endif // SPI_SCREENS_H
