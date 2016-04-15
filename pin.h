/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
**/

#define BAUD_RATE  9600  //115200    //9600
#define MJGSM

#define DEBUG
#ifdef DEBUG
//	#define DEBUG_KEY
//	#define DEBUG_SETTINGS
//	#define DEBUG_SENS
//	#define DEBUG_SENS2
//	#define DEBUG_PIR
//	#define DEBUG_SECTIMER
//	#define DEBUG_PRINTDATA
	#define DEBUG_SMS
#endif

#define ROWS  4  // Four rows
#define COLS  4  // Four columns

const char keys[ROWS][COLS] = { // Define the Keymap
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

#define I2CADDR 0x21 //keypad
byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

#define BOARD 2  // 0 mega2560, 1 uno r3
#if ( BOARD==0 )
//	#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

	#define TIMER2_PIN1 9
	#define TIMER2_PIN2 10
	
	#define YELLOW_LED  37
	#define RED_LED     46

	#define PIR_PIN1    47
	#define RELAY_SIRENA1 4
	#define RELAY_SIRENA2 5
#endif
#if ( BOARD==1 )

	#define TIMER1_PIN1 9   //buzzer pin
	//#define TIMER1_PIN2 10   //buzzer pin
	//#define TIMER2_PIN1 3
	//#define TIMER2_PIN2 11
	#define GREEN_LED  2
	#define RED_LED    4
	//#define GIALLO_LED  8
	//#define RELAY_SIRENA1 6
	//#define RELAY_SIRENA2 7
#endif
#if ( BOARD==2 )
	#define TIMER1_PIN1 13 //13   //buzzer pin
	#define TIMER1_PIN2 12   //buzzer pin

	#define GREEN_LED  2
	#define RED_LED    3
	#define GIALLO_LED  1
	#define RELAY_SIRENA1 11
	//#define RELAY_SIRENA2 7
#endif

#define I2C_ADDR    0x20 // LCD: Define I2C Address for controller
#define BACKLIGHT_PIN  7
#define En_pin  4
#define Rw_pin  5
#define Rs_pin  6
#define D4_pin  0
#define D5_pin  1
#define D6_pin  2
#define D7_pin  3
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, BACKLIGHT_PIN, NEGATIVE);

//Real Time Clock
RTC_DS1307 RTC;
DateTime now;

boolean alarmeAttivo=false;
boolean statoAllarme=false;
boolean adminZone=false;

uint8_t passwd_pos=9;  // the postition of the password input

// id timer event
int8_t timerLCDbacklight=0;
int8_t timerPrintData=0;

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
/**********************************************************/
boolean mostraMenu=false;
/**********************************************************/
