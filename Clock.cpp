#include "Clock.h"

void Clock::inizializza() {
  RTC.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  if (!RTC.IsDateTimeValid()) {
    RTC.SetDateTime(compiled);
  }

  now = RTC.GetDateTime();
  if (now < compiled) {
#ifdef DEBUG
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
#endif
    RTC.SetDateTime(compiled);
  } else if (now > compiled) {
#ifdef DEBUG
    Serial.println("RTC is newer than compile time. (this is expected)");
#endif
  } else if (now == compiled) {
#ifdef DEBUG
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
#endif
  }
  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  RTC.Enable32kHzPin(false);
  RTC.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}

String Clock::getDate() {
  now = RTC.GetDateTime();
  String txt = "";

  txt += printDigit(now.Hour()) + F(":");
  txt += printDigit(now.Minute()); // + F(":");
  //txt += printDigit(now.Second());
  txt += TXT_SPAZIO;
  txt += printDigit(now.Day()) + F("/");
  txt += printDigit(now.Month()) + F("/");
  txt += printDigit(now.Year());

  return txt;
}

String Clock::printDigit(int digits) {
	String temp = "";
	if (digits < 10)
		temp += "0";
	temp += digits;
	return temp;
}



// void MandJBeep::inizializzaClock() {
//   //Adding time
// #ifndef CLKDS3231
//   RTC.begin();
//   //togli il commento per aggiornare l'ora con il pc, upload, poi disattivalo subito dopo
//   //RTC.adjust(DateTime(__DATE__, __TIME__));
// #else
//   RTC.Begin();
//   RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
//   if (!RTC.IsDateTimeValid())
//     RTC.SetDateTime(compiled);
// #endif

// #ifdef DEBUG
// #ifndef CLKDS3231
//   if (!RTC.isrunning())
// #else
//   if (!RTC.GetIsRunning())
// #endif
//     Serial.println(F("RTC NOT run"));
//   else
//     Serial.println(F("RTC run"));
// #endif

// #ifdef CLKDS3231
//   now = RTC.GetDateTime();
//   if (now < compiled) {
//     Serial.println("RTC is older than compile time!  (Updating DateTime)");
//     RTC.SetDateTime(compiled);
//   } else if (now > compiled) {
//     Serial.println("RTC is newer than compile time. (this is expected)");
//   } else if (now == compiled) {
//     Serial.println(
//       "RTC is the same as compile time! (not expected but all is fine)");
//   }
//   // never assume the Rtc was last configured by you, so
//   // just clear them to your needed state
//   RTC.Enable32kHzPin(false);
//   RTC.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
// #endif
// }