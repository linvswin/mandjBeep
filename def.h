/*
 * def.h
 *
 *  Created on: 23/feb/2016
 *      Author: peppe
 */

#ifndef DEF_H_
#define DEF_H_

//void attiva();
//void codiceErrato(char adm);
//void disattiva();
//bool checkPassword2();
//void checkPassword();
void primaDiAttivare();
void printDate();
//String getDate();
//void alarmTriggered();
void keypadEvent(KeypadEvent eKey);
///void standby();
//void saveSettings(void);
//void loadSettings(void);
void doAfterTimerT();
void doAfterRitActivate();
void printSettings();
//void doEveryPrintDate();
bool setPulseWidth(long microseconds);
void doPrintRitAttivazione();
void timerDoLCDbacklight();
//boolean checkSensori();
//void disattivaSensori();
//void riAttivaSensori();
//void controlloMenu();
//void store_lcdline(int i, char sbuffer[20]) ;
//void salvaEventoEprom(int num);
//String leggiEventoEprom(byte a);

//void check_activity();
//void refresh_lcd();

#ifdef MJGSM
void serialhwread();
void serialswread();
void inviaSMScomando(char *number_str, char *message_str);
#else
void serialhwread();
void gsmRead();
void sendSMS(char *number_str, char *message_str);
void ivioComandoAT(char *cmd);
#endif

#endif /* DEF_H_ */
