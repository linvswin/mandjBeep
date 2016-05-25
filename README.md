#### Working in progress !!!
# mandjBeep
## Cosa &egrave;? 
Centralina di allarme modulare pilotata da un atmega1284. 
### Storia
Il progetto &egrave; nato dall'esigenza di in stallare un sistema di allarme in casa. La prima bozza prevedeva l'uso di un atmega328, ma poi con crescere delle
funzionalit&agrave;, sono stato costretto a trovare un microcontrollore con un po di memoria in pi&ugrave;. La scelta &egrave; ricaduta su un atmega1284. Di seguito un comparazione 
tra i microcontrollori pi&ugrave; diffusi (Arduino like) 

<table>
	<tr><th>Feature</th><th>328P</th><th>1284P</th><th>2560P</th></tr>
	<tr><td>Price</td><td>$2.99</td><td>$4.66</td><td>$11.28</td></tr>
	<tr><td>RAM</td><td>2k</td><td>16k</td><td>8k</td></tr>
	<tr><td>Flash</td><td>32k</td><td>128k</td><td>256k</td></tr>
	<tr><td>EEPROM</td><td>1k</td><td>4k</td><td>4k</td></tr>
	<tr><td>UART</td><td>1</td><td>2</td><td>4</td></tr>
	<tr><td>IO Pins</td><td>23</td><td>32</td><td>86</td></tr>
	<tr><td>Interrupts</td><td>2</td><td>3</td><td>8</td></tr>
	<tr><td>Analog Inputs</td><td>6</td><td>8</td><td>16</td></tr>
</table>

### Caratteristiche:

* RTC: modulo DS3231 per la gestione del tempo
* LCD 20x4 per impostazioni/visualizzazione stato, etc (collegato ad un PCF8574 che lo rende I2C)
* tastierino 4x4 (tastierino a membrana classico x arduino collegato ad un PCF8574 che lo rende I2C)
* 2 zone (da implementare)
* avviso tramite modulo GSM (al momento solo tramite sms)
* relay per attivizione sirena.
* batteria tampone al piombo 12v 7A
 
##  Author

 * M&J 
 * Sito: [siatienfalla](http://siatienfalla.altervista.org/)
 * Data inizio: 09/02/2016
 * Versione: 1.0
 
## Licence: GPL ver. 3
## Immagini
![Allarme](img/allarme.jpg)
