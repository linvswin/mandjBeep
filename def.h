/*
 * def.h
 *
 *  Created on: 23/feb/2016
 *      Author: peppe
 */

#ifndef DEF_H_
#define DEF_H_

void attiva();
void codiceErrato(char adm);
void disattiva();
bool checkPassword2();
void checkPassword();
void primaDiAttivare();
void printDate();
String getDate();
void alarmTriggered();
void keypadEvent(KeypadEvent eKey);
void standby();
void saveSettings(void);
void loadSettings(void);
void doAfterTimerT();
void doAfterRitActivate();
void printSettings();
//void doEveryPrintDate();
bool setPulseWidth(long microseconds);
void doPrintRitAttivazione();
void timerDoLCDbacklight();
boolean checkSensori();
void disattivaSensori();
void riAttivaSensori();
void controlloMenu();
void store_lcdline(int i, char sbuffer[20]) ;
void salvaEventoEprom(int num);
String leggiEventoEprom(byte a);

void check_activity();
void refresh_lcd();
//void menu_crea();
//void menu_screen();
//void menu_loadvar();
//void menu_savevar();
//void menuSetup();

#endif /* DEF_H_ */
