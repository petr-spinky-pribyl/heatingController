#include "thermometer.h"

#define DIVIDER_RESISTANCE  1000
#define REFERENCE_VOLTAGE   5.0d

TermistorKTY81_110::tempResistance TermistorKTY81_110::tempResistances[] = {
  { -55, 475, 490, 502 },
  { -50, 503, 515, 541 },
  { -40, 541, 567, 595 },
  { -30, 596, 624, 654 },
  { -20, 655, 684, 715 },
  { -10, 716, 747, 781 },
  { 0, 782, 815, 850 },
  { 10, 851, 886, 923 },
  { 20, 924, 961, 980 },
  { 25, 981, 1000, 1020 },
  { 30, 1021, 1040, 1081 },
  { 40, 1082, 1122, 1165 },
  { 50, 1166, 1209, 1254 },
  { 60, 1255, 1299, 1345 },
  { 70, 1346, 1392, 1441 },
  { 80, 1442, 1490, 1540 },
  { 90, 1541, 1591, 1643 },
  { 100, 1643, 1696, 1750 },
  { 110, 1750, 1805, 1860 },
  { 120, 1861, 1915, 1942 },
  { 125, 1943, 1970, 1996 },
  { 130, 1997, 2023, 2073 },
  { 140, 2074, 2124, 2167 },
  { 150, 2168, 2211, 2277 }
};

void TermistorKTY81_110::init(int _pin) {
  pin = _pin;
}

float TermistorKTY81_110::getTemperature() {
  int index = 0;

  int voltageRatio = analogRead(pin);
  Serial.println(voltageRatio);
  double voltage = REFERENCE_VOLTAGE * voltageRatio / 1024;
  Serial.println(voltage);
  int resistance = (int)(DIVIDER_RESISTANCE * voltage / (REFERENCE_VOLTAGE - voltage));
  Serial.println(resistance);
  
  for (int i=0; i<24; i++) {
    if (resistance <= tempResistances[i].highResistance) {
      index = i;
      break;
    }
  }

  if (index == 0) {
    return -55.0;
  }

  if (index == 23) {
    return 150.0;
  }

  if (resistance < tempResistances[index].midResistance) {
     int tempDelta = tempResistances[index].temperature - tempResistances[index-1].temperature;
     int resDelta = tempResistances[index].midResistance - tempResistances[index-1].midResistance;
     float delta = (float)(tempResistances[index].midResistance - resistance) / resDelta;
     float temp = (float)tempResistances[index].temperature - ((float)tempDelta * delta);
     return temp;
  }
  else {
     int tempDelta = tempResistances[index+1].temperature - tempResistances[index].temperature;
     int resDelta = tempResistances[index+1].midResistance - tempResistances[index].midResistance;
     float delta = (float)(tempResistances[index+1].midResistance - resistance) / resDelta;
     float temp = (float)tempResistances[index+1].temperature - ((float)tempDelta * delta);
     return temp;
  }
  
  return 0;
};

