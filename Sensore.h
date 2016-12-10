/*
 * Sensore.h
 *
 *  Created on: 26 apr 2016
 *      Author: peppe
 */

#ifndef SENSORE_H_
#define SENSORE_H_
#include "Arduino.h"

enum znZone {znTotale, znPerimetrale, znInterno};
enum statoSensore {sensNonAttivo, sensAttivo, sensDisabilitato, sensTempDisabilitato, sensTrigged, sensMalfunzionamento};
enum tipoSensore {tpReed, tpPIR, tpSirena, tpTamper};

class Sensore{
protected:
	uint8_t pin;
	tipoSensore tipo;
	statoSensore stato;
	byte logica;
	String messaggio;
	uint8_t conta;
	boolean ritardato;
	znZone zona;

public:
	Sensore(int p, tipoSensore tipo, byte logica, const String msg, znZone zona, boolean rit);
	virtual ~Sensore();

	uint8_t getPin(){return this->pin;};
	void setPin(uint8_t p){this->pin=p;};

	tipoSensore getTipo(){return this->tipo;};
	void setTipo(tipoSensore tipo){this->tipo=tipo;};

	statoSensore getStato(){return this->stato;};
	void setStato(statoSensore a){this->stato=a;};

	byte getLogica(){return this->logica;};
	void setLogica(byte logica){this->logica=logica;};

	String getMessaggio(){return this->messaggio;};
	void setMessaggio(String m){this->messaggio=m;};

	uint8_t getConta(){return this->conta;};
	void setConta(uint8_t conta){this->conta=conta;};

	boolean getRitardato(){return this->ritardato;};
	void setRitardato(boolean m){this->ritardato=m;};

	znZone getZona(){return this->zona;};
	void setZona(znZone z){this->zona=z;};
};

#endif /* SENSORE_H_ */
