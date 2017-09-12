/*
* Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "./include/Parque.h"

Carro::Carro(int capacidade_, Parque* parque_,int* turns_)  : parque(parque_), capacidade(capacidade_){
	numPassageiros.store(0);
	turns = turns_;
	cheio = false;
	voltaAcabou = true;
}

Carro::~Carro() {
	if(thr != nullptr)
		if(thr->joinable())
				thr->join();
}

std::atomic<int>* Carro::getNumPassageiros(){
	return &numPassageiros;
}

int* Carro::getTurnsPtr(){
	return turns;
}

Parque* Carro::getParquePtr(){
	return parque;
}

std::thread*& Carro::getThreadPtr(){
	return thr;
}

void Carro::esperaEncher() {
	std::cout << "Esperando encher" << std::endl;
	while(!cheio){
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	std::cout << "Carro está cheio" << std::endl;
}

void Carro::daUmaVolta() {
	voltaAcabou = false;

	if(voltas > NUMERO_DE_VOLTAS) throw Done();

	std::cout << "Iniciando uma volta" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	voltas++;
	std::cout << "A volta acabou" << std::endl;

	voltaAcabou = true;
}

void Carro::esperaEsvaziar() {
	//Sincronização aqui foi implementada com test_and_set
	std::cout << "Esperando esvaziar" << std::endl;
	//Await sequido de instrucao 
	lock(parque->parqueSharedLock); //CSEnter
	while (numPassageiros.load() != 0) {
			unlock(parque->parqueSharedLock); //CSExit
			std::this_thread::sleep_for(std::chrono::milliseconds(30)); //Delay
			lock(parque->parqueSharedLock); //CSEnter
	}
	voltaAcabou = true;
	unlock(parque->parqueSharedLock); //CSExit

	std::cout << "O carro ja esvaziou" << std::endl;
}

int Carro::getNVoltas() {
	return voltas;
}

int Carro::getCapacidade(){
	return capacidade;
}

void Carro::run() {
	thr = new std::thread([&](){
	while (voltas < NUMERO_DE_VOLTAS) {
		esperaEncher();
		daUmaVolta();
		esperaEsvaziar();
	}});
}
