#include "buttons.h"

void ButtonController::init() {
  pinMode(BTPLUS_PIN, INPUT);
  pinMode(BTMINUS_PIN, INPUT);
  pinMode(BTSETUP_PIN, INPUT);
  timePressed = 0;
  pressStartTime = 0;
  state = NOTHING_PRESSED;
}

void ButtonController::resetTimer() {
  timePressed = 0;
  pressStartTime = millis();
}

byte ButtonController::collectButtonState() {
  buttonPlusState = digitalRead(BTPLUS_PIN);
  buttonMinusState = digitalRead(BTMINUS_PIN);
  buttonSetupState = digitalRead(BTSETUP_PIN);

  if (buttonPlusState == LOW && 
      buttonMinusState == LOW && 
      buttonSetupState == LOW) {
    if (state & BTPLUS_PRESSED) {
      state = BTPLUS_RELEASED;
      timePressed = 0;
      pressStartTime = millis();
    }
    else {
      if (state & BTMINUS_PRESSED) {
        state = BTMINUS_RELEASED;
        timePressed = 0;
        pressStartTime = millis();
      }
      else {
        if (state & BTSETUP_PRESSED) {
          state = BTSETUP_RELEASED;
          timePressed = 0;
          pressStartTime = millis();
          return state;
        }
        else {
          timePressed = millis() - pressStartTime;
          state = NOTHING_PRESSED;
        }
      }
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
    else {
      timePressed = 0;
      pressStartTime = millis();
      state = BTPLUS_PRESSED;
    }
  }

  if (buttonMinusState == HIGH) {
    if (state & BTMINUS_PRESSED) {
      timePressed = millis() - pressStartTime;
    }
    else {
      timePressed = 0;
      pressStartTime = millis();
      state = BTMINUS_PRESSED; 
    }
  }

  if (buttonSetupState == HIGH) {
    if (state & BTSETUP_PRESSED) {
      timePressed = millis() - pressStartTime;
    }
    else {
      timePressed = 0;
      pressStartTime = millis();
      state = BTSETUP_PRESSED;
    }
  }

  if (timePressed > LONG2_LIMIT) {
    state |= BTLONG2_PRESSED;
  }
  
  if (timePressed > LONG5_LIMIT) {
    state |= BTLONG5_PRESSED;
  }

  return state;
}

