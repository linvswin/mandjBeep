/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
 * Note: basato sul progetto Home Security System di Jun Peng - Tech 169
 **/

#include "MandJBeep.h"

String printDigit(int digits) {
	String temp = "";
	if (digits < 10)
		temp += "0";
	temp += digits;
	return temp;
}

void setup() {
	Serial.begin(BAUD_RATE);

	allarm.inizializza();

	lcd.begin(20, 4);
	MenuSetup();

#ifdef DEBUG_SETTINGS
	Serial.print(F("Setting sizeof: "));
	Serial.println(sizeof(settings));
	printSettings();
#endif

	allarm.standby();

	allarm.t.startTimer();
	// avvia evento stampa data ogni secondo
	timerPrintData = allarm.t.every(1, printDate);
	// attiva evento spegni LCD dopo lcdBacklightTime secondi
	timerLCDbacklight = allarm.t.every(settings.lcdBacklightTime,
			timerDoLCDbacklight);

	if (settings.gsm == 1) {
		lcd.setCursor(0, 2);
		lcd.println(TXT_INIZIALIZZA_GSM);
		allarm.inizializzaGSM();
		allarm.standby();
	}
	// attivo watchdog 8s
	wdt_enable(WDTO_8S);
}

void loop() {

#ifndef CLKDS3231
	allarm.now = allarm.RTC.now();
#else
	allarm.now = allarm.RTC.GetDateTime();
#endif

	keypad.getKey();

	// legge la presenza di messaggi sms
	allarm.checkSMS();
	// legge lo stato dei sensori
	allarm.checkAttivita();

	MenuLoop();
	allarm.t.update();
	// reset il  watchdog
	wdt_reset();
}

void keypadEvent(KeypadEvent eKey) {

#ifdef DEBUG
#ifdef DEBUG_KEY
	Serial.print(F("Tasto: "));
	Serial.println(eKey);
	lcd.setCursor(0, 2);
	lcd.print(eKey);
#endif
#endif

	switch (keypad.getState()) {
	case PRESSED:
		if (passwd_pos - 9 >= 10) {
			//return;
			passwd_pos = 9;
		}
		lcd.backlight();
		allarm.t.stop(timerLCDbacklight);
		timerLCDbacklight = allarm.t.every(settings.lcdBacklightTime,
				timerDoLCDbacklight);

		switch (eKey) {
		case '#':
			if (mostraMenu == false) { //# is to validate password
				passwd_pos = 9;
				allarm.checkPassword();
			} else {
				LCDML_BUTTON_enter()
				;
			}
			break;
		case '*':                 //* is to reset password attempt
			if (mostraMenu == false) {
				password.reset();
				passwd_pos = 9;
				mostraMenu = false;
				allarm.standby();
			} else {
				LCDML_BUTTON_quit()
				;
			}
			break;
		case 'A':
			if (mostraMenu == false) {
				if (allarm.statoAllarme == false) {
					allarm.primaDiAttivare();
					//	disattivaSensori();
				}
			}
			break;
		case 'B':
			if (mostraMenu == false) {
				passwd_pos = 9;
				password.set(settings.menuPassword);
				if (allarm.checkPassword2()) {
					allarm.t.stop(timerPrintData);
					mostraMenu = true;
					LCDML.goRoot();
					LCDML_BUTTON_up()
					;
				} else
					allarm.codiceErrato(1);
			} else {
				password.reset();
				password.set(settings.alarmPassword1);
				mostraMenu = false;
				timerPrintData = allarm.t.every(1, printDate);
				allarm.standby();
			}
			break;
		case 'C':
			if (mostraMenu == false) {
				lcd.backlight();
			} else {
				LCDML_BUTTON_up()
				;
			}
			break;
		case 'D':
			if (mostraMenu == false) {
				//lcd.noBacklight();
			} else {
				LCDML_BUTTON_down()
				;
			}
			break;
		default:
			if (mostraMenu == false) {
				password.append(eKey);
				lcd.setCursor((passwd_pos++), 0);
				lcd.print(F("*"));
			} else {
				if (mnuNewTxtVal == 0) {
					if (indNewTxtVal < PasswordLength_Max - 1) {
						newTxtVal[indNewTxtVal] = eKey;
						indNewTxtVal++;
					}
				} else if (mnuNewTxtVal == 1) {
					if (indNewTxtVal2 < 19) {
						newTxtVal2[indNewTxtVal2] = eKey;
						indNewTxtVal2++;
					}
				}
			}
			break;
		}
	}
}

void printDate() {
	//TIME and DATE
	lcd.setCursor(0, 1);
	lcd.print(allarm.getDate());
}

#ifdef DEBUG_SETTINGS
void printSettings()
{
	Serial.print(F("tempo sirena: "));
	Serial.println(settings.tempoSirena);
	Serial.print(F("tempo lcd: "));
	Serial.println(settings.lcdBacklightTime);
	Serial.print(F("conta REED: "));
	Serial.println(settings.maxReed_Conta);
	Serial.print(F("sens: "));
	Serial.println(settings.sens);
	Serial.print(F("zona: "));
	Serial.println(settings.zona);
	Serial.print(F("AdminPassword: "));
	Serial.println(settings.menuPassword);
	Serial.print(F("Password1: "));
	Serial.println(settings.alarmPassword1);
	Serial.print(F("Password2: "));
	Serial.println(settings.alarmPassword2);
}
#endif

/*
 * evento dopo ritardo attivazione
 */
void doAfterRitActivate() {
#ifdef DEBUG
	Serial.println(F("Attivo Allarme"));
#endif
	conta = 0;
	//allarm.attiva();
	allarm.ritardoAttivato=false;
	mostraMenu = false;
	allarm.standby();
}

/*
 * evento dopo tempoSirena:
 *   - disattiva Timer1PWM
 *   - disattiva sirena
 *   - cambia stato al sensore attivato
 */
void doAfterTimerT() {
	Timer1.disablePwm(TIMER1_PIN1);

	digitalWrite(RELAY_SIRENA1, HIGH);
	for (int i = 0; i < numSens; i++) {
		if (sensore[i].getStato() == sensTrigged)
			sensore[i].setStato(sensAttivo);
	}
}

bool setPulseWidth(long microseconds) {
	//bool ret = false;
	//int prescaleValue = prescale[Timer1.clockSelectBits];

	// calculate time per counter tick in nanoseconds
	long precision = (F_CPU / 128000) * prescale[Timer1.clockSelectBits];
	period = precision * ICR1 / 1000; // period in microseconds
	if (microseconds < period) {
		int duty = map(microseconds, 0, period, 0, 1024);
		if (duty < 1)
			duty = 1;
		if (microseconds > 0 && duty < RESOLUTION) {
			Timer1.pwm(TIMER1_PIN1, duty);
			return true;
		}
	}
	return false;
}

int xxxx = 0;

void doPrintRitAttivazione() {
	//standby();
	lcd.setCursor(0, 2);
	lcd.print(F("Rit. "));
	lcd.print(++conta);

	if (xxxx == 0) {
		xxxx = 1;
		Timer1.initialize(period); // initialize timer1, 1000 microseconds
		setPulseWidth(pulseWidth); // long pulseWidth = 950; // width of a pulse in microseconds
	} else {
		Timer1.disablePwm(TIMER1_PIN1);
		xxxx = 0;
	}
}

void doAfterRitardoTrigged(){
	allarm.alarmTriggered();
}

void timerDoLCDbacklight() {
	if (mostraMenu == true) {
		mostraMenu == false;
		allarm.standby();
	}
	lcd.noBacklight();
}

void inviaSMScomando(char *number_str, char *message_str) {
	wdt_disable();
#ifdef DEBUG_SMS
	Serial.print("Num: ");
	Serial.println(number_str);
	Serial.print("Msg: ");
	Serial.println(message_str);
#endif
	sms.SendSMS(number_str, message_str);
	wdt_enable(WDTO_8S);
}

/********************************************************/
/*
 * funzione che stampa su LCD
 */
void MandJBeep::standby() {
	//display time and date
	lcd.clear();
	lcd.setCursor(0, 0);
	if (this->alarmeAttivo)
		lcd.print(TXT_SYS_ACTIVE);
	else
		lcd.print(TXT_ENTER_PIN);
//	lcd.setCursor(0, 1);
//	lcd.print(getDate());
	lcd.setCursor(5, 3);
	lcd.print(TXT_AUTOR);
}

/*
 * funzione che formatta per stampa su LCD di data e ora
 */
String MandJBeep::getDate() {
	String txt = F("");
#ifndef CLKDS3231
	txt += printDigit(now.hour()) + F(":");
	txt += printDigit(now.minute()) + F(":");
	txt += printDigit(now.second());
	txt += TXT_SPAZIO;
	txt += printDigit(now.day()) + F("/");
	txt += printDigit(now.month()) + F("/");
	txt += printDigit(now.year());
#else
	txt += printDigit(now.Hour()) + F(":");
	txt += printDigit(now.Minute()) + F(":");
	txt += printDigit(now.Second());
	txt += TXT_SPAZIO;
	txt += printDigit(now.Day()) + F("/");
	txt += printDigit(now.Month()) + F("/");
	txt += printDigit(now.Year());
#endif

#ifdef  DEBUG
#ifdef DEBUG_PRINTDATA
	Serial.print(F("date: "));
	Serial.println(txt);
#endif
#endif
	return txt;
}

/*
 * check la password di admin
 */
bool MandJBeep::checkPassword2() {
	return password.evaluate();
}

/*
 * check la password di attivazione
 * 	se corretta e l'allarme non attivo ==>  fa i controlli prima dell'attivazione
 * 		altrimento lo disattiva
 */
void MandJBeep::checkPassword() {
	if (password.evaluate()) {
		if (this->alarmeAttivo == false && this->statoAllarme == false) {
			primaDiAttivare();
		} else if (this->alarmeAttivo == true || this->statoAllarme == true)
			disattiva();
	} else
		codiceErrato(0);
}

/*
 *
 */
void MandJBeep::codiceErrato(char adm = 0) {
	password.reset();
	lcd.clear();

	if (adm == 0) {
		lcd.setCursor(3, 0);
		lcd.print(TXT_INVALID_PIN);
	} else {
		password.set(settings.alarmPassword1);
		lcd.setCursor(0, 0);
		lcd.print(TXT_INVALID_ADMIN_PIN);
	}
	lcd.setCursor(5, 2);
	lcd.print(TXT_RIPROVA_PIN);
	delay(1000);
	allarm.standby();
}

/*
 *  esegue il checkSensori, se tutto ok attiva gli eventi:
 *    - ritardo attivazione
 *    - dopo ritardo attiva allarme
 */
void MandJBeep::primaDiAttivare() {
#ifdef DEBUG
	Serial.println(F("Ritardo attivazione ..........."));
#endif
	lcd.backlight();
	if (this->checkSensori()) {
		if (settings.tempoRitardo % 2 == 0)
			xxxx = 0;
		else
			xxxx = 1;
		position2 = position;
		conta=0;
		this->ritardoAttivato=true;
		this->attiva();
		evRitardoAttivazione=this->t.every(1, doPrintRitAttivazione, settings.tempoRitardo);
		this->t.after(settings.tempoRitardo, doAfterRitActivate);
		this->standby();
	}
}

/*
 * attiva allarme, azzera password, attiva/disattiva led, se il comando è arrivato tramite sms
 * invia sms
 */
void MandJBeep::attiva() {
	this->alarmeAttivo = true;
	this->statoAllarme = true;
	password.reset();

	digitalWrite(RED_LED, HIGH);
	digitalWrite(GREEN_LED, LOW);

	this->standby();
	if (position2 > 0) {
		char txtTemp[13] = "ATTIVO";
		inviaSMScomando(phone_number, txtTemp);
		position2 = 0;
	}
}

/*
 * diattiva allarme, azzera password, attiva/disattiva led, disattiva TImer1PWM, disattiva sirena
 * se il comando è arrivato tramite sms invia sms
 */
void MandJBeep::disattiva() {
	this->statoAllarme = false;
	this->alarmeAttivo = false;

	if (evRitardoAttivazione>0)
	{
		this->t.stop(evRitardoAttivazione);
		this->t.stop(evAfterRitardoTrigger);
	}

	password.reset();
	Timer1.disablePwm(TIMER1_PIN1);

	digitalWrite(RED_LED, LOW);
	digitalWrite(GREEN_LED, HIGH);
	digitalWrite(RELAY_SIRENA1, HIGH);

	lcd.backlight();
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(TXT_SISTEMA_DISATTIVO);

	delay(4000);
	this->standby();
	this->riAttivaSensori();

	if (position > 0) {
		char txtTemp[13] = "DISATTIVO";
		inviaSMScomando(phone_number, txtTemp);
	}
}

/*
 * Intrusione:
 *   - attiva Timer1PWM
 *   - attiva sirena
 *   - invio sms
 *   - salva evento nella EPROM
 *   - dopo tempoSirena secondi disattiva la sirena
 */
void MandJBeep::alarmTriggered() {
	if (allarm.ritardoAttivato)
	{
		allarm.ritardoAttivato=false;
		// TODO stoppare fase attivazione ritardata
		t.stop(evRitardoAttivazione);
	}
	Timer1.initialize(period); // initialize timer1, 1000 microseconds
	setPulseWidth(pulseWidth); // long pulseWidth = 950; // width of a pulse in microseconds

	digitalWrite(RELAY_SIRENA1, LOW);

	password.reset();
	this->statoAllarme = true;

	lcd.clear();
	lcd.setCursor(5, 2);
	lcd.print(TXT_INTRUSIONE);
	lcd.setCursor(0, 3);

	for (uint8_t i = 0; i < numSens; i++) {
		if (sensore[i].getStato() == sensTrigged) {
			lcd.print(sensore[i].getMessaggio());
			allarm.salvaEventoEprom(i);
#ifdef MJGSM
			if (settings.gsm == 1) {
				if (started == true) {
					String msg = "Intrusione: " + sensore[i].getMessaggio();
					msg.toCharArray(sms_text, 160);
					//Serial.println(sms_text);

					if (strcmp(settings.phoneNumber1, "0000000000") != 0)
						inviaSMScomando(settings.phoneNumber1, sms_text);
					if (strcmp(settings.phoneNumber2, "0000000000") != 0)
						inviaSMScomando(settings.phoneNumber2, sms_text);
					if (strcmp(settings.phoneNumber3, "0000000000") != 0)
						inviaSMScomando(settings.phoneNumber3, sms_text);
					if (strcmp(settings.phoneNumber4, "0000000000") != 0)
						inviaSMScomando(settings.phoneNumber4, sms_text);
					if (strcmp(settings.phoneNumber5, "0000000000") != 0)
						inviaSMScomando(settings.phoneNumber5, sms_text);
				}
			}
#endif
		}
	}
	t.after(settings.tempoSirena, doAfterTimerT);
}

void MandJBeep::alarmTriggeredRitardato(uint8_t sensId){
	if (settings.tempoRitardo % 2 == 0) xxxx = 0;
	else xxxx = 1;
	conta=0;

	if (evRitardoAttivazione>0) // controlla se altro evento già avviato
	{
		evRitardoAttivazione=this->t.every(1, doPrintRitAttivazione, settings.tempoRitardo);
		evAfterRitardoTrigger=this->t.after(settings.tempoRitardo, doAfterRitardoTrigged);
	}
}

MandJBeep::MandJBeep() {
	this->alarmeAttivo = false;
	this->statoAllarme = false;
	this->adminZone = false;
	this->ritardoAttivato=false;
}

void MandJBeep::inizializza() {
	//this->saveSettings();
	this->loadSettings();
	password.set(settings.alarmPassword1);

	keypad.begin(makeKeymap(keys));
	keypad.addEventListener(keypadEvent); //add an event listener for this keypad

	this->inizializzaClock();
	this->inizializzaSensori();
	this->inizializzaLed();
}

void MandJBeep::saveSettings(void) {
	byte* p = (byte*) &settings;
	for (int i = 12; i < sizeof(AlarmSettings); i++)
		EEPROM.write(i, p[i]);
}

void MandJBeep::loadSettings(void) {
	byte* p = (byte*) &settings;
	for (int i = 12; i < sizeof(AlarmSettings); i++)
		p[i] = EEPROM.read(i);
}

boolean MandJBeep::checkSensori() {
	for (int i = 0; i < numSens; i++)
		if (sensore[i].getStato() == sensMalfunzionamento)
			sensore[i].setStato(sensAttivo);

	for (int i = 0; i < numSens; i++) {
		if (sensore[i].getStato() != sensDisabilitato
				and sensore[i].getStato() != sensTempDisabilitato) {
			if (sensore[i].getTipo() == tpReed) {
				if (PCF_24.read(sensore[i].getPin())
						== sensore[i].getLogica()) {
					sensore[i].setStato(sensMalfunzionamento);

					lcd.clear();
					lcd.setCursor(0, 2);
					lcd.print(F("Err: "));
					lcd.print(sensore[i].getMessaggio());
#ifdef MJGSM
					if (started == true) {
						if (position > 0) {
							String msg = "Err: " + sensore[i].getMessaggio();
							msg.toCharArray(sms_text, 160);
							//Serial.println(sms_text);
							inviaSMScomando(phone_number, sms_text);
						}
					}
#endif
					password.reset();
					passwd_pos = 9;
					return false;
				}
			}
		}
	}
	password.reset();
	passwd_pos = 9;
	standby();
	return true;
}

void MandJBeep::disattivaSensori() {
	for (int i = 0; i < numSens; i++) {
		if (sensore[i].getStato() == sensMalfunzionamento) {
			sensore[i].setStato(sensTempDisabilitato);
			//PORTB |= _BV(PB0);
			digitalWrite(GIALLO_LED, HIGH);
#ifdef MJGSM
			if (started == true) {
				if (position > 0) {
					String msg = "Sensore disattivato: " + sensore[i].getMessaggio();
					msg.toCharArray(sms_text, 160);
					//Serial.println(sms_text);
					inviaSMScomando(phone_number, sms_text);
				}
			}
#endif
		}
	}
	password.reset();
	passwd_pos = 9;
	standby();
}

void MandJBeep::riAttivaSensori() {
	for (int i = 0; i < numSens; i++) {
		if (sensore[i].getStato() != sensDisabilitato) {
			sensore[i].setStato(sensAttivo);
			sensore[i].setConta(0);
			//PORTB &= ~(_BV(PB0));
			digitalWrite(GIALLO_LED, LOW);
		}
	}
	password.reset();
	passwd_pos = 9;
	standby();
}

void MandJBeep::salvaEventoEprom(int num) {
	EEPROM.write(6, EEPROM.read(0));
	EEPROM.write(7, EEPROM.read(1));
	EEPROM.write(8, EEPROM.read(2));
	EEPROM.write(9, EEPROM.read(3));
	EEPROM.write(10, EEPROM.read(4));
	EEPROM.write(11, EEPROM.read(5));

	EEPROM.write(0, num);

#ifndef CLKDS3231
	EEPROM.write(1, now.day());
	EEPROM.write(2, now.month());
	EEPROM.write(3, now.year()-2000);
	EEPROM.write(4, now.hour());
	EEPROM.write(5, now.minute());
#else
	EEPROM.write(1, now.Day());
	EEPROM.write(2, now.Month());
	EEPROM.write(3, now.Year() - 2000);
	EEPROM.write(4, now.Hour());
	EEPROM.write(5, now.Minute());
#endif
}

String MandJBeep::leggiEventoEprom(byte a) {	// S:num sensore|gg/mm/yy|hh:mm
	if (a == 0)
		return (String) sensore[EEPROM.read(0)].getMessaggio() + F("|")
				+ printDigit(EEPROM.read(1)) + printDigit(EEPROM.read(2))
				+ printDigit(EEPROM.read(3)) + F("|")
				+ printDigit(EEPROM.read(4)) + printDigit(EEPROM.read(5));
	else
		return (String) sensore[EEPROM.read(6)].getMessaggio() + F("|")
				+ printDigit(EEPROM.read(7)) + printDigit(EEPROM.read(8))
				+ printDigit(EEPROM.read(9)) + F("|")
				+ printDigit(EEPROM.read(10)) + printDigit(EEPROM.read(11));
}

void MandJBeep::inizializzaClock() {
	//Adding time
#ifndef CLKDS3231
	RTC.begin();
	//togli il commento per aggiornare l'ora con il pc, upload, poi disattivalo subito dopo
	//RTC.adjust(DateTime(__DATE__, __TIME__));
#else
	RTC.Begin();
	RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
	if (!RTC.IsDateTimeValid())
		RTC.SetDateTime(compiled);
#endif

#ifdef DEBUG
#ifndef CLKDS3231
	if (!RTC.isrunning())
#else
	if (!RTC.GetIsRunning())
#endif
	Serial.println(F("RTC NOT run"));
	else
	Serial.println(F("RTC run"));
#endif

#ifdef CLKDS3231
	now = RTC.GetDateTime();
	if (now < compiled) {
		Serial.println("RTC is older than compile time!  (Updating DateTime)");
		RTC.SetDateTime(compiled);
	} else if (now > compiled) {
		Serial.println("RTC is newer than compile time. (this is expected)");
	} else if (now == compiled) {
		Serial.println(
				"RTC is the same as compile time! (not expected but all is fine)");
	}
	// never assume the Rtc was last configured by you, so
	// just clear them to your needed state
	RTC.Enable32kHzPin(false);
	RTC.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
#endif
}

void MandJBeep::inizializzaLed() {
	pinMode(GREEN_LED, OUTPUT);
	pinMode(RED_LED, OUTPUT);
	pinMode(RELAY_SIRENA1, OUTPUT);
	pinMode(GIALLO_LED, OUTPUT);
	pinMode(TIMER1_PIN1, OUTPUT);
	pinMode(TIMER1_PIN2, OUTPUT);

	digitalWrite(RELAY_SIRENA1, HIGH);
	digitalWrite(RED_LED, LOW);
	digitalWrite(GREEN_LED, HIGH);
}

void MandJBeep::inizializzaSensori() {
	for (int i = 0; i < numSens; i++)
		sensore[i].setStato(
				(bitRead(settings.sens, i) == 0 ? sensDisabilitato : sensAttivo));
}

void MandJBeep::inizializzaGSM() {
#ifdef MJGSM
	if (gsm.begin(2400)) {
		Serial.println("\nGSM status=READY");
		Serial.println(gsm.getStatus());
		started = true;
	} else {
		Serial.println("\nGSM status=IDLE");
		started = false;
		//if (settings.gsm) settings.gsm=0;
	}
	//started = gsm.getStatus();
#else
	//myGSM.begin(2400);
	myGSM.begin(BAUD_RATE);

	if (myGSM) Serial.println("Serila GSM connected");
	else Serial.println("Serila GSM not connected");
#endif
}

void MandJBeep::eseguiSMSComando(char sms_text[]) {
	if (!strcmp(sms_text, "ATTIVA")) {
		if (this->alarmeAttivo == false && this->statoAllarme == false) {
			this->primaDiAttivare();
		}
	} else if (!strcmp(sms_text, "DISATTIVA")) {
		this->disattiva();
	} else if (!strcmp(sms_text, "DISSENTEMP")) {
		this->disattivaSensori();
	} else if (!strcmp(sms_text, "STATUS")) {
		char txtTemp[13] = "";
		if (this->getAllarmStatus() == true)
			strcpy(txtTemp, "ATTIVO");
		else
			strcpy(txtTemp, "NON ATTIVO");
		inviaSMScomando(phone_number, txtTemp);
	}
}

void MandJBeep::checkAttivita() {
	if (this->alarmeAttivo) {
		for (uint8_t i = 0; i < numSens; i++) {
#ifdef DEBUG_SENS
			Serial.print("sens ");
			Serial.print(sensore[i].getMessaggio());
			Serial.print(" - stato");
			Serial.println(sensore[i].getStato());
#endif

			if ((sensore[i].getStato() != sensDisabilitato)	and (sensore[i].getStato() != sensTempDisabilitato))
			{

				
				if ( sensore[i].getRitardato()==true and allarm.ritardoAttivato==true){
					//caso: in fase di attivazione
				/*} else
				/*if (sensore[i].getRitardato()==true and allarm.ritardoAttivato==false) {
					// attivare procedura allarm trigged ritardata
					sensore[i].setStato(sensTrigged);
					this->alarmTriggeredRitardato(i);*/
				}else if (sensore[i].getZona() == settings.zona or settings.zona == znTotale) {
					if (PCF_24.read(sensore[i].getPin()) == sensore[i].getLogica() and sensore[i].getStato() != sensTrigged) {
						sensore[i].setStato(sensTrigged);
						if (sensore[i].getRitardato())
							this->alarmTriggeredRitardato(i); // TODO: forse parametro inutile !!!!
						else this->alarmTriggered();

						if (sensore[i].getTipo() == tpReed) {
							if (sensore[i].getConta() >= settings.maxReed_Conta) {
								sensore[i].setStato(sensTempDisabilitato);
							}
							sensore[i].setConta((sensore[i].getConta() + 1));
						}
					}
#ifdef DEBUG_PIR
					if (sensore[i].getTipo()==tpPIR)
					{
						Serial.print("PIR: ");
						Serial.println( PCF_24.read(sensore[i].getPin()) );
					}
#endif
				}
			}
		}
	} else {
		/*for (uint8_t i = 0; i < numSens; i++) {
			if (sensore[i].getTipo() == tpTamper) {
#ifdef DEBUG_SENS
				Serial.print("sens ");
				Serial.print(sensore[i].getMessaggio());
				Serial.print(" - stato");
				Serial.println(sensore[i].getStato());
#endif
				if ((sensore[i].getStato() != sensDisabilitato)
						and (sensore[i].getStato() != sensTempDisabilitato)) {
					if (PCF_24.read(sensore[i].getPin())
							== sensore[i].getLogica()
							and sensore[i].getStato() != sensTrigged) {
						//sensore[i].setStato(sensTrigged);

						digitalWrite(GIALLO_LED, HIGH);
					}/*else{
					 sensore[i].setStato(sensAttivo);
					 digitalWrite(GIALLO_LED, LOW);

					 }*/
				/*}

			} else if (sensore[i].getTipo() == tpSirena) {

			}

		}*/
	}

}

void MandJBeep::checkSMS() {
#ifdef MJGSM
	if (settings.gsm == 1) {
		//started = gsm.getStatus();
		//if (started==gsm.READY)
		if (started == true) {
			//Serial.println("ddddd");
			position = sms.IsSMSPresent(SMS_UNREAD);
			if (position > 0) {
				// read new SMS
				sms.GetSMS(position, phone_number, sms_text, 160);

				int telAutorizzato = 0;

				/*char xx[20]="+39";
				 strcat(xx, settings.phoneNumber1);
				 if (strcmp(phone_number,settings.phoneNumber1) != 0) telAutorizzato=1;
				 else if (strcmp(phone_number,settings.phoneNumber2) != 0) telAutorizzato=2;
				 else if (strcmp(phone_number,settings.phoneNumber3) != 0) telAutorizzato=3;
				 else if (strcmp(phone_number,settings.phoneNumber4) != 0) telAutorizzato=4;
				 else if (strcmp(phone_number,settings.phoneNumber5) != 0) telAutorizzato=5;*/

				char xx[20] = "+39";
				strcat(xx, settings.phoneNumber1);
				if (strcmp(phone_number, xx) == 0)
					telAutorizzato = 1;

				memtozero_v(xx);
				strcpy(xx, "+39");
				strcat(xx, settings.phoneNumber2);
				if (strcmp(phone_number, xx) == 0)
					telAutorizzato = 2;

				memtozero_v(xx);
				strcpy(xx, "+39");
				strcat(xx, settings.phoneNumber3);
				if (strcmp(phone_number, xx) == 0)
					telAutorizzato = 3;

				memtozero_v(xx);
				strcpy(xx, "+39");
				strcat(xx, settings.phoneNumber4);
				if (strcmp(phone_number, xx) == 0)
					telAutorizzato = 4;

				memtozero_v(xx);
				strcpy(xx, "+39");
				strcat(xx, settings.phoneNumber5);
				if (strcmp(phone_number, xx) == 0)
					telAutorizzato = 5;

#ifdef DEBUG_SMS
				Serial.print("Num tel: ");
				Serial.println(phone_number);
				Serial.print("Text: ");
				Serial.println(sms_text);
				Serial.print("Auth Tel: ");
				Serial.println(xx);
				Serial.print("Auth: ");
				Serial.println(telAutorizzato);
#endif
				if (telAutorizzato > 0) {
					this->eseguiSMSComando(sms_text);
					sms.DeleteSMS(position);
				}
			}
		}
	}
#else
	serialhwread();
	gsmRead();
#endif
}

/************* **************/

unsigned int timeout = 0;
void waitResponse() {
	while (myGSM.available() == 0) {
		if (++timeout > 10000) { // set this to your timeout value in milliseconds
			// your error handling code here
			break;
		}
	}
	timeout = 0; // got a char so reset timeout
	// code hear to read data
}

/*
 #define TIMEOUT 1000

 void modem_command(String command){
 mySerial.println(command);
 Serial.println(command);
 while (mySerial.available() == 0);  // wait for first char

 unsigned long lastRead = millis();   // last time a char was available
 while (millis() - lastRead < TIMEOUT){
 while (mySerial.available()){
 Serial.write(mySerial.read());
 lastRead = millis();   // update the lastRead timestamp
 }
 }
 // No need for extra line feed since most responses contain them anyways
 }*/

