/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"
#include <iostream>

Carro::Carro(Parque *p, int capacidade_) {
	capacidade = capacidade_;
	turns = p->getTurnsPtr();
	parque = p;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	std::cout << "Esperando encher" << std::endl;
	aberto = true;
	while (!cheio) { asm(""); }
	std::cout << "Cheio" << std::endl;
}

void Carro::daUmaVolta() {
	//Dorme por um tempo fixo
	std::cout << "Iniciando uma volta" << std::endl;
	aberto = false;
	std::this_thread::sleep_for(std::chrono::milliseconds(DURACAO_DA_VOLTA));
	aberto = true;
}

void Carro::esperaEsvaziar() {
	std::cout << "Esperando esvaziar" << std::endl;
	while (Carro::numPassageiros > 0) { asm(""); }
	cheio = false;
	std::cout << "Carro vazio" << std::endl;
	
}

int Carro::getNVoltas() {
	return voltas;
}

Parque* Carro::getParquePtr(){
	return parque;
}

void Carro::run() {
	t = std::move(std::thread([this](){
		while (parque->getNumPessoas() > 0) {
			esperaEncher();
			daUmaVolta();
			esperaEsvaziar();
			voltas++;
		}
	}));
}
