/*
 * def.h
 *
 *  Created on: 23/feb/2016
 *      Author: peppe
 */

#ifndef DEF_H_
#define DEF_H_

void printDate();
void keypadEvent(KeypadEvent eKey);

void doAfterTimerT();
void doAfterRitActivate();
void readGSMSlave();
void printSettings();

bool setPulseWidth(long microseconds);
void doPrintRitAttivazione();
void timerDoLCDbacklight();

void serialhwread();
void serialswread();
void inviaSMScomando(/*char *number_str,*/ char *message_str);

#endif /* DEF_H_ */
