# mandjBeep
## Cosa è 
Centralina di allarme modulare pilotata da un atmega1284. 
### Storia
Il progetto è nato dall'esigenza di in stallare un sistema di allarme in casa. La prima bozza prevedeva l'uso di un atmega328, ma poi con crescere delle
funzionalità, sono stato costretto a trovare un microcontrollore con un po di memoria in più. La scelta è ricaduta su un atmega1284. Di seguito un comparazione 
tra i microcontrollori più diffusi (Arduino like) 

Feature          328P    1284P   2560P
Price	        $2.99    $4.66  $11.28
RAM	               2k	   16k      8k
Flash	          32k     128k	  256k
EEPROM	           1k    	4k   	4k
UART	            1   	 2	     4
IO Pins	           23       32      86
Interrupts          2        3       8
Analog Inputs       6        8      16

### Caratteristiche:

* RTC: modulo DS3231 per la gestione del tempo
* LCD 20x4 per impostazioni/visualizzazione stato, etc (collegato ad un PCF8574 che lo rende I2C)
* tastierino 4x4 (tastierino a membrana classico x arduino collegato ad un PCF8574 che lo rende I2C)
* 2 zone (da implementare)
* avviso tramite modulo GSM (al momento solo tramite sms)
 
##  Author: M&J - http://siatienfalla.altervista.org/

 * Started Date: 09/02/2016
 * Version: 1.0
 
## Licence: GPL ver 3
