/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
 **/
#ifndef _Pin_H_
#define _Pin_H_

#include "Arduino.h"

#include "Sensore.h"

#define BAUD_RATE  9600  //115200

// software reset
#define Reset_AVR() wdt_enable(WDTO_30MS); while(1) {}

//#define DEBUG
#ifdef DEBUG
//	#define DEBUG_KEY
//	#define DEBUG_SETTINGS
//	#define DEBUG_SENS
//	#define DEBUG_SENS2
//	#define DEBUG_PIR
//	#define DEBUG_SECTIMER
//	#define DEBUG_PRINTDATA
//	#define DEBUG_SMS
#endif

#define ROWS  4  // Four rows
#define COLS  4  // Four columns

const char keys[ROWS][COLS] = { // Define the Keymap
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
	{ '*', '0', '#', 'D' } };

#define I2CADDR 0x21 //keypad
static byte rowPins[ROWS] = { 3, 2, 1, 0 }; //connect to the row pinouts of the keypad
static byte colPins[COLS] = { 7, 6, 5, 4 }; //connect to the column pinouts of the keypad

#define TIMER1_PIN1 13 //13   //buzzer pin
#define TIMER1_PIN2 12   //buzzer pin

#define GREEN_LED  2
#define RED_LED    3
#define GIALLO_LED  1
//#define RELAY_SIRENA1 11
#define RELAY_SIRENA1 14
//#define RELAY_SIRENA2 7

//Indirizzo I2C Slave GSM
#define GSMI2C 0x08

/************* LCD *************/
#define I2C_ADDR    0x20 // LCD: Define I2C Address for controller
#define BACKLIGHT_PIN  7
#define En_pin  4
#define Rw_pin  5
#define Rs_pin  6
#define D4_pin  0
#define D5_pin  1
#define D6_pin  2
#define D7_pin  3
//LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, BACKLIGHT_PIN, NEGATIVE);
/*===============================*/

static uint8_t passwd_pos = 9;  // the postition of the password input

// id timer event
static int8_t timerLCDbacklight = 0;
static int8_t timerPrintData = 0;
static int8_t timerReadGSMSlave = 0;
static int8_t evRitardoAttivazione=0;
static int8_t evAfterRitardoTrigger=0;

/**********************************************************
 **    Definizione di stringhe
 ***********************************************************/
#define TXT_AUTOR              F("Beep by M&J")
#define TXT_SYS_ACTIVE         F("Attivo: ")
#define TXT_ENTER_PIN          F("Codice: ")
#define TXT_INVALID_PIN        F("Codice errato!")
#define TXT_INVALID_ADMIN_PIN  F("Codice Admin errato!")
#define TXT_RIPROVA_PIN        F("Riprova")
#define TXT_SISTEMA_DISATTIVO  F("Sistema Disattivato!")
#define TXT_INTRUSIONE   	   F("Intrusione")
#define TXT_SPAZIO			   F(" ")
#define TXT_INIZIALIZZA_GSM	   "Inizializza GSM.."

//#define TXT_MENU               "Menu"
#define TXT_SICUREZZA			"Sicurezza"
#define TXT_ATTIVA				"Attiva"
#define TXT_PERIMETRALE			"Perimetrale"
#define TXT_INTERNO				"Interno"
#define TXT_TOTALE				"Totale"
#define TXT_DISATTIVA_SENSORI	"Dis.Temp.Sensori"
#define TXT_IMPOSTAZIONE       	"Impostazioni"
#define TXT_SAVE_TO_EPROM     	"Salva EPROM"
#define TXT_LOAD_TO_EPROM      	"Carica EEPROM"
#define TXT_TEMPO_SIRENA       	"Tempo Sirena"
#define TXT_TEMPO_RITARDO      	"Tempo Ritardo"
#define TXT_CONTA_REED			"ContaReed"
#define TXT_LCDBACK_LIGHT_TIME 	"Retroillum"
#define TXT_ADMIN_PASSWORD     	"Admin Password "
#define TXT_PASSWORD1          	"Password1 "
#define TXT_PASSWORD2          	"Password2 "
#define TXT_CONFERMA			"#conferma"
#define TXT_REPORT  			"Report"
#define TXT_SENSORI				"Sensori"
#define TXT_ATTIVA_GSM		    "Attiva GSM"
#define TXT_DISATTIVA_GSM		"Disattiva GSM"
#define TXT_GSM                 "GSM"
#define TXT_NUMERI_GSM          "Numeri"
#define TXT_NUMERI1_GSM          "Numero1"
#define TXT_NUMERI2_GSM          "Numero2"
#define TXT_NUMERI3_GSM          "Numero3"
#define TXT_NUMERI4_GSM          "Numero4"
#define TXT_NUMERI5_GSM          "Numero5"
#define TXT_SYNC_GSM             "Sync Imp GSM"
#define TXT_STATE_GSM            "Stato GSM"
#define TXT_GSM_READY			 "GSM READY"
#define TXT_GSM_NOT_READY		 "GSM Not Ready"
#define TXT_RIAVVIA_GSM			 "Riavvia"
#define TXT_TEMPERATURA			"Temperatura: "
#define TXT_DATA_ORA        "Data/Ora"
#define TXT_DATA        "Data"
#define TXT_ORA        "Ora"
//#define TXT_ATTDIS_GSM       (settings.gsm==0?TXT_ATTIVA_GSM:TXT_DISATTIVA_GSM)
/**********************************************************/
static boolean mostraMenu = false;
/**********************************************************/

/************ Sensori ************/
//numero sensori
#define numSens 8
// pin del PCF8574 connessi al sensore
#define I2C_REED1_PIN 0
#define I2C_REED2_PIN 1
#define I2C_REED3_PIN 2
#define I2C_REED4_PIN 3
#define I2C_PIR0_PIN 4
#define I2C_PIR1_PIN  5
#define I2C_GUASTISIRENA_PIN  6
#define I2C_TAMPER_PIN  7

static Sensore sensore[numSens]={
	Sensore(I2C_REED1_PIN,  tpReed,  LOW, "CAMERA", znPerimetrale, false),
#ifdef TEST
	Sensore(I2C_REED2_PIN,  tpPIR,  LOW, "BAGNO",  znInterno, true),
#else
	Sensore(I2C_REED2_PIN,  tpReed,  LOW, "BAGNO", znPerimetrale, false),
#endif
	Sensore(I2C_REED3_PIN,  tpReed,  LOW, "SALONE", znPerimetrale, false),
	Sensore(I2C_REED4_PIN,  tpReed,  LOW, "INGRES", znPerimetrale, true),
	Sensore(I2C_PIR0_PIN,   tpPIR,   LOW, "CAMER2",     znInterno, false),
	Sensore(I2C_PIR1_PIN,   tpPIR,   LOW,  "SALA2",     znInterno, false),
	Sensore(I2C_GUASTISIRENA_PIN, tpSirena,  HIGH, "SIRENA",znTotale, false),
	Sensore(I2C_TAMPER_PIN, tpTamper,  HIGH, "SABOT.",  znTotale, false),
};
/*===============================*/

/* Struttura parametri di configurazione*/
//const static byte SettingsMagic = 0x11;
const static byte PasswordLength_Max = 7;
static struct AlarmSettings {
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
	znTotale,	// zona
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
#endif
