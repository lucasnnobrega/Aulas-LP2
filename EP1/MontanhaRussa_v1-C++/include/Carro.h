/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_

#include "Thread.h"

class Parque;

class Carro: public Thread {
public:
	static const int CAPACIDADE;
	static int numPassageiros;

	Carro(Parque *p);
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();

	void run();
private:
	int voltas;
	Parque *parque;
};

#endif /* CARRO_H_ */
