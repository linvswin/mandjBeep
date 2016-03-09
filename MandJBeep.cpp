/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
 * Note: basato sul progetto Home Security System di Jun Peng - Tech 169
 **/

#include "MandJBeep.h"

String printDigits(int digits)
{
	String temp = "";
	if (digits < 10) temp += "0";
	temp += digits;
	return temp;
}

void setup() {
	Serial.begin(BAUD_RATE);

	lcd.begin(20, 4);
	MenuSetup();

	saveSettings();
	loadSettings();
#ifdef DEBUG_SETTINGS
	Serial.print(F("Setting sizeof: "));
	Serial.println(sizeof(settings));
#endif
	password.set(settings.alarmPassword1);

	/*pinMode(PIR0_PIN, INPUT);	*/

	//DDRD=0b11011111;
	DDRD |= _BV(PD2); //pinMode(GREEN_LED, OUTPUT);
	DDRD |= _BV(PD4); //pinMode(RED_LED, OUTPUT);
	DDRD |= _BV(PD6); //pinMode(RELAY_SIRENA1, OUTPUT);
	DDRD |= _BV(PD7); //pinMode(RELAY_SIRENA2, OUTPUT);

	//DDRB=0b00101110;
	DDRB |= _BV(PB1);  //pinMode(TIMER1_PIN1, OUTPUT);
	DDRB |= _BV(PB2);  //pinMode(TIMER1_PIN2, OUTPUT);
	//DDRB &= ~(_BV(PB2));  //pinMode(PIR1_PIN, INPUT);
	//DDRB &= ~(_BV(PB4));  //pinMode(PIR2_PIN, INPUT);

	PORTD |= _BV(PD7);    //digitalWrite(RELAY_SIRENA2, HIGH);
	PORTD &= ~(_BV(PD6)); //digitalWrite(RELAY_SIRENA1, LOW);
	PORTD &= ~(_BV(PD4)); //digitalWrite(RED_LED, LOW);
	PORTD |= _BV(PD2);    //digitalWrite(GREEN_LED, HIGH);

	//Adding time
	RTC.begin();
	//togli il commento per aggiornare l'ora con il pc, upload, poi disattivalo subito dopo
	//RTC.adjust(DateTime(__DATE__, __TIME__));
	if (!RTC.isrunning())
		Serial.println(F("RTC NOT run"));
	else
		Serial.println(F("RTC run"));

	keypad.begin(makeKeymap(keys));
	keypad.addEventListener(keypadEvent); //add an event listener for this keypad

	standby();

#ifdef DEBUG_SETTINGS
	printSettings();
#endif

	wdt_enable(WDTO_8S);
	t.startTimer();
	timerPrintData=t.every(1, printDate);
	//timerLCDbacklight = t.every(settings.lcdBacklightTime, timerDoLCDbacklight);
}

void loop() {
	now = RTC.now();
	keypad.getKey();

	if (alarmeAttivo) {
		for(int i=0; i < numSens; i++){

#ifdef DEBUG_SENS
			Serial.print("sens ");
			Serial.print(sensore[i].getMessaggio());
			Serial.print(" - stato");
			Serial.println(sensore[i].getStato());
#endif

			if (sensore[i].getStato() != sensDisabilitato or sensore[i].getStato() != sensTempDisabilitato){
				//if ( sensore[i].getZona() == settings.zona )
				{
					if (PCF_24.read(sensore[i].getPin())==sensore[i].getLogica() and sensore[i].getStato()==sensAttivo ) {

						if (sensore[i].getTipo()==intReed){
							int f=sensore[i].getConta()+1;
#ifdef DEBUG_SENS2
							Serial.print("conta reed: ");
							Serial.print(f);
							Serial.print(" - max conta reed: ");
							Serial.print(settings.maxReed_Conta);
							Serial.print(" - stato: ");
							Serial.println(sensore[i].getStato());
#endif
							sensore[i].setConta( (sensore[i].getConta()+1) );

							if (sensore[i].getConta() >= settings.maxReed_Conta){
								sensore[i].setStato(sensTempDisabilitato);
							}
						}

#ifdef DEBUG_PIR
						if (sensore[i].getTipo()==tpPIR)
						{
							Serial.print("PIR: ");
							Serial.println( PCF_24.read(sensore[i].getPin()) );
						}
#endif

						sensore[i].setStato(sensTrigged);
						alarmTriggered();
					}
				}
			}
		}
	}

	//if (mostraMenu==true)
		MenuLoop();
	t.update();
	wdt_reset();
}

void standby() {
	//display time and date
	lcd.backlight();
	lcd.clear();
	lcd.setCursor(0, 0);
	if (alarmeAttivo) lcd.print(TXT_SYS_ACTIVE);
	else lcd.print(TXT_ENTER_PIN);
	lcd.setCursor(0, 1);
	lcd.print(getDate());
	lcd.setCursor(5, 3);
	lcd.print(TXT_AUTOR);
}

void printDate() {
	//TIME and DATE
	lcd.setCursor(0, 1);
	lcd.print(getDate());
}

String getDate() {
	String txt = F("");
	txt += printDigits(now.hour()) + F(":");
	txt += printDigits(now.minute()) + F(":");
	txt += printDigits(now.second());
	txt += " " + printDigits(now.day()) + F("/");
	txt += printDigits(now.month()) + F("/");
	txt += printDigits(now.year());
#ifdef  DEBUG
#ifdef DEBUG_PRINTDATA
	Serial.print(F("date: "));
	Serial.println(txt);
#endif
#endif
	return txt;
}

void keypadEvent(KeypadEvent eKey) {

#ifdef DEBUG
#ifdef DEBUG_KEY
	Serial.print(F("Tasto: "));
	Serial.println(eKey);
#endif
#endif

	switch (keypad.getState()) {
	case PRESSED:
		if (passwd_pos - 9 >= 10) {
			//return;
			passwd_pos = 9;
		}
		lcd.backlight();

		switch (eKey) {
		case '#':
			if (mostraMenu==false) {//# is to validate password
				passwd_pos = 9;
				checkPassword();
			} else {
				LCDML_BUTTON_enter();
			}
			break;
		case '*':                 //* is to reset password attempt
			if (mostraMenu==false) {
				password.reset();
				passwd_pos = 9;
				mostraMenu=false;
				standby();
			}else {
				LCDML_BUTTON_quit();
			}
			//displayCodeEntryScreen();
			// TODO: clear the screen output
			break;
		case 'A':
			if (statoAllarme==false) {
				disattivaSensori();
			}
			break;
		case 'B':
			if (mostraMenu==false)
			{
				t.stop(timerPrintData);
				mostraMenu=true;
				LCDML.goRoot();
				LCDML_BUTTON_up();
			} else {
				mostraMenu=false;
				timerPrintData=t.every(1, printDate);
				standby();
			}
			break;
		case 'C':
			if (mostraMenu==false){
				lcd.backlight();
			} else {
				LCDML_BUTTON_up();
			}
			break;
		case 'D':
			if (mostraMenu==false){
				lcd.noBacklight();
			} else {
				LCDML_BUTTON_down();
			}
			break;
		default:
			if (mostraMenu==false){
				password.append(eKey);
				lcd.setCursor((passwd_pos++), 0);
				lcd.print(F("*"));
			} else {
				if (indNewTxtVal<PasswordLength_Max-1)
				{
					newTxtVal[indNewTxtVal]=eKey;
					indNewTxtVal++;
				}
			}
			break;
		}
	}
}

void checkPassword() {           // To check if PIN is corrected, if not, retry!
	if (password.evaluate()) {
		if (alarmeAttivo == false && statoAllarme == false) {
#ifdef DEBUG
			Serial.println(F("Ritardo attivazione ..........."));
#endif
			if (checkSensori()) {
				t.after(settings.tempoSirena, doAfterRitActivate);
				t.every(1, doPrintRitAttivazione, settings.tempoSirena);
				standby();
			}

		} else if (alarmeAttivo == true || statoAllarme == true)
			disattiva();
	} else
		codiceErrato();
}

void codiceErrato()
{
	password.reset();
	lcd.backlight();
	lcd.clear();
	lcd.setCursor(3, 0);
	lcd.print(TXT_INVALID_PIN);
	lcd.setCursor(5, 2);
	lcd.print(TXT_RIPROVA_PIN);
	delay(1000);
	standby();
}

void attiva() // Activate the system if correct PIN entered and display message on the screen
{
	alarmeAttivo = true;
	statoAllarme = true;
	password.reset();

	//digitalWrite(RED_LED, HIGH);
	//PORTD |= (1<<5);
	PORTD |= (1<<PD4);
	PORTD |= _BV(PD4);

	//digitalWrite(GREEN_LED, LOW);
	//PORTD &= ~(1<<2);
	PORTD &= ~(1<<PD2);
	PORTD &= ~(_BV(PD2));


	standby();
/*if((digitalRead(reedPin1) == HIGH) && (digitalRead(reedPin2) == HIGH))*/
}

void disattiva() {
	statoAllarme = false;
	alarmeAttivo = false;

	password.reset();
	Timer1.disablePwm(TIMER1_PIN1);

	PORTD &= ~(_BV(PD4));	//digitalWrite(RED_LED, LOW);
	PORTD |= _BV(PD2);	//digitalWrite(GREEN_LED, HIGH);
	PORTD &= ~(_BV(PD6));	//digitalWrite(RELAY_SIRENA1, LOW);
	PORTD |= _BV(PD7); 	//digitalWrite(RELAY_SIRENA2, HIGH);

	lcd.backlight();
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(TXT_SISTEMA_DISATTIVO);

//	for(int i=0; i < numSens; i++)
//		sensore[i].setStato(sensNonAttivo);

	delay(5000);
	standby();

	riAttivaSensori();
}

void alarmTriggered() {
	Timer1.initialize(period); // initialize timer1, 1000 microseconds
	setPulseWidth(pulseWidth);

	PORTD |= _BV(PD6);      //digitalWrite(RELAY_SIRENA1, HIGH);
	PORTD &= ~(_BV(PD7));	//digitalWrite(RELAY_SIRENA2, LOW);

	password.reset();
	statoAllarme = true;

	lcd.clear();
	lcd.setCursor(5, 2);
	lcd.print(TXT_INTRUSIONE);
	lcd.setCursor(0, 3);

	for(int i=0; i < numSens; i++){
		if ( sensore[i].getStato()==sensTrigged ) {
			lcd.print( sensore[i].getMessaggio() );
		}
	}

	//int afterEvent=t.after(settings.tempoSirena * 1000, doAfterTimerT);
	t.after(settings.tempoSirena, doAfterTimerT);
}

void saveSettings(void) {
	byte* p = (byte*) &settings;
	for (int i = 0; i < sizeof(AlarmSettings); i++)
		EEPROM.write(i, p[i]);
}

void loadSettings(void) {
	byte* p = (byte*) &settings;
	for (int i = 0; i < sizeof(AlarmSettings); i++)
		p[i] = EEPROM.read(i);
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
	Serial.print(F("AdminPassword: "));
	Serial.println(settings.menuPassword);
	Serial.print(F("Password1: "));
	Serial.println(settings.alarmPassword1);
	Serial.print(F("Password2: "));
	Serial.println(settings.alarmPassword2);
}
#endif

void doAfterRitActivate() {
#ifdef DEBUG
	Serial.println(F("Attivo Allarme"));
#endif
	conta = 0;
	attiva();
	mostraMenu=false;
	standby();
}

void doAfterTimerT() {
	Timer1.disablePwm(TIMER1_PIN1);

//	digitalWrite(RELAY_SIRENA1, LOW);
//	digitalWrite(RELAY_SIRENA2, HIGH);
	PORTD &= ~(_BV(PD6));
	PORTD |= _BV(PD7);

	for(int i=0; i < numSens; i++){
		if (sensore[i].getStato()==sensTrigged )
			sensore[i].setStato(sensAttivo);
	}
}

bool setPulseWidth(long microseconds) {
	bool ret = false;
	int prescaleValue = prescale[Timer1.clockSelectBits];

	// calculate time per counter tick in nanoseconds
	long precision = (F_CPU / 128000) * prescaleValue;
	period = precision * ICR1 / 1000; // period in microseconds
	if (microseconds < period) {
		int duty = map(microseconds, 0, period, 0, 1024);
		if (duty < 1)
			duty = 1;
		if (microseconds > 0 && duty < TIMER1_RESOLUTION) {
			Timer1.pwm(outPin, duty);
			ret = true;
		}
	}
	return ret;
}

void doPrintRitAttivazione() {
	//standby();
	lcd.setCursor(0, 2);
	lcd.print(F("Rit. "));
	lcd.print(++conta);
}

void timerDoLCDbacklight() { lcd.noBacklight(); }

boolean checkSensori(){
	for(int i=0; i < numSens; i++){
		if (sensore[i].getStato()==sensAttivo)
		{
			if ( PCF_24.read( sensore[i].getPin())==sensore[i].getLogica() ){
				//sensore[i].setMalfunzionamento(true);
				sensore[i].setStato(sensMalfunzionamento);

				lcd.clear();
				lcd.setCursor(0, 2);
				lcd.print(F("Err: "));
				lcd.print( sensore[i].getMessaggio() );
				return false;
			}
		}
	}
	password.reset();
	passwd_pos = 9;
	standby();
	return true;
}

void disattivaSensori(){
	for(int i=0; i < numSens; i++){
		if ( sensore[i].getStato()==sensMalfunzionamento )
			sensore[i].setStato(sensTempDisabilitato);
	}
	password.reset();
	passwd_pos = 9;
	standby();
}

void riAttivaSensori(){
	for(int i=0; i < numSens; i++){
		if (sensore[i].getStato()==sensTempDisabilitato){
			sensore[i].setStato(sensAttivo);
			//sensore[i].setMalfunzionamento(true);
		}
	}
	password.reset();
	passwd_pos = 9;
	standby();
}
