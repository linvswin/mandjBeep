/**
 * Project Title: M&J Allarm
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
#include <MandJTimer.h>
#include <TimerOne.h>
#include <LCDMenuLib.h>
#include "PCF8574_Class.h"

#include "pin.h"
#include "def.h"

enum znZone {znTotale, znPerimetrale};
enum statoSensore {sensNonAttivo, sensAttivo, sensDisabilitato, sensTempDisabilitato, sensTrigged, sensMalfunzionamento};
enum tipoSensore {intReed, tpPIR, sensSirena};

#define numSens 8

#define I2C_REED1_PIN 4
#define I2C_REED2_PIN 5
#define I2C_REED3_PIN 6
#define I2C_REED4_PIN 7
#define I2C_REED5_PIN 3
#define I2C_PIR0_PIN  0
#define I2C_PIR1_PIN  1
#define I2C_PIR2_PIN  2

/*
 char alarmPassword3[PasswordLength_Max];
 char alarmPassword4[PasswordLength_Max];
 unsigned int keypadDebounceTime;
 unsigned int beforeTurnOnDelay;
 unsigned int beforeAlarmDelay;
 unsigned int alarmOutMask;
 unsigned int alarmInMask;
 unsigned int alarmTamperMask;
 unsigned int alarmFireMask;
 unsigned int alarmStatOutCount;
 unsigned int alarmStatInCount;
 unsigned int alarmStatTamperCount;
 unsigned int alarmStatFireCount;
 ---------------------------------
 "1111", // alarmPassword3,
 "1111", // alarmPassword4,
 80,     // keypadDebounceTime
 30000,   // beforeTurnOnDelay
 15000,   // beforeAlarmDelay
 0xFFFFFFFF, // alarmOutMask - all outputs are enabled
 0xFFFFFFFF, // alarmInMask - all inputs are enabled
 0xFFFFFFFF, // alarmTamperMask - all tampers are enabled
 0xFFFFFFFF, // alarmFireMask - all fire inputs are enabled
 0, // alarmStatOutCount
 0, // alarmStatInCount
 0, // alarmStatTamperCount
 0, // alarmFireCount
 */

class Sensore{
protected:
	char pin;
	tipoSensore tipo;
	statoSensore stato;
	char logica;
	String messaggio;
	int conta;
	boolean ritardato;
	char zona;

public:
	/*      pin - tipoSensore - logica*/
	Sensore(char p, tipoSensore t, char l){
		this->pin=p;
		this->tipo=t;
		this->stato=sensAttivo;
		this->logica=l;
		this->messaggio=F("Allarme");
		this->conta=0;
		this->ritardato=false;
		this->zona=0;
	};

	/*         pin - tipoSensore - logica - messaggio - zona */
	Sensore(char p, tipoSensore t, char l, const String msg, char zona=znPerimetrale){
		this->pin=p;
		this->tipo=t;
		this->stato=sensAttivo;
		this->logica=l;
		this->messaggio=msg;
		this->conta=0;
		this->ritardato=false;
		this->zona=zona;
	};

	char getPin(){return this->pin;};
	void setPin(char p){this->pin=p;};

	tipoSensore getTipo(){return this->tipo;};
	void setTipo(tipoSensore t){this->tipo=t;};

	statoSensore getStato(){return this->stato;};
	void setStato(statoSensore a){this->stato=a;};

	char getLogica(){return this->logica;};
	void setLogica(char l){this->logica=l;};

	String getMessaggio(){return this->messaggio;};
	void setMessaggio(String m){this->messaggio=m;};

	char getConta(){return this->conta;};
	void setConta(int c){this->conta=c;};

	boolean getRitardato(){return this->ritardato;};
	void setRitardato(boolean m){this->ritardato=m;};

	char getZona(){return this->zona;};
	void setZona(char z){this->zona=z;};
};

//const static byte SettingsMagic = 0x11;
const static byte PasswordLength_Max = 7;
struct AlarmSettings {
	char alarmPassword1[PasswordLength_Max];
	char alarmPassword2[PasswordLength_Max];
	/*unsigned*/
	byte tempoSirena;
	char menuPassword[PasswordLength_Max];
	/*unsigned*/
	int lcdBacklightTime;
	const int maxReed_Conta;
	int zona;
///	Sensore sensore[numSens];
} settings = {
	"1111",        // alarmPassword1,
	"2222",        // alarmPassword2,
	20,            // tempoSirena secondi
	"0000",        // menuPassword
	30,            // lcdBacklightTime secondi
	5,             //maxReedConta
	znPerimetrale, // zona
	/*
	{
		Sensore(REED1_PIN, intReed,  LOW, "REED1"),
		Sensore(REED2_PIN, intReed,  LOW, "REED2"),
		Sensore(REED3_PIN, intReed,  LOW, "REED3"),
		Sensore(REED4_PIN, intReed,  LOW, "REED4"),
		Sensore(REED5_PIN, intReed,  LOW, "REED5"),
		Sensore( PIR0_PIN,  senPIR, HIGH, "PIR 1"),
		Sensore( PIR1_PIN,  senPIR, HIGH, "PIR 2"),
		Sensore( PIR2_PIN,  senPIR, HIGH, "PIR 3")
	}*/
};

Sensore sensore[numSens]={
		Sensore(I2C_REED1_PIN, intReed,  LOW, "REED1"),
		Sensore(I2C_REED2_PIN, intReed,  LOW, "REED2"),
		Sensore(I2C_REED3_PIN, intReed,  LOW, "REED3"),
		Sensore(I2C_REED4_PIN, intReed,  LOW, "REED4"),
		Sensore(I2C_REED5_PIN, intReed,  LOW, "REED5"),
		Sensore(I2C_PIR0_PIN,   tpPIR,  HIGH, "PIR 1"),
		Sensore(I2C_PIR1_PIN,   tpPIR,  HIGH, "PIR 2"),
		Sensore(I2C_PIR2_PIN,   tpPIR,  HIGH, "PIR 3")
};

// Create the Keypad
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);
//Password
Password password = Password(settings.alarmPassword1);
// PCF8574
PCF8574_Class PCF_24(0x24);
// timer
MandJTimer t;
int conta = 0;

#include "Menu.h"

#define pwmRegister OCR1A // the logical pin, can be set to OCR1B
const char outPin = 9; // the physical pin
long period = 1000; // the period in microseconds
long pulseWidth = 950; // width of a pulse in microseconds
int prescale[] = { 0, 1, 8, 64, 256, 1024 }; // the range of prescale values

//Do not add code below this line
#endif /* _MandJBeep_H_ */
