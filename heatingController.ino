// LCD displej pres I2C
// navody.arduino-shop.cz

// knihovny pro LCD přes I2C
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "screens.h"
#include "buttons.h"

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

// Obsluha tlacitek
ButtonController* buttons;
byte buttonsState;

// data kontroleru
float t1;
float t2;
byte hours;
byte minutes;


void setup()
{
  // inicializace dat kontroleru
  t1 = 15.2;
  t2 = 2.1;
  hours = 15;
  minutes = 3;
  
  // inicializace obrazovek
  temperatureScreen = new TemperatureScreen(&t1, &t2, &hours, &minutes);
  actualScreen = temperatureScreen;

  // inicializace tlacitek
  buttons = new ButtonController();
  buttons->init();
  buttonsState = NOTHING_PRESSED;
  
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

  if (isSetup(actualScreen)) {
    
  }
  else {
    
  }
  
  // stavy
  // spi -> nespi = stisk libovolneno tlacitka
  // nespi -> spi = 10 vterin bez stisku tlacitka
  // provoz -> nastaveni = stisk tlacitka Set
  // nastaveni -> provoz = 5 vterin bez stisku tlacitka

  if (buttonSetState == HIGH)
    if (sleeping) {
      sleeping = false;
      lcd.backlight();
      delay(500);
    }
    else {
      sleeping = true;
      lcd.noBacklight();
      delay(500);
    }
    
}

