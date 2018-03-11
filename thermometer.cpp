#include "thermometer.h"

#define MEASURING_INTERVAL  2000  // measure temperature every 2 seconds

#define T1_PIN  0
#define T2_PIN  1

TermistorKTY81_110::tempResistance TermistorKTY81_110::tempResistances[] = {
  { -55, 475, 502 },
  { -50, 503, 541 },
  { -40, 541, 595 },
  { -30, 596, 654 },
  { -20, 655, 715 },
  { -10, 716, 781 },
  { 0, 782, 850 },
  { 10, 851, 923 },
  { 20, 924, 980 },
  { 25, 981, 1020 },
  { 30, 1021, 1081 },
  { 40, 1082, 1165 },
  { 50, 1166, 1254 },
  { 60, 1255, 1345 },
  { 70, 1346, 1441 },
  { 80, 1442, 1540 },
  { 90, 1541, 1643 },
  { 100, 1643, 1750 },
  { 110, 1750, 1860 },
  { 120, 1861, 1942 },
  { 125, 1943, 1996 },
  { 130, 1997, 2073 },
  { 140, 2074, 2167 },
  { 150, 2168, 2277 }
};

void TermistorKTY81_110::init(int _pin) {
  pin = _pin;
}

float TermistorKTY81_110::getTemperature() {
  int index;

  int value = analogRead(pin);

  for (int i=0; i<24; i++) {
    if (value >= tempResistances[i].lowResistance && value <= tempResistances[i].highResistance) {
      index = i;
      break;
    }
  }

   
  return 0;
};

