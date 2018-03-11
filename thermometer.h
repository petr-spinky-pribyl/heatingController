#ifndef SPI_THERMOMETER_H
#define SPI_THERMOMETER_H

#include <Arduino.h>

/**
 * Class serves KTY81-110 termistor
 */
class TermistorKTY81_110 {
public:
  struct tempResistance {
    int temperature;
    int lowResistance;
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
