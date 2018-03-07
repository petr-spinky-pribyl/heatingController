#ifndef SPI_BUTTONS_H
#define SPI_BUTTONS_H

#include <Arduino.h>

#define NOTHING_PRESSED  0b00000000
#define BTPLUS_PRESSED   0b00000001
#define BTMINUS_PRESSED  0b00000010
#define BTSETUP_PRESSED  0b00000100
#define BTPLUS_RELEASED  0b00001000
#define BTMINUS_RELEASED 0b00010000
#define BTSETUP_RELEASED 0b00100000
#define BTLONG2_PRESSED  0b01000000
#define BTLONG5_PRESSED  0b10000000
#define BTPLUS_PIN      2
#define BTMINUS_PIN     3
#define BTSETUP_PIN     4
#define LONG2_LIMIT     2000
#define LONG5_LIMIT     5000

/**
 * Obecna trida pro obsluhu obrazovky. Jednotlive podtridy implementuji samotne chovani
 */
class ButtonController {
public:
  void init();
  void resetTimer();
  byte collectButtonState();
private:
  unsigned long timePressed;
  unsigned long pressStartTime;
  byte state;
  byte buttonPlusState;
  byte buttonMinusState;
  byte buttonSetupState;
};

#endif // SPI_BUTTONS_H
