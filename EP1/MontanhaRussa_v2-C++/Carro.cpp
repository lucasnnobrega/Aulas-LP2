/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"

const int Carro::CAPACIDADE = 5;
int Carro::numPassageiros = 0;

Carro::Carro(Parque *p) {
	this->parque = p;
	this->voltas = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	//while (Carro::numPassageiros < Carro::CAPACIDADE) { delay; }
	/* Deve ficar no while até encher
	 Join nas threads que entraram no carrinho
	*/
}

void Carro::daUmaVolta() {
	/*Dorme por um tempo fixo
	1 - todas tem que dormir?
	Como Fazer isso?
		1- Colocando A thread principal (carro) para dormir
		controlará todas os passageiros(Threads com Join)
		2- Mandando todas as threads (passageiros) dormir 
		por um tempo determinado (Tempo deslocado)

	*/
	// voltaAcabou = true
}

void Carro::esperaEsvaziar() {
	//while (Carro::numPassageiros > 0) { delay; }
	/*





	*/
}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::run() {
	while (Parque::numPessoas > 0) {
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

		voltas++;
	}
}
