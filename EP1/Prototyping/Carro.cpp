/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"
#include <iostream>
using namespace std::chrono_literals;

Carro::Carro(Parque *p, int capacidade_) {
	capacidade = capacidade_;
	turns = p->getTurnsPtr();
	parque = p;
	cheio = false;
	aberto = true;
}

Carro::~Carro() {

}

void Carro::join(){
	if(t.joinable())
		t.join();
}

void Carro::esperaEncher() {
	//TODO FIX POSSIBLE RACE
	std::cout << "Esperando encher" << std::endl;
//	lock(parque->sharedLock);
	while (numPassageiros < capacidade){
//		unlock(parque->sharedLock);
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
//		lock(parque->sharedLock);
	}
	cheio = true;
//	unlock(parque->sharedLock);
	std::cout << "Cheio" << std::endl;
}

void Carro::daUmaVolta() {
	//Dorme por um tempo fixo
	std::cout << "Iniciando uma volta" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(DURACAO_DA_VOLTA));
	aberto = false;
}

void Carro::esperaEsvaziar() {
	std::cout << "Esperando esvaziar" << std::endl;

	//lock(parque->sharedLock);
	while(numPassageirosAux == capacidade){
		//unlock(parque->sharedLock);
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		//lock(parque->sharedLock);
	}

	aberto = true;
	vazio = true;
	numPassageiros.store(0);
	//unlock(parque->sharedLock);

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
		while (parque->getNumPessoas() >= 0) {
			esperaEncher();
			daUmaVolta();
			esperaEsvaziar();
			voltas++;
		}
	}));
}
