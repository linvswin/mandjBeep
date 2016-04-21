/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
 * Note: basato sul progetto Home Security System di Jun Peng - Tech 169
 **/

#include "MandJBeep.h"

String printDigit(int digits)
{
	String temp = "";
	if (digits < 10) temp += "0";
	temp += digits;
	return temp;
}

void setup() {
	Serial.begin(BAUD_RATE);
//	Serial1.begin(2400);
	//salvaEventoEprom(-1);
#ifdef MJGSM
	if (gsm.begin(2400)) {
	        Serial.println("\nGSM status=READY");
	        started = true;
	} else Serial.println("\nGSM status=IDLE");
#endif
	//saveSettings();
	loadSettings();

	//Adding time
	RTC.begin();
	//togli il commento per aggiornare l'ora con il pc, upload, poi disattivalo subito dopo
	//RTC.adjust(DateTime(__DATE__, __TIME__));
#ifdef DEBUG
	if (!RTC.isrunning())
		Serial.println(F("RTC NOT run"));
	else
		Serial.println(F("RTC run"));
#endif
	//Serial.println("GSM Shield testing.");
	//Start configuration of shield with baudrate.
	//For http uses is raccomanded to use 4800 or slower.

	sensore[0].setStato( (bitRead(settings.sens, 0)==0?sensDisabilitato:sensAttivo ) );
	sensore[1].setStato( (bitRead(settings.sens, 1)==0?sensDisabilitato:sensAttivo ) );
	sensore[2].setStato( (bitRead(settings.sens, 2)==0?sensDisabilitato:sensAttivo ) );
	sensore[3].setStato( (bitRead(settings.sens, 3)==0?sensDisabilitato:sensAttivo ) );
	sensore[4].setStato( (bitRead(settings.sens, 4)==0?sensDisabilitato:sensAttivo ) );

	//sensore[4].setStato( (bitRead(settings.sens, 3)==0?sensDisabilitato:sensAttivo ) );
	//sensore[5].setStato( (bitRead(settings.sens, 2)==0?sensDisabilitato:sensAttivo ) );
	//sensore[6].setStato( (bitRead(settings.sens, 1)==0?sensDisabilitato:sensAttivo ) );
	//sensore[7].setStato( (bitRead(settings.sens, 0)==0?sensDisabilitato:sensAttivo ) );

	lcd.begin(20, 4);
	MenuSetup();

#ifdef DEBUG_SETTINGS
	Serial.print(F("Setting sizeof: "));
	Serial.println(sizeof(settings));
#endif
	password.set(settings.alarmPassword1);

	//DDRD=0b11011111;
	//DDRD |= _BV(PD2);
	pinMode(GREEN_LED, OUTPUT);
	//DDRD |= _BV(PD4);
	pinMode(RED_LED, OUTPUT);
	//DDRD |= _BV(PD6);
	pinMode(RELAY_SIRENA1, OUTPUT);
	//DDRD |= _BV(PD7); //pinMode(RELAY_SIRENA2, OUTPUT);

	//DDRB=0b00101110;
	//DDRB |= _BV(PB0);
	pinMode(GIALLO_LED, OUTPUT);
	//DDRB |= _BV(PB1);
	pinMode(TIMER1_PIN1, OUTPUT);
	//DDRB |= _BV(PB2);
	pinMode(TIMER1_PIN2, OUTPUT);
	//DDRB &= ~(_BV(PB2));  //pinMode(PIR1_PIN, INPUT);
	//DDRB &= ~(_BV(PB4));  //pinMode(PIR2_PIN, INPUT);

	//PORTD |= _BV(PD7);     //digitalWrite(RELAY_SIRENA2, HIGH);
	//PORTD |= _BV(PD6);
	digitalWrite(RELAY_SIRENA1, HIGH);
	//PORTD &= ~(_BV(PD6));  //digitalWrite(RELAY_SIRENA1, LOW);
	//PORTD &= ~(_BV(PD4));
	digitalWrite(RED_LED, LOW);
	//PORTD |= _BV(PD2);
	digitalWrite(GREEN_LED, HIGH);

	keypad.begin(makeKeymap(keys));
	keypad.addEventListener(keypadEvent); //add an event listener for this keypad

#ifdef DEBUG_SETTINGS
	printSettings();
#endif

	wdt_enable(WDTO_8S);
	standby();
	t.startTimer();
	timerPrintData=t.every(1, printDate);
	timerLCDbacklight = t.every(settings.lcdBacklightTime, timerDoLCDbacklight);
}

void loop() {
	now = RTC.now();
	keypad.getKey();

	// read from port 1, send to port 0:
	/*if (Serial1.available()) {
		//int inByte = Serial1.read();
		Serial.write(Serial1.read());
	}

	// read from port 0, send to port 1:
	if (Serial.available()) {
		//int inByte = Serial.read();
		Serial1.write(Serial.read());
	}*/
#ifdef MJGSM
	position = sms.IsSMSPresent(SMS_UNREAD);
	if (position) {
	  // read new SMS
	  sms.GetSMS(position, phone_number, sms_text, 160);

	  Serial.print("Num tel: ");
	  Serial.println(phone_number);

	  Serial.print("Text: ");
	  Serial.println(sms_text);

	  if (!strcmp(sms_text, "ATTIVA"))
	  {
		  if (alarmeAttivo == false && statoAllarme == false) {
			  primaDiAttivare();
		  }
	  }else if (!strcmp(sms_text, "DISATTIVA"))
	  {
		  disattiva();
	  }else if (!strcmp(sms_text, "DISSENTEMP"))
	  {
		  disattivaSensori();
	  }
	  sms.DeleteSMS(position);
	} /*else {

	//Read for new byte on serial hardware,
	//and write them on NewSoftSerial.
		serialhwread();
	//Read for new byte on NewSoftSerial.
		serialswread();
	}*/
#endif
	if (alarmeAttivo)
	{
		for(uint8_t i=0; i < numSens; i++){
#ifdef DEBUG_SENS
			Serial.print("sens ");
			Serial.print(sensore[i].getMessaggio());
			Serial.print(" - stato");
			Serial.println(sensore[i].getStato());
#endif

			if ( (sensore[i].getStato() != sensDisabilitato) and (sensore[i].getStato() != sensTempDisabilitato) )
			{
				if ( sensore[i].getZona()==settings.zona or settings.zona==znTotale )
				{
					if (PCF_24.read(sensore[i].getPin())==sensore[i].getLogica() and sensore[i].getStato()!=sensTrigged)
					{
						sensore[i].setStato(sensTrigged);
						alarmTriggered();

						if (sensore[i].getTipo()==tpReed){
							if ( sensore[i].getConta() >= settings.maxReed_Conta){
								sensore[i].setStato(sensTempDisabilitato);
							}
							sensore[i].setConta( (sensore[i].getConta()+1) );
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
	}

	MenuLoop();
	t.update();
	wdt_reset();
}

void standby() {
	//display time and date
	lcd.clear();
	lcd.setCursor(0, 0);
	if (alarmeAttivo) lcd.print(TXT_SYS_ACTIVE);
	else lcd.print(TXT_ENTER_PIN);
//	lcd.setCursor(0, 1);
//	lcd.print(getDate());
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
	txt += printDigit(now.hour()) + F(":");
	txt += printDigit(now.minute()) + F(":");
	txt += printDigit(now.second());
	txt += TXT_SPAZIO;
	txt += printDigit(now.day()) + F("/");
	txt += printDigit(now.month()) + F("/");
	txt += printDigit(now.year());
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
		t.stop(timerLCDbacklight);
		timerLCDbacklight = t.every(settings.lcdBacklightTime, timerDoLCDbacklight);

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
			break;
		case 'A':
			if (statoAllarme==false) {
				primaDiAttivare();
			//	disattivaSensori();
			}
			break;
		case 'B':
			if (mostraMenu==false)
			{
				passwd_pos = 9;

				password.set(settings.menuPassword);
				if (checkPassword2())
				{
					t.stop(timerPrintData);
					mostraMenu=true;
					LCDML.goRoot();
					LCDML_BUTTON_up();
				} else codiceErrato(1);
			} else {
				password.set(settings.alarmPassword1);
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
				//lcd.noBacklight();
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

bool checkPassword2() {
	return password.evaluate();
}

void checkPassword() {           // To check if PIN is corrected, if not, retry!
	if (password.evaluate()) {
		if (alarmeAttivo == false && statoAllarme == false) {
			primaDiAttivare();
		} else if (alarmeAttivo == true || statoAllarme == true)
			disattiva();
	} else
		codiceErrato(0);
}

void codiceErrato(char adm=0)
{
	password.reset();
	lcd.clear();

	if (adm==0)
	{
		lcd.setCursor(3, 0);
		lcd.print(TXT_INVALID_PIN);
	}else{
		password.set(settings.alarmPassword1);
		lcd.setCursor(0, 0);
		lcd.print(TXT_INVALID_ADMIN_PIN);
	}
	lcd.setCursor(5, 2);
	lcd.print(TXT_RIPROVA_PIN);
	delay(1000);
	standby();
}

void primaDiAttivare(){
#ifdef DEBUG
		Serial.println(F("Ritardo attivazione ..........."));
#endif
	lcd.backlight();
	if (checkSensori()) {
		t.after(settings.tempoRitardo, doAfterRitActivate);
		t.every(1, doPrintRitAttivazione, settings.tempoRitardo-1);
		standby();
	}
}

void attiva() // Activate the system if correct PIN entered and display message on the screen
{
	alarmeAttivo = true;
	statoAllarme = true;
	password.reset();

	digitalWrite(RED_LED, HIGH);
	//PORTD |= (1<<5);
	//PORTD |= (1<<PD4);
	//PORTD |= _BV(PD4);

	digitalWrite(GREEN_LED, LOW);
	//PORTD &= ~(1<<2);
	//PORTD &= ~(1<<PD2);
	//PORTD &= ~(_BV(PD2));

	standby();
/*if((digitalRead(reedPin1) == HIGH) && (digitalRead(reedPin2) == HIGH))*/
}

void disattiva() {
	statoAllarme = false;
	alarmeAttivo = false;

	password.reset();
	Timer1.disablePwm(TIMER1_PIN1);

	//PORTD &= ~(_BV(PD4));
	digitalWrite(RED_LED, LOW);
	//PORTD |= _BV(PD2);
	digitalWrite(GREEN_LED, HIGH);
	//PORTD &= ~(_BV(PD6));	//digitalWrite(RELAY_SIRENA1, LOW);
	//PORTD |= _BV(PD6);
	digitalWrite(RELAY_SIRENA1, HIGH);
	//PORTD |= _BV(PD7); 	//digitalWrite(RELAY_SIRENA2, HIGH);

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
	setPulseWidth(pulseWidth); // long pulseWidth = 950; // width of a pulse in microseconds

	//PORTD |= _BV(PD6);      //digitalWrite(RELAY_SIRENA1, HIGH);
	//PORTD &= ~(_BV(PD6));
	digitalWrite(RELAY_SIRENA1, LOW);
	//PORTD &= ~(_BV(PD7));	  //digitalWrite(RELAY_SIRENA2, LOW);

	password.reset();
	statoAllarme = true;

	lcd.clear();
	lcd.setCursor(5, 2);
	lcd.print(TXT_INTRUSIONE);
	lcd.setCursor(0, 3);

	for(uint8_t i=0; i < numSens; i++){
		if ( sensore[i].getStato()==sensTrigged ) {
			lcd.print( sensore[i].getMessaggio() );
			salvaEventoEprom(i);

#ifdef MJGSM
			//if (position>0)
			{
				String msg="Intrusione: "+sensore[i].getMessaggio();
				msg.toCharArray(sms_text, 160);
				//Serial.println(sms_text);
				inviaSMScomando(phone_number, sms_text);
			}
#endif
		}
	}

	//int afterEvent=t.after(settings.tempoSirena * 1000, doAfterTimerT);
	t.after(settings.tempoSirena, doAfterTimerT);
}

void saveSettings(void) {
	byte* p = (byte*) &settings;
	for (int i = 12; i < sizeof(AlarmSettings); i++)
		EEPROM.write(i, p[i]);
}

void loadSettings(void) {
	byte* p = (byte*) &settings;
	for (int i = 12; i < sizeof(AlarmSettings); i++)
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

	//PORTD &= ~(_BV(PD6));  //	digitalWrite(RELAY_SIRENA1, LOW);
	//PORTD |= _BV(PD6);
	digitalWrite(RELAY_SIRENA1, HIGH);
	//PORTD |= _BV(PD7);     //	digitalWrite(RELAY_SIRENA2, HIGH);

	for(int i=0; i < numSens; i++){
		if (sensore[i].getStato()==sensTrigged )
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

void doPrintRitAttivazione() {
	//standby();
	lcd.setCursor(0, 2);
	lcd.print(F("Rit. "));
	lcd.print(++conta);
}

void timerDoLCDbacklight() {
	if (mostraMenu==true){
		mostraMenu==false;
		standby();
	}
	lcd.noBacklight();
}

boolean checkSensori(){
	for(int i=0; i < numSens; i++){
		//if (sensore[i].getStato()==sensAttivo)
		if (sensore[i].getStato()!=sensDisabilitato and sensore[i].getStato()!=sensTempDisabilitato)
		{
			if (sensore[i].getTipo()==tpReed)
			{
				if ( PCF_24.read( sensore[i].getPin())==sensore[i].getLogica() ){
					sensore[i].setStato(sensMalfunzionamento);

					lcd.clear();
					lcd.setCursor(0, 2);
					lcd.print(F("Err: "));
					//lcd.setCursor(5, 2);
					lcd.print( sensore[i].getMessaggio() );
#ifdef MJGSM
					if (position>0)
					{
						String msg="Err: "+sensore[i].getMessaggio();
						msg.toCharArray(sms_text, 160);
						//Serial.println(sms_text);
						inviaSMScomando(phone_number, sms_text);
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

void disattivaSensori(){
	for(int i=0; i < numSens; i++){
		if ( sensore[i].getStato()==sensMalfunzionamento )
		{
			sensore[i].setStato(sensTempDisabilitato);
			//PORTB |= _BV(PB0);
			digitalWrite(GIALLO_LED, HIGH);
		}
	}
	password.reset();
	passwd_pos = 9;
	standby();
}

void riAttivaSensori(){
	for(int i=0; i < numSens; i++){
		if (sensore[i].getStato()!=sensDisabilitato){
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

void salvaEventoEprom(int num)
{
	EEPROM.write(5, EEPROM.read(0));
	EEPROM.write(7, EEPROM.read(1));
	EEPROM.write(8, EEPROM.read(2));
	EEPROM.write(9, EEPROM.read(3));
	EEPROM.write(10, EEPROM.read(4));
	EEPROM.write(11, EEPROM.read(5));

	EEPROM.write(0, num);
	EEPROM.write(1, now.day());
	EEPROM.write(2, now.month());
	EEPROM.write(3, now.year()-2000);
	EEPROM.write(4, now.hour());
	EEPROM.write(5, now.minute());
}

String leggiEventoEprom(byte a)
{	// S:num sensore|gg/mm/yy|hh:mm
	if (a==0)
		return (String)sensore[EEPROM.read(0)].getMessaggio()+
					F("|")+printDigit(EEPROM.read(1))+printDigit(EEPROM.read(2))+printDigit(EEPROM.read(3))+
					F("|")+printDigit(EEPROM.read(4))+printDigit(EEPROM.read(5));
	else
		return (String)sensore[EEPROM.read(6)].getMessaggio()+
							F("|")+printDigit(EEPROM.read(7))+printDigit(EEPROM.read(8))+printDigit(EEPROM.read(9))+
							F("|")+printDigit(EEPROM.read(10))+printDigit(EEPROM.read(11));
}

#ifdef MJGSM
//LEGGE DALLA SERIALE HARDWARE
void serialhwread() {
	i_serialh = 0;
    if (Serial.available() > 0) {
        while (Serial.available() > 0) {
            inSerial[i_serialh] = (Serial.read());
            delay(10);
            i_serialh++;
        }

        inSerial[i_serialh] = '\0';
        if (!strcmp(inSerial, "/END")) {
            Serial.println("_");
            inSerial[0] = 0x1a;
            inSerial[1] = '\0';
            gsm.SimpleWriteln(inSerial);
        }
        //Send a saved AT command using serial port.
        if (!strcmp(inSerial, "TEST")) {
            Serial.println("SIGNAL QUALITY");
            gsm.SimpleWriteln("AT+CSQ");
            gsm.SimpleWriteln("AT+COPS?");
        } else if(!strcmp(inSerial, "SMS")){
            Serial.println("SMS TEST");
            if (sms.SendSMS("3392160999", "Test SMS"))
                Serial.println("\nSMS sent OK");
        } else if(!strcmp(inSerial, "ALL")){
            Serial.println("SMS LEGGI TUTTI");
            gsm.SimpleWriteln("AT+CMGL=\"ALL\",1");
        } else {
            Serial.println(inSerial);
            gsm.SimpleWriteln(inSerial);
        }
        inSerial[0] = '\0';
    }
}

//LEGGE DALLA SERIALE SOFTWARE
void serialswread() {
    gsm.SimpleRead();
}

void inviaSMScomando(char *number_str, char *message_str)
{
	wdt_disable();
	sms.SendSMS(number_str, message_str);
	wdt_enable(WDTO_8S);
}
#endif
