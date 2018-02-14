#include "buttons.h"

void ButtonController::init() {
  pinMode(BTPLUS_PIN, INPUT);
  pinMode(BTMINUS_PIN, INPUT);
  pinMode(BTSETUP_PIN, INPUT);
  timepressed = 0;
  pressStartTime = 0;
  state = NOTHING_PRESSED;
}

byte ButtonController::collectButtonState() {
  buttonPlusState = digitalRead(BTPLUS_PIN);
  buttonMinusState = digitalRead(BTMINUS_PIN);
  buttonSetupState = digitalRead(BTSETUP_PIN);

  if (buttonPlusState == LOW && 
      buttonMinusState == LOW && 
      buttonSetupState == LOW) {
    if (state == BTLONG2_PRESSED || state == BTLONG4_PRESSED) {
      timePressed = millis() - pressStartTime;
    }
    else {
      state = NOTHING_PRESSED;
      timePressed = 0;
      pressStartTime = 0;
      return state;
    }
  }
  else {
    if (pressStartTime == 0) {
      pressStartTime = millis();
    }
  }

  if (buttonPlusState == HIGH) {
    if (state & BTPLUS_PRESSED) {
      timePressed = millis() - pressStartTime;
    }
    state = BTPLUS_PRESSED;
  }

  if (buttonMinusState == HIGH) {
    if (state & BTMINUS_PRESSED) {
      timePressed = millis() - pressStartTime;
    }
    state = BTMINUS_PRESSED;
  }

  if (buttonSetupState == HIGH) {
    if (state & BTSETUP_PRESSED) {
      timePressed = millis() - pressStartTime;
    }
    state = BTSETUP_PRESSED;
  }

  if (timepressed > LONG2_LIMIT) {
    state |= BTLONG2_PRESSED;
  }
  
  if (timepressed > LONG5_LIMIT) {
    state |= BTLONG5_PRESSED;
  }
  
}

