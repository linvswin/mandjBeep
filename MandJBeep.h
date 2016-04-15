/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
**/
#ifndef _MandJBeep_H_
#define _MandJBeep_H_
#include "Arduino.h"

#include <avr/wdt.h>
#include <EEPROM.h>
#include "lib/MandJTimer/MandJTimer.h"

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;
boolean started = false;
int i_serialh = 0;
char inSerial[40];
char position=0;
char phone_number[20]; // array for the phone number string
char sms_text[160];

#include "lib/LCDMenuLib/LCDMenuLib.h"
#include "lib/PCF8574/PCF8574_Class.h"
#include <avr/pgmspace.h>
#include <LiquidCrystal_I2C.h>

#include "lib/Keypad_I2C/Keypad_I2C.h"
#include "lib/Password/Password.h" //http://www.arduino.cc/playground/uploads/Code/Password.zip
// cambia wuesta riga in RTClib.h
//enum Ds1307SqwPinMode { SQW_OFF = 0x00, SQW_ON = 0x80, SquareWave1HZ = 0x10, SquareWave4kHz = 0x11, SquareWave8kHz = 0x12, SquareWave32kHz = 0x13 };
#include "lib/RTClib/RTClib.h"
//#include "lib/Flash/Flash.h"

#include "pin.h"
#include "def.h"
#if BOARD == 2
#include "lib/TimerOneThree/TimerOneThree.h"  //https://github.com/heliosoph/TimerOneThree
#else
#include <TimerOne.h>
#endif

enum znZone {znTotale, znPerimetrale, znInterno};
enum statoSensore {sensNonAttivo, sensAttivo, sensDisabilitato, sensTempDisabilitato, sensTrigged, sensMalfunzionamento};
enum tipoSensore {tpReed, tpPIR, tpSirena, tpTamper};

#define numSens 5

#define I2C_REED1_PIN 0
#define I2C_REED2_PIN 1
#define I2C_REED3_PIN 2
#define I2C_REED4_PIN 3
#define I2C_REED5_PIN 4
#define I2C_PIR0_PIN  7
#define I2C_PIR1_PIN  6
#define I2C_PIR2_PIN  5

class Sensore{
protected:
	uint8_t pin;
	tipoSensore tipo;
	statoSensore stato;
	byte logica;
	String messaggio;
	uint8_t conta;
	boolean ritardato;
	znZone zona;

public:
	Sensore(int p, tipoSensore tipo, byte logica, const String msg, znZone zona=znPerimetrale){
		this->pin=p;
		this->tipo=tipo;
		this->stato=sensAttivo;
		this->logica=logica;
		this->messaggio=msg;
		this->conta=0;
		this->ritardato=false;
		this->zona=zona;
	};

	uint8_t getPin(){return this->pin;};
	void setPin(uint8_t p){this->pin=p;};

	tipoSensore getTipo(){return this->tipo;};
	void setTipo(tipoSensore tipo){this->tipo=tipo;};

	statoSensore getStato(){return this->stato;};
	void setStato(statoSensore a){this->stato=a;};

	byte getLogica(){return this->logica;};
	void setLogica(byte logica){this->logica=logica;};

	String getMessaggio(){return this->messaggio;};
	void setMessaggio(String m){this->messaggio=m;};

	uint8_t getConta(){return this->conta;};
	void setConta(uint8_t conta){this->conta=conta;};

	boolean getRitardato(){return this->ritardato;};
	void setRitardato(boolean m){this->ritardato=m;};

	znZone getZona(){return this->zona;};
	void setZona(znZone z){this->zona=z;};
};

//const static byte SettingsMagic = 0x11;
const static byte PasswordLength_Max = 7;
struct AlarmSettings {
	char alarmPassword1[PasswordLength_Max];
	char alarmPassword2[PasswordLength_Max];
	uint8_t tempoSirena;
	char menuPassword[PasswordLength_Max];
	uint8_t lcdBacklightTime;
	uint8_t maxReed_Conta;
	uint8_t zona;
	byte sens;
	//byte adminpass;
	uint8_t tempoRitardo;
} settings = {
	"1111",        // alarmPassword1,
	"2222",        // alarmPassword2,
	30,            // tempoSirena secondi
	"0000",        // menuPassword
	60,            // lcdBacklightTime secondi
	5,             //maxReedConta
	znPerimetrale, // zona
	//B11000100		// sens
	B00010001,		// sens
	//1,				// adminpass
	20				// tempo ritardo
};

Sensore sensore[numSens]={
	Sensore(I2C_REED1_PIN,  tpReed,  LOW, "CAMERA"),
	Sensore(I2C_REED2_PIN,  tpReed,  LOW, "BAGNO"),
	Sensore(I2C_REED3_PIN,  tpReed,  LOW, "SALONE"),
	Sensore(I2C_REED4_PIN,  tpReed,  LOW, "INGRES"),
	Sensore(I2C_PIR0_PIN,    tpPIR,  HIGH, "PIR1", znInterno),
	//Sensore(I2C_REED5_PIN,  tpReed,  LOW, "REED5"),
	//Sensore(I2C_PIR1_PIN,    tpPIR,  HIGH, "PIR2"),
	//Sensore(I2C_PIR2_PIN,    tpPIR,  HIGH, "PIR3")
};

// Create the Keypad
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);
//Password
Password password = Password(settings.alarmPassword1);
// PCF8574
PCF8574_Class PCF_24(0x22);
// timer
MandJTimer t;
uint8_t conta = 0;

#include "Menu.h"

#define pwmRegister OCR1A // the logical pin, can be set to OCR1B
long period = 1000; // the period in microseconds
long pulseWidth = 950; // width of a pulse in microseconds
const int prescale[] = { 0, 1, 8, 64, 256, 1024 }; // the range of prescale values
//Do not add code below this line
#endif /* _MandJBeep_H_ */
