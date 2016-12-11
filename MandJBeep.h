/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
**/
#ifndef _MandJBeep_H_
#define _MandJBeep_H_

#define ECLIPSE

#include "Arduino.h"

#include <avr/wdt.h>
#include <avr/pgmspace.h>

#include <EEPROM.h>
#ifdef ECLIPSE
	#include "lib/MandJTimer/MandJTimer.h"
#else
	#include <MandJTimer.h>
#endif

#define MJGSM
#ifdef MJGSM

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;
boolean started = false;
//int started = 0;

int i_serialh = 0;
char inSerial[40];
char position=0;
char position2=0;
char phone_number[20]; // array for the phone number string
char sms_text[160];

#else
int i_serialh = 0;
char inSerial[40];
#endif

#include <LiquidCrystal_I2C.h>
#ifdef ECLIPSE
	#include "lib/LCDMenuLib/LCDMenuLib.h"
	#include "lib/PCF8574/PCF8574_Class.h"
	#include "lib/Keypad_I2C/Keypad_I2C.h"
	#include "lib/Password/Password.h" //http://www.arduino.cc/playground/uploads/Code/Password.zip
#else
	#include <LCDMenuLib.h>
	#include <PCF8574_Class.h>
	#include <Keypad_I2C.h>
	#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#endif

#define CLKDS3231

#ifndef CLKDS3231
// cambia wuesta riga in RTClib.h
//enum Ds1307SqwPinMode { SQW_OFF = 0x00, SQW_ON = 0x80, SquareWave1HZ = 0x10, SquareWave4kHz = 0x11, SquareWave8kHz = 0x12, SquareWave32kHz = 0x13 };
#include "lib/RTClib/RTClib.h"
#else

#ifdef ECLIPSE
	#include "lib/Rtc/src/RtcDS3231.h"
#else
	#include <RtcDS3231.h>
#endif

#endif

// azzera variabili
#define memtozero_s(var) var ^= var;
#define memtozero_v(var) memset((void*)&var,0,sizeof(var));

#include "pin.h"
#include "def.h"

#ifdef ECLIPSE
	#include "lib/TimerOneThree/TimerOneThree.h"  //https://github.com/heliosoph/TimerOneThree
#else
	#include <TimerOneThree.h>  //https://github.com/heliosoph/TimerOneThree
#endif

#include "Sensore.h"

/* Struttura parametri di configurazione*/
//const static byte SettingsMagic = 0x11;
const static byte PasswordLength_Max = 7;
struct AlarmSettings {
	char alarmPassword1[PasswordLength_Max];	//    password di attivazione
	char alarmPassword2[PasswordLength_Max];	// 				||
	uint8_t tempoSirena;						// tempo attivazione sirena
	char menuPassword[PasswordLength_Max];		// password di accesso menu
	uint8_t lcdBacklightTime;					// durata retroilluminazione
	uint8_t maxReed_Conta;						// numero max di controllo sensore reed attivo, dopodich� disattiva temp il sensore
	uint8_t zona;								// zona attiva
	byte sens;									// configurazione sensori
	//byte adminpass;
	uint8_t tempoRitardo;						// tempo ritardo attiazione
	uint8_t gsm;								// attiva gms
	char phoneNumber1[20]; // array for the phone number string
	char phoneNumber2[20]; // array for the phone number string
	char phoneNumber3[20]; // array for the phone number string
	char phoneNumber4[20]; // array for the phone number string
	char phoneNumber5[20]; // array for the phone number string
} settings = {
	"1111",			// alarmPassword1,
	"2222",			// alarmPassword2,
	30,				// tempoSirena secondi
	"0000",			// menuPassword
	60,				// lcdBacklightTime secondi
	5,				//maxReedConta
	znPerimetrale,	// zona
	//B11000100		// sens
	B10000001,		// sens
	//1,			// adminpass
	20,				// tempo ritardo
	0,				// gsm
	"0000000000",	// phoneNumber1
	"0000000000",	// phoneNumber2
	"0000000000",	// phoneNumber3
	"0000000000",	// phoneNumber4
	"0000000000",	// phoneNumber5
};
/*========================================*/

Sensore sensore[numSens]={
	Sensore(I2C_REED1_PIN,  tpReed,  LOW, "CAMERA", znPerimetrale, false),
	Sensore(I2C_REED2_PIN,  tpReed,  LOW, "BAGNO",  znPerimetrale, false),
	Sensore(I2C_REED3_PIN,  tpReed,  LOW, "SALONE", znPerimetrale, false),
	Sensore(I2C_REED4_PIN,  tpReed,  LOW, "INGRES", znPerimetrale, true),
	Sensore(I2C_REED5_PIN,   tpPIR,  LOW, "CAMER2",     znInterno, true),
	Sensore(I2C_PIR0_PIN,    tpPIR,  LOW,  "SALA2",     znInterno, true),
	Sensore(I2C_GUASTISIRENA_PIN, tpSirena,  HIGH, "SIRENA",znTotale, false),
	Sensore(I2C_TAMPER_PIN, tpTamper,  HIGH, "SABOT.",  znTotale, false),
};

// Create the Keypad
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);
// LCD
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, BACKLIGHT_PIN, NEGATIVE);
//Password
Password password = Password(settings.alarmPassword1);
// PCF8574 modulo sensori 1
PCF8574_Class PCF_24(0x22);

uint8_t conta = 0;		// contatore ritardo attivazione
uint8_t ritardoTriggedGiaAttivato=0;

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

	// timer
	MandJTimer t;
	//Real Time Clock
#ifndef CLKDS3231
	RTC_DS1307 RTC;
	DateTime now;
#else
	RtcDS3231 RTC;
	RtcDateTime now;
#endif

	MandJBeep();
	void inizializza();
	void inizializzaClock();
	void inizializzaLed();
	void inizializzaSensori();
	void inizializzaGSM();

	boolean checkSensori();
	void disattivaSensori();
	void riAttivaSensori();
	void salvaEventoEprom(int num);
	String leggiEventoEprom(byte a);

	void standby();
	void printDate();
	String getDate();

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

	void eseguiSMSComando(char sms_text[]);
	bool getAllarmStatus(){return this->alarmeAttivo;};
};

MandJBeep allarm; //=new MandJBeep();

#include "Menu.h"

#endif /* _MandJBeep_H_ */
