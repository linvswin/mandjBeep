#ifndef _MJLcd_H_
#define _MJLcd_H_

#include "pin.h"
#include <LiquidCrystal_I2C.h>

class MJLcd : public LiquidCrystal_I2C{
public:
 
  //MJLcd();
  MJLcd(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs, 
                     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                     uint8_t backlighPin, t_backlighPol pol);
  void inizializza();
  //void mjBacklight(bool attiva);
  size_t mjPrint(String str);
  size_t mjPrint(uint8_t col, uint8_t row, String str);
  //void clear();
  //void createChar(uint8_t location, uint8_t charmap[]);
  //size_t write(uint8_t value);
  void mjBlink(bool blink);
};

#endif