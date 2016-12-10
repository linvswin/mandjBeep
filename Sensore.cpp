/*
 * Sensore.cpp
 *
 *  Created on: 26 apr 2016
 *      Author: peppe
 */

#include "Sensore.h"

Sensore::Sensore(int p, tipoSensore tipo, byte logica, const String msg, znZone zona=znPerimetrale, boolean rit=false){
		this->pin=p;
		this->tipo=tipo;
		this->stato=sensAttivo;
		this->logica=logica;
		this->messaggio=msg;
		this->conta=0;
		this->ritardato=rit;
		this->zona=zona;
	};

Sensore::~Sensore() {
	// TODO Auto-generated destructor stub
}

