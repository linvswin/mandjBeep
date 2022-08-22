/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
**/
#ifndef _MandJBeep_H_
#define _MandJBeep_H_

//#define TEST
//#define ECLIPSE

#include "Arduino.h"

#include <avr/wdt.h>
#include <avr/pgmspace.h>

#include <EEPROM.h>

#ifdef ECLIPSE
	#include "lib/MandJTimer/MandJTimer.h"
	#include "lib/LCDMenuLib/LCDMenuLib.h"
	#include "lib/PCF8574/PCF8574_Class.h"
	#include "lib/Keypad_I2C/Keypad_I2C.h"
	#include "lib/Password/Password.h" //http://www.arduino.cc/playground/uploads/Code/Password.zip
#else
	#include <MandJTimer.h>
	#include <LCDMenuLib.h>
	#include <PCF8574_Class.h>
	#include <Keypad_I2C.h>
	#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#endif

#include <LiquidCrystal_I2C.h>

#define CLKDS3231
#ifndef CLKDS3231
// cambia wuesta riga in RTClib.h
//enum Ds1307SqwPinMode { SQW_OFF = 0x00, SQW_ON = 0x80, SquareWave1HZ = 0x10, SquareWave4kHz = 0x11, SquareWave8kHz = 0x12, SquareWave32kHz = 0x13 };
#include "lib/RTClib/RTClib.h"
#else

#ifdef ECLIPSE
	#include "lib/Rtc/src/RtcDS3231.h"
#else
	//#include <Wire.h>
	#include <RtcDS3231.h>
#endif

#endif

int i_serialh = 0;
char inSerial[40];
char position=0;   // indica la posizione del SMS
char position2=0; // indica la posizione del SMS
//char phone_number[20]; // array for the phone number string
char sms_text[160];
int statoGSM=0;

#include "pin.h"
#include "def.h"

#ifdef ECLIPSE
	#include "lib/TimerOneThree/TimerOneThree.h"  //https://github.com/heliosoph/TimerOneThree
#else
	#include <TimerOneThree.h>  //https://github.com/heliosoph/TimerOneThree
#endif


#include "MJLcd.h"
#include "Clock.h"


// Create the Keypad
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);

// PCF8574 modulo sensori 1
PCF8574_Class PCF_24(0x22);

uint8_t conta = 0;		// contatore ritardo attivazione
byte risposteGSMSlave=0;
uint8_t ritardoAttivato=0;  // settato a 1 quanto si attiva il ritardo in attivazione/disattivazione
//uint8_t ritardoTriggedGiaAttivato=0;

// generare treno PWM
#define pwmRegister OCR1A // the logical pin, can be set to OCR1B
long period = 1000; // the period in microseconds
long pulseWidth = 950; // width of a pulse in microseconds
const int prescale[] = { 0, 1, 8, 64, 256, 1024 }; // the range of prescale values

class MandJBeep
{
//private:
//protected:
public:
	boolean alarmeAttivo;
	boolean statoAllarme;
	boolean adminZone;
	boolean ritardoAttivato;  // settato a true quanto si attiva il ritardo in attivazione/disattivazione

  Password password=Password("");
	// timer
	MandJTimer mjTimer;
  MJLcd &lcd;
  Clock clock;

// 	//Real Time Clock
// #ifndef CLKDS3231
// 	RTC_DS1307 RTC;
// 	DateTime now;
// #else
// 	//RtcDS3231<TwoWire> Rtc(Wire);
// 	RtcDS3231 RTC;
// 	RtcDateTime now;
// #endif

	MandJBeep(MJLcd &_lcd);
	void inizializza();
	//void inizializzaClock();
	void inizializzaLed();
	void inizializzaSensori();
	//void inizializzaGSM();

	boolean checkSensori();
	void disattivaSensori();
	void riAttivaSensori();
	void salvaEventoEprom(int num);
	String leggiEventoEprom(byte a);

	void standby();
	void printDate();
	// String getDate();

	void checkAttivita();
	void checkSMS();
	void alarmTriggered();
	void alarmTriggeredRitardato(uint8_t sensId);
	void primaDiAttivare();
	void attiva();
	void codiceErrato(char adm);
	void disattiva();

	bool checkPassword2();
	void checkPassword();

	void saveSettings(void);
	void loadSettings(void);

	//void eseguiSMSComando(char sms_text[]);
	bool getAllarmStatus(){return this->alarmeAttivo;};

	void sendI2CCmd(String cmd, int ch);
  void setPassword(char* pass);
};

// LCD
MJLcd  _lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, BACKLIGHT_PIN, NEGATIVE);
MandJBeep allarm(_lcd); //=new MandJBeep();

#include "Menu.h"

#endif /* _MandJBeep_H_ */

