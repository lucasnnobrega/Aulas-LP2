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
	aberto = false;
}

Carro::~Carro() {

}

void Carro::join(){
	if(t.joinable())
		t.join();
}

void Carro::esperaEncher() {
	std::cout << "Esperando encher" << std::endl;
	while (numPassageiros <= capacidade){

	}
	std::cout << "Cheio" << std::endl;
}

Carro::cheio(){
	return numPassageiros == capacidade;
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

	while(numPassageiros > 0){
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

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
