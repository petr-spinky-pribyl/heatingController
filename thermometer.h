#ifndef SPI_THERMOMETER_H
#define SPI_THERMOMETER_H

#include <Arduino.h>

#define MEASURING_INTERVAL  2000  // measure temperature every 2 seconds
#define T1_PIN  0
#define T2_PIN  1

/**
 * Class serves KTY81-110 termistor
 */
class TermistorKTY81_110 {
public:
  struct tempResistance {
    int temperature;
    int lowResistance;
    int midResistance;
    int highResistance;
  };

  static tempResistance tempResistances[24];
  /**
   * Constructor connects termistor to specific pin
   */
  void init(int _pin);
  
  /**
   * Read termistor resistance and convert it to temperature.
   */
  float getTemperature();
private:
  int pin;
};





#endif // SPI_THERMOMETER_H
