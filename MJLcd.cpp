#include "MJLcd.h"

MJLcd::MJLcd(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
             uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
             uint8_t backlighPin, t_backlighPol pol)
  : LiquidCrystal_I2C(lcd_Addr, En, Rw, Rs, d4, d5, d6, d7, backlighPin, pol) {}

void MJLcd::inizializza() {
  begin(20, 4);
  clear();
}

// void MJLcd::mjBacklight(bool attiva = false) {
//   if (attiva) {
//     backlight();
//   } else {
//     noBacklight();
//   }
// }

size_t MJLcd::mjPrint(String str = "") {
  print(str);
}

size_t MJLcd::mjPrint(uint8_t col = -1, uint8_t row = -1, String str = "") {
  setCursor(col, row);
  print(str);
}



void MJLcd::mjBlink(bool b) {
  if (b) {
    blink();
  } else {
    noBlink();
  }
}