# mandjBeep
## Cosa &egrave;? 
Centralina di allarme modulare pilotata da un atmega1284. 
### Storia
Il progetto &egrave; nato dall'esigenza di in stallare un sistema di allarme in casa. La prima bozza prevedeva l'uso di un atmega328, ma poi con crescere delle
funzionalit&agrave;, sono stato costretto a trovare un microcontrollore con un po di memoria in pi&ugrave;. La scelta &egrave; ricaduta su un atmega1284. Di seguito un comparazione 
tra i microcontrollori pi&ugrave; diffusi (Arduino like) 


### Caratteristiche:

* RTC: modulo DS3231 per la gestione del tempo
* LCD 20x4 per impostazioni/visualizzazione stato, etc (collegato ad un PCF8574 che lo rende I2C)
* tastierino 4x4 (tastierino a membrana classico x arduino collegato ad un PCF8574 che lo rende I2C)
* 2 zone (da implementare)
* avviso tramite modulo GSM (al momento solo tramite sms)
 
##  Author: M&J - [siatienfalla](http://siatienfalla.altervista.org/)
 * M&J - 
 * Sito: [siatienfalla](http://siatienfalla.altervista.org/)
 * Data inizio: 09/02/2016
 * Versione: 1.0
 
## Licence: GPL ver 3
