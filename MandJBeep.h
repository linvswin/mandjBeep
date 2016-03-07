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
enum statoSensore {sensNonAttivo, sensAttivo};
enum tipoSensore {intReed, senPIR, sensSirena};

const static byte numSens=8;

const static byte REED1_PIN=4;
const static byte REED2_PIN=5;
const static byte REED3_PIN=6;
const static byte REED4_PIN=7;
const static byte REED5_PIN=8;

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
	int pin;
	tipoSensore tipo;
	boolean attivo;
	statoSensore stato;
	int logica;
	String messaggio;
	boolean malfunzionamento;
	short int conta;
	boolean ritardato;
	short int zona;
public:
	/*        pin - tipoSensore */
	/*Sensore(int p, tipoSensore t){
		this->pin=p;
		this->tipo=t;
		this->attivo=true;
		this->stato=sensNonAttivo;
		this->logica=LOW;
		this->messaggio=F("Allarme");
		this->malfunzionamento=false;
		this->conta=0;
		this->ritardato=false;
	};*/

	/*      pin - tipoSensore - logica*/
	Sensore(int p, tipoSensore t, int l){
		this->pin=p;
		this->tipo=t;
		this->attivo=true;
		this->stato=sensNonAttivo;
		this->logica=l;
		this->messaggio=F("Allarme");
		this->malfunzionamento=false;
		this->conta=0;
		this->ritardato=false;
		this->zona=0;
	};

	/*         pin - tipoSensore - logica - messaggio - zona */
	Sensore(int p, tipoSensore t, int l, const String msg, short int zona=znPerimetrale){
		this->pin=p;
		this->tipo=t;
		this->attivo=true;
		this->stato=sensNonAttivo;
		this->logica=l;
		this->messaggio=msg;
		this->malfunzionamento=false;
		this->conta=0;
		this->ritardato=false;
		this->zona=zona;
	};

	int getPin(){return this->pin;};
	void setPin(int p){this->pin=p;};

	tipoSensore getTipo(){return this->tipo;};
	void setTipo(tipoSensore t){this->tipo=t;};

	boolean getAttivo(){return this->attivo;};
	void setAttivo(boolean a){this->attivo=a;};

	statoSensore getStato(){return this->stato;};
	void setStato(statoSensore a){this->stato=a;};

	int getLogica(){return this->logica;};
	void setLogica(int l){this->logica=l;};

	String getMessaggio(){return this->messaggio;};
	void setMessaggio(String m){this->messaggio=m;};

	boolean getMalfunzionamento(){return this->malfunzionamento;};
	void setMalfunzionamento(boolean m){this->malfunzionamento=m;};

	short int getConta(){return this->conta;};
	void setConta(short int c){this->conta=c;};

	boolean getRitardato(){return this->ritardato;};
	void setRitardato(boolean m){this->ritardato=m;};

	short int getZona(){return this->zona;};
	void setZona(short int z){this->zona=z;};

};


//const static byte SettingsMagic = 0x11;
const static byte PasswordLength_Max = 7;
struct AlarmSettings {
	char alarmPassword1[PasswordLength_Max];
	char alarmPassword2[PasswordLength_Max];
	/*unsigned*/
	int tempoSirena;
	char menuPassword[PasswordLength_Max];
	/*unsigned*/
	int lcdBacklightTime;
	const byte maxReed_Conta;
	short int zona;
///	Sensore sensore[numSens];
} settings = {
	//SettingsMagic, // magic
	"1111", // alarmPassword1,
	"1111", // alarmPassword2,
	20,     // tempoSirena secondi
	"0000", // menuPassword
	30,     // lcdBacklightTime secondi
	5,      //maxReedConta
	/*znPerimetrale, /// zona
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
		Sensore(REED1_PIN, intReed,  LOW, "REED1"),
		Sensore(REED2_PIN, intReed,  LOW, "REED2"),
		Sensore(REED3_PIN, intReed,  LOW, "REED3"),
		Sensore(REED4_PIN, intReed,  LOW, "REED4"),
		Sensore(REED5_PIN, intReed,  LOW, "REED5"),
		Sensore( PIR0_PIN,  senPIR, HIGH, "PIR 1"),
		Sensore( PIR1_PIN,  senPIR, HIGH, "PIR 2"),
		Sensore( PIR2_PIN,  senPIR, HIGH, "PIR 3")
};

// Create the Keypad
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);

//Password
Password password = Password(settings.alarmPassword1);

PCF8574_Class PCF_24(0x24);

MandJTimer t;
int conta = 0;

#include "Menu.h"

#define pwmRegister OCR1A // the logical pin, can be set to OCR1B
const int outPin = 9; // the physical pin
long period = 1000; // the period in microseconds
long pulseWidth = 950; // width of a pulse in microseconds
int prescale[] = { 0, 1, 8, 64, 256, 1024 }; // the range of prescale values

//Do not add code below this line
#endif /* _MandJBeep_H_ */