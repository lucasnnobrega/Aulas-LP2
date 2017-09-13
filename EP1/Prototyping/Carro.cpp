/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"
#include "include/helper.h"
#include <iostream>
using namespace std::chrono_literals;
using namespace Helpers;

Carro::Carro(Parque *p, int capacidade_) {
	capacidade = capacidade_;
	turns = p->getTurnsPtr();
	parque = p;
	cheio = false;
	voltaAcabou = false;
	saindo = false;
}

Carro::~Carro() {

}

void Carro::join(){
	if(t.joinable())
		t.join();
}

void Carro::esperaEncher() {
	std::cout << "Esperando encher" << std::endl;
//	lock(parque->sharedLock);
	voltaAcabou = false;
	saindo = false;
	while (!cheio){
//		unlock(parque->sharedLock);
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
//		lock(parque->sharedLock);
	}
//	aberto = false;
//	cheio = true;
//	unlock(parque->sharedLock);
	std::cout << "Cheio" << std::endl;

}

void Carro::daUmaVolta() {
	//Dorme por um tempo fixo
	
	voltaAcabou = false;
	std::this_thread::sleep_for(std::chrono::milliseconds(DURACAO_DA_VOLTA));
	 voltaAcabou = true;

	std::cout << "Iniciando uma volta" << std::endl;
//	lock(parque->sharedLock);
//	aberto = true;
//	unlock(parque->sharedLock);
}

void Carro::esperaEsvaziar() {
//	aberto = false;
	saindo = true;
	std::cout << "Esperando esvaziar" << std::endl;

//	lock(parque->sharedLock);
	while( cheio  ){
//		unlock(parque->sharedLock);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
//		lock(parque->sharedLock);
	}
//	aberto = true;
//	unlock(parque->sharedLock);

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
