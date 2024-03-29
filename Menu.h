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
#define _LCDML_DISP_cnt   30

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
LCDML_DISP_addMenu        (0 , _LCDML_G1 , LCDML_root      , 1 , TXT_ATTIVA);
	LCDML_DISP_add          (1 , _LCDML_G1 , LCDML_root_1    , 1 , TXT_ATTIVA             , mnuTipoAttivazione);
	LCDML_DISP_addParam     (2 , _LCDML_G1 , LCDML_root_1    , 2 , TXT_DISATTIVA_SENSORI  , mnuTempoSirena, 5);
LCDML_DISP_addMenu        (3 , _LCDML_G1 , LCDML_root      , 2 , TXT_IMPOSTAZIONE);
  LCDML_DISP_addMenu      (4 , _LCDML_G1 , LCDML_root_2    , 10, TXT_DATA_ORA);
    LCDML_DISP_addParam   (5 , _LCDML_G1 , LCDML_root_2_10 , 1 , TXT_DATA               , mnuCambioDataOra, 1);
    LCDML_DISP_addParam   (6 , _LCDML_G1 , LCDML_root_2_10 , 2 , TXT_ORA                , mnuCambioDataOra, 2);
	LCDML_DISP_addMenu      (7 , _LCDML_G1 , LCDML_root_2    , 1 , TXT_SICUREZZA);
		LCDML_DISP_addParam   (8 , _LCDML_G1 , LCDML_root_2_1  , 1 , TXT_ADMIN_PASSWORD     , mnuPassword, 1);
		LCDML_DISP_addParam   (9 , _LCDML_G1 , LCDML_root_2_1  , 2 , TXT_PASSWORD1          , mnuPassword, 2);
		LCDML_DISP_addParam   (10 , _LCDML_G1 , LCDML_root_2_1  , 3 , TXT_PASSWORD2          , mnuPassword, 3);
	LCDML_DISP_addParam     (11 , _LCDML_G1 , LCDML_root_2    , 2 , TXT_TEMPO_SIRENA       , mnuTempoSirena, 1);
	LCDML_DISP_addParam     (12, _LCDML_G1 , LCDML_root_2    , 7 , TXT_TEMPO_RITARDO      , mnuTempoSirena, 10);
LCDML_DISP_addMenu        (13, _LCDML_G1 , LCDML_root      , 3 , TXT_GSM);
	LCDML_DISP_addParam     (14, _LCDML_G1 , LCDML_root_3    , 1 , TXT_ATTIVA_GSM         , mnuTempoSirena, 11);
	LCDML_DISP_addMenu      (15, _LCDML_G1 , LCDML_root_3    , 2 , TXT_NUMERI_GSM);
	     LCDML_DISP_addParam(16 , _LCDML_G1 , LCDML_root_3_2 , 1 , TXT_NUMERI1_GSM     , mnuGsmNumeri, 1);
	     LCDML_DISP_addParam(17 , _LCDML_G1 , LCDML_root_3_2 , 2 , TXT_NUMERI2_GSM     , mnuGsmNumeri, 2);
	     LCDML_DISP_addParam(18 , _LCDML_G1 , LCDML_root_3_2 , 3 , TXT_NUMERI3_GSM     , mnuGsmNumeri, 3);
	     LCDML_DISP_addParam(19 , _LCDML_G1 , LCDML_root_3_2 , 4 , TXT_NUMERI4_GSM     , mnuGsmNumeri, 4);
	     LCDML_DISP_addParam(20 , _LCDML_G1 , LCDML_root_3_2 , 5 , TXT_NUMERI5_GSM     , mnuGsmNumeri, 5);
	LCDML_DISP_addParam     (21, _LCDML_G1 , LCDML_root_3    , 3 , TXT_SYNC_GSM        , mnuTempoSirena, 13);
	LCDML_DISP_addParam     (22, _LCDML_G1 , LCDML_root_3    , 4 , TXT_STATE_GSM       , mnuTempoSirena, 14);
	LCDML_DISP_addParam     (23, _LCDML_G1 , LCDML_root_3    , 5 , TXT_RIAVVIA_GSM     , mnuTempoSirena, 15);
	LCDML_DISP_addParam     (24, _LCDML_G1 , LCDML_root_2    , 6 , TXT_CONTA_REED         , mnuTempoSirena, 8);
	LCDML_DISP_addParam     (25, _LCDML_G1 , LCDML_root_2    , 9 , TXT_TEMPERATURA        , mnuTempoSirena, 12);
	LCDML_DISP_addParam     (26, _LCDML_G1 , LCDML_root_2    , 4 , TXT_LCDBACK_LIGHT_TIME , mnuTempoSirena, 2);
	//LCDML_DISP_addParam     (24, _LCDML_G1 , LCDML_root_2    , 5 , TXT_LOAD_TO_EPROM      , mnuTempoSirena, 3);
	//LCDML_DISP_addParam     (25, _LCDML_G1 , LCDML_root_2    , 8 , TXT_SAVE_TO_EPROM      , mnuTempoSirena, 4);
 	LCDML_DISP_addParam     (27, _LCDML_G1 , LCDML_root      , 5 , TXT_REPORT             , mnuTempoSirena, 9);
LCDML_DISP_add            (28, _LCDML_G1 , LCDML_root      , 6 , TXT_SENSORI            , mnuSensori);
LCDML_DISP_addParam       (29, _LCDML_G1 , LCDML_root      , 7 , TXT_LOAD_TO_EPROM      , mnuTempoSirena, 3);
LCDML_DISP_addParam       (30, _LCDML_G1 , LCDML_root      , 8 , TXT_SAVE_TO_EPROM      , mnuTempoSirena, 4);
LCDML_DISP_addParam       (31, _LCDML_G2 , LCDML_root      , 9 , TXT_RIAVVIA_GSM        , mnuTempoSirena, 16);
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
	allarm.lcd.createChar(0, (uint8_t*) scroll_bar[0]);
	allarm.lcd.createChar(1, (uint8_t*) scroll_bar[1]);
	allarm.lcd.createChar(2, (uint8_t*) scroll_bar[2]);
	allarm.lcd.createChar(3, (uint8_t*) scroll_bar[3]);
	allarm.lcd.createChar(4, (uint8_t*) scroll_bar[4]);


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
	if (allarm.alarmeAttivo)
		LCDML_DISP_groupDisable(_LCDML_G2);
	else
		LCDML_DISP_groupEnable(_LCDML_G2);
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
				// set content
				allarm.lcd.mjPrint(1,n,LCDML.content[n]);
			}
		}

		// update cursor and scrollbar
		if (LCDML_DISP_update_cursor()) {

			// display rows
			for (uint8_t n = 0; n < n_max; n++) {
				//set cursor
				allarm.lcd.mjPrint(0, n,"");

				//set cursor char
				if (n == LCDML.getCursorPos()) {
					allarm.lcd.write(_LCDML_DISP_cfg_cursor);
				} else {
					allarm.lcd.write(' ');
				}

				// delete or reset scrollbar
				if (_LCDML_DISP_cfg_scrollbar == 1) {
					if (scrollbar_max > n_max) {
						allarm.lcd.mjPrint((_LCDML_DISP_cols - 1), n, "");
						allarm.lcd.write((uint8_t) 0);
					} else {
						allarm.lcd.mjPrint((_LCDML_DISP_cols - 1), n, " ");
					}
				}
			}

			// display scrollbar
			if (_LCDML_DISP_cfg_scrollbar == 1) {
				if (scrollbar_max > n_max) {
					//set scroll position
					if (scrollbar_cur_pos == scrollbar_min) {
						// min pos
						allarm.lcd.mjPrint((_LCDML_DISP_cols - 1), 0, "");
						allarm.lcd.write((uint8_t) 1);
					} else if (scrollbar_cur_pos == (scrollbar_max - 1)) {
						// max pos
						allarm.lcd.mjPrint((_LCDML_DISP_cols - 1), (n_max - 1), "");
						allarm.lcd.write((uint8_t) 4);
					} else {
						// between
						allarm.lcd.mjPrint((_LCDML_DISP_cols - 1), scroll_pos / n_max, "");
						allarm.lcd.write((uint8_t) (scroll_pos % n_max) + 1);
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
	allarm.lcd.clear();
	allarm.lcd.mjPrint(0, 0, "");
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

uint8_t indNewTxtVal2=0;
char newTxtVal2[20];

char newTxtVal3[11];

int mnuNewTxtVal=0;

void mngTempoSirena(uint8_t par){
	allarm.lcd.mjPrint(0, 0, "");
	switch(par)
	{
		case 1:
			allarm.lcd.mjPrint(TXT_TEMPO_SIRENA);
			break;
		case 2:
			allarm.lcd.mjPrint(TXT_LCDBACK_LIGHT_TIME);
			break;
		case 3:
			allarm.lcd.mjPrint(TXT_LOAD_TO_EPROM);
			break;
		case 4:
			allarm.lcd.mjPrint(TXT_SAVE_TO_EPROM);
			break;
		case 5:
			allarm.lcd.mjPrint(TXT_DISATTIVA_SENSORI);
			break;
		case 8:
			allarm.lcd.mjPrint(TXT_CONTA_REED);
			break;
		case 9:
			allarm.lcd.mjPrint(TXT_REPORT);
			break;
		case 10:
			allarm.lcd.mjPrint(TXT_TEMPO_RITARDO);
			break;
		case 11:
			if (settings.gsm) allarm.lcd.mjPrint(TXT_DISATTIVA_GSM);
			else allarm.lcd.mjPrint(TXT_ATTIVA_GSM);
			break;
		case 12:
			allarm.lcd.mjPrint(TXT_TEMPERATURA);
			break;
		case 13:
			allarm.lcd.mjPrint(TXT_SYNC_GSM);
			break;
		case 14:
			allarm.lcd.mjPrint(TXT_STATE_GSM);
			//allarm.sendI2CCmd("1|Status~", GSMI2C);
			break;
		case 15:
			allarm.lcd.mjPrint(TXT_RIAVVIA_GSM);
			//allarm.sendI2CCmd("1|Status~", GSMI2C);
			break;
		case 16: // riavvia sistema allarme
			allarm.lcd.mjPrint(TXT_RIAVVIA_GSM);
			break;
	}
	allarm.lcd.mjPrint(0, 1,"");
	allarm.lcd.mjBlink(true);
	allarm.lcd.mjPrint(1, 1,"");
	switch(par){
	case 3:
	case 4:
	case 5:
	case 11:
	case 13:
	case 15:
	case 16:
		allarm.lcd.mjPrint(TXT_CONFERMA);
		break;
	case 9:
		allarm.lcd.mjPrint(0,1,allarm.leggiEventoEprom(0));
		allarm.lcd.mjPrint(0,2,allarm.leggiEventoEprom(1));
		allarm.lcd.mjBlink(false);
		break;
	case 12:
		allarm.lcd.print(allarm.clock.RTC.GetTemperature().AsFloat());
		break;
	case 14:
		if (statoGSM==1)
			allarm.lcd.println(TXT_GSM_READY);
		else if (statoGSM==2)
			allarm.lcd.println(TXT_GSM_NOT_READY);
		//Serial.print("statoGSM: ");
		//Serial.println(statoGSM);
		break;
	default:
		allarm.lcd.print(newIntVal);
//		lcd.print(newTxtVal);
		break;
	}

	/*if (par >=3 and par <= 7) lcd.print(TXT_CONFERMA);
	else lcd.print(newIntVal);*/
}

void LCDML_DISP_setup(mnuTempoSirena)
// ********************************************************************* */
{
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
	case 10:
		newIntVal = settings.tempoRitardo;
		break;
	case 14:
		//lcd.print(TXT_STATE_GSM);
		allarm.sendI2CCmd("1|Status~", GSMI2C);
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
			String s="";
			switch (param) {
			case 1:
				settings.tempoSirena = newIntVal;
				break;
			case 2:
				settings.lcdBacklightTime = newIntVal;
				break;
			case 3:
				allarm.loadSettings();
#ifdef DEBUG_SETTINGS
				printSettings();
#endif
				break;
			case 4:
				allarm.saveSettings();
#ifdef DEBUG_SETTINGS
				printSettings();
#endif
				break;
			case 5:
				allarm.disattivaSensori();
				break;
			case 8:
				settings.maxReed_Conta=newIntVal;
				break;
			case 9:
				break;
			case 10:
				settings.tempoRitardo=newIntVal;
				break;
			case 11:
				settings.gsm=(!settings.gsm);
				break;
			case 12:
				//settings.tempoRitardo=newIntVal;
				break;
			case 13:
				s="4|"+String(settings.gsm)+","+String(settings.phoneNumber1)+","+String(settings.phoneNumber2)+","+String(settings.phoneNumber3)+","+String(settings.phoneNumber4)+","+String(settings.phoneNumber5)+"~";
				allarm.sendI2CCmd(s, GSMI2C);
				break;
			case 15:
				s="9|riavvia~";
				allarm.sendI2CCmd(s, GSMI2C);
				break;
			case 16:
				Reset_AVR();
				break;
			}
			newIntVal = 0;
			LCDML_DISP_funcend();
		}
		allarm.lcd.clear();
		mngTempoSirena(param);
	}
}

void LCDML_DISP_loop_end(mnuTempoSirena)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing

    // disable the cursor
  allarm.lcd.mjBlink(false);
  param=0;
  //indNewTxtVal=0;
  //memset(newTxtVal,0,sizeof(newTxtVal));
}

void mngCambiPassword(uint8_t par){
	allarm.lcd.setCursor(0, 0);
	switch(par)
	{
		case 1:
			allarm.lcd.print(TXT_ADMIN_PASSWORD);
			break;
		case 2:
			allarm.lcd.print(TXT_PASSWORD1);
			break;
		case 3:
			allarm.lcd.print(TXT_PASSWORD2);
			break;
	}
	allarm.lcd.setCursor(0, 1);
	allarm.lcd.blink();
	allarm.lcd.setCursor(1, 1);
	/*if (par ==3 or par == 4 or par==5)
		lcd.print(TXT_CONFERMA);
	else*/
		allarm.lcd.print(newTxtVal);
}
// *********************************************************************
void LCDML_DISP_setup(mnuPassword)
// *********************************************************************
{
	param = LCDML_DISP_getParameter();
	switch (param) {
	case 1:
		allarm.lcd.print(TXT_ADMIN_PASSWORD);
		break;
	case 2:
		allarm.lcd.print(TXT_PASSWORD1);
		break;
	case 3:
		allarm.lcd.print(TXT_PASSWORD2);
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
	allarm.lcd.clear();
	mngCambiPassword(param);
}

void LCDML_DISP_loop_end(mnuPassword) {  // loop end
	allarm.lcd.noBlink();
	param=0;
	indNewTxtVal=0;
	memset(newTxtVal,0,sizeof(newTxtVal));
}

void mngGsmNumeri(uint8_t par){
	allarm.lcd.setCursor(0, 0);
	switch(par)
	{
		case 1:
			allarm.lcd.print(TXT_NUMERI1_GSM);
			allarm.lcd.setCursor(1, 1);
			allarm.lcd.print(settings.phoneNumber1);
			break;
		case 2:
			allarm.lcd.print(TXT_NUMERI2_GSM);
			allarm.lcd.setCursor(1, 1);
			allarm.lcd.print(settings.phoneNumber2);
			break;
		case 3:
			allarm.lcd.print(TXT_NUMERI3_GSM);
			allarm.lcd.setCursor(1, 1);
			allarm.lcd.print(settings.phoneNumber3);
			break;
		case 4:
			allarm.lcd.print(TXT_NUMERI4_GSM);
			allarm.lcd.setCursor(1, 1);
			allarm.lcd.print(settings.phoneNumber4);
			break;
		case 5:
			allarm.lcd.print(TXT_NUMERI5_GSM);
			allarm.lcd.setCursor(1, 1);
			allarm.lcd.print(settings.phoneNumber5);
			break;
	}
	//lcd.setCursor(0, 1);
	allarm.lcd.blink();
	allarm.lcd.setCursor(1, 2);
	/*if (par ==3 or par == 4 or par==5)
		lcd.print(TXT_CONFERMA);
	else*/
		allarm.lcd.print(newTxtVal2);
}
// *********************************************************************
void LCDML_DISP_setup(mnuGsmNumeri)
// *********************************************************************
{
	mnuNewTxtVal=1;
	param = LCDML_DISP_getParameter();
	switch (param) {
	case 1:
		allarm.lcd.print(TXT_NUMERI1_GSM);
		break;
	case 2:
		allarm.lcd.print(TXT_NUMERI2_GSM);
		break;
	case 3:
		allarm.lcd.print(TXT_NUMERI3_GSM);
		break;
	case 4:
		allarm.lcd.print(TXT_NUMERI5_GSM);
		break;
	case 5:
		allarm.lcd.print(TXT_NUMERI5_GSM);
		break;
	}
	mngGsmNumeri(param);
	//LCDML_DISP_funcend();
}

void LCDML_DISP_loop(mnuGsmNumeri) {  // loop
	//if (LCDML_BUTTON_checkAny())
	if (LCDML_BUTTON_checkEnter()) {
		switch (param) {
		case 1:
			strcpy(settings.phoneNumber1, newTxtVal2);
			break;
		case 2:
			strcpy(settings.phoneNumber2, newTxtVal2);
			break;
		case 3:
			strcpy(settings.phoneNumber3, newTxtVal2);
			break;
		case 4:
			strcpy(settings.phoneNumber4, newTxtVal2);
			break;
		case 5:
			strcpy(settings.phoneNumber5, newTxtVal2);
			break;
		}
		LCDML_DISP_funcend();
	}
	allarm.lcd.clear();
	mngGsmNumeri(param);
}

void LCDML_DISP_loop_end(mnuGsmNumeri) {  // loop end
	allarm.lcd.noBlink();
	param=0;
	indNewTxtVal2=0;
	mnuNewTxtVal=0;
	memset(newTxtVal2,0,sizeof(newTxtVal2));
}

uint8_t scroll_row;          // scroll row position
uint8_t cursor_real_pos;     // cursor real position on lcd lines (0 - _LCDML_DISP_rows - 1)
uint8_t cursor_position_cur; // cursor position to file list entry

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
		allarm.lcd.setCursor(1, n - scroll_row);
		// set content
		allarm.lcd.setCursor(1, n - scroll_row);
		allarm.lcd.print(sensore[n].getMessaggio());
		allarm.lcd.setCursor(_LCDML_DISP_cols-3, n - scroll_row);

		switch(sensore[n].getStato())
		{
		case sensDisabilitato:
			allarm.lcd.print(F("D"));
			break;
		case sensTempDisabilitato:
			allarm.lcd.print(F("T"));
			break;
		case sensAttivo:
			allarm.lcd.print(F("A"));
			break;
		}
	}
	// set cursor and scrollbar
	// =============================
	for (uint8_t n = scroll_row; n < (scroll_row + _LCDML_DISP_rows); n++) {
		allarm.lcd.setCursor(0, n - scroll_row);

		// set cursor
		// =====================
		if (n == cursor_position_cur) {
			allarm.lcd.write(_LCDML_DISP_cfg_cursor);
			cursor_real_pos = n - scroll_row;
		} else {
			allarm.lcd.write(' ');
		}

		// display scrollbar
		// ==============================
		// delete or reset scrollbar
		if (scrollbar_max > n_max) {
			allarm.lcd.setCursor((_LCDML_DISP_cols - 1), n - scroll_row);
			allarm.lcd.write((uint8_t) 0);
		} else {
			allarm.lcd.setCursor((_LCDML_DISP_cols - 1), n - scroll_row);
			allarm.lcd.print(' ');
		}

		// set scrollbar
		if (scrollbar_max > n_max) {
			//set scroll position
			if (cursor_position_cur == scrollbar_min) {
				// min pos
				allarm.lcd.setCursor((_LCDML_DISP_cols - 1), 0);
				allarm.lcd.write((uint8_t) 1);
			} else if (cursor_position_cur == (scrollbar_max - 1)) {
				// max pos
				allarm.lcd.setCursor((_LCDML_DISP_cols - 1), (n_max - 1));
				allarm.lcd.write((uint8_t) 4);
			} else {
				// between
				allarm.lcd.setCursor((_LCDML_DISP_cols - 1), scroll_pos / n_max);
				allarm.lcd.write((uint8_t) (scroll_pos % n_max) + 1);
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
			//LCDML_DISP_funcend();
			// output of current line
			//Serial.println(sensore[cursor_position_cur].getMessaggio());
			sensore[cursor_position_cur].setStato( (sensore[cursor_position_cur].getStato()==sensAttivo?sensDisabilitato:sensAttivo) );
			bitWrite(settings.sens, cursor_position_cur, (sensore[cursor_position_cur].getStato()==sensAttivo?1:0) );
			//Serial.println(settings.sens);
		}
		// clear display
		allarm.lcd.clear();
		mngSensori();
	}
}

void LCDML_DISP_loop_end(mnuSensori) {

}

const String tipoAttivazione[3]={TXT_TOTALE, TXT_PERIMETRALE, TXT_INTERNO };

void mngTipoAttivazione(){
	// loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
	// the quit button works in every DISP function without any checks; it starts the loop_end function

	// init some vars for scrollbar
	uint8_t n_max = (3 >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (3);

	uint8_t scrollbar_min = 0;
	uint8_t scrollbar_max = 3;
	//uint8_t scrollbar_cur_pos = cursor_position_cur;
	uint8_t scroll_pos = ((1. * n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * cursor_position_cur);

	// display content
	// ==================
	for (uint8_t n = scroll_row; n < (scroll_row + _LCDML_DISP_rows)-1; n++) {
		// set cursor
		//lcd.setCursor(1, n - scroll_row);
		// set content
		allarm.lcd.setCursor(1, n - scroll_row);
		allarm.lcd.print(tipoAttivazione[n]);
		allarm.lcd.setCursor(_LCDML_DISP_cols-3, n - scroll_row);

		if (n==settings.zona) allarm.lcd.print(F("*"));
		else allarm.lcd.print( TXT_SPAZIO );
	}
	// set cursor and scrollbar
	// =============================
	for (uint8_t n = scroll_row; n < (scroll_row + _LCDML_DISP_rows); n++) {
		allarm.lcd.setCursor(0, n - scroll_row);

		// set cursor
		// =====================
		if (n == cursor_position_cur) {
			allarm.lcd.write(_LCDML_DISP_cfg_cursor);
			cursor_real_pos = n - scroll_row;
		} else {
			//lcd.write(' ');
			allarm.lcd.print( TXT_SPAZIO );
		}

		// display scrollbar
		// ==============================
		// delete or reset scrollbar
		if (scrollbar_max > n_max) {
			allarm.lcd.setCursor((_LCDML_DISP_cols - 1), n - scroll_row);
			allarm.lcd.write((uint8_t) 0);
		} else {
			allarm.lcd.setCursor((_LCDML_DISP_cols - 1), n - scroll_row);
			allarm.lcd.print(TXT_SPAZIO);
		}

		// set scrollbar
		if (scrollbar_max > n_max) {
			//set scroll position
			if (cursor_position_cur == scrollbar_min) {
				// min pos
				allarm.lcd.setCursor((_LCDML_DISP_cols - 1), 0);
				allarm.lcd.write((uint8_t) 1);
			} else if (cursor_position_cur == (scrollbar_max - 1)) {
				// max pos
				allarm.lcd.setCursor((_LCDML_DISP_cols - 1), (n_max - 1));
				allarm.lcd.write((uint8_t) 4);
			} else {
				// between
				allarm.lcd.setCursor((_LCDML_DISP_cols - 1), scroll_pos / n_max);
				allarm.lcd.write((uint8_t) (scroll_pos % n_max) + 1);
			}
		}
	}
}

void LCDML_DISP_setup(mnuTipoAttivazione) {
	// use this to init some vars
	// set max file counter
	//current_max_list_count = 8;
	// set current cursor position
	cursor_position_cur = 0;
	scroll_row = 0;
	cursor_real_pos = 0;
	mngTipoAttivazione();
}

void LCDML_DISP_loop(mnuTipoAttivazione) {

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
			if (cursor_position_cur < (3 - 1)) {    // check list end
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
			settings.zona=cursor_position_cur;
		}
		// clear display
		allarm.lcd.clear();
		mngTipoAttivazione();
	}
}

void LCDML_DISP_loop_end(mnuTipoAttivazione) {

}


void mngCambioDataOra(uint8_t par){
  allarm.lcd.setCursor(0, 0);
  switch(par)
  {
    case 1:
      allarm.lcd.print(TXT_DATA);
      strcpy(newTxtVal3,"__/__/____");
      break;
    case 2:
      allarm.lcd.print(TXT_ORA);
      break;
    /*case 3:
      lcd.print(TXT_PASSWORD2);
      break;*/
  }
  allarm.lcd.setCursor(0, 1);
  allarm.lcd.blink();

  allarm.lcd.setCursor(1, 1);
  allarm.lcd.print(newTxtVal3);
  allarm.lcd.setCursor(1, 1);
  /*if (par ==3 or par == 4 or par==5)
    lcd.print(TXT_CONFERMA);
  else*/

}
// *********************************************************************
void LCDML_DISP_setup(mnuCambioDataOra)
// *********************************************************************
{
  param = LCDML_DISP_getParameter();
  switch (param) {
  case 1:
    allarm.lcd.print(TXT_DATA);
    break;
  case 2:
    allarm.lcd.print(TXT_ORA);
    break;
  /*case 3:
    lcd.print(TXT_PASSWORD2);
    break;*/
  }
  mngCambioDataOra(param);
  //LCDML_DISP_funcend();
}

void LCDML_DISP_loop(mnuCambioDataOra) {  // loop
  //if (LCDML_BUTTON_checkAny())
  if (LCDML_BUTTON_checkEnter()) {
    switch (param) {
    case 1:
      //strcpy(settings.menuPassword, newTxtVal);
      break;
    case 2:
      //strcpy(settings.alarmPassword1, newTxtVal);
      break;
    case 3:
      //strcpy(settings.alarmPassword2, newTxtVal);
      break;
    }
    LCDML_DISP_funcend();
  }
  allarm.lcd.clear();
  mngCambioDataOra(param);
}

void LCDML_DISP_loop_end(mnuCambioDataOra) {  // loop end
  allarm.lcd.noBlink();
  //param=0;
  //indNewTxtVal=0;
  //memset(newTxtVal,0,sizeof(newTxtVal));
}
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

