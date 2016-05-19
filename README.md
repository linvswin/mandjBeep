# mandjBeep
## Cosa è 
Centralina di allarme modulare pilotata da un atmega1284. 
### Storia
Il progetto è nato dall'esigenza di in stallare un sistema di allarme in casa. La prima bozza prevedeva l'uso di un atmega328, ma poi con crescere delle
funzionalità, sono stato costretto a trovare un microcontrollore con un po di memoria in più. La scelta è ricaduta su un atmega1284. Di seguito un comparazione 
tra i microcontrollori più diffusi (Arduino like) 

> Feature:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**328P**&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**1284P**&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**2560P**<br>
> Price:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; $2.99 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; $4.66 &nbsp;&nbsp;&nbsp;  $11.28<br>
> RAM:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2k &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 16k &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 8k<br>
> Flash:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 32k &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 128k &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 256k<br>
> EEPROM:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 1k &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 4k &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 4k<br>
> UART:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 1 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 2 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 4<br>
> IO Pins:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 23 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 32 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 86<br>
> Interrupts:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 2 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 3 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 8<br>
> Analog Inputs:&nbsp;&nbsp;&nbsp; 6 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 8 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 16<br>

### Caratteristiche:

* RTC: modulo DS3231 per la gestione del tempo
* LCD 20x4 per impostazioni/visualizzazione stato, etc (collegato ad un PCF8574 che lo rende I2C)
* tastierino 4x4 (tastierino a membrana classico x arduino collegato ad un PCF8574 che lo rende I2C)
* 2 zone (da implementare)
* avviso tramite modulo GSM (al momento solo tramite sms)
 
##  Author: M&J - (http://siatienfalla.altervista.org/)

 * Started Date: 09/02/2016
 * Version: 1.0
 
## Licence: GPL ver 3
