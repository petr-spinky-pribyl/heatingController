// LCD displej pres I2C
// navody.arduino-shop.cz

// knihovny pro LCD přes I2C
#include <Wire.h>
#include <TimeLib.h>
#include "LiquidCrystal_I2C.h"
#include "screens.h"
#include "buttons.h"
#include "thermometer.h"

// nastavení adresy I2C (0x27 v mém případě),
// a dále počtu znaků a řádků LCD, zde 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);


// stavy displeje
bool sleeping = false;
bool dirty = true;
byte actualScreenNumber = TEMPERATURE_SCREEN;

// timeouty displeje a nastaveni
unsigned int sleepDelay = 10000;
unsigned int settingsDelay = 5000;

// Obrazovky
Screen* actualScreen;
TemperatureScreen* temperatureScreen;
DeltaScreen*       deltaScreen;
DailyScreen*       dailyScreen;
TotalScreen*       totalScreen;
SetupDeltaScreen*  setupDeltaScreen;
SetupDateScreen*   setupDateScreen;
SetupTimeScreen*   setupTimeScreen;

// Obsluha tlacitek
ButtonController* buttons;
byte buttonsState;

// teplomery
//TermistorKTY81_110*  termistor1;
//TermistorKTY81_110*  termistor2;
Sensor_DS18B20*      thermometer1;
Sensor_DS18B20*      thermometer2;
unsigned long        lastMeasure;
unsigned long        measureInterval = 2000;

// data kontroleru
float t1;
float t2;
float delta;
unsigned long dailyTime;
unsigned long totalTime;


void setup()
{
  // inicializace dat kontroleru
  setTime(0, 0, 0, 1, 1, 2017);
  totalTime = 0;
  delta = 2.5;
  
  // inicializace obrazovek
  temperatureScreen = new TemperatureScreen(&t1, &t2);
  deltaScreen = new DeltaScreen(&delta);
  dailyScreen = new DailyScreen(&dailyTime);
  totalScreen = new TotalScreen(&totalTime);
  setupDeltaScreen = new SetupDeltaScreen(&delta);
  setupDateScreen = new SetupDateScreen();
  setupTimeScreen = new SetupTimeScreen();
  actualScreen = temperatureScreen;

  // inicializace tlacitek
  buttons = new ButtonController();
  buttons->init();
  buttonsState = NOTHING_PRESSED;

  Serial.begin(9600);
    Serial.println("Start");

  // inicializace teplomeru
//  termistor1 = new TermistorKTY81_110();
//  termistor2 = new TermistorKTY81_110();
//  termistor1->init(T1_PIN);
//  termistor2->init(T2_PIN);
  thermometer1 = new Sensor_DS18B20();
  thermometer1->init(5);
  t1 = thermometer1->getTemperature();
//  t2 = termistor2->getTemperature();
  lastMeasure = 0;
  
  // inicializace LCD
  lcd.begin();
  // zapnutí podsvícení
  lcd.backlight();
  // zabraz logo
  lcd.print("*heating control");
  delay(2000);
  lcd.clear();

}

void loop()
{
  if (!sleeping && dirty) {
    actualScreen->draw(lcd);
    dirty = false;
  }

  // stavy
  // spi -> nespi = stisk libovolneno tlacitka
  // nespi -> spi = 10 vterin bez stisku tlacitka
  // provoz -> nastaveni = stisk tlacitka Set
  // nastaveni -> provoz = 5 vterin bez stisku tlacitka
  buttonsState = buttons->collectButtonState();
  if (sleeping && (buttonsState & (BTPLUS_RELEASED | BTMINUS_RELEASED | BTSETUP_RELEASED))) {
    lcd.backlight();
    sleeping = false;
    actualScreen->draw(lcd);
    return;
  }
  if (!sleeping && (buttonsState == (BTLONG5_PRESSED | BTLONG2_PRESSED)) && actualScreenNumber <= TOTAL_SCREEN) {
    lcd.noBacklight();
    sleeping = true;
    return;
  }
  if (!sleeping && (buttonsState == (BTLONG5_PRESSED | BTLONG2_PRESSED)) && actualScreenNumber > TOTAL_SCREEN) {
    actualScreenNumber = TEMPERATURE_SCREEN;
    actualScreen = temperatureScreen;
    buttons->resetTimer();
    dirty = true;
    return; 
  }
  if (abs(millis() - lastMeasure) > measureInterval) {
    lastMeasure = millis();
    t1 = thermometer1->getTemperature();
  }
  
  dirty = actualScreen->doAction(buttonsState, &actualScreenNumber);
  actualScreen = getScreenByNumber(actualScreenNumber);
}

Screen* getScreenByNumber(byte screenNumber) {
// TEMPERATURE_SCREEN 0x1
// DELTA_SCREEN 0x2
// DAILY_SCREEN 0x3
// TOTAL_SCREEN 0x4
// SETUP_DELTA_SCREEN 0x11
// SETUP_DATE_SCREEN 0x12
// SETUP_TIME_SCREEN 0x13

  switch (screenNumber) {
    case TEMPERATURE_SCREEN : return temperatureScreen;
    case DELTA_SCREEN       : return deltaScreen;
    case DAILY_SCREEN       : return dailyScreen;
    case TOTAL_SCREEN       : return totalScreen;
    case SETUP_DELTA_SCREEN : return setupDeltaScreen;
    case SETUP_DATE_SCREEN  : return setupDateScreen;
    case SETUP_TIME_SCREEN  : return setupTimeScreen;
  }
}

