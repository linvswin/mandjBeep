/**
 * Project Title: M&J Beep
 * Author: M&J
 * Started Date: 09/02/2016
 * Version: 1.0
 * Licence: GPL ver 3
**/

#ifndef MENU_H_
#define MENU_H_

// lib config
//#define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
#define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar
#define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol

// *********************************************************************
// LCDML TYPE SELECT
// *********************************************************************
// settings for lcd
#define _LCDML_DISP_cols    20
#define _LCDML_DISP_rows     4

uint8_t  scroll_bar[5][8] = {
	{ B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001 }, // scrollbar top
	{ B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001 }, // scroll state 1
	{ B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001 }, // scroll state 2
	{ B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001 }, // scroll state 3
	{ B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111 } // scrollbar bottom
};

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
// create menu
// menu element count - last element id
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt   15 // 26

// LCDML_root        => layer 0
// LCDML_root_X      => layer 1
// LCDML_root_X_X    => layer 2
// LCDML_root_X_X_X  => layer 3
// LCDML_root_... 	 => layer ...

/**
 * LCDMenuLib_add     (id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
 * LCDMenuLib_addMenu (id, group, prev_layer_element, new_element_num, lang_char_array)
 * LCDMenuLib_addParam(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function, parameter [0-255]) // needs LCDML_DISP_initParam
 **/

LCDML_DISP_initParam(_LCDML_DISP_cnt);// enbable parameters (needs one byte per menu element)
// Menu
LCDML_DISP_addMenu          (0 , _LCDML_G1 , LCDML_root     , 1 , TXT_ATTIVA);
	LCDML_DISP_addParam     (1 , _LCDML_G1 , LCDML_root_1   , 1 , TXT_PERIMETRALE ,        mnuTempoSirena, 6);
	LCDML_DISP_addParam     (2 , _LCDML_G1 , LCDML_root_1   , 2 , TXT_TOTALE ,             mnuTempoSirena, 7);
	LCDML_DISP_addParam     (3 , _LCDML_G1 , LCDML_root_1   , 3 , TXT_DISATTIVA_SENSORI ,  mnuTempoSirena, 5);
	//LCDML_DISP_add          (4 , _LCDML_G1 , LCDML_root     , 4 , TXT_SENSORI           ,  mnuSensori);
	//LCDML_DISP_addMenu      (4 , _LCDML_G1 , LCDML_root_1   , 4 , TXT_SENSORI ,            mnuTempoSirena, 5);
LCDML_DISP_addMenu          (4 , _LCDML_G1 , LCDML_root     , 2 , TXT_IMPOSTAZIONE);
	LCDML_DISP_addMenu      (5 , _LCDML_G1 , LCDML_root_2   , 1 , TXT_SICUREZZA);
		LCDML_DISP_addParam (6 , _LCDML_G1 , LCDML_root_2_1 , 1 , TXT_ADMIN_PASSWORD,      mnuPassword, 1);
		LCDML_DISP_addParam (7 , _LCDML_G1 , LCDML_root_2_1 , 2 , TXT_PASSWORD1 ,          mnuPassword, 2);
		LCDML_DISP_addParam (8 , _LCDML_G1 , LCDML_root_2_1 , 3 , TXT_PASSWORD2 ,          mnuPassword, 3);
	LCDML_DISP_addParam     (9 , _LCDML_G1 , LCDML_root_2   , 2 , TXT_TEMPO_SIRENA ,       mnuTempoSirena, 1);
	LCDML_DISP_addParam     (10, _LCDML_G1 , LCDML_root_2   , 6 , TXT_CONTA_REED ,         mnuTempoSirena, 8);
	LCDML_DISP_addParam     (11, _LCDML_G1 , LCDML_root_2   , 3 , TXT_LCDBACK_LIGHT_TIME , mnuTempoSirena, 2);
	LCDML_DISP_addParam     (12, _LCDML_G1 , LCDML_root_2   , 5 , TXT_LOAD_TO_EPROM      , mnuTempoSirena, 3);
	LCDML_DISP_addParam     (13, _LCDML_G1 , LCDML_root_2   , 4 , TXT_SAVE_TO_EPROM      , mnuTempoSirena, 4);
//LCDML_DISP_addMenu          (14, _LCDML_G1 , LCDML_root     , 3 , TXT_REPORT);
	LCDML_DISP_addParam     (14, _LCDML_G1 , LCDML_root     , 4 , TXT_REPORT,              mnuTempoSirena, 9);
LCDML_DISP_add              (15, _LCDML_G1 , LCDML_root     , 5 , TXT_SENSORI           ,  mnuSensori);
//LCDML_DISP_addMenu         (15 , _LCDML_G1 , LCDML_root   , 5 , TXT_SENSORI);
// create Menu
LCDML_DISP_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// LCDML BACKEND (core of the menu, do not change here anything yet)
// *********************************************************************
// define backend function
// *********************************************************************
// LCDML BACKEND (core of the menu, do not change here anything yet)
// *********************************************************************
// define backend function
#define _LCDML_BACK_cnt    1  // last backend function id

LCDML_BACK_init(_LCDML_BACK_cnt);
LCDML_BACK_new_timebased_dynamic (0 , ( 20UL ) , _LCDML_start , LCDML_BACKEND_control);
LCDML_BACK_new_timebased_dynamic (1 , ( 1000UL ) , _LCDML_stop , LCDML_BACKEND_menu);
LCDML_BACK_create();

// *********************************************************************
// SETUP
// *********************************************************************
void MenuSetup() {
	//Serial.println(F(_LCDML_VERSION)); // only for examples
	// LCD Begin
	//lcd.begin(_LCDML_DISP_cols, _LCDML_DISP_rows);
	// set special chars for scrollbar
	lcd.createChar(0, (uint8_t*) scroll_bar[0]);
	lcd.createChar(1, (uint8_t*) scroll_bar[1]);
	lcd.createChar(2, (uint8_t*) scroll_bar[2]);
	lcd.createChar(3, (uint8_t*) scroll_bar[3]);
	lcd.createChar(4, (uint8_t*) scroll_bar[4]);


	/*lcd.createChar(0, (uint8_t*) pgm_read_byte(&scroll_bar [0]));
	lcd.createChar(1, (uint8_t*) pgm_read_byte(&scroll_bar [1]));
	lcd.createChar(2, (uint8_t*) pgm_read_byte(&scroll_bar [2]));
	lcd.createChar(3, (uint8_t*) pgm_read_byte(&scroll_bar [3]));
	lcd.createChar(4, (uint8_t*) pgm_read_byte(&scroll_bar [4]));*/


	// Enable all items with _LCDML_G1
	LCDML_DISP_groupEnable (_LCDML_G1); // enable group 1
	LCDML_DISP_groupEnable (_LCDML_G2); // enable group 21

	// LCDMenu Setup
	LCDML_setup(_LCDML_BACK_cnt);
}

/**********************************************************************
 *  LOOP
**********************************************************************/
void MenuLoop() {
	//if (mostraMenu==true)
	//	LCDML_DISP_jumpToFunc(mnuStandby);
	// this function must called here, do not delete it
	LCDML_run (_LCDML_priority);
}

/*********************************************************************
 * check some errors - do not change here anything
*********************************************************************/
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif

#define _LCDML_CONTROL_cfg    4  // keypad
/*********************************************************************
 * setup
*********************************************************************/
void LCDML_CONTROL_setup() {
//	kpd.begin(makeKeymap(keys));
//	kpd.addEventListener(keypadEvent); //add an event listener for this keypad
}
// *********************************************************************
// loop
void LCDML_CONTROL_loop() {

}

/*********************************************************************
 * CONTROL TASK, DO NOT CHANGE
**********************************************************************/
void LCDML_BACK_setup(LCDML_BACKEND_control){
	// call setup
	LCDML_CONTROL_setup();
}

// backend loop
boolean LCDML_BACK_loop(LCDML_BACKEND_control) {
	// call loop
	LCDML_CONTROL_loop();

	// go to next backend function and do not block it
	return true;
}
// backend stop stable
void LCDML_BACK_stable(LCDML_BACKEND_control) {
}

/* ********************************************************************
 * Output function
**********************************************************************/
void LCDML_lcd_menu_display(){
	// check if menu needs an update
	if (LCDML_DISP_update()) {
		// init vars
		uint8_t n_max = (LCDML.getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.getChilds());
		uint8_t scrollbar_min = 0;
		uint8_t scrollbar_max = LCDML.getChilds();
		uint8_t scrollbar_cur_pos = LCDML.getCursorPosAbs();
		uint8_t scroll_pos = ((1. * n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * scrollbar_cur_pos);

		// update content
		if (LCDML_DISP_update_content()) {
			// clear menu
			LCDML_lcd_menu_clear();

			// display rows
			for (uint8_t n = 0; n < n_max; n++) {
				// set cursor
				lcd.setCursor(1, n);
				// set content
				lcd.print(LCDML.content[n]);
			}
		}

		// update cursor and scrollbar
		if (LCDML_DISP_update_cursor()) {

			// display rows
			for (uint8_t n = 0; n < n_max; n++) {
				//set cursor
				lcd.setCursor(0, n);

				//set cursor char
				if (n == LCDML.getCursorPos()) {
					lcd.write(_LCDML_DISP_cfg_cursor);
				} else {
					lcd.write(' ');
				}

				// delete or reset scrollbar
				if (_LCDML_DISP_cfg_scrollbar == 1) {
					if (scrollbar_max > n_max) {
						lcd.setCursor((_LCDML_DISP_cols - 1), n);
						lcd.write((uint8_t) 0);
					} else {
						lcd.setCursor((_LCDML_DISP_cols - 1), n);
						lcd.print(' ');
					}
				}
			}

			// display scrollbar
			if (_LCDML_DISP_cfg_scrollbar == 1) {
				if (scrollbar_max > n_max) {
					//set scroll position
					if (scrollbar_cur_pos == scrollbar_min) {
						// min pos
						lcd.setCursor((_LCDML_DISP_cols - 1), 0);
						lcd.write((uint8_t) 1);
					} else if (scrollbar_cur_pos == (scrollbar_max - 1)) {
						// max pos
						lcd.setCursor((_LCDML_DISP_cols - 1), (n_max - 1));
						lcd.write((uint8_t) 4);
					} else {
						// between
						lcd.setCursor((_LCDML_DISP_cols - 1),
								scroll_pos / n_max);
						lcd.write((uint8_t) (scroll_pos % n_max) + 1);
					}
				}
			}
		}
	}
	// reinit some vars
	LCDML_DISP_update_end();
}

// lcd clear
void LCDML_lcd_menu_clear() {
	lcd.clear();
	lcd.setCursor(0, 0);
}

/* ===================================================================== *
 *                                                                       *
 * DISPLAY SYSTEM                                                        *
 *                                                                       *
 * ===================================================================== *
 * every "disp menu function" needs three functions
 * - void LCDML_DISP_setup(func_name)
 * - void LCDML_DISP_loop(func_name)
 * - void LCDML_DISP_loop_end(func_name)
 *
 * EXAMPLE CODE:
 void LCDML_DISP_setup(..menu_func_name..)
 {
 // setup
 // is called only if it is started

 // starts a trigger event for the loop function every 100 millisecounds
 LCDML_DISP_triggerMenu(100);
 }

 void LCDML_DISP_loop(..menu_func_name..)
 {
 // loop
 // is called when it is triggert
 // - with LCDML_DISP_triggerMenu( millisecounds )
 // - with every button status change

 // check if any button is presed (enter, up, down, left, right)
 if(LCDML_BUTTON_checkAny()) {
 LCDML_DISP_funcend();
 }
 }

 void LCDML_DISP_loop_end(..menu_func_name..)
 {
 // loop end
 // this functions is ever called when a DISP function is quit
 // you can here reset some global vars or do nothing
 }
 * ===================================================================== **/

int newIntVal=0;
uint8_t param=0;
uint8_t indNewTxtVal=0;
char newTxtVal[PasswordLength_Max];

void mngTempoSirena(uint8_t par){
	lcd.setCursor(0, 0);
	switch(par)
	{
		case 1:
			lcd.print(TXT_TEMPO_SIRENA);
			break;
		case 2:
			lcd.print(TXT_LCDBACK_LIGHT_TIME);
			break;
		case 3:
			lcd.print(TXT_LOAD_TO_EPROM);
			break;
		case 4:
			lcd.print(TXT_SAVE_TO_EPROM);
			break;
		case 5:
			lcd.print(TXT_DISATTIVA_SENSORI);
			break;
		case 6:
			lcd.print(TXT_PERIMETRALE);
			break;
		case 7:
			lcd.print(TXT_TOTALE);
			break;
		case 8:
			lcd.print(TXT_CONTA_REED);
			break;
		case 9:
			lcd.print(TXT_REPORT);
			break;
	}
	lcd.setCursor(0, 1);
	lcd.blink();
	lcd.setCursor(1, 1);
	switch(par){
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		lcd.print(TXT_CONFERMA);
		break;
	case 9:
		lcd.setCursor(0, 1);
		lcd.print(leggiEventoEprom(0));
		lcd.setCursor(0, 2);
		lcd.print(leggiEventoEprom(1));
		lcd.noBlink();
		break;
	default:
		lcd.print(newIntVal);
		break;
	}

	/*if (par >=3 and par <= 7) lcd.print(TXT_CONFERMA);
	else lcd.print(newIntVal);*/
}

void LCDML_DISP_setup(mnuTempoSirena)
// ********************************************************************* */
{
	// setup function
	//LCDML_DISP_triggerMenu(500); // set trigger for this function to 1000 millisecounds
	// print default value

	param = LCDML_DISP_getParameter();
	switch (param) {
	case 1:
		newIntVal = settings.tempoSirena;
		break;
	case 2:
		newIntVal = settings.lcdBacklightTime;
		break;
	case 8:
		newIntVal = settings.maxReed_Conta;
		break;
	}
	mngTempoSirena(param);
}

void LCDML_DISP_loop(mnuTempoSirena) {
	// loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
	// the quit button works in every DISP function without any checks; it starts the loop_end function
	if (LCDML_BUTTON_checkAny()) { // check if any button is presed (enter, up, down, left, right)
		// LCDML_DISP_funcend calls the loop_end function

		if (LCDML_BUTTON_checkUp()) {
			newIntVal++;
			LCDML_BUTTON_resetUp();
		}
		if (LCDML_BUTTON_checkDown()) {
			newIntVal--;
			LCDML_BUTTON_resetDown();
		}
		if (LCDML_BUTTON_checkEnter()) {
			switch (param) {
			case 1:
				settings.tempoSirena = newIntVal;
				break;
			case 2:
				settings.lcdBacklightTime = newIntVal;
				break;
			case 3:
				loadSettings();
#ifdef DEBUG_SETTINGS
				printSettings();
#endif
				break;
			case 4:
				saveSettings();
#ifdef DEBUG_SETTINGS
				printSettings();
#endif
				break;
			case 5:
				disattivaSensori();
				break;
			case 6:
				settings.zona=znPerimetrale;
				break;
			case 7:
				settings.zona=znTotale;
				break;
			case 8:
				settings.maxReed_Conta=newIntVal;
				break;
			case 9:

				break;
			}
			newIntVal = 0;
			LCDML_DISP_funcend();
		}
		lcd.clear();
		mngTempoSirena(param);
	}
}

void LCDML_DISP_loop_end(mnuTempoSirena)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing

    // disable the cursor
  lcd.noBlink();
  param=0;
}

void mngCambiPassword(uint8_t par){
	lcd.setCursor(0, 0);
	switch(par)
	{
		case 1:
			lcd.print(TXT_ADMIN_PASSWORD);
			break;
		case 2:
			lcd.print(TXT_PASSWORD1);
			break;
		case 3:
			lcd.print(TXT_PASSWORD2);
			break;
	}
	lcd.setCursor(0, 1);
	lcd.blink();
	lcd.setCursor(1, 1);
	/*if (par ==3 or par == 4 or par==5)
		lcd.print(TXT_CONFERMA);
	else*/
		lcd.print(newTxtVal);
}
// *********************************************************************
void LCDML_DISP_setup(mnuPassword)
// *********************************************************************
{
	param = LCDML_DISP_getParameter();
	switch (param) {
	case 1:
		lcd.print(TXT_ADMIN_PASSWORD);
		break;
	case 2:
		lcd.print(TXT_PASSWORD1);
		break;
	case 3:
		lcd.print(TXT_PASSWORD2);
		break;
	}
	mngCambiPassword(param);
	//LCDML_DISP_funcend();
}

void LCDML_DISP_loop(mnuPassword) {  // loop
	//if (LCDML_BUTTON_checkAny())
	if (LCDML_BUTTON_checkEnter()) {
		switch (param) {
		case 1:
			strcpy(settings.menuPassword, newTxtVal);
			break;
		case 2:
			strcpy(settings.alarmPassword1, newTxtVal);
			break;
		case 3:
			strcpy(settings.alarmPassword2, newTxtVal);
			break;
		}
		LCDML_DISP_funcend();
	}
	lcd.clear();
	mngCambiPassword(param);
}

void LCDML_DISP_loop_end(mnuPassword) {  // loop end
	lcd.noBlink();
	param=0;
	indNewTxtVal=0;
	memset(newTxtVal,0,sizeof(newTxtVal));
}



// scroll row position
uint8_t scroll_row;
// cursor real position on lcd lines (0 - _LCDML_DISP_rows - 1)
uint8_t cursor_real_pos;
// max filelist count
//uint8_t current_max_list_count;
// cursor position to file list entry
uint8_t cursor_position_cur;

void mngSensori(){
	// loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
	// the quit button works in every DISP function without any checks; it starts the loop_end function

	// init some vars for scrollbar
	uint8_t n_max = (numSens >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (numSens);

	uint8_t scrollbar_min = 0;
	uint8_t scrollbar_max = numSens;
	//uint8_t scrollbar_cur_pos = cursor_position_cur;
	uint8_t scroll_pos = ((1. * n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * cursor_position_cur);

	// display content
	// ==================
	for (uint8_t n = scroll_row; n < (scroll_row + _LCDML_DISP_rows); n++) {
		// set cursor
		lcd.setCursor(1, n - scroll_row);
		// set content
		lcd.setCursor(1, n - scroll_row);
		lcd.print(sensore[n].getMessaggio());
		lcd.setCursor(_LCDML_DISP_cols-3, n - scroll_row);

		switch(sensore[n].getStato())
		{
		case sensDisabilitato:
			lcd.print(F("D"));
			break;
		case sensTempDisabilitato:
			lcd.print(F("T"));
			break;
		case sensAttivo:
			lcd.print(F("A"));
			break;
		}
	}
	// set cursor and scrollbar
	// =============================
	for (uint8_t n = scroll_row; n < (scroll_row + _LCDML_DISP_rows); n++) {
		lcd.setCursor(0, n - scroll_row);

		// set cursor
		// =====================
		if (n == cursor_position_cur) {
			lcd.write(_LCDML_DISP_cfg_cursor);
			cursor_real_pos = n - scroll_row;
		} else {
			lcd.write(' ');
		}

		// display scrollbar
		// ==============================
		// delete or reset scrollbar
		if (scrollbar_max > n_max) {
			lcd.setCursor((_LCDML_DISP_cols - 1), n - scroll_row);
			lcd.write((uint8_t) 0);
		} else {
			lcd.setCursor((_LCDML_DISP_cols - 1), n - scroll_row);
			lcd.print(' ');
		}

		// set scrollbar
		if (scrollbar_max > n_max) {
			//set scroll position
			if (cursor_position_cur == scrollbar_min) {
				// min pos
				lcd.setCursor((_LCDML_DISP_cols - 1), 0);
				lcd.write((uint8_t) 1);
			} else if (cursor_position_cur == (scrollbar_max - 1)) {
				// max pos
				lcd.setCursor((_LCDML_DISP_cols - 1), (n_max - 1));
				lcd.write((uint8_t) 4);
			} else {
				// between
				lcd.setCursor((_LCDML_DISP_cols - 1), scroll_pos / n_max);
				lcd.write((uint8_t) (scroll_pos % n_max) + 1);
			}
		}

	}


}

void LCDML_DISP_setup(mnuSensori) {
	// use this to init some vars
	// set max file counter
	//current_max_list_count = 8;
	// set current cursor position
	cursor_position_cur = 0;
	scroll_row = 0;
	cursor_real_pos = 0;
	mngSensori();
}

void LCDML_DISP_loop(mnuSensori) {

	if (LCDML_BUTTON_checkAny()) {
		// move up in list
		if (LCDML_BUTTON_checkUp()) {
			LCDML_BUTTON_resetAll();
			// scroll up
			if (cursor_position_cur > 0) { // check minimum cursor
				cursor_position_cur--;      // scroll up
				if (cursor_real_pos == 0) {
					scroll_row--;             // scroll display rows
				}
			}
			// update content above or remove this line and copy button checks on top of this function
			LCDML_BACK_start (LCDML_BACKEND_menu);
		}

		// move down in list
		if (LCDML_BUTTON_checkDown()) {
			LCDML_BUTTON_resetAll();
			// scroll down
			if (cursor_position_cur < (numSens - 1)) {    // check list end
				cursor_position_cur++;                         // go to next element
				if (cursor_real_pos == (_LCDML_DISP_rows - 1)) { // check if current cursor is in last display line
					scroll_row++;                                  // scroll content
				}
			}
			// update content above or remove this line and copy button checks on top of this function
			LCDML_BACK_start (LCDML_BACKEND_menu);
		}

		// enter file name
		if (LCDML_BUTTON_checkEnter()) {
			LCDML_BUTTON_resetAll();
			// save selected file (serial.print)
			LCDML_DISP_funcend();
			// output of current line
			Serial.println(sensore[cursor_position_cur].getMessaggio());
		}

		// clear display
		// ================
		lcd.clear();
		mngSensori();
	}
}

void LCDML_DISP_loop_end(mnuSensori) {

}

/*
  // define help function to display the current clock settings
  void digitalClockDisplay(){

    lcd.setCursor(3,0);
    printDigits2(hour1());
    lcd.print(":");
    if(_pos == 1) { lcd.print(" "); }
    printDigits2(minute1());
    lcd.print(":");
    printDigits2(second1());
    lcd.setCursor(3,1);
    lcd.print(day1());
    lcd.print(".");
    if(_pos == 3) { lcd.print(" "); }
    lcd.print(month1());
    lcd.print(".");
    if(_pos == 4) { lcd.print(" "); }
    lcd.print(year1());
    // set cursor
    switch(_pos) {
      case 0: lcd.setCursor(2,0); lcd.blink(); break; //hour
      case 1: lcd.setCursor(6,0); lcd.blink(); break; //min
      case 2: lcd.setCursor(2,1); lcd.blink(); break; //day
      case 3: lcd.setCursor(5+((day1()<10)?0:1),1); lcd.blink(); break;//month
      case 4: lcd.setCursor(7+((day1()<10)?0:1)+((month1()<10)?0:1),1); lcd.blink(); break; //year
      default: lcd.noBlink(); break;
     }
  }
*/


/* ===================================================================== *
 *                                                                       *
 * BACKEND SYSTEM                                                        *
 *                                                                       *
 * ===================================================================== *
 * every "backend function" needs three functions
 * - void LCDML_BACK_setup(..func_name..)
 * - void LCDML_BACK_loop(..func_name..)
 * - void LCDML_BACK_stable(..func_name..)
 *
 * - every BACKEND function can be stopped and started
 * EXAMPLE CODE:
 void LCDML_BACK_setup(LCDML_BACKEND_control)
 {
 // setup
 // is called only if it is started or restartet (reset+start)
 }

 boolean LCDML_BACK_loop(LCDML_BACKEND_control)
 {
 // runs in loop


 return false;
 }

 void LCDML_BACK_stable(LCDML_BACKEND_control)
 {
 // stable stop
 // is called when a backend function is stopped with stopStable
 }
 * ===================================================================== *
 */

#endif /* MENU_H_ */
